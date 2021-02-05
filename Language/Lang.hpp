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

class SymTable final {
    private:
        std::unordered_map <std::string, NumberType> data_ {};
    public:
        //  METHODS
        bool GetValue (const std::string& name, NumberType& value) const;
        bool SetValue (const std::string& name, NumberType value);
        bool Add (const std::string& name, NumberType value);

        //  CTOR
        SymTable ():
            data_ ({})
            {}

        //  DTOR
        ~SymTable () = default;
};

class FunctionSymTable final {
    private:
        std::unordered_map <std::string, ScopeNodeInterface*> namedData_ {};
        std::vector <ScopeNodeInterface*> unnamedData_ {};
    public:
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

class ScopeNode final : public ScopeNodeInterface {
    private:
        std::vector <NodeInterface*> branches_ {};
        SymTable table_ {};      
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override { stream << "{ ... }"; }   

        //  METHODS FROM SCOPE INTERFACE
        void AddNode (NodeInterface* node) override { branches_.push_back (node); }
        NumberType GetVariable (const std::string& name) const override;
        void SetVariable (const std::string& name, NumberType value) override;
        void Entry () const override    { globalCurrentScope = next_; }
        void Return () const override   { globalCurrentScope = globalCurrentScope->previous_; }

        //  CTOR
        ScopeNode (ScopeNodeInterface* previous, ScopeNodeInterface* next):
            ScopeNodeInterface (previous, next),
            branches_ ({}),
            table_ ({})
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
        std::string name_ {};
        std::variant <int, std::string> id_ {};

        //  mutable because it only changes the way this node dumps
        mutable NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { 
            globalFunctionSymTable->ExecuteFunction (id_, value_);
            return value_; 
        }
        void Dump (std::ostream &stream) const override { stream << name_ << " () {" << value_ << "}"; }

        //  EXTRA METHOD
        void Assign (ScopeNodeInterface* scope) { globalFunctionSymTable->AddFunction (id_, scope); }

        //  CTOR
        FunctionVariableNode (const std::string& name):
            NodeInterface (NodeType::FUNCTION_VARIABLE),
            name_ (name),
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