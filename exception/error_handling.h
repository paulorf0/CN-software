#pragma once
#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include "..\enum\response.h"
#include "Expr_Exception.h"
std::string report_error(const ExprException &e);
std::string ErrorCodeVE_toString(ErrorCodeVE code);
std::string ErrorCodeResponse_toString(Response code);

#endif