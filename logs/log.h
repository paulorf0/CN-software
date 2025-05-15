#ifndef LOG_H
#define LOG_H

#include "..\enum\err.h"
#include "..\exception\error_handling.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

struct _LOG_FORMAT_ {
  std::string function;
  std::string arquivo;
  std::string acao;
  ErrorCode error;
  std::string time;
};

std::string get_time();
void create_report(std::string function, std::string arquivo, std::string acao,
                   ErrorCode error);
void report_log(struct _LOG_FORMAT_ log);
void report_log_file(struct _LOG_FORMAT_ log, std::string file, bool append);
#endif