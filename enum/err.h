#pragma once
#ifndef ERR_H
#define ERR_H

#include <string>

typedef enum {
  SUCESS = 0,
  NOT_EXIST_VARS,
  WRONG_SYNTAX,
  ERROR_CREATING_VARIABLES,
  EXPR_COMPILATION_ERROR,
  MALLOC_ERROR,
  UNKNOW_ERROR,
  END
} ErrorCodeVE;

typedef enum { INVALID_INTERVAL, INVALID_FUNCTION, END } ErrorCodeCN;

typedef enum {
  NEW_INTERVAL,
  GET_INPUT,

  ERROR,
  END
} RoutineCN;

#endif