#include "error_handling.h"

std::string ErrorCodeVE_toString(ErrorCodeVE code) {
  static const char *names[] = {"SUCESS",
                                "NOT_EXIST_VARS",
                                "WRONG_SYNTAX",
                                "ERROR_CREATING_VARIABLES",
                                "EXPR_COMPILATION_ERROR",
                                "MALLOC_ERROR",
                                "UNKNOW_ERROR"};
  if (code < 0 || code >= END)
    return "UNKNOWN_ERROR_CODE";
  return names[code];
}

std::string ErrorCodeResponse_toString(Response response) {
  static const char *names[] = {
      "WAIT_USER_INPUT_STRING",
      "WAIT_USER_INPUT_INT",
      "WAIT_USER_INPUT_DOUBLE",
  };
  if (response < 0 || response >= END)
    return "UNKNOWN_RESPONSE";
  return names[response];
}

std::string report_error(const ExprException &e) {
  std::string report;

  report.append("Mensagem de erro: " + e.msg + "\n");
  report.append("Código: " + std::to_string(e.code) + " (" +
                ErrorCodeVE_toString((ErrorCodeVE)e.code) + ")\n");
  report.append("Arquivo: " + e.file + "\n");
  report.append("Função: " + e.function + "\n");
  report.append("Horário: " + e.timestamp + "\n");

  return report;
}
