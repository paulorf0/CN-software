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
  ERROR_CODE_COUNT
} ErrorCode;

#endif