#pragma once

#include <vector>
#include <unordered_map>
#include <exception>

#include "LangInterface.hpp"

class SymTable final {
    private:
        std::unordered_map <std::string, double> data_ {};
    public:
        SymTable ():
            data_ ({})
            {}
        bool GetValue (const std::string& name, double& value) const {
            auto search = data_.find (name);
            if (search == data_.end ()) {
                return false;
            }
            else {
                value = search->second;
                return true;
            }
        }
        bool SetValue (const std::string& name, double value) {
            auto search = data_.find (name);
            if (search == data_.end ()) {
                return false;
            }
            else {
                search->second = value;
                return true;
            }
        }
        bool Add (const std::string& name, double value) {
            auto search = data_.find (name);
            if (search != data_.end ()) {
                return false;
            }
            else {
                data_[name] = value;
                return true;
            }
        }
};

class Scope final : public ScopeInterface {
    private:
        ScopeInterface* previous_ = nullptr;
        std::vector <NodeInterface*> branches_ {};
        SymTable table_ {};       
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override {
            for (auto branch : branches_) {
                branch->Execute ();
            }
            return 0.0;
        }
        virtual void Dump () const override {
            // TODO TREE DUMP
            std::cout << "Test Dump!" << std::endl;
        }

        //  METHODS FROM SCOPE INTERFACE
        virtual ~Scope () override = default;
        virtual void AddNode (NodeInterface* node) override {
            branches_.push_back (node);
        }
        virtual double GetVariable (const std::string& name) const override {
            const SymTable* cur = &table_;
            double value = 0;
            while (!cur->GetValue (name, value)) {
                if (parent_) {
                    cur = &(static_cast <Scope*> (parent_)->table_);
                }
                else {
                    throw std::invalid_argument ("Wrong name of variable");
                }
            }
            return value;
        }
        virtual void SetVariable (const std::string& name, double value) override {
            if (!table_.SetValue (name, value)) {
                table_.Add (name, value);
            }
        }

        //  CTOR
        explicit Scope (NodeInterface* parent, ScopeInterface* previous):
            ScopeInterface (parent),
            previous_ (previous),
            branches_ ({}),
            table_ ({})
            {}
};

extern Scope* globalCurrentScope;

class Value final : public NodeInterface {
    private:
        double value_ = 0.0;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override {
            return value_;
        }
        virtual void Dump () const override {
            // TODO TREE DUMP
        }

        //  CTOR
        explicit Value (NodeInterface* parent, double value):
            NodeInterface (parent, NodeType::VALUE),
            value_ (value)
            {}
};

class Variable final : public NodeInterface {
    private:
        std::string name_ {};
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override {
            return globalCurrentScope->GetVariable (name_);
        }
        virtual void Dump () const override {
            // TODO TREE DUMP
        }

        //  EXTRA METHOD
        virtual void Assign (double value) const {
            globalCurrentScope->SetVariable (name_, value);
        }

        //  CTOR
        explicit Variable (NodeInterface* parent, std::string& name):
            NodeInterface (parent, NodeType::VARIABLE),
            name_ (name)
            {}
};

class BinaryOp final : public NodeInterface {
    private:
        NodeInterface* leftChild_ = nullptr;
        NodeInterface* rightChild_ = nullptr;
    protected:
        /* empty */
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override {
            switch (type_) {
                case NodeType::BINARY_OP_ADD: {
                    return leftChild_->Execute () + rightChild_->Execute ();
                    break;
                }
                case NodeType::BINARY_OP_SUB: {
                    return leftChild_->Execute () - rightChild_->Execute ();
                    break;
                }
                case NodeType::BINARY_OP_MUL: {
                    return leftChild_->Execute () * rightChild_->Execute ();
                    break;
                }
                case NodeType::BINARY_OP_DIV: {
                    return leftChild_->Execute () / rightChild_->Execute ();
                    break;
                }
                case NodeType::BINARY_OP_ASSIGN: {
                    Variable* leftChildAsVariable = static_cast <Variable*> (leftChild_);
                    leftChildAsVariable->Assign (rightChild_->Execute ());
                    return 0.0;
                    break;
                }
                case NodeType::BINARY_OP_GREATER: {
                    return (leftChild_->Execute () > rightChild_->Execute () ? 1.0 : -1.0);
                    break;
                }
                case NodeType::BINARY_OP_GREATER_OR_EQ: {
                    return (leftChild_->Execute () >= rightChild_->Execute () ? 1.0 : -1.0);
                    break;
                }
                case NodeType::BINARY_OP_LESS: {
                    return (leftChild_->Execute () < rightChild_->Execute () ? 1.0 : -1.0);
                    break;
                }
                case NodeType::BINARY_OP_LESS_OR_EQ: {
                    return (leftChild_->Execute () <= rightChild_->Execute () ? 1.0 : -1.0);
                    break;
                }
                case NodeType::BINARY_OP_EQ: {
                    return (leftChild_->Execute () == rightChild_->Execute () ? 1.0 : -1.0);
                    break;
                }
                case NodeType::BINARY_OP_NOT_EQ: {
                    return (leftChild_->Execute () != rightChild_->Execute () ? 1.0 : -1.0);
                    break;
                }
            }
        }
        virtual void Dump () const override {
            // TODO TREE DUMP
        }

        //  CTOR
        explicit BinaryOp (NodeInterface* parent, NodeType type,
            NodeInterface* leftChild, NodeInterface* rightChild):
            NodeInterface (parent, type),
            leftChild_ (leftChild),
            rightChild_ (rightChild)
            {}
};

//  IF
//  WHILE
//  SCAN

class Print final : public NodeInterface {
    private:
       NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override {
            static size_t outputCounter = 0;
            std::cout << "[" << outputCounter++ << "]: " << child_->Execute ();
            return 0.0;
        }
        virtual void Dump () const override {
            // TODO TREE DUMP
        }

        //  CTOR
        explicit Print (NodeInterface* parent, NodeInterface* child):
            NodeInterface (parent, NodeType::PRINT),
            child_ (child)
            {}
};