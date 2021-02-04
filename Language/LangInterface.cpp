//	LANGUAGE
#include "../Language/Lang.hpp"

NodeInterface* NodeInterface::CreateValueNode (NumberType value) {
    return new ValueNode (value);
}
NodeInterface* NodeInterface::CreateVariableNode (const std::string& name) { 
    return new VariableNode (name); 
}

NodeInterface* NodeInterface::CreateBinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild) {
    return new BinaryOpNode (type, leftChild, rightChild);
}

NodeInterface* NodeInterface::CreateIfNode (NodeInterface* condition, ScopeNodeInterface* scope) {
    return new IfNode (condition, scope);
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

ScopeNodeInterface* ScopeNodeInterface::CreateScopeNode (ScopeNodeInterface* previous, ScopeNodeInterface* next) {
    return new ScopeNode (previous, next);
}