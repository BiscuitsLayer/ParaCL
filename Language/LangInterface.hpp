#pragma once

//  SYSTEM
#include <iostream>
#include <stack>

//  SETTINGS
#include "../Settings/Settings.hpp"

enum class NodeType {
    RETURN,

    VALUE,
    VARIABLE,
    FUNCTION_VARIABLE,

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
        std::stack <ScopeNodeInterface*> previousStack_ {};

        //  METHODS
        virtual void AddNode (NodeInterface* node) = 0;
        virtual bool ExecuteWithArguments (ArgumentsListElement* arguments, NumberType& result) = 0;
        virtual bool SetArgumentsNames (ArgumentsListElement* arguments) = 0;
        virtual NumberType GetVariable (const std::string& name) const = 0;
        virtual void SetVariable (const std::string& name, NumberType value) = 0;
        virtual void GetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments) const = 0;
        virtual NumberType ExecuteFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments) const = 0;
        virtual void SetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") = 0;
        virtual void Entry (ScopeNodeInterface* scope) = 0;
        virtual ScopeNodeInterface* Previous () const = 0;
        virtual void Outro () = 0;

        //  CTOR
        ScopeNodeInterface ():
            NodeInterface (NodeType::SCOPE)
            {}

        //  DTOR
        virtual ~ScopeNodeInterface () = default;

        //  DERIVED CLASS CTOR
        static ScopeNodeInterface* CreateScopeNode ();
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
        ~ArgumentsListElement () {
            delete previous_;
            delete node_;
        }
        ArgumentsListElement* GetPreviousArgument () const {
            return previous_;
        }
        const std::string& GetArgumentName () const;
        NumberType ExecuteNode () const {
            return node_->Execute ();
        }
        void Dump (std::ostream &stream) const {
            node_->Dump (stream);
            if (previous_) {
                stream << ", ";
                previous_->Dump (stream);
            }
        }
        int GetListLength () {
            if (previous_) {
                return previous_->GetListLength () + 1;
            }
            return 1;
        }
};