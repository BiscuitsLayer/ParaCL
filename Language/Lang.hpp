#pragma once

//  SYSTEM
#include <cmath>
#include <vector>
#include <variant>
#include <unordered_map>
#include <exception>

//  INTERFACE
#include "LangInterface.hpp"

extern ScopeNodeInterface* globalCurrentScope;

class VariableSymTable final {
    private:
        std::unordered_map <std::string, NumberType> data_ {};
    public:
        //  METHODS
        bool GetVariableValue (const std::string& name, NumberType& value) const;
        bool SetVariableValue (const std::string& name, NumberType value);
        bool AddVariable (const std::string& name, NumberType value);

        //  CTOR
        VariableSymTable ():
            data_ ({})
            {}

        //  DTOR
        ~VariableSymTable () = default;
};

class FunctionSymTable final {
    private:
        std::unordered_map <std::string, ScopeNodeInterface*> namedData_ {};
        std::vector <ScopeNodeInterface*> unnamedData_ {};
    public:
        //  POISON IDX
        static const int poisonFunctionIdx = -1;

        //  METHODS
        bool ExecuteFunction (const std::variant <int, std::string>& id, NumberType& result) const {
            try {
                auto search = namedData_.find (std::get <std::string> (id));
                if (search == namedData_.end ()) {
                    return false;
                }
                else {
                    result = search->second->Execute ();
                    return true;
                }
            }
            catch (const std::bad_variant_access&) {
                if (unnamedData_.size () <= std::get <int> (id)) {
                    return false;
                }
                else {
                    result = unnamedData_[std::get <int> (id)]->Execute ();
                    return true;
                }
            }
        }
        bool SetFunction (std::variant <int, std::string>& id, ScopeNodeInterface* scope) {
            try {
                auto search = namedData_.find (std::get <std::string> (id));
                if (search == namedData_.end ()) {
                    return false;
                }
                else {
                    namedData_[std::get <std::string> (id)] = scope;
                    return true;
                }
            }
            catch (const std::bad_variant_access&) {
                unnamedData_[std::get <int> (id)] = scope;
                return true;
            }
        }
        bool AddFunction (std::variant <int, std::string>& id, ScopeNodeInterface* scope) {
            try {
                auto search = namedData_.find (std::get <std::string> (id));
                if (search != namedData_.end ()) {
                    return false;
                }
                else {
                    namedData_[std::get <std::string> (id)] = scope;
                    return true;
                }
            }
            catch (const std::bad_variant_access&) {
                static int unnamedIdx = 0;
                id = unnamedIdx++;
                unnamedData_.push_back (scope);
                return true;
            }
        }

        //  CTOR
        FunctionSymTable ():
            namedData_ ({}),
            unnamedData_ ({})
            {}

        //  DTOR
        ~FunctionSymTable () {
            for (auto nameToScope : namedData_) {
                delete nameToScope.second;
            }
            for (auto scope : unnamedData_) {
                delete scope;
            }
        }
};

extern FunctionSymTable* globalFunctionSymTable;

class FunctionVariableSymTable final {
    private:
        std::unordered_map <std::string, std::variant <int, std::string>> data_ {};
    public:
        //  METHODS
        bool ExecuteFunctionVariable (const std::string& variableName, NumberType& value) const {
            auto search = data_.find (variableName);
            if (search == data_.end ()) {
                return false;
            }
            else {
                globalFunctionSymTable->ExecuteFunction (search->second, value);
                return true;
            }
        }
        bool SetFunctionVariable (const std::string& variableName, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") {
            auto search = data_.find (variableName);
            if (search == data_.end ()) {
                return false;
            }
            else {
                std::variant <int, std::string> ans {};
                if (hasFunctionName) {
                    ans = functionName;
                }
                else {
                    ans = FunctionSymTable::poisonFunctionIdx;
                }
                globalFunctionSymTable->SetFunction (ans, scope);
                search->second = ans;
                return true;
            }
        }
        bool AddFunctionVariable (const std::string& variableName, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") {
            auto search = data_.find (variableName);
            if (search != data_.end ()) {
                return false;
            }
            else {
                std::variant <int, std::string> ans {};
                if (hasFunctionName) {
                    ans = functionName;
                }
                else {
                    ans = FunctionSymTable::poisonFunctionIdx;
                }
                globalFunctionSymTable->AddFunction (ans, scope);
                data_[variableName] = ans;
                return true;
            }
        }

        //  CTOR
        FunctionVariableSymTable ():
            data_ ({})
            {}

        //  DTOR
        ~FunctionVariableSymTable () = default;
};

class ReturnNode final : public NodeInterface {
    private:
        NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override {
            //  FIXME
            // NumberType returnValue = child_->Execute ();
            // now skip, later we will throw exception and do return in ScopeNode::Execute ();
            return child_->Execute ();
        }
        void Dump (std::ostream &stream) const override { stream << "return "; child_->Dump (stream); }

        //  CTOR
        ReturnNode (NodeInterface* child):
            NodeInterface (NodeType::PRINT),
            child_ (child)
            {}

        //  DTOR
        ~ReturnNode () { delete child_; }
};

class ScopeNode final : public ScopeNodeInterface {
    private:
        std::vector <NodeInterface*> branches_ {};
        VariableSymTable variableTable_ {};
        FunctionVariableSymTable functionVariableTable_ {};
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override { stream << "{ ... }"; }   

