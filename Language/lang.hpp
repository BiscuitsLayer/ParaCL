#pragma once

#include <FlexLexer.h>
#include "../Build/lang.tab.hh"

namespace yy {

    class LangDriver {
        private:
            FlexLexer* lexer_;
        public:
            LangDriver (FlexLexer* lexer):
                lexer_ (lexer)
                {}
            parser::token_type yylex (parser::semantic_type* yylval) {
                parser::token_type tokenType = static_cast <parser::token_type> (lexer_->yylex ());
                switch (tokenType) {
                    case yy::parser::token_type::NUMBER: {
                        //  Получаем численное значение token-а, если это число
                        yylval->as <double> () = std::stod (lexer_->YYText ());
                        break;
                    }
                    case yy::parser::token_type::VARIABLE: {
                        // TODO
                        yylval->as <double> () = 0;
                    }
                    default: {
                        break;
                    }
                }
                return tokenType;
            }
            bool parse () {
                parser parser (this);
                bool result = parser.parse ();
                return !result;
            }
    };

}

enum class NodeType {
    VALUE = 0,
    VARIABLE = 1,

    BINARY_OP_ADD = 2,
    BINARY_OP_SUB = 3,
    BINARY_OP_MUL = 4,
    BINARY_OP_DIV = 5,
    BINARY_OP_ASSIGN = 6,

    BINARY_OP_GREATER = 7,
    BINARY_OP_GREATER_OR_EQ = 8,
    BINARY_OP_LESS = 9,
    BINARY_OP_LESS_OR_EQ = 10,

    BINARY_OP_EQ = 11,
    BINARY_OP_NOT_EQ = 12,

    IF = 13,
    WHILE = 14,

    SCAN = 15,
    PRINT = 16,

    ERROR = 17
};

class NodeInterface {
    private:
        NodeInterface* parent_ = nullptr;
        NodeType type_ = NodeType::ERROR;
    public:
        virtual ~NodeInterface () = 0;
        virtual double Execute () = 0;
        virtual double Dump () = 0;

        //  CTOR-S
        static NodeInterface* CreateValue (NodeInterface* parent, double value);
        static NodeInterface* CreateVariable (NodeInterface* parent, const std::string& name);
        static NodeInterface* CreateBinaryOp (NodeInterface* parent, 
            NodeInterface* leftChild, NodeInterface* rightChild);

};