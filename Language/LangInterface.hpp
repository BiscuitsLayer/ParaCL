#pragma once

//  SYSTEM
#include <iostream>

//  SETTINGS
#include "../Settings/Settings.hpp"

enum class NodeType {
    VALUE = 0,
    VARIABLE = 1,

    BINARY_OP_ADD,
    BINARY_OP_SUB,
    BINARY_OP_MUL,
    BINARY_OP_DIV,
    BINARY_OP_ASSIGN,
    BINARY_OP_FUNCTION_ASSIGN,

    BINARY_OP_GREATER,
    BINARY_OP_GREATER_OR_EQ,
    BINARY_OP_LESS,
    BINARY_OP_LESS_OR_EQ,

    BINARY_OP_EQ,
    BINARY_OP_NOT_EQ,

    IF,
    WHILE,
    SCAN,
    PRINT,
    SCOPE,

    FUNCTION,
    FUNCTION_VARIABLE,
    ERROR
};

class NodeInterface;
class ScopeNodeInterface;
class ArgumentsListElement;

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
        NodeInterface (NodeType type):
            type_ (type)
            {}

        //  DTOR
        virtual ~NodeInterface () = default;

        //  DERIVED CLASSES CTOR-S
        static NodeInterface* CreateReturnNode (NodeInterface* child);
        static NodeInterface* CreateValueNode (NumberType value);
        static NodeInterface* CreateVariableNode (const std::string& name);
        static NodeInterface* CreateFunctionVariableNode (const std::string& variableName, ArgumentsListElement* arguments);
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
        virtual void GetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments) const = 0;
        virtual NumberType ExecuteFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments) const = 0;
        virtual void SetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") = 0;
        virtual void Entry () const = 0;
        virtual void Return () const = 0;

        //  CTOR
        ScopeNodeInterface (ScopeNodeInterface* previous, ScopeNodeInterface* next):
            NodeInterface (NodeType::SCOPE),
            previous_ (previous),
            next_ (next)
            {}

        //  DTOR
        virtual ~ScopeNodeInterface () = default;

        //  DERIVED CLASS CTOR
        static ScopeNodeInterface* CreateScopeNode (ScopeNodeInterface* previous = nullptr, ScopeNodeInterface* next = nullptr);
};

class ArgumentsListElement final {
    private:
        ArgumentsListElement* previous_ = nullptr;
        NodeInterface* node_ = nullptr;
    public:
        ArgumentsListElement (NodeInterface* node, ArgumentsListElement* previous):
            previous_ (previous),
            node_ (node)
            {}
        ArgumentsListElement* GetPrevious () const {
            return previous_;
        }
        NumberType ExecuteNode () const {
            return node_->Execute ();
        }
        int GetListLength () {
            if (previous_) {
                return previous_->GetListLength () + 1;
            }
            return 1;
        }
};