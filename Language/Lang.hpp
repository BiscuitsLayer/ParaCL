#pragma once

//  SYSTEM
#include <cmath>
#include <vector>
#include <variant>
#include <map>
#include <exception>

//  INTERFACE
#include "LangInterface.hpp"

extern ScopeNodeInterface* globalCurrentScope;
const int poisonFunctionIdx = -1;

using PairIS = std::pair <int, std::string>;
using VariantIS = std::variant <int, std::string>;

template <typename T, typename U>
using VectorOfPair = std::vector <std::pair <T, U>>;

class VariableSymTable final {
    private:
        std::map <std::string, NumberType> data_ {};
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
        std::map <PairIS, ScopeNodeInterface*> namedData_ {};
        // first idx = id, second idx = arguments count
        VectorOfPair <int, ScopeNodeInterface*> unnamedData_ {};
    public:
        //  METHODS
        bool GetFunction (const std::string& functionName, int argumentsCount) const {
            auto search = namedData_.find ({ argumentsCount, functionName });
            if (search == namedData_.end ()) {
                return false;
            }
            else {
                return true;
            }
        }
        bool ExecuteFunction (const VariantIS& id, ArgumentsListElement* arguments, NumberType& result) const {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            ScopeNodeInterface* foundScope = nullptr;
            if (std::holds_alternative <std::string> (id)) {
                auto search = namedData_.find ({ argumentsCount, std::get <std::string> (id) });
                if (search == namedData_.end ()) {
                    return false;
                }
                else {
                    foundScope = search->second;
                    result = foundScope->Execute ();
                }
            }
            else {
                int numberId = std::get <int> (id);
                if (unnamedData_.size () <= numberId || unnamedData_[numberId].first != argumentsCount) {
                    return false;
                }
                else {
                    foundScope = unnamedData_[numberId].second;
                    result = foundScope->Execute ();
                }
            }
            //  Loading arguments to scope
            std::vector <std::string> argumentsNames = foundScope->GetArgumentsNames ();
            if (argumentsNames.size () != argumentsCount) {
                return false;
            }
            int i = 0;
            while (arguments) {
                foundScope->SetVariable (argumentsNames[i++], arguments->ExecuteNode ());
                arguments = arguments->GetPrevious ();
            }
            return true;
        }
        bool SetFunction (const VariantIS& id, ArgumentsListElement* arguments, ScopeNodeInterface* scope) {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            if (std::holds_alternative <std::string> (id)) {
                auto search = namedData_.find ({ argumentsCount, std::get <std::string> (id) });
                if (search == namedData_.end ()) {
                    return false;
                }
                else {
                    namedData_[{ argumentsCount, std::get <std::string> (id) }] = scope;
                }
            }
            else {
                unnamedData_[std::get <int> (id)].second = scope;
            }
            //  Loading arguments to scope
            std::vector <std::string> argumentsNames = {};
            while (arguments) {
                argumentsNames.push_back (arguments->GetArgumentName ());
                arguments = arguments->GetPrevious ();
            }
            if (argumentsNames.size () != argumentsCount) {
                return false;
            }
            if (scope) {
                scope->SetArgumentsNames (argumentsNames);
            }
            return true;
        }
        bool AddFunction (VariantIS& id, ArgumentsListElement* arguments, ScopeNodeInterface* scope) {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            if (std::holds_alternative <std::string> (id)) {
                auto search = namedData_.find ({ argumentsCount, std::get <std::string> (id) });
                if (search != namedData_.end ()) {
                    return false;
                }
                else {
                    namedData_[{ argumentsCount, std::get <std::string> (id) }] = scope;
                }
            }
            else {
                static int unnamedIdx = 0;
                id = unnamedIdx++;
                unnamedData_.push_back ({argumentsCount, scope});
            }
            //  Loading arguments to scope
            std::vector <std::string> argumentsNames = {};
            while (arguments) {
                argumentsNames.push_back (arguments->GetArgumentName ());
                arguments = arguments->GetPrevious ();
            }
            if (argumentsNames.size () != argumentsCount) {
                return false;
            }
            if (scope) {
                scope->SetArgumentsNames (argumentsNames);
            }
            return true;
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
            for (auto pair : unnamedData_) {
                delete pair.second;
            }
        }
};

extern FunctionSymTable* globalFunctionSymTable;

