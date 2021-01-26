#pragma once

//	BISON AND FLEX
#include "../Build/location.hh"
#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

class SyntaxCheck : public yyFlexLexer {
    private:
        yy::location location_ {};
        std::string currentString_ {};
        bool isCR (const char* str) {
            return ((str[0] == '\n') || (str[0] == '\v'));
        }
    public:
        SyntaxCheck ():
            location_ ({})
            {}
        void SetLocation () {
            int oldEndColumn = location_.end.column;
            location_.begin.line = location_.end.line = lineno ();
            if (isCR (yytext)) {
                location_.begin.column = location_.end.column = 1;
                currentString_.clear ();
            }
            else {
                location_.begin.column = oldEndColumn;
                location_.end.column = location_.begin.column + YYLeng ();
                currentString_ += yytext;
            }
        }
        yy::location GetLocation () const {
            return location_;
        }
        std::string GetCurrentString () const {
            return currentString_;
        }
        virtual int yylex () override;
};
