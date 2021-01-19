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
        } 
        catch (std::overflow_error& ex) {
            ERRSTREAM << ex.what () << std::endl;
            branch->Dump (OUTSTREAM);
            OUTSTREAM << std::endl;
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
            throw std::invalid_argument ("Wrong name of variable!");
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

void ScopeNode::Entry () const {
    globalCurrentScope = next_;
}

void ScopeNode::Return () const {
    globalCurrentScope = globalCurrentScope->previous_;
}

ScopeNode::ScopeNode (ScopeNodeInterface* previous, ScopeNodeInterface* next):
    ScopeNodeInterface (previous, next),
    branches_ ({}),
    table_ ({})
    {}

ScopeNode::~ScopeNode () {
    for (auto branch : branches_) {
        delete branch;
    }
}

ScopeNodeInterface* ScopeNodeInterface::CreateScopeNode (ScopeNodeInterface* previous, ScopeNodeInterface* next) {
    return new ScopeNode (previous, next);
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
    value_ = globalCurrentScope->GetVariable (name_);
    return value_;
}

void VariableNode::Dump (std::ostream &stream) const {
    stream << name_ << " {" << value_ << "}";
}

void VariableNode::Assign (NumberType value) const {
    value_ = value;
    globalCurrentScope->SetVariable (name_, value);
}

VariableNode::VariableNode (const std::string& name):
    NodeInterface (NodeType::VARIABLE),
    name_ (name),
    value_ (0)
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
                isRed_ = true;
                throw std::overflow_error ("Division by zero! (runtime)");
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
    return 0;
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
            if (isRed_) {
                ERRSTREAM << "(";
                leftChild_->Dump (ERRSTREAM);
                ERRSTREAM << " / ";
                rightChild_->Dump (ERRSTREAM);
                ERRSTREAM << ")";
            }
            else {
                stream << "(";
                leftChild_->Dump (stream);
                stream << " / ";
                rightChild_->Dump (stream);
                stream << ")";
            }
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
        globalCurrentScope->next_ = static_cast <ScopeNodeInterface*> (scope_);
        globalCurrentScope->Entry ();
        scope_->Execute ();
        globalCurrentScope->Return ();
    }
    return 0;
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
        globalCurrentScope->next_ = static_cast <ScopeNodeInterface*> (scope_);
        globalCurrentScope->Entry ();
        scope_->Execute ();
        globalCurrentScope->Return ();
    }
    return 0;
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
    OUTSTREAM << "In [" << inputCounter++ << "]: ";
    INSTREAM >> inputValue;
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
    OUTSTREAM << "Out[" << outputCounter++ << "]: " << child_->Execute () << std::endl;
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