#pragma once

//  SYSTEM
#include <cmath>
#include <vector>
#include <variant>
#include <map>
#include <set>
#include <exception>
#include <algorithm>

//  INTERFACE
#include "LangInterface.hpp"

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
        bool SetVariableValue (const std::string& name, NumberType value, bool mustExist);

        //  CTOR
        VariableSymTable ():
            data_ ({})
            {}
};

class FunctionSymTable final {
    // TODO: should be singleton
    private:
        //  in pair -> first = arguments count, second = function name
        std::map <PairIS, ScopeNode*> namedData_ {};
        //  first idx = id, second idx = arguments count
        VectorOfPair <int, ScopeNode*> unnamedData_ {};
        std::set <PairIS> missingFunctions_ {};
        int unnamedIdx = 0;
    public:
        //  METHODS
        ScopeNode* GetFunctionScope (const VariantIS& id, ArgumentsListElement* arguments) const;
        bool SetFunctionScope (VariantIS& id, ArgumentsListElement* arguments, ScopeNode* scope, bool mustExist);
        void AddMissingFunction (const std::string& name, ArgumentsListElement* arguments);
        bool CheckMissingFunctions () const;

        //  CTORS
        FunctionSymTable ():
            namedData_ ({}),
            unnamedData_ ({}),
            missingFunctions_ ({})
            {}
        FunctionSymTable (const FunctionSymTable& table) = delete;

        //  DTOR
        ~FunctionSymTable () {
            for (auto nameToScope : namedData_) {
                delete nameToScope.second;
            }
            for (auto pair : unnamedData_) {
                delete pair.second;
            }
        }

        //  OPERATORS
        FunctionSymTable& operator = (const FunctionSymTable& table) = delete;
};

extern FunctionSymTable* globalFunctionSymTable;

class FunctionVariableSymTable final {
    private:
        //  map: { argumentsCount, variableName } -> std::variant { }
        std::map <PairIS, VariantIS> data_ {};
    public:
        //  METHODS
        ScopeNode* GetFunctionVariableScope (const std::string& name, ArgumentsListElement* arguments) const;
        bool SetFunctionVariable (const std::string& variableName, ArgumentsListElement* arguments, ScopeNode* scope, bool mustExist, bool hasFunctionName = false, const std::string& functionName = "");
        
        //  CTOR
        FunctionVariableSymTable ():
            data_ ({})
            {}
};

class ReturnNode final : public NodeInterface {
    private:
        ReturnGetter* returnGetter_ = nullptr;
        NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override;
        void Dump (std::ostream& stream) const override { stream << "return "; child_->Dump (stream); }

        //  CTORS
        ReturnNode (ReturnGetter* returnGetter, NodeInterface* child):
            NodeInterface (NodeType::RETURN),
            returnGetter_ (returnGetter),
            child_ (child)
            {}
        ReturnNode (const ReturnNode& node) = delete;

        //  DTOR
        ~ReturnNode () { delete child_; }

        //  OPERATORS
        ReturnNode& operator = (ReturnNode& node) = delete;
};

class ScopeNode final : public ScopeNodeInterface, public ReturnGetter {
    private:
        //  The one we gonna send returned node to
        ReturnGetter* wrappingReturnGetter = nullptr;

        //  BRANCHES
        std::vector <NodeInterface*> branches_ {};

        //  VARIABLE AND FUNC VARIABLE TABLES
        VariableSymTable variableTable_ {};
        FunctionVariableSymTable functionVariableTable_ {};

        //  ARGUMENTS
        std::vector <std::string> argumentsNames_ {};
        std::vector <NumberType> savedArgumentValues_ {};
    public:
        //  FRIEND CLASS
        friend class ScopeManager;

        //  METHODS FROM NODE INTERFACE
        void Dump (std::ostream& stream) const override { stream << "{ ... }"; }   
        NumberType Execute () override;

        //  METHODS FROM SCOPE INTERFACE
        void AddBranch (NodeInterface* node) override { branches_.push_back (node); }

        //  ARGUMENTS
        
