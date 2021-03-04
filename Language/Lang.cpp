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

bool VariableSymTable::SetVariableValue (const std::string& name, NumberType value, bool mustExist) {
    auto search = data_.find (name);
    if (search == data_.end ()) {
        if (mustExist) {
            return false;
        }
        else {
            data_[name] = value;
            return true;
        }
    }
    else {
        search->second = value;
        return true;
    }
}

ScopeNodeInterface* FunctionSymTable::GetFunctionScope (const VariantIS& id, ArgumentsListElement* arguments) const {
    int argumentsCount = (arguments ? arguments->GetListLength () : 0);
    ScopeNodeInterface* foundScope = nullptr;
    if (std::holds_alternative <std::string> (id)) {
        auto search = namedData_.find ({ argumentsCount, std::get <std::string> (id) });
        if (search == namedData_.end ()) {
            return nullptr;
        }
        else {
            foundScope = search->second;
        }
    }
    else {
        int numberId = std::get <int> (id);
        if (unnamedData_.size () <= numberId || unnamedData_[numberId].first != argumentsCount) {
            return nullptr;
        }
        else {
            foundScope = unnamedData_[numberId].second;
        }
    }
    return foundScope;
}

bool FunctionSymTable::SetFunctionScope (VariantIS& id, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool mustExist) {
    int argumentsCount = (arguments ? arguments->GetListLength () : 0);
    if (std::holds_alternative <std::string> (id)) {
        auto search = namedData_.find ({ argumentsCount, std::get <std::string> (id) });
        if (search == namedData_.end ()) {
            if (mustExist) {
                return false;
            }
            else {
                namedData_[{ argumentsCount, std::get <std::string> (id) }] = scope;
                auto searchInMissing = missingFunctions_.find ({ argumentsCount, std::get <std::string> (id) });
                if (searchInMissing != missingFunctions_.end ()) {
                    missingFunctions_.erase (searchInMissing);
                }
            }
        }
        else {
            namedData_[{ argumentsCount, std::get <std::string> (id) }] = scope;
        }
    }
    else {
        if (unnamedData_.size () <= std::get <int> (id)) {
            if (mustExist) {
                return false;
            }
            else {
                static int unnamedIdx = 0;
                id = unnamedIdx++;
                unnamedData_.push_back ({ argumentsCount, scope });
            }
        }
        else {
            unnamedData_[std::get <int> (id)].second = scope;
        }
    }
    return scope->SetArgumentsNames (arguments);
}

void FunctionSymTable::AddMissingFunction (const std::string& name, ArgumentsListElement* arguments) {
    int argumentsCount = (arguments ? arguments->GetListLength () : 0);
    missingFunctions_.insert ({ argumentsCount, name });
}

bool FunctionSymTable::CheckMissingFunctions () const {
    if (!missingFunctions_.empty ()) {
        *ERRSTREAM << "Functions' scopes missing:" << std::endl;
        for (auto& miss : missingFunctions_) {
            *OUTSTREAM << miss.second << " (" << miss.first << (miss.first == 1 ? " argument)" : " arguments)") << std::endl;
        }
        return false;
    }
    return true;
}

ScopeNodeInterface* FunctionVariableSymTable::GetFunctionVariableScope (const std::string& name, ArgumentsListElement* arguments) const {
    int argumentsCount = (arguments ? arguments->GetListLength () : 0);
    auto search = data_.find ({ argumentsCount, name });
    if (search != data_.end ()) {
        return globalFunctionSymTable->GetFunctionScope (search->second, arguments);
    }
    else {
        //  variableName not found -> try to search as functionName
        return globalFunctionSymTable->GetFunctionScope ({ name }, arguments);
    }
}

