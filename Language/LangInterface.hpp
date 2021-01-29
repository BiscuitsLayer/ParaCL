#pragma once

//  SYSTEM
#include <iostream>

//  SETTINGS
#include "../Settings/Settings.hpp"

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

class NodeInterface;
class ScopeNodeInterface;

class NodeInterface {
    private:
        /* empty */
    protected:
        NodeType type_ = NodeType::ERROR;
    public:
        //  METHODS
        virtual NumberType Execute () const = 0;
        virtual void Dump (std::ostream &stream) const = 0;

        //  CTOR
        NodeInterface::NodeInterface (NodeType type):
            type_ (type)
            {}

        //  DTOR
        virtual ~NodeInterface () = default;

        //  DERIVED CLASSES CTOR-S
        static NodeInterface* CreateValueNode (NumberType value);
        static NodeInterface* CreateVariableNode (const std::string& name);
        static NodeInterface* CreateBinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild);
        static NodeInterface* CreateIfNode (NodeInterface* condition, ScopeNodeInterface* scope);
        static NodeInterface* CreateWhileNode (NodeInterface* condition, ScopeNodeInterface* scope);
        static NodeInterface* CreateScanNode ();
        static NodeInterface* CreatePrintNode (NodeInterface* child);
};

class ScopeNodeInterface : public NodeInterface {
    private:
        /* empty */
    protected:
        /* empty */
    public:
        ScopeNodeInterface* previous_ = nullptr;
        ScopeNodeInterface* next_ = nullptr;

        //  METHODS
        virtual void AddNode (NodeInterface* node) = 0;
        virtual NumberType GetVariable (const std::string& name) const = 0;
        virtual void SetVariable (const std::string& name, NumberType value) = 0;
        virtual void Entry () const = 0;
        virtual void Return () const = 0;

        //  CTOR
        ScopeNodeInterface::ScopeNodeInterface (ScopeNodeInterface* previous, ScopeNodeInterface* next):
            NodeInterface (NodeType::SCOPE),
            previous_ (previous),
            next_ (next)
            {}

        //  DTOR
        virtual ~ScopeNodeInterface () = default;

        //  DERIVED CLASS CTOR
        static ScopeNodeInterface* CreateScopeNode (ScopeNodeInterface* previous = nullptr, ScopeNodeInterface* next = nullptr);
};