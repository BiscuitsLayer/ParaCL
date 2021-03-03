#pragma once

//  SYSTEM
#include <cmath>
#include <vector>
#include <variant>
#include <map>
#include <set>
#include <exception>

//  INTERFACE
#include "LangInterface.hpp"

//TODO list
/*
1) разделить код по файлам
2) исправить ошибки с 1 уровня
*/

extern ScopeNodeInterface* globalCurrentScope;
const int poisonFunctionIdx = -1;

using PairIS = std::pair <int, std::string>;
using VariantIS = std::variant <int, std::string>;

template <typename T, typename U>
using VectorOfPair = std::vector <std::pair <T, U>>;

class VariableSymTable final {
    private:
        std::map <std::string, NumberType> data_ {};
    public:
        //  METHODS
        bool GetVariableValue (const std::string& name, NumberType& value) const;
        bool SetVariableValue (const std::string& name, NumberType value);
        bool AddVariable (const std::string& name, NumberType value);

        //  CTOR
        VariableSymTable ():
            data_ ({})
            {}

        //  DTOR
        ~VariableSymTable () = default;
};

class FunctionSymTable final {
    private:
        //  in pair -> first = arguments count, second = function name
        std::map <PairIS, ScopeNodeInterface*> namedData_ {};
        //  first idx = id, second idx = arguments count
        VectorOfPair <int, ScopeNodeInterface*> unnamedData_ {};
        std::set <PairIS> missingFunctions_ {};
    public:
        //  METHODS
        bool GetFunction (const std::string& functionName, int argumentsCount) const {
            auto search = namedData_.find ({ argumentsCount, functionName });
            if (search == namedData_.end ()) {
                return false;
            }
            else {
                return true;
            }
        }
        bool ExecuteFunction (const VariantIS& id, ArgumentsListElement* arguments, NumberType& result) const {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            ScopeNodeInterface* foundScope = nullptr;
            if (std::holds_alternative <std::string> (id)) {
                auto search = namedData_.find ({ argumentsCount, std::get <std::string> (id) });
                if (search == namedData_.end ()) {
                    return false;
                }
                else {
                    foundScope = search->second;
                }
            }
            else {
                int numberId = std::get <int> (id);
                if (unnamedData_.size () <= numberId || unnamedData_[numberId].first != argumentsCount) {
                    return false;
                }
                else {
                    foundScope = unnamedData_[numberId].second;
                }
            }
            if (!foundScope->ExecuteWithArguments (arguments, result)) {
                return false;
            }
            return true;
        }
        bool SetFunction (const VariantIS& id, ArgumentsListElement* arguments, ScopeNodeInterface* scope) {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            if (std::holds_alternative <std::string> (id)) {
                auto search = namedData_.find ({ argumentsCount, std::get <std::string> (id) });
                if (search == namedData_.end ()) {
                    return false;
                }
                else {
                    namedData_[{ argumentsCount, std::get <std::string> (id) }] = scope;
                }
            }
            else {
                unnamedData_[std::get <int> (id)].second = scope;
            }
            return scope->SetArgumentsNames (arguments);
        }
        bool AddFunction (VariantIS& id, ArgumentsListElement* arguments, ScopeNodeInterface* scope) {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            if (std::holds_alternative <std::string> (id)) {
                auto search = namedData_.find ({ argumentsCount, std::get <std::string> (id) });
                if (search != namedData_.end ()) {
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
                static int unnamedIdx = 0;
                id = unnamedIdx++;
                unnamedData_.push_back ({argumentsCount, scope});
            }
            return scope->SetArgumentsNames (arguments);
        }
        void AddMissingFunction (const std::string& name, ArgumentsListElement* arguments) {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            missingFunctions_.insert ({ argumentsCount, name });
        }
        bool CheckMissingFunctions () const {
            if (!missingFunctions_.empty ()) {
                ERRSTREAM << "Functions' scopes missing:" << std::endl;
                for (auto& miss : missingFunctions_) {
                    OUTSTREAM << miss.second << " (" << miss.first << (miss.first == 1 ? " argument)" : " arguments)") << std::endl;
                }
                return false;
            }
            return true;
        }

        //  CTOR
        FunctionSymTable ():
            namedData_ ({}),
            unnamedData_ ({}),
            missingFunctions_ ({})
            {}

        //  DTOR
        ~FunctionSymTable () {
            for (auto nameToScope : namedData_) {
                delete nameToScope.second;
            }
            for (auto pair : unnamedData_) {
                delete pair.second;
            }
        }
};

extern FunctionSymTable* globalFunctionSymTable;

class FunctionVariableSymTable final {
    private:
        std::map <PairIS, VariantIS> data_ {};
    public:
        //  METHODS
        bool GetFunctionVariable (const std::string& name, ArgumentsListElement* arguments) const {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            auto search = data_.find ({ argumentsCount, name });
            if (search == data_.end () && !globalFunctionSymTable->GetFunction (name, argumentsCount)) {
                return false;
            }
            else {
                return true;
            }
        }
        bool ExecuteFunctionVariable (const std::string& name, ArgumentsListElement* arguments, NumberType& value) const {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            auto search = data_.find ({ argumentsCount, name });
            if (search != data_.end ()) {
                return globalFunctionSymTable->ExecuteFunction (search->second, arguments, value);
            }
            else if (globalFunctionSymTable->GetFunction (name, argumentsCount)) {
                return globalFunctionSymTable->ExecuteFunction ({ name }, arguments, value);
            }
            else {
                return false;
            }
        }
        bool SetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            auto search = data_.find ({ argumentsCount, variableName });
            if (search == data_.end ()) {
                return false;
            }
            else {
                std::variant <int, std::string> ans {};
                ans = search->second;
                if (!globalFunctionSymTable->SetFunction (ans, arguments, scope)) {
                    return false;
                }
                search->second = ans;
                return true;
            }
        }
        bool AddFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") {
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            auto search = data_.find ({ argumentsCount, variableName });
            if (search != data_.end ()) {
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
                if (!globalFunctionSymTable->AddFunction (ans, arguments, scope)) {
                    return false;
                }
                data_[{ argumentsCount, variableName }] = ans;
                return true;
            }
        }

        //  CTOR
        FunctionVariableSymTable ():
            data_ ({})
            {}

        //  DTOR
        ~FunctionVariableSymTable () = default;
};