        //  METHODS FROM SCOPE INTERFACE
        void AddNode (NodeInterface* node) override { branches_.push_back (node); }
        NumberType GetVariable (const std::string& name) const override;
        void SetVariable (const std::string& name, NumberType value) override;
        NumberType GetFunctionVariable (const std::string& variableName) const override {
            const ScopeNode* cur = this;
            NumberType value = 0;
            while (!cur->functionVariableTable_.ExecuteFunctionVariable (variableName, value)) {
                if (cur->previous_) {
                    cur = static_cast <ScopeNode*> (cur->previous_);
                }
                else {
                    throw std::invalid_argument ("Wrong name of function variable!");
                }
            }
            return value;
        }
        void SetFunctionVariable (const std::string& variableName, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") override {
            ScopeNode* cur = this;
            while (!cur->functionVariableTable_.SetFunctionVariable (variableName, scope, hasFunctionName, functionName)) {
                if (cur->previous_) {
                    cur = static_cast <ScopeNode*> (cur->previous_);
                }
                else {
                    functionVariableTable_.AddFunctionVariable (variableName, scope, hasFunctionName, functionName);
                    break;
                }
            }
        }
        void Entry () const override    { globalCurrentScope = next_; }
        void Return () const override   { globalCurrentScope = globalCurrentScope->previous_; }

        //  CTOR
        ScopeNode (ScopeNodeInterface* previous, ScopeNodeInterface* next):
            ScopeNodeInterface (previous, next),
            branches_ ({}),
            variableTable_ ({}),
            functionVariableTable_ ({})
            {}

        //  DTOR
        ~ScopeNode () {
            for (auto branch : branches_) {
                delete branch;
            }
        }
};

class ValueNode final : public NodeInterface {
    private:
        NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { return value_; }
        void Dump (std::ostream &stream) const override { stream << value_; }

        //  CTOR
        ValueNode (NumberType value):
            NodeInterface (NodeType::VALUE),
            value_ (value)
            {}

        //  DTOR
        ~ValueNode () = default;
};

class VariableNode final : public NodeInterface {
    private:
        std::string name_ {};

        //  mutable because it only changes the way this node dumps
        mutable NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { value_ = globalCurrentScope->GetVariable (name_); return value_; }
        void Dump (std::ostream &stream) const override { stream << name_ << " {" << value_ << "}"; }

        //  EXTRA METHOD
        void Assign (NumberType value) { value_ = value; globalCurrentScope->SetVariable (name_, value); }

        //  CTOR
        VariableNode (const std::string& name):
            NodeInterface (NodeType::VARIABLE),
            name_ (name),
            value_ (0)
            {}

        //  DTOR
        ~VariableNode () = default;
};

class FunctionVariableNode final : public NodeInterface {
    private:
        std::string variableName_ {};

        //  mutable because it only changes the way this node dumps
        mutable NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { value_ = globalCurrentScope->GetFunctionVariable (variableName_); return value_; }
        void Dump (std::ostream &stream) const override { stream << variableName_ << "() {" << value_ << "}"; }

        //  EXTRA METHOD
        void Assign (ScopeNodeInterface* scope) { globalCurrentScope->SetFunctionVariable (variableName_, scope);
        //  I don't really know if we need other params there (hasName, functionName) or not, so test it (I think that we dont))
        //  FIXME
        }

        //  CTOR
        FunctionVariableNode (const std::string& variableName, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = ""):
            //  FIXME find out params that we really need in ctor
            NodeInterface (NodeType::FUNCTION_VARIABLE),
            variableName_ (variableName),
            value_ (0)
            {}

        //  DTOR
        ~FunctionVariableNode () = default;
};

class BinaryOpNode final : public NodeInterface {
    private:
        NodeInterface* leftChild_ = nullptr;
        NodeInterface* rightChild_ = nullptr;

        //  mutable because it only changes the way this node dumps
        mutable bool isRed_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  CTOR
        BinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild):
            NodeInterface (type),
            leftChild_ (leftChild),
            rightChild_ (rightChild)
            {}
        
        //  DTOR
        ~BinaryOpNode () { delete leftChild_; delete rightChild_; }
};

class IfNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       ScopeNodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override {
            stream << "if ";
            condition_->Dump (stream);
            stream << " ";
            scope_->Dump (stream);
        }

        //  CTOR
        IfNode (NodeInterface* condition, ScopeNodeInterface* scope):
            NodeInterface (NodeType::IF),
            condition_ (condition),
            scope_ (scope)
            {}

        //  DTOR
        ~IfNode () { delete condition_; delete scope_; }
};

class WhileNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       ScopeNodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override {
            stream << "while ";
            condition_->Dump (stream);
            stream << " ";
            scope_->Dump (stream);
        }

        //  CTOR
        WhileNode (NodeInterface* condition, ScopeNodeInterface* scope):
            NodeInterface (NodeType::WHILE),
            condition_ (condition),
            scope_ (scope)
            {}

        //  DTOR
        ~WhileNode () { delete condition_; delete scope_; }
};

class ScanNode final : public NodeInterface {
    private:
        // mutable because they only change the way this node dumps
        mutable NumberType value_ = 0;
        mutable bool isScanned_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override {
            if (isScanned_) {
                stream << "{" << value_ << "}";
            }
            else {
                stream << "{not scanned}";
            }
        }

        //  CTOR
        ScanNode ():
            NodeInterface (NodeType::SCAN),
            value_ (0),
            isScanned_ (false)
            {}

        //  DTOR
        ~ScanNode () = default;
};

class PrintNode final : public NodeInterface {
    private:
        NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override { stream << "print "; child_->Dump (stream); }

        //  CTOR
        PrintNode (NodeInterface* child):
            NodeInterface (NodeType::PRINT),
            child_ (child)
            {}

        //  DTOR
        ~PrintNode () { delete child_; }
};