bool FunctionVariableSymTable::SetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool mustExist, bool hasFunctionName, const std::string& functionName) {
    int argumentsCount = (arguments ? arguments->GetListLength () : 0);
    auto search = data_.find ({ argumentsCount, variableName });
    if (search == data_.end ()) {
        if (mustExist) {
            return false;
        }
        else {
            VariantIS ans {};
            if (hasFunctionName) {
                ans = functionName;
            }
            else {
                ans = poisonFunctionIdx;
            }
            if (!globalFunctionSymTable->SetFunctionScope (ans, arguments, scope, false)) {
                return false;
            }
            data_[{ argumentsCount, variableName }] = ans;
            return true;
        }
    }
    else {
        std::variant <int, std::string> ans {};
        ans = search->second;
        if (!globalFunctionSymTable->SetFunctionScope (ans, arguments, scope, true)) {
            return false;
        }
        search->second = ans;
        return true;
    }
}

NumberType ScopeNode::Execute () const {
    NumberType result = 0;
    globalCurrentScope->Entry (const_cast <ScopeNode *> (this));
    for (int i = 0; i < branches_.size (); ++i) {
        try {
            result = branches_[i]->Execute ();
        }
        catch (ReturnPerformer& performer) {
            globalCurrentScope->Outro ();
            throw performer;
        }
        catch (std::overflow_error& ex) {
            *ERRSTREAM << ex.what () << std::endl;
            branches_[i]->Dump (*OUTSTREAM);
            *OUTSTREAM << std::endl;
            exit (ErrorCodes::ERROR_OVF);
        }
    }
    globalCurrentScope->Outro ();
    return result;
}

bool ScopeNode::SetArgumentsNames (ArgumentsListElement* arguments) { 
    int argumentsCount = (arguments ? arguments->GetListLength () : 0);
    argumentsNames_.resize (argumentsCount);
    for (int i = 0; i < argumentsCount; ++i) {
        argumentsNames_[i] = arguments->GetArgumentName ();
        SetVariableValue (argumentsNames_[i], 0);
        arguments = arguments->GetPreviousArgument ();
    }
    if (argumentsNames_.size () != argumentsCount) {
        return false;
    }
    return true;
}

NumberType ScopeNode::ExecuteWithArguments (ArgumentsListElement* arguments) {
    globalCurrentScope->Entry (this);
    int argumentsCount = (arguments ? arguments->GetListLength () : 0);
    std::vector <NumberType> oldArgumentValues (argumentsCount);
    for (int i = 0; i < argumentsCount; ++i) {
        try {
            oldArgumentValues[i] = globalCurrentScope->GetVariableValue (argumentsNames_[i]);
        }
        catch (std::invalid_argument& ex) {
            oldArgumentValues[i] = 0;
        }
        globalCurrentScope->SetVariableValue (argumentsNames_[i], arguments->ExecuteNode ());
        arguments = arguments->GetPreviousArgument ();
    }
    //  Outro from scope, since arguments are ready
    globalCurrentScope->Outro ();
    NumberType result = 0;
    try {
        result = Execute ();
    }
    catch (ReturnPerformer& performer) {
        result = performer.value_;
    }
    //  Returning back to function's scope (to set variables back)
    globalCurrentScope->Entry (this);
    for (int i = 0; i < argumentsCount; ++i) {
        globalCurrentScope->SetVariableValue (argumentsNames_[i], oldArgumentValues[i]);
    }
    globalCurrentScope->Outro ();
    return result;
}

