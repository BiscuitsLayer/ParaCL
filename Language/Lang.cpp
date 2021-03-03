#include "Lang.hpp"

bool VariableSymTable::GetVariableValue (const std::string& name, NumberType& value) const {
    auto search = data_.find (name);
    if (search == data_.end ()) {
        return false;
    }
    else {
        value = search->second;
        return true;
    }
}

bool VariableSymTable::SetVariableValue (const std::string& name, NumberType value) {
    auto search = data_.find (name);
    if (search == data_.end ()) {
        return false;
    }
    else {
        search->second = value;
        return true;
    }
}

bool VariableSymTable::AddVariable (const std::string& name, NumberType value) {
    auto search = data_.find (name);
    if (search != data_.end ()) {
        return false;
    }
    else {
        data_[name] = value;
        return true;
    }
}

NumberType ScopeNode::ExecuteFrom (int startBranch) const {
    NumberType result = 0;
    globalCurrentScope->Entry (const_cast <ScopeNode *> (this));
    for (int i = startBranch; i < branches_.size (); ++i) {
        try {
            result = branches_[i]->Execute ();
        }
        catch (ReturnPerformer& performer) {
            globalCurrentScope->Outro ();
            throw performer;
        }
        catch (std::overflow_error& ex) {
            ERRSTREAM << ex.what () << std::endl;
            branches_[i]->Dump (OUTSTREAM);
            OUTSTREAM << std::endl;
            exit (ErrorCodes::ERROR_OVF);
        }
    }
    globalCurrentScope->Outro ();
    return result;
}

NumberType ScopeNode::GetVariable (const std::string& name) const {
    const ScopeNode* cur = this;
    NumberType value = 0;
    while (!cur->variableTable_.GetVariableValue (name, value)) {
        if (cur->Previous ()) {
            cur = static_cast <ScopeNode*> (cur->Previous ());
        }
        else {
            throw std::invalid_argument ("Wrong name of variable!");
        }
    }
    return value;
}

void ScopeNode::SetVariable (const std::string& name, NumberType value) {
    ScopeNode* cur = this;
    while (!cur->variableTable_.SetVariableValue (name, value)) {
        if (cur->Previous ()) {
            cur = static_cast <ScopeNode*> (cur->Previous ());
        }
        else {
            variableTable_.AddVariable (name, value);
            break;
        }
    }
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
            NumberType result = rightChild_->Execute ();
            leftChildAsVariable->Assign (result);
            return result;
            break;
        }
        case NodeType::BINARY_OP_FUNCTION_ASSIGN: {
            FunctionVariableNode* leftChildAsFunctionVariable = static_cast <FunctionVariableNode*> (leftChild_);
            ScopeNodeInterface* rightChildAsScopeInterface = static_cast <ScopeNodeInterface*> (rightChild_);
            leftChildAsFunctionVariable->Assign (rightChildAsScopeInterface);
            return 0;
            break;
        }
        case NodeType::BINARY_OP_GREATER: {
            return (leftChild_->Execute () > rightChild_->Execute () ? 1 : -1);
            break;
        }
        case NodeType::BINARY_OP_GREATER_OR_EQ: {
            return (leftChild_->Execute () >= rightChild_->Execute () ? 1 : -1);
            break;
        }
        case NodeType::BINARY_OP_LESS: {
            return (leftChild_->Execute () < rightChild_->Execute () ? 1 : -1);
            break;
        }
        case NodeType::BINARY_OP_LESS_OR_EQ: {
            return (leftChild_->Execute () <= rightChild_->Execute () ? 1 : -1);
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
        case NodeType::BINARY_OP_FUNCTION_ASSIGN: {
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

NumberType IfNode::Execute () const {
    NumberType result = 0;
    if (condition_->Execute () > 0) {
        result = scopeTrue_->Execute ();
    }
    else {
        if (scopeFalse_) {
            result = scopeFalse_->Execute ();
        }
    }
    return result;
}

NumberType WhileNode::Execute () const {
    NumberType result = 0;
    while (condition_->Execute () > 0) {
        result = scope_->Execute ();
    }
    return result;
}

NumberType ScanNode::Execute () const {
    static size_t inputCounter = 0;
    NumberType inputValue = 0;
    if (pythonStyleIO) {
        OUTSTREAM << "In [" << inputCounter++ << "]: ";
    }
    INSTREAM >> inputValue;
    while (!INSTREAM.good ()) {
        INSTREAM.clear ();
        INSTREAM.ignore ();
        ERRSTREAM << "Please, input a number!" << std::endl;
        if (pythonStyleIO) {
            OUTSTREAM << "In [" << inputCounter++ << "]: ";
        }
        INSTREAM >> inputValue;
    }
    isScanned_ = true;
    value_ = inputValue;
    return inputValue;
}

NumberType PrintNode::Execute () const {
    static size_t outputCounter = 0;
    NumberType outputValue = child_->Execute ();
    if (pythonStyleIO) {
        OUTSTREAM << "Out[" << outputCounter++ << "]: " ;
    }
    OUTSTREAM << outputValue << std::endl;
    return outputValue;
}