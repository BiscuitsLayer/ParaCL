#include "Lang.hpp"

extern ScopeNodeInterface* globalCurrentScope;

bool SymTable::GetValue (const std::string& name, NumberType& value) const {
    auto search = data_.find (name);
    if (search == data_.end ()) {
        return false;
    }
    else {
        value = search->second;
        return true;
    }
}

bool SymTable::SetValue (const std::string& name, NumberType value) {
    auto search = data_.find (name);
    if (search == data_.end ()) {
        return false;
    }
    else {
        search->second = value;
        return true;
    }
}

bool SymTable::Add (const std::string& name, NumberType value) {
    auto search = data_.find (name);
    if (search != data_.end ()) {
        return false;
    }
    else {
        data_[name] = value;
        return true;
    }
}

SymTable::SymTable ():
    data_ ({})
    {}

NumberType ScopeNode::Execute () const {
    for (auto branch : branches_) {
        try {
            branch->Execute ();
        } catch (std::invalid_argument& ex) {
            std::cerr << ex.what () << std::endl;
            branch->Dump (std::cerr);
            std::cerr << std::endl;
            exit (ErrorCodes::ERROR_INV_ARG);
        } catch (std::overflow_error& ex) {
            std::cerr << ex.what () << std::endl;
            branch->Dump (std::cerr);
            std::cerr << std::endl;
            exit (ErrorCodes::ERROR_OVF);
        }
    }
    return 0;
}

void ScopeNode::Dump (std::ostream &stream) const {
    /* empty */
}

void ScopeNode::AddNode (NodeInterface* node) {
    branches_.push_back (node);
}

NumberType ScopeNode::GetVariable (const std::string& name) const {
    const ScopeNode* cur = this;
    NumberType value = 0;
    while (!cur->table_.GetValue (name, value)) {
        if (cur->previous_) {
            cur = static_cast <ScopeNode*> (cur->previous_);
        }
        else {
            throw std::invalid_argument ("Wrong name of variable");
        }
    }
    return value;
}

void ScopeNode::SetVariable (const std::string& name, NumberType value) {
    ScopeNode* cur = this;
    while (!cur->table_.SetValue (name, value)) {
        if (cur->previous_) {
            cur = static_cast <ScopeNode*> (cur->previous_);
        }
        else {
            table_.Add (name, value);
            break;
        }
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

ScopeNode::~ScopeNode () {
    for (auto branch : branches_) {
        delete branch;
    }
}

ScopeNodeInterface* ScopeNodeInterface::CreateScopeNode (ScopeNodeInterface* previous) {
    return new ScopeNode (previous);
}

NumberType ValueNode::Execute () const {
    return value_;
}

void ValueNode::Dump (std::ostream &stream) const {
    stream << value_;
}

ValueNode::ValueNode (NumberType value):
    NodeInterface (NodeType::VALUE),
    value_ (value)
    {}

NodeInterface* NodeInterface::CreateValueNode (NumberType value) {
    return new ValueNode (value);
}

NumberType VariableNode::Execute () const {
    return globalCurrentScope->GetVariable (name_);
}

void VariableNode::Dump (std::ostream &stream) const {
    stream << name_;
}

void VariableNode::Assign (NumberType value) const {
    globalCurrentScope->SetVariable (name_, value);
}

VariableNode::VariableNode (const std::string& name):
    NodeInterface (NodeType::VARIABLE),
    name_ (name)
    {}

NodeInterface* NodeInterface::CreateVariableNode (const std::string& name) {
    return new VariableNode (name);
}

NumberType BinaryOpNode::Execute () const {
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
            NumberType leftResult = leftChild_->Execute ();
            NumberType rightResult = rightChild_->Execute ();
            if (std::fabs (rightResult) < EPS) {
                throw std::overflow_error ("Division by zero");
            }
            else {
                return leftResult / rightResult;
            }
            break;
        }
        case NodeType::BINARY_OP_ASSIGN: {
            VariableNode* leftChildAsVariable = static_cast <VariableNode*> (leftChild_);
            leftChildAsVariable->Assign (rightChild_->Execute ());
            return 0;
            break;
        }
        case NodeType::BINARY_OP_GREATER: {
            return ((leftChild_->Execute () - rightChild_->Execute ()) > EPS ? 1 : -1);
            break;
        }
        case NodeType::BINARY_OP_GREATER_OR_EQ: {
            return ((leftChild_->Execute () - rightChild_->Execute ()) >= EPS ? 1 : -1);
            break;
        }
        case NodeType::BINARY_OP_LESS: {
            return ((leftChild_->Execute () - rightChild_->Execute ()) < EPS ? 1 : -1);
            break;
        }
        case NodeType::BINARY_OP_LESS_OR_EQ: {
            return ((leftChild_->Execute () - rightChild_->Execute ()) <= EPS ? 1 : -1);
            break;
        }
        case NodeType::BINARY_OP_EQ: {
            return (std::fabs (leftChild_->Execute () - rightChild_->Execute ()) < EPS ? 1 : -1);
            break;
        }
        case NodeType::BINARY_OP_NOT_EQ: {
            return (std::fabs (leftChild_->Execute () - rightChild_->Execute ()) > EPS ? 1 : -1);
            break;
        }
    }
}

