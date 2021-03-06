//	LANGUAGE
#include "../Language/Lang.hpp"

NodeInterface* NodeInterface::CreateReturnNode (ReturnGetter* returnGetter, NodeInterface* child) {
    return new ReturnNode (returnGetter, child);
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

bool ReturnGetter::GetReturnedNodeValue (NumberType& value) { 
    if (executed_) { 
        value = value_; 
        executed_ = false; 
        return true; 
    }
    return false; 
}


ScopeNodeInterface* ScopeNodeInterface::CreateScopeNode () {
    return new ScopeNode ();
}

const std::string& ArgumentsListElement::GetArgumentName () const {
    return static_cast <VariableNode*> (child_)->GetName ();
}

NumberType ArgumentsListElement::Execute () {
    NumberType result = 0;
    if (child_->GetType () == NodeType::SCOPE) {
        static_cast <ScopeNode*> (child_)->SetWrappingReturnGetter (this);
    }
    result = child_->Execute ();
    GetReturnedNodeValue (result);
    return result;
}

void ArgumentsListElement::Dump (std::ostream& stream) const {
    child_->Dump (stream);
    if (previous_) {
        stream << ", ";
        previous_->Dump (stream);
    }
}

int ArgumentsListElement::GetListLength () {
    if (previous_) {
        return previous_->GetListLength () + 1;
    }
    return 1;
}