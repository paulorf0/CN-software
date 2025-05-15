#include "log.h"

std::string get_time() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

void report_log(struct _LOG_FORMAT_ log) {
  std::cout << "[" << log.time << "] "
            << "Função: " << log.function << " | "
            << "Arquivo: " << log.arquivo << " | "
            << "Ação: " << log.acao << " | "
            << "Erro: " << ErrorCode_toString(log.error) << std::endl;

  report_log_file(log, "log.txt", true);
}

void report_log_file(struct _LOG_FORMAT_ log, std::string file, bool append) {
  std::ofstream outfile;

  if (append)
    outfile.open(file, std::ios_base::app);
  else
    outfile.open(file);

  outfile << "[" << log.time << "] "
          << "Função: " << log.function << " | "
          << "Arquivo: " << log.arquivo << " | "
          << "Ação: " << log.acao << " | "
          << "Erro: " << ErrorCode_toString(log.error) << "\n";
}

void create_report(std::string function, std::string arquivo, std::string acao,
                   ErrorCode error) {
  struct _LOG_FORMAT_ log = {function, arquivo, acao, error, get_time()};

  report_log(log);
}