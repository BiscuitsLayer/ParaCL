#pragma once

//  NUMBER TYPE
using NumberType = int;

//  ACCURACY
const double EPS = 1e-3;

//  INSTREAM, OUTSTREAM
#define INSTREAM std::cin
#define OUTSTREAM std::cout
#define ERRSTREAM std::cerr

//  PYTHON-STYLE INPUT, OUTPUT
const bool pythonStyleIO = false;

//  ERROR CODES
enum ErrorCodes {
    ERROR_INV_ARG = 1,
    ERROR_OVF = 2,
    ERROR_SYNTAX = 3
};