        bool SetArgumentsNames (ArgumentsListElement* arguments) override;
        NumberType ExecuteWithArguments (ArgumentsListElement* arguments) override;

        //  RETURN MECHANICS
        void SetWrappingReturnGetter (ReturnGetter* returnGetter) { wrappingReturnGetter = returnGetter; }

        //  CTORS
        ScopeNode ():
            ScopeNodeInterface (),
            wrappingReturnGetter (nullptr),
            branches_ ({}),
            variableTable_ ({}),
            functionVariableTable_ ({}),
            argumentsNames_ ({})
            {}
        ScopeNode (const ScopeNode& node) = delete;

        //  DTOR
        ~ScopeNode () {
            for (auto branch : branches_) {
                delete branch;
            }
        }

        //  OPERATORS
        ScopeNode& operator = (ScopeNode& node) = delete;
};

class ScopeManager {
    //  SINGLETON CLASS
    //  Loads a scope node, copies its arguments, branches, and executes it
    private:
        std::vector <ScopeNode*> scopes_ {};
        
        //  PRIVATE CTOR
        ScopeManager ():
            scopes_ ()
            {}
    public:
        //  INSTANCE
        static ScopeManager* GetInstance () {
            static ScopeManager instance_;
            return &instance_;
        }

        //  VARIABLES
        NumberType GetVariableValue (const std::string& name);
        void SetVariableValue (const std::string& name, NumberType value);

        //  FUNCTION VARIABLES
        ScopeNode* GetFunctionVariableScope (const std::string& variableName, ArgumentsListElement* arguments);
        void SetFunctionVariableScope (const std::string& variableName, ArgumentsListElement* arguments, ScopeNode* scope, bool hasFunctionName, const std::string& functionName);
        
        //  GET CURRENT
        ScopeNode* GetCurrent () const { auto ans = &scopes_.back (); return const_cast <ScopeNode*> (ans); }
        
        //  SCOPE MOVES
        void SetWrappingReturnGetter (ReturnGetter* returnGetter) { scopes_.back ().SetWrappingReturnGetter (returnGetter); }
        void Entry (ScopeNode* scope) { 
            scopes_.push_back (scope); 
        }
        ScopeNode* Previous (ScopeNode* scope) { 
            auto resultIt = std::find (scopes_.begin (), scopes_.end (), *scope);
            if (resultIt == scopes_.end ()) {
                throw std::runtime_error ("Wrong scope node!");
            }
            int resultIdx = resultIt - scopes_.begin ();
            if (--resultIdx >= 0) {
                return &scopes_[resultIdx];
            }
            return nullptr;
        }
        ScopeNode* Previous () const { return Previous (&scopes_.back ()); }
        void Outro () { scopes_.pop_back (); }

        //  CTORS
        ScopeManager (const ScopeManager& manager) = delete;

        //  OPERATORS
        ScopeManager& operator = (ScopeManager& manager) = delete;
};

extern ScopeManager* globalCurrentScope;

class ValueNode final : public NodeInterface {
    private:
        NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override { return value_; }
        void Dump (std::ostream& stream) const override { stream << value_; }

        //  CTOR
        ValueNode (NumberType value):
            NodeInterface (NodeType::VALUE),
            value_ (value)
            {}
};

class VariableNode final : public NodeInterface {
    private:
        std::string name_ {};
        NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override { value_ = globalCurrentScope->GetVariableValue (name_); return value_; }
        void Dump (std::ostream& stream) const override { stream << name_ << " {" << value_ << "}"; }

        //  EXTRA METHODS
        void Assign (NumberType value) { value_ = value; globalCurrentScope->SetVariableValue (name_, value); }
        const std::string& GetName () const { return name_; }

        //  CTOR
        VariableNode (const std::string& name):
            NodeInterface (NodeType::VARIABLE),
            name_ (name),
            value_ (0)
            {}
};

class FunctionVariableNode final : public NodeInterface {
    private:
        std::string variableName_ {};
        ArgumentsListElement* argumentsList_ = nullptr;
        NumberType value_ = 0;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override;
        void Dump (std::ostream& stream) const override;

