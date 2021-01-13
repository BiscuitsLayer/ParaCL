#pragma once

//  SYSTEM
#include <vector>
#include <unordered_map>
#include <exception>

//  INTERFACE
#include "LangInterface.hpp"

class SymTable final {
    private:
        std::unordered_map <std::string, double> data_ {};
    public:
        SymTable ();
        bool GetValue (const std::string& name, double& value) const;
        bool SetValue (const std::string& name, double value);
        bool Add (const std::string& name, double value);
};

class ScopeNode final : public ScopeNodeInterface {
    private:
        std::vector <NodeInterface*> branches_ {};
        SymTable table_ {};      
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override;
        virtual void Dump () const override;

        //  METHODS FROM SCOPE INTERFACE
        virtual ~ScopeNode () override = default;
        virtual void AddNode (NodeInterface* node) override;
        virtual double GetVariable (const std::string& name) const override;
        virtual void SetVariable (const std::string& name, double value) override;
        virtual void Entry (ScopeNodeInterface* next) const override;
        virtual void Return () const override;

        //  CTOR
        explicit ScopeNode (ScopeNodeInterface* previous);
};

class ValueNode final : public NodeInterface {
    private:
        double value_ = 0.0;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override;
        virtual void Dump () const override;

        //  CTOR
        explicit ValueNode (double value);
};

class VariableNode final : public NodeInterface {
    private:
        std::string name_ {};
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override;
        virtual void Dump () const override;

        //  EXTRA METHOD
        virtual void Assign (double value) const;

        //  CTOR
        explicit VariableNode (const std::string& name);
};

class BinaryOpNode final : public NodeInterface {
    private:
        NodeInterface* leftChild_ = nullptr;
        NodeInterface* rightChild_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override;
        virtual void Dump () const override;

        //  CTOR
        explicit BinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild);
};

class IfNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       NodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override;
        virtual void Dump () const override;

        //  CTOR
        explicit IfNode (NodeInterface* condition, NodeInterface* scope);
};

class WhileNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       NodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override;
        virtual void Dump () const override;

        //  CTOR
        explicit WhileNode (NodeInterface* condition, NodeInterface* scope);
};

class ScanNode final : public NodeInterface {
    private:
        /* empty */
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override;
        virtual void Dump () const override;

        //  CTOR
        explicit ScanNode ();
};

class PrintNode final : public NodeInterface {
    private:
       NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        virtual double Execute () const override;
        virtual void Dump () const override;

        //  CTOR
        explicit PrintNode (NodeInterface* child);
};