NumberType ScopeNode::GetVariableValue (const std::string& name) const {
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

void ScopeNode::SetVariableValue (const std::string& name, NumberType value) {
    ScopeNode* cur = this;
    while (!cur->variableTable_.SetVariableValue (name, value, true)) {
        if (cur->Previous ()) {
            cur = static_cast <ScopeNode*> (cur->Previous ());
        }
        else {
            variableTable_.SetVariableValue (name, value, false);
            break;
        }
    }
}

ScopeNodeInterface* ScopeNode::GetFunctionVariableScope (const std::string& variableName, ArgumentsListElement* arguments) const {
    const ScopeNode* cur = this;
    ScopeNodeInterface* foundScope = cur->functionVariableTable_.GetFunctionVariableScope (variableName, arguments);
    while (!foundScope) {
        if (cur->Previous ()) {
            cur = static_cast <ScopeNode*> (cur->Previous ());
            foundScope = cur->functionVariableTable_.GetFunctionVariableScope (variableName, arguments);
        }
        else {
            throw std::invalid_argument ("Wrong name of function variable!");
        }
    }
    return foundScope;
}

void ScopeNode::SetFunctionVariableScope (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName, const std::string& functionName) {
    ScopeNode* cur = this;
    while (!cur->functionVariableTable_.SetFunctionVariable (variableName, arguments, scope, true, hasFunctionName, functionName)) {
        if (cur->Previous ()) {
            cur = static_cast <ScopeNode*> (cur->Previous ());
        }
        else {
            functionVariableTable_.SetFunctionVariable (variableName, arguments, scope, false, hasFunctionName, functionName);
            break;
        }
    }
}

void ScopeNode::Entry (ScopeNodeInterface* scope) {
    static_cast <ScopeNode*> (scope)->previousStack_.push (globalCurrentScope);
    //std::cout << "entry from " << globalCurrentScope << " to " << scope << std::endl;
    globalCurrentScope = scope;
}

void ScopeNode::Outro () {
    ScopeNodeInterface* previous = globalCurrentScope->Previous ();
    static_cast <ScopeNode*> (globalCurrentScope)->previousStack_.pop ();
    //std::cout << "outro from " << globalCurrentScope << " to " << previous << std::endl;
    globalCurrentScope = previous;
}

NumberType FunctionVariableNode::Execute () const { 
    ScopeNodeInterface* foundScope = globalCurrentScope->GetFunctionVariableScope (variableName_, argumentsList_);
    value_ = foundScope->ExecuteWithArguments (argumentsList_);
    return value_; 
}

void FunctionVariableNode::Dump (std::ostream &stream) const { 
    stream << variableName_ << " (";
    argumentsList_->Dump (stream);
    stream << ") {" << value_ << "}";
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
                *ERRSTREAM << "(";
                leftChild_->Dump (*ERRSTREAM);
                *ERRSTREAM << " / ";
                rightChild_->Dump (*ERRSTREAM);
                *ERRSTREAM << ")";
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

void IfNode::Dump (std::ostream &stream) const {
    stream << "if ";
    condition_->Dump (stream);
    stream << " ";
    scopeTrue_->Dump (stream);
    if (scopeFalse_) {
        stream << " else ";
        scopeFalse_->Dump (stream);
    }
}

NumberType WhileNode::Execute () const {
    NumberType result = 0;
    while (condition_->Execute () > 0) {
        result = scope_->Execute ();
    }
    return result;
}

void WhileNode::Dump (std::ostream &stream) const {
    stream << "while ";
    condition_->Dump (stream);
    stream << " ";
    scope_->Dump (stream);
}

NumberType ScanNode::Execute () const {
    static size_t inputCounter = 0;
    NumberType inputValue = 0;
    if (pythonStyleIO) {
        *OUTSTREAM << "In [" << inputCounter++ << "]: ";
    }
    *INSTREAM >> inputValue;
    while (!INSTREAM->good ()) {
        INSTREAM->clear ();
        INSTREAM->ignore ();
        *ERRSTREAM << "Please, input a number!" << std::endl;
        if (pythonStyleIO) {
            *OUTSTREAM << "In [" << inputCounter++ << "]: ";
        }
        *INSTREAM >> inputValue;
    }
    isScanned_ = true;
    value_ = inputValue;
    return inputValue;
}

void ScanNode::Dump (std::ostream &stream) const {
    if (isScanned_) {
        stream << "{" << value_ << "}";
    }
    else {
        stream << "{not scanned}";
    }
}

NumberType PrintNode::Execute () const {
    static size_t outputCounter = 0;
    NumberType outputValue = child_->Execute ();
    if (pythonStyleIO) {
        *OUTSTREAM << "Out[" << outputCounter++ << "]: " ;
    }
    *OUTSTREAM << outputValue << std::endl;
    return outputValue;
}