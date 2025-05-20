#ifndef LOG_H
#define LOG_H

#include "..\enum\err.h"
#include "..\exception\error_handling.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

static const std::filesystem::path LOG_DIR =
    std::filesystem::path("__FILE__").parent_path();

struct _LOG_FORMAT_ {
  std::string function;
  std::string arquivo;
  std::string acao;
  ErrorCodeVE error;
  std::string time;
};

std::string get_time();
void create_report(std::string function, std::string arquivo, std::string acao,
                   ErrorCodeVE error);
void report_log(struct _LOG_FORMAT_ log);
void report_log_file(struct _LOG_FORMAT_ log, const std::filesystem::path &path,
                     bool append);
#endif