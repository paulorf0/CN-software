#pragma once
#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include "..\enum\err.h"
#include "Expr_Exception.h"
std::string report_error(const ExprException &e);
std::string ErrorCode_toString(ErrorCode code);

#endif