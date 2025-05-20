#pragma once
#ifndef VE_H
#define VE_H

#include "..\enum\err.h"
#include "..\exception\Expr_Exception.h"
#include "..\logs\log.h"
#include "..\tinyexpr\tinyexpr.h"
#include "..\structs.h"
#include <list>
#include <stack>
#include <string>

bool check_expr(std::string f);
struct _VARS_ find_vars(std::string f);
struct _ADDR_VARS_
make_vars(struct _VARS_ vars); // Transformar as variáveis encontradas em
struct _EXPR_ compile_exp(const char *f, struct _ADDR_VARS_ vars);
struct _VE_RETURN_ make_exp(std::string f);

#endif