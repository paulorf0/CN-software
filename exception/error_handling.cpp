#include "error_handling.h"

std::string ErrorCode_toString(ErrorCode code) {
  static const char *names[] = {
      "SUCESS",
      "NOT_EXIST_VARS",
      "WRONG_SYNTAX",
      "ERROR_CREATING_VARIABLES",
      "EXPR_COMPILATION_ERROR",
      "MALLOC_ERROR",
      "UNKNOW_ERROR",
      "INVALID_INTERVAL",
      "INVALID_FUNCTION",
      "NEW_INTERVAL",
      "GET_INPUT",
      "ERROR",
  };
  if (code < 0 || code >= END_ERR)
    return "UNKNOWN_ERROR_CODE";
  return names[code];
}

std::string report_error(const ExprException &e) {
  std::string report;

  report.append("Mensagem de erro: " + e.msg + "\n");
  report.append("Código: " + std::to_string(e.code) + " (" +
                ErrorCode_toString((ErrorCode)e.code) + ")\n");
  report.append("Arquivo: " + e.file + "\n");
  report.append("Função: " + e.function + "\n");
  report.append("Horário: " + e.timestamp + "\n");

  return report;
}
