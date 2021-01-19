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
        virtual NumberType Execute () const override;
        virtual void Dump (std::ostream &stream) const override;

        //  METHODS FROM SCOPE INTERFACE
        virtual void AddNode (NodeInterface* node) override;
        virtual NumberType GetVariable (const std::string& name) const override;
        virtual void SetVariable (const std::string& name, NumberType value) override;
        virtual void Entry () const override;
        virtual void Return () const override;

        //  CTOR AND DTOR
        explicit ScopeNode (ScopeNodeInterface* previous, ScopeNodeInterface* next);
        virtual ~ScopeNode ();
};

class ValueNode final : public NodeInterface {
    private:
        NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual NumberType Execute () const override;
        virtual void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        explicit ValueNode (NumberType value);
        virtual ~ValueNode () = default;
};

class VariableNode final : public NodeInterface {
    private:
        std::string name_ {};

        //  mutable because it only changes the way this node dumps
        mutable NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual NumberType Execute () const override;
        virtual void Dump (std::ostream &stream) const override;

        //  EXTRA METHOD
        virtual void Assign (NumberType value) const;

        //  CTOR AND DTOR
        explicit VariableNode (const std::string& name);
        virtual ~VariableNode () = default;
};

class BinaryOpNode final : public NodeInterface {
    private:
        NodeInterface* leftChild_ = nullptr;
        NodeInterface* rightChild_ = nullptr;

        //  mutable because it only changes the way this node dumps
        mutable bool isRed_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual NumberType Execute () const override;
        virtual void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        explicit BinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild);
        virtual ~BinaryOpNode ();
};

class IfNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       NodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual NumberType Execute () const override;
        virtual void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        explicit IfNode (NodeInterface* condition, NodeInterface* scope);
        virtual ~IfNode ();
};

class WhileNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       NodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual NumberType Execute () const override;
        virtual void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        explicit WhileNode (NodeInterface* condition, NodeInterface* scope);
        virtual ~WhileNode ();
};

class ScanNode final : public NodeInterface {
    private:
        // mutable because they only change the way this node dumps
        mutable NumberType value_ = 0;
        mutable bool isScanned_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual NumberType Execute () const override;
        virtual void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        explicit ScanNode ();
        virtual ~ScanNode () = default;
};

class PrintNode final : public NodeInterface {
    private:
       NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual NumberType Execute () const override;
        virtual void Dump (std::ostream &stream) const override;

        //  CTOR AND DTOR
        explicit PrintNode (NodeInterface* child);
        virtual ~PrintNode ();
};