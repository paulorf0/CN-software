#pragma once
#ifndef EXPR_EXCEPTION_H
#define EXPR_EXCEPTION_H

#include "..\enum\err.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
class CNError : public std::exception {
public:
  int code;    // Código de erro
  int routine; // Código de tratamento de rotina
  std::string msg;
  std::string solution;

  CNError() : code(0), routine(0), msg(""), solution("") {}

  CNError(const std::string &m, const std::string &s, int c, int r)
      : code(c), routine(r), msg(m), solution(s) {}

  CNError(const CNError &other) = default;
  CNError &operator=(const CNError &other) = default;
  CNError(CNError &&other) noexcept = default;
  CNError &operator=(CNError &&other) noexcept = default;

  const char *what() const noexcept override { return msg.c_str(); }
};

struct _EXPR_EXCEPTION_ {
  CNError exception;

  _EXPR_EXCEPTION_() = default;
  _EXPR_EXCEPTION_(const _EXPR_EXCEPTION_ &) = default;
  _EXPR_EXCEPTION_ &operator=(const _EXPR_EXCEPTION_ &) = default;
  _EXPR_EXCEPTION_(_EXPR_EXCEPTION_ &&) noexcept = default;
  _EXPR_EXCEPTION_ &operator=(_EXPR_EXCEPTION_ &&) noexcept = default;
};

#endif