void BinaryOpNode::Dump (std::ostream& stream) const {
    switch (type_) {
        case NodeType::BINARY_OP_ADD: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " + ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_SUB: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " - ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_MUL: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " * ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_DIV: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " / ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_ASSIGN: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " = ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_GREATER: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " > ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_GREATER_OR_EQ: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " >= ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_LESS: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " < ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_LESS_OR_EQ: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " <= ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_EQ: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " == ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
        case NodeType::BINARY_OP_NOT_EQ: {
            stream << "(";
            leftChild_->Dump (stream);
            stream << " != ";
            rightChild_->Dump (stream);
            stream << ")";
            break;
        }
    }
}

BinaryOpNode::BinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild):
    NodeInterface (type),
    leftChild_ (leftChild),
    rightChild_ (rightChild)
    {}

BinaryOpNode::~BinaryOpNode () {
    delete leftChild_;
    delete rightChild_;
}

NodeInterface* NodeInterface::CreateBinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild) {
    return new BinaryOpNode (type, leftChild, rightChild);
}

NumberType IfNode::Execute () const {
    if (condition_->Execute () > 0) {
        globalCurrentScope->Entry (static_cast <ScopeNodeInterface*> (scope_));
        scope_->Execute ();
        globalCurrentScope->Return ();
    }
}

void IfNode::Dump (std::ostream& stream) const {
    stream << "if ";
    condition_->Dump (stream);
    stream << " { ... }";
}

IfNode::IfNode (NodeInterface* condition, NodeInterface* scope):
    NodeInterface (NodeType::IF),
    condition_ (condition),
    scope_ (scope)
    {}

IfNode::~IfNode () {
    delete condition_;
    delete scope_;
}

NodeInterface* NodeInterface::CreateIfNode (NodeInterface* condition, NodeInterface* scope) {
    return new IfNode (condition, scope);
}

NumberType WhileNode::Execute () const {
    while (condition_->Execute () > 0) {
        globalCurrentScope->Entry (static_cast <ScopeNodeInterface*> (scope_));
        scope_->Execute ();
        globalCurrentScope->Return ();
    }
}

void WhileNode::Dump (std::ostream& stream) const {
    stream << "while ";
    condition_->Dump (stream);
    stream << " { ... }";
}

WhileNode::WhileNode (NodeInterface* condition, NodeInterface* scope):
    NodeInterface (NodeType::WHILE),
    condition_ (condition),
    scope_ (scope)
    {}

WhileNode::~WhileNode () {
    delete condition_;
    delete scope_;
}

NodeInterface* NodeInterface::CreateWhileNode (NodeInterface* condition, NodeInterface* scope) {
    return new WhileNode (condition, scope);
}

NumberType ScanNode::Execute () const {
    static size_t inputCounter = 0;
    NumberType inputValue = 0;
    std::cout << "In [" << inputCounter++ << "]: ";
    std::cin >> inputValue;
    isScanned_ = true;
    value_ = inputValue;
    return inputValue;
}

void ScanNode::Dump (std::ostream& stream) const {
    if (isScanned_) {
        stream << "{" << value_ << "}";
    }
    else {
        stream << "{not scanned}";
    }
}

ScanNode::ScanNode ():
    NodeInterface (NodeType::SCAN),
    value_ (0),
    isScanned_ (false)
    {}

NodeInterface* NodeInterface::CreateScanNode () {
    return new ScanNode ();
}

NumberType PrintNode::Execute () const {
    static size_t outputCounter = 0;
    std::cout << "Out[" << outputCounter++ << "]: " << child_->Execute () << std::endl;
    return 0;
}

void PrintNode::Dump (std::ostream& stream) const {
    stream << "print ";
    child_->Dump (stream);
}

PrintNode::PrintNode (NodeInterface* child):
    NodeInterface (NodeType::PRINT),
    child_ (child)
    {}

PrintNode::~PrintNode () {
    delete child_;
}

NodeInterface* NodeInterface::CreatePrintNode (NodeInterface* child) {
    return new PrintNode (child);
}