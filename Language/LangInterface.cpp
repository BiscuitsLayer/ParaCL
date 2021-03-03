//	LANGUAGE
#include "../Language/Lang.hpp"

NodeInterface* NodeInterface::CreateReturnNode (NodeInterface* child) {
    return new ReturnNode (child);
}

NodeInterface* NodeInterface::CreateValueNode (NumberType value) {
    return new ValueNode (value);
}

NodeInterface* NodeInterface::CreateVariableNode (const std::string& name) { 
    return new VariableNode (name);
}

NodeInterface* NodeInterface::CreateFunctionVariableNode (const std::string& variableName, ArgumentsListElement* arguments) { 
    return new FunctionVariableNode (variableName, arguments); 
}

NodeInterface* NodeInterface::CreateBinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild) {
    return new BinaryOpNode (type, leftChild, rightChild);
}

NodeInterface* NodeInterface::CreateIfNode (NodeInterface* condition, ScopeNodeInterface* scopeTrue, ScopeNodeInterface* scopeFalse) {
    return new IfNode (condition, scopeTrue, scopeFalse);
}

NodeInterface* NodeInterface::CreateWhileNode (NodeInterface* condition, ScopeNodeInterface* scope) {
    return new WhileNode (condition, scope);
}

NodeInterface* NodeInterface::CreateScanNode () {
    return new ScanNode ();
}

NodeInterface* NodeInterface::CreatePrintNode (NodeInterface* child) {
    return new PrintNode (child);
}

ScopeNodeInterface* ScopeNodeInterface::CreateScopeNode () {
    return new ScopeNode ();
}

const std::string& ArgumentsListElement::GetArgumentName () const {
    return static_cast <VariableNode*> (node_)->GetName ();
}