class ReturnPerformer final {
    public:
        NodeInterface* child_ = 0;
        ReturnPerformer (NodeInterface* child):
            child_ (child)
            {}
};

class ReturnNode final : public NodeInterface {
    private:
        NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { 
            throw ReturnPerformer (child_);
        }
        void Dump (std::ostream &stream) const override { stream << "return "; child_->Dump (stream); }

        //  CTOR
        ReturnNode (NodeInterface* child):
            NodeInterface (NodeType::RETURN),
            child_ (child)
            {}

        //  DTOR
        ~ReturnNode () { delete child_; }
};

class ScopeNode final : public ScopeNodeInterface {
    private:
        std::vector <NodeInterface*> branches_ {};
        VariableSymTable variableTable_ {};
        FunctionVariableSymTable functionVariableTable_ {};
        std::vector <std::string> argumentsNames_ {};
    public:
        //  METHODS FROM NODE INTERFACE
        void Dump (std::ostream &stream) const override { stream << "{ ... }"; }   

        //  METHODS FROM SCOPE INTERFACE
        NumberType ExecuteFrom (int startBranch = 0) const override;
        NumberType Execute () const override { return ExecuteFrom (0); }
        void AddNode (NodeInterface* node) override { branches_.push_back (node); }
        bool ExecuteWithArguments (ArgumentsListElement* arguments, NumberType& result) override {
            globalCurrentScope->Entry (this);
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            if (argumentsNames_.size () != argumentsCount) {
                return false;
            }
            std::vector <NumberType> oldArgumentValues (argumentsCount);
            for (int i = 0; i < argumentsCount; ++i) {
                try {
                    oldArgumentValues[i] = globalCurrentScope->GetVariable (argumentsNames_[i]);
                }
                catch (std::invalid_argument& ex) {
                    oldArgumentValues[i] = 0;
                }
                globalCurrentScope->SetVariable (argumentsNames_[i], arguments->ExecuteNode ());
                arguments = arguments->GetPreviousArgument ();
            }
            //  Outro from scope, since arguments are ready
            globalCurrentScope->Outro ();
            try {
                result = Execute ();
            }
            catch (ReturnPerformer& performer) {
                globalCurrentScope->Entry (this);
                result = performer.child_->Execute ();
                globalCurrentScope->Outro ();
            }
            //  Returning back to function's scope (to set variables back)
            globalCurrentScope->Entry (this);
            for (int i = 0; i < argumentsCount; ++i) {
                globalCurrentScope->SetVariable (argumentsNames_[i], oldArgumentValues[i]);
            }
            globalCurrentScope->Outro ();
            return true;
        }
        bool SetArgumentsNames (ArgumentsListElement* arguments) override { 
            int argumentsCount = (arguments ? arguments->GetListLength () : 0);
            argumentsNames_.resize (argumentsCount);
            for (int i = 0; i < argumentsCount; ++i) {
                argumentsNames_[i] = arguments->GetArgumentName ();
                SetVariable (argumentsNames_[i], 0);
                arguments = arguments->GetPreviousArgument ();
            }
            if (argumentsNames_.size () != argumentsCount) {
                return false;
            }
            return true;
        }
        NumberType GetVariable (const std::string& name) const override;
        void SetVariable (const std::string& name, NumberType value) override;
        void GetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments) const override {
            const ScopeNode* cur = this;
            NumberType value = 0;
            while (!cur->functionVariableTable_.GetFunctionVariable (variableName, arguments)) {
                if (cur->Previous ()) {
                    cur = static_cast <ScopeNode*> (cur->Previous ());
                }
                else {
                    throw std::invalid_argument ("Wrong name of function variable!");
                }
            }
        }
        NumberType ExecuteFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments) const override {
            const ScopeNode* cur = this;
            NumberType value = 0;
            while (!cur->functionVariableTable_.ExecuteFunctionVariable (variableName, arguments, value)) {
                if (cur->Previous ()) {
                    cur = static_cast <ScopeNode*> (cur->Previous ());
                }
                else {
                    throw std::invalid_argument ("Wrong name of function variable!");
                }
            }
            return value;
        }
        void SetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNodeInterface* scope, bool hasFunctionName, const std::string& functionName) override {
            ScopeNode* cur = this;
            while (!cur->functionVariableTable_.SetFunctionVariable (variableName, arguments, scope, hasFunctionName, functionName)) {
                if (cur->Previous ()) {
                    cur = static_cast <ScopeNode*> (cur->Previous ());
                }
                else {
                    functionVariableTable_.AddFunctionVariable (variableName, arguments, scope, hasFunctionName, functionName);
                    break;
                }
            }
        }
        void Entry (ScopeNodeInterface* scope) override {
            scope->previousStack_.push (globalCurrentScope);
            //std::cout << "entry from " << globalCurrentScope << " to " << scope << std::endl;
            globalCurrentScope = scope;
        }
        ScopeNodeInterface* Previous () const override {
            return (previousStack_.empty () ? nullptr : previousStack_.top ());
        }
        void Outro () override {
            ScopeNodeInterface* previous = globalCurrentScope->Previous ();
            globalCurrentScope->previousStack_.pop ();
            //std::cout << "outro from " << globalCurrentScope << " to " << previous << std::endl;
            globalCurrentScope = previous;
        }

        //  CTOR
        ScopeNode ():
            ScopeNodeInterface (),
            branches_ ({}),
            variableTable_ ({}),
            functionVariableTable_ ({}),
            argumentsNames_ ({})
            {}

        //  DTOR
        ~ScopeNode () {
            for (auto branch : branches_) {
                delete branch;
            }
        }
};