        //  EXTRA METHOD
        void Assign (ScopeNode* scope, bool hasFunctionName = false, const std::string& functionName = "") { 
            globalCurrentScope->SetFunctionVariableScope (variableName_, argumentsList_, scope, hasFunctionName, functionName);
        }

        //  CTORS
        FunctionVariableNode (const std::string& variableName, ArgumentsListElement* argumentsList):
            NodeInterface (NodeType::FUNCTION_VARIABLE),
            variableName_ (variableName),
            argumentsList_ (argumentsList),
            value_ (0)
            {}
        FunctionVariableNode (const FunctionVariableNode& node) = delete;

        //  DTOR
        ~FunctionVariableNode () {
            delete argumentsList_;
        }

        //  OPERATORS
        FunctionVariableNode& operator = (FunctionVariableNode& node) = delete;
};

class BinaryOpNode final : public NodeInterface {
    private:
        NodeInterface* leftChild_ = nullptr;
        NodeInterface* rightChild_ = nullptr;

        //  FOR DUMP
        bool isRed_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override;
        void Dump (std::ostream& stream) const override;

        //  CTORS
        BinaryOpNode (NodeType type, NodeInterface* leftChild, NodeInterface* rightChild):
            NodeInterface (type),
            leftChild_ (leftChild),
            rightChild_ (rightChild)
            {}
        BinaryOpNode (const BinaryOpNode& node) = delete;
        
        //  DTOR
        ~BinaryOpNode () { 
            delete leftChild_;
            if (type_ != NodeType::BINARY_OP_FUNCTION_ASSIGN) {
                delete rightChild_; 
            }
        }

        //  OPERATORS
        BinaryOpNode& operator = (BinaryOpNode& node) = delete;
};

class IfNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       ScopeNode* scopeTrue_ = nullptr;
       ScopeNode* scopeFalse_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override;
        void Dump (std::ostream& stream) const override;

        //  CTORS
        IfNode (NodeInterface* condition, ScopeNode* scopeTrue, ScopeNode* scopeFalse):
            NodeInterface (NodeType::IF),
            condition_ (condition),
            scopeTrue_ (scopeTrue),
            scopeFalse_ (scopeFalse)
            {}
        IfNode (const IfNode& node) = delete;

        //  DTOR
        ~IfNode () { delete condition_; delete scopeTrue_; delete scopeFalse_; }

        //  OPERATORS
        IfNode& operator = (IfNode& node) = delete;
};

class WhileNode final : public NodeInterface {
    private:
       NodeInterface* condition_ = nullptr;
       ScopeNode* scope_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override;
        void Dump (std::ostream& stream) const override;

        //  CTORS
        WhileNode (NodeInterface* condition, ScopeNode* scope):
            NodeInterface (NodeType::WHILE),
            condition_ (condition),
            scope_ (scope)
            {}
        WhileNode (const WhileNode& node) = delete;

        //  DTOR
        ~WhileNode () { delete condition_; delete scope_; }

        //  OPERATORS
        WhileNode& operator = (WhileNode& node) = delete;
};

class ScanNode final : public NodeInterface {
    private:
        NumberType value_ = 0;
        
        // FOR DUMP
        bool isScanned_ = false;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override;
        void Dump (std::ostream& stream) const override;

        //  CTOR
        ScanNode ():
            NodeInterface (NodeType::SCAN),
            value_ (0),
            isScanned_ (false)
            {}
};

class PrintNode final : public NodeInterface {
    private:
        NodeInterface* child_ = nullptr;
    public:
        //  METHODS FROM NODE INTERFACE
        NumberType Execute () override;
        void Dump (std::ostream& stream) const override { stream << "print "; child_->Dump (stream); }

        //  CTORS
        PrintNode (NodeInterface* child):
            NodeInterface (NodeType::PRINT),
            child_ (child)
            {}
        PrintNode (const PrintNode& node) = delete;

        //  DTOR
        ~PrintNode () { delete child_; }

        //  OPERATORS
        PrintNode& operator = (PrintNode& node) = delete;
};