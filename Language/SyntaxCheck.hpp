#pragma once

//	BISON AND FLEX
#include "../Build/location.hh"
#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

class SyntaxCheck : public yyFlexLexer {
    private:
        //  DUMP STUFF
        yy::location location_ {};
        std::string currentString_ {};

        //  CARRIAGE RETURN CHECK
        bool isCR (const char* str) { return ((str[0] == '\n') || (str[0] == '\v')); }
    public:
        //  CTOR
        SyntaxCheck ():
            location_ ({})
            {}

        //  SETTER
        void SetLocation ();

        //  GETTERS
        yy::location GetLocation () const { return location_; }
        std::string GetCurrentString () const { return currentString_; }

        //  OVERLOADED METHOD
        int yylex () override;
};