class ValueNode final : public NodeInterface {
    private:
        NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { return value_; }
        void Dump (std::ostream &stream) const override { stream << value_; }

        //  CTOR
        ValueNode (NumberType value):
            NodeInterface (NodeType::VALUE),
            value_ (value)
            {}

        //  DTOR
        ~ValueNode () = default;
};

class VariableNode final : public NodeInterface {
    private:
        std::string name_ {};

        //  mutable because it only changes the way this node dumps
        mutable NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { value_ = globalCurrentScope->GetVariable (name_); return value_; }
        void Dump (std::ostream &stream) const override { stream << name_ << " {" << value_ << "}"; }

        //  EXTRA METHODS
        void Assign (NumberType value) { value_ = value; globalCurrentScope->SetVariable (name_, value); }
        const std::string& GetName () const { return name_; }

        //  CTOR
        VariableNode (const std::string& name):
            NodeInterface (NodeType::VARIABLE),
            name_ (name),
            value_ (0)
            {}

        //  DTOR
        ~VariableNode () = default;
};

class FunctionVariableNode final : public NodeInterface {
    private:
        std::string variableName_ {};
        ArgumentsListElement* argumentsList_ = nullptr;

        //  mutable because it only changes the way this node dumps
        mutable NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override { 
            value_ = globalCurrentScope->ExecuteFunctionVariable (variableName_, argumentsList_);
            return value_; 
        }
        void Dump (std::ostream &stream) const override { 
            stream << variableName_ << " (";
            argumentsList_->Dump (stream);
            stream << ") {" << value_ << "}";
        }

