#pragma once
#ifndef EXPR_EXCEPTION_H
#define EXPR_EXCEPTION_H

#include "..\enum\err.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

class ExprException : public std::exception {
public:
  int code;
  std::string msg;
  std::string file;
  std::string function;
  std::string timestamp;

  // construtor padrão
  ExprException() : code(0), msg(""), file(""), function(""), timestamp("") {}

  // seu construtor existente
  ExprException(const std::string &m, const std::string &a,
                const std::string &f, int c)
      : code(c), msg(m), file(a), function(f) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    timestamp = ss.str();
  }

  // copy/move…
  ExprException(const ExprException &other) = default;
  ExprException &operator=(const ExprException &other) = default;
  ExprException(ExprException &&other) noexcept = default;
  ExprException &operator=(ExprException &&other) noexcept = default;

  const char *what() const noexcept override { return msg.c_str(); }
};

struct _EXPR_EXCEPTION_ {
  ExprException exception;

  _EXPR_EXCEPTION_() = default;
  _EXPR_EXCEPTION_(const _EXPR_EXCEPTION_ &) = default;
  _EXPR_EXCEPTION_ &operator=(const _EXPR_EXCEPTION_ &) = default;
  _EXPR_EXCEPTION_(_EXPR_EXCEPTION_ &&) noexcept = default;
  _EXPR_EXCEPTION_ &operator=(_EXPR_EXCEPTION_ &&) noexcept = default;
};

#endif