class FunctionVariableSymTable final {
    private:
        std::map <PairIS, VariantIS> data_ {};
    public:
        //  METHODS
        bool GetFunctionVariable (const std::string& name, ArgumentsListElement* arguments) const {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            auto search = data_.find ({ argumentsCount, name });
            if (search == data_.end () && !globalFunctionSymTable->GetFunction (name, argumentsCount)) {
                return false;
            }
            else {
                return true;
            }
        }
        bool ExecuteFunctionVariable (const std::string& name, ArgumentsListElement* arguments, NumberType& value) const {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            auto search = data_.find ({ argumentsCount, name });
            if (search != data_.end ()) {
                globalFunctionSymTable->ExecuteFunction (search->second, arguments, value);
                return true;
            }
            else if (globalFunctionSymTable->GetFunction (name, argumentsCount)) {
                globalFunctionSymTable->ExecuteFunction ({ name }, arguments, value);
                return true;
            }
            else {
                return false;
            }
        }
        bool SetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            auto search = data_.find ({ argumentsCount, variableName });
            if (search == data_.end ()) {
                return false;
            }
            else {
                std::variant <int, std::string> ans {};
                ans = search->second;
                globalFunctionSymTable->SetFunction (ans, arguments, scope);
                search->second = ans;
                return true;
            }
        }
        bool AddFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            auto search = data_.find ({ argumentsCount, variableName });
            if (search != data_.end ()) {
                return false;
            }
            else {
                VariantIS ans {};
                if (hasFunctionName) {
                    ans = functionName;
                }
                else {
                    ans = poisonFunctionIdx;
                }
                globalFunctionSymTable->AddFunction (ans, arguments, scope);
                data_[{ argumentsCount, variableName }] = ans;
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

class ScopeNode final : public ScopeNodeInterface {
    private:
        std::vector <NodeInterface*> branches_ {};
        VariableSymTable variableTable_ {};
        FunctionVariableSymTable functionVariableTable_ {};
        std::vector <std::string> argumentNames_ {};
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override { stream << "{ ... }"; }   

        //  METHODS FROM SCOPE INTERFACE
        void AddNode (NodeInterface* node) override { branches_.push_back (node); }
        void SetArgumentsNames (const std::vector <std::string>& names) override { argumentNames_ = names; }
        const std::vector <std::string>& GetArgumentsNames () const override { return argumentNames_; }
        NumberType GetVariable (const std::string& name) const override;
        void SetVariable (const std::string& name, NumberType value) override;
        void GetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments) const override {
            const ScopeNode* cur = this;
            NumberType value = 0;
            while (!cur->functionVariableTable_.GetFunctionVariable (variableName, arguments)) {
                if (cur->previous_) {
                    cur = static_cast <ScopeNode*> (cur->previous_);
                }
                else {
                    throw std::invalid_argument ("Wrong name of function variable!");
                }
            }
        }
        NumberType ExecuteFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments) const override {
            const ScopeNode* cur = this;
            NumberType value = 0;
            while (!cur->functionVariableTable_.ExecuteFunctionVariable (variableName, arguments, value)) {
                if (cur->previous_) {
                    cur = static_cast <ScopeNode*> (cur->previous_);
                }
                else {
                    throw std::invalid_argument ("Wrong name of function variable!");
                }
            }
            return value;
        }
        void SetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName, const std::string& functionName) override {
            ScopeNode* cur = this;
            while (!cur->functionVariableTable_.SetFunctionVariable (variableName, arguments, scope, hasFunctionName, functionName)) {
                if (cur->previous_) {
                    cur = static_cast <ScopeNode*> (cur->previous_);
                }
                else {
                    functionVariableTable_.AddFunctionVariable (variableName, arguments, scope, hasFunctionName, functionName);
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
            functionVariableTable_ ({}),
            argumentNames_ ({})
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

        //  EXTRA METHODS
        void Assign (NumberType value) { value_ = value; globalCurrentScope->SetVariable (name_, value); }
        const std::string& GetName () const { return name_; }

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
        ArgumentsListElement* argumentsList_ = nullptr;

        //  mutable because it only changes the way this node dumps
        mutable NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { value_ = globalCurrentScope->ExecuteFunctionVariable (variableName_, argumentsList_); return value_; }
        void Dump (std::ostream &stream) const override { stream << variableName_ << " {" << value_ << "}"; }

        //  EXTRA METHOD
        void Assign (ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") { 
            globalCurrentScope->SetFunctionVariable (variableName_, argumentsList_, scope, hasFunctionName, functionName);
        }

        //  CTOR
        FunctionVariableNode (const std::string& variableName, ArgumentsListElement* argumentsList):
            NodeInterface (NodeType::FUNCTION_VARIABLE),
            variableName_ (variableName),
            argumentsList_ (argumentsList),
            value_ (0)
            {}

        //  DTOR
        ~FunctionVariableNode () = default;
};

class ReturnPerformer final {
    private:
        /* empty */
    public:
        NumberType value_ = 0;
        ReturnPerformer (NumberType value):
            value_ (value)
            {}
};

class ReturnNode final : public NodeInterface {
    private:
        NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override {
            NumberType value = child_->Execute ();
            throw ReturnPerformer (value);
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
        ~BinaryOpNode () { 
            delete leftChild_;
            if (type_ != NodeType::BINARY_OP_FUNCTION_ASSIGN) {
                delete rightChild_; 
            }
        }
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