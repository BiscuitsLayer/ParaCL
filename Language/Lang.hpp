#pragma once

//  SYSTEM
#include <cmath>
#include <vector>
#include <unordered_map>
#include <exception>

//  INTERFACE
#include "LangInterface.hpp"

class SymTable final {
    private:
        std::unordered_map <std::string, NumberType> data_ {};
    public:
        //  METHODS
        bool GetValue (const std::string& name, NumberType& value) const;
        bool SetValue (const std::string& name, NumberType value);
        bool Add (const std::string& name, NumberType value);

        //  CTOR AND DTOR
        SymTable ();
        ~SymTable () = default;
};

class ScopeNode final : public ScopeNodeInterface {
    private:
        std::vector <NodeInterface*> branches_ {};
        SymTable table_ {};      
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  METHODS FROM SCOPE INTERFACE
        void AddNode (NodeInterface* node) override;
        NumberType GetVariable (const std::string& name) const override;
        void SetVariable (const std::string& name, NumberType value) override;
        void Entry () const override;
        void Return () const override;

        //  CTOR AND DTOR
        ScopeNode (ScopeNodeInterface* previous, ScopeNodeInterface* next);
        ~ScopeNode ();
};

class ValueNode final : public NodeInterface {
    private:
        NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        ValueNode (NumberType value);
        ~ValueNode () = default;
};

class VariableNode final : public NodeInterface {
    private:
        std::string name_ {};

        //  mutable because it only changes the way this node dumps
        mutable NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  EXTRA METHOD
        void Assign (NumberType value) const;

        //  CTOR AND DTOR
        VariableNode (const std::string& name);
        ~VariableNode () = default;
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

        //  CTOR AND DTOR
        BinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild);
        ~BinaryOpNode ();
};

class IfNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       ScopeNodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        IfNode (NodeInterface* condition, ScopeNodeInterface* scope);
        ~IfNode ();
};

class WhileNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       ScopeNodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        WhileNode (NodeInterface* condition, ScopeNodeInterface* scope);
        ~WhileNode ();
};

class ScanNode final : public NodeInterface {
    private:
        // mutable because they only change the way this node dumps
        mutable NumberType value_ = 0;
        mutable bool isScanned_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        ScanNode ();
        ~ScanNode () = default;
};

class PrintNode final : public NodeInterface {
    private:
       NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        PrintNode (NodeInterface* child);
        ~PrintNode ();
};