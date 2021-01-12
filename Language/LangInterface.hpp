#pragma once

#include <iostream>

enum class NodeType {
    VALUE = 0,
    VARIABLE = 1,

    BINARY_OP_ADD = 2,
    BINARY_OP_SUB = 3,
    BINARY_OP_MUL = 4,
    BINARY_OP_DIV = 5,
    BINARY_OP_ASSIGN = 6,

    BINARY_OP_GREATER = 7,
    BINARY_OP_GREATER_OR_EQ = 8,
    BINARY_OP_LESS = 9,
    BINARY_OP_LESS_OR_EQ = 10,

    BINARY_OP_EQ = 11,
    BINARY_OP_NOT_EQ = 12,

    IF = 13,
    WHILE = 14,
    SCAN = 15,
    PRINT = 16,
    SCOPE = 17,

    ERROR = 18
};

class NodeInterface {
    private:
        /* empty */
    protected:
        NodeType type_ = NodeType::ERROR;
    public:
        NodeInterface* parent_ = nullptr;

        //  CTOR
        explicit NodeInterface (NodeInterface* parent, NodeType type):
            parent_ (parent),
            type_ (type)
            {}

        //  METHODS
        virtual ~NodeInterface () = default;
        virtual double Execute () const = 0;
        virtual void Dump () const = 0;

        //  DERIVED CLASSES CTOR-S
        static NodeInterface* CreateValue (NodeInterface* parent, 
            double value);
        static NodeInterface* CreateVariable (NodeInterface* parent, 
            const std::string& name);
        static NodeInterface* CreateBinaryOp (NodeInterface* parent, 
            NodeType type, NodeInterface* leftChild, NodeInterface* rightChild);
        static NodeInterface* CreateIf (NodeInterface* parent, 
            NodeInterface* condition, NodeInterface* scope);
        static NodeInterface* CreateWhile (NodeInterface* parent, 
            NodeInterface* condition, NodeInterface* scope);
        static NodeInterface* CreateScan (NodeInterface* parent, 
            const std::string& name);
        static NodeInterface* CreatePrint (NodeInterface* parent, 
            NodeInterface* child);
};

class ScopeInterface : public NodeInterface {
    private:
        /* empty */
    protected:
        /* empty */
    public:
        //  METHODS
        virtual ~ScopeInterface () = default;
        virtual void AddNode (NodeInterface* node) = 0;
        virtual double GetVariable (const std::string& name) const = 0;
        virtual void SetVariable (const std::string& name, double value) = 0;

        //  CTOR
        explicit ScopeInterface (NodeInterface* parent):
            NodeInterface (parent, NodeType::SCOPE)
            {}

        //  DERIVED CLASSE CTOR
        static ScopeInterface* CreateScope (ScopeInterface* previous = nullptr);
};