        //  EXTRA METHOD
        void Assign (ScopeNodeInterface* scope, bool hasFunctionName = false, const std::string& functionName = "") { 
            globalCurrentScope->SetFunctionVariable (variableName_, argumentsList_, scope, hasFunctionName, functionName);
        }

        //  CTOR
        FunctionVariableNode (const std::string& variableName, ArgumentsListElement* argumentsList):
            NodeInterface (NodeType::FUNCTION_VARIABLE),
            variableName_ (variableName),
            argumentsList_ (argumentsList),
            value_ (0)
            {}

        //  DTOR
        ~FunctionVariableNode () {
            delete argumentsList_;
        }
};

class BinaryOpNode final : public NodeInterface {
    private:
        NodeInterface* leftChild_ = nullptr;
        NodeInterface* rightChild_ = nullptr;

        //  mutable because it only changes the way this node dumps
        mutable bool isRed_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override;

        //  CTOR
        BinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild):
            NodeInterface (type),
            leftChild_ (leftChild),
            rightChild_ (rightChild)
            {}
        
        //  DTOR
        ~BinaryOpNode () { 
            delete leftChild_;
            if (type_ != NodeType::BINARY_OP_FUNCTION_ASSIGN) {
                delete rightChild_; 
            }
        }
};

class IfNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       ScopeNodeInterface* scopeTrue_ = nullptr;
       ScopeNodeInterface* scopeFalse_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override {
            stream << "if ";
            condition_->Dump (stream);
            stream << " ";
            scopeTrue_->Dump (stream);
            if (scopeFalse_) {
                stream << " else ";
                scopeFalse_->Dump (stream);
            }
        }

        //  CTOR
        IfNode (NodeInterface* condition, ScopeNodeInterface* scopeTrue, ScopeNodeInterface* scopeFalse):
            NodeInterface (NodeType::IF),
            condition_ (condition),
            scopeTrue_ (scopeTrue),
            scopeFalse_ (scopeFalse)
            {}

        //  DTOR
        ~IfNode () { delete condition_; delete scopeTrue_; delete scopeFalse_; }
};

class WhileNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       ScopeNodeInterface* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override {
            stream << "while ";
            condition_->Dump (stream);
            stream << " ";
            scope_->Dump (stream);
        }

        //  CTOR
        WhileNode (NodeInterface* condition, ScopeNodeInterface* scope):
            NodeInterface (NodeType::WHILE),
            condition_ (condition),
            scope_ (scope)
            {}

        //  DTOR
        ~WhileNode () { delete condition_; delete scope_; }
};

class ScanNode final : public NodeInterface {
    private:
        // mutable because they only change the way this node dumps
        mutable NumberType value_ = 0;
        mutable bool isScanned_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override {
            if (isScanned_) {
                stream << "{" << value_ << "}";
            }
            else {
                stream << "{not scanned}";
            }
        }

        //  CTOR
        ScanNode ():
            NodeInterface (NodeType::SCAN),
            value_ (0),
            isScanned_ (false)
            {}

        //  DTOR
        ~ScanNode () = default;
};

class PrintNode final : public NodeInterface {
    private:
        NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () const override;
        void Dump (std::ostream &stream) const override { stream << "print "; child_->Dump (stream); }

        //  CTOR
        PrintNode (NodeInterface* child):
            NodeInterface (NodeType::PRINT),
            child_ (child)
            {}

        //  DTOR
        ~PrintNode () { delete child_; }
};