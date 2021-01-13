#include "Lang.hpp"

extern ScopeNodeInterface* globalCurrentScope;

SymTable::SymTable ():
    data_ ({})
    {}

bool SymTable::GetValue (const std::string& name, double& value) const {
    auto search = data_.find (name);
    if (search == data_.end ()) {
        return false;
    }
    else {
        value = search->second;
        return true;
    }
}

bool SymTable::SetValue (const std::string& name, double value) {
    auto search = data_.find (name);
    if (search == data_.end ()) {
        return false;
    }
    else {
        search->second = value;
        return true;
    }
}

bool SymTable::Add (const std::string& name, double value) {
    auto search = data_.find (name);
    if (search != data_.end ()) {
        return false;
    }
    else {
        data_[name] = value;
        return true;
    }
}

double ScopeNode::Execute () const {
    for (auto branch : branches_) {
        branch->Execute ();
    }
    return 0.0;
}

void ScopeNode::Dump () const {
    // TODO TREE DUMP
    std::cout << "Test Dump!" << std::endl;
}

void ScopeNode::AddNode (NodeInterface* node) {
    branches_.push_back (node);
}

double ScopeNode::GetVariable (const std::string& name) const {
    const SymTable* cur = &table_;
    double value = 0;
    while (!cur->GetValue (name, value)) {
        if (previous_) {
            cur = &(static_cast <ScopeNode*> (previous_)->table_);
        }
        else {
            throw std::invalid_argument ("Wrong name of variable");
        }
    }
    return value;
}

void ScopeNode::SetVariable (const std::string& name, double value) {
    if (!table_.SetValue (name, value)) {
        table_.Add (name, value);
    }
}

void ScopeNode::Entry (ScopeNodeInterface* next) const {
    globalCurrentScope = next;
}

void ScopeNode::Return () const {
    globalCurrentScope = globalCurrentScope->previous_;
}

ScopeNode::ScopeNode (ScopeNodeInterface* previous):
    ScopeNodeInterface (previous),
    branches_ ({}),
    table_ ({})
    {}

ScopeNodeInterface* ScopeNodeInterface::CreateScopeNode (ScopeNodeInterface* previous) {
    return new ScopeNode (previous);
}

double ValueNode::Execute () const {
    return value_;
}

void ValueNode::Dump () const {
    // TODO TREE DUMP
}

ValueNode::ValueNode (double value):
    NodeInterface (NodeType::VALUE),
    value_ (value)
    {}

NodeInterface* NodeInterface::CreateValueNode (double value) {
    return new ValueNode (value);
}

double VariableNode::Execute () const {
    return globalCurrentScope->GetVariable (name_);
}

void VariableNode::Dump () const {
    // TODO TREE DUMP
}

void VariableNode::Assign (double value) const {
    globalCurrentScope->SetVariable (name_, value);
}

VariableNode::VariableNode (const std::string& name):
    NodeInterface (NodeType::VARIABLE),
    name_ (name)
    {}

NodeInterface* NodeInterface::CreateVariableNode (const std::string& name) {
    return new VariableNode (name);
}

double BinaryOpNode::Execute () const {
    switch (type_) {
        case NodeType::BINARY_OP_ADD: {
            return leftChild_->Execute () + rightChild_->Execute ();
            break;
        }
        case NodeType::BINARY_OP_SUB: {
            return leftChild_->Execute () - rightChild_->Execute ();
            break;
        }
        case NodeType::BINARY_OP_MUL: {
            return leftChild_->Execute () * rightChild_->Execute ();
            break;
        }
        case NodeType::BINARY_OP_DIV: {
            return leftChild_->Execute () / rightChild_->Execute ();
            break;
        }
        case NodeType::BINARY_OP_ASSIGN: {
            VariableNode* leftChildAsVariable = static_cast <VariableNode*> (leftChild_);
            leftChildAsVariable->Assign (rightChild_->Execute ());
            return 0.0;
            break;
        }
        case NodeType::BINARY_OP_GREATER: {
            return (leftChild_->Execute () > rightChild_->Execute () ? 1.0 : -1.0);
            break;
        }
        case NodeType::BINARY_OP_GREATER_OR_EQ: {
            return (leftChild_->Execute () >= rightChild_->Execute () ? 1.0 : -1.0);
            break;
        }
        case NodeType::BINARY_OP_LESS: {
            return (leftChild_->Execute () < rightChild_->Execute () ? 1.0 : -1.0);
            break;
        }
        case NodeType::BINARY_OP_LESS_OR_EQ: {
            return (leftChild_->Execute () <= rightChild_->Execute () ? 1.0 : -1.0);
            break;
        }
        case NodeType::BINARY_OP_EQ: {
            return (leftChild_->Execute () == rightChild_->Execute () ? 1.0 : -1.0);
            break;
        }
        case NodeType::BINARY_OP_NOT_EQ: {
            return (leftChild_->Execute () != rightChild_->Execute () ? 1.0 : -1.0);
            break;
        }
    }
}

void BinaryOpNode::Dump () const {
    // TODO TREE DUMP
}

BinaryOpNode::BinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild):
    NodeInterface (type),
    leftChild_ (leftChild),
    rightChild_ (rightChild)
    {}

NodeInterface* NodeInterface::CreateBinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild) {
    return new BinaryOpNode (type, leftChild, rightChild);
}

double IfNode::Execute () const {
    if (condition_->Execute () == 1.0) {
        scope_->Execute ();
    }
}

void IfNode::Dump () const {
    // TODO TREE DUMP
}

IfNode::IfNode (NodeInterface* condition, NodeInterface* scope):
    NodeInterface (NodeType::IF),
    condition_ (condition),
    scope_ (scope)
    {}

NodeInterface* NodeInterface::CreateIfNode (NodeInterface* condition, NodeInterface* scope) {
    return new IfNode (condition, scope);
}

double WhileNode::Execute () const {
    while (condition_->Execute () == 1.0) {
        scope_->Execute ();
    }
}

void WhileNode::Dump () const {
    // TODO TREE DUMP
}

WhileNode::WhileNode (NodeInterface* condition, NodeInterface* scope):
    NodeInterface (NodeType::WHILE),
    condition_ (condition),
    scope_ (scope)
    {}

NodeInterface* NodeInterface::CreateWhileNode (NodeInterface* condition, NodeInterface* scope) {
    return new WhileNode (condition, scope);
}

double ScanNode::Execute () const {
    static size_t inputCounter = 0;
    double returnValue = 0.0;
    std::cout << "In [" << inputCounter++ << "]: ";
    std::cin >> returnValue;
    return returnValue;
}

void ScanNode::Dump () const {
    // TODO TREE DUMP
}

ScanNode::ScanNode ():
    NodeInterface (NodeType::SCAN)
    {}

NodeInterface* NodeInterface::CreateScanNode () {
    return new ScanNode ();
}

double PrintNode::Execute () const {
    static size_t outputCounter = 0;
    std::cout << "Out[" << outputCounter++ << "]: " << child_->Execute () << std::endl;
    return 0.0;
}

void PrintNode::Dump () const {
    // TODO TREE DUMP
}

PrintNode::PrintNode (NodeInterface* child):
    NodeInterface (NodeType::PRINT),
    child_ (child)
    {}

NodeInterface* NodeInterface::CreatePrintNode (NodeInterface* child) {
    return new PrintNode (child);
}