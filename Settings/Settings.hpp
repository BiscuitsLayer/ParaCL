#pragma once

//  NUMBER TYPE
using NumberType = int;

//  ACCURACY
const double EPS = 1e-3;

//  INSTREAM, OUTSTREAM
//#define INSTREAM std::cin
extern std::istream* INSTREAM;
extern std::ostream* OUTSTREAM;
extern std::ostream* ERRSTREAM;

//  PYTHON-STYLE INPUT, OUTPUT
const bool pythonStyleIO = false;

//  ERROR CODES
enum ErrorCodes {
    ERROR_INV_ARG = 1,
    ERROR_OVF = 2,
    ERROR_SYNTAX = 3
};