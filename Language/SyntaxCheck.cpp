#include "SyntaxCheck.hpp"

void SyntaxCheck::SetLocation () {
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