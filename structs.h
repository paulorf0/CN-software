
#pragma once
#ifndef STRUCT_H
#define STRUCT_H

#include "tinyexpr\tinyexpr.h"
#include <list>

typedef struct _vector_ {
  float a; // x
  float b; // y
} Vector;

struct _solEDO_ {
  struct _vector_ y; // y = x'
  struct _vector_ x;
};

struct _solMATRIZ_ {
  double *sol; // Lista de soluções
  int n;       // Quantidade de soluções
};

struct _VARS_ {
  std::list<char> vars;
  bool exist_vars;
};
struct _ADDR_VARS_ {
  double *vars_addr;
  te_variable *vars;
  int size;
};

struct _EXPR_ {
  te_expr *expr;
  double *vars_addr;
  int n; // Quantidade de variáveis
};

struct _VE_RETURN_ {
  struct _EXPR_ exp;
  struct _EXPR_EXCEPTION_ exception;
  int error;
};

// Expressão definida como variável global para todos os arquivos que importarem
// esse header.
typedef struct {
  te_expr *expr;
  double *vars_addr;
  int n;
} EXPR;

extern EXPR expr_global;
#endif