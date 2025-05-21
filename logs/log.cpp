#include "log.h"

std::string get_time() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

void report_log_file(struct _LOG_FORMAT_ log, const std::filesystem::path &path,
                     bool append) {
  std::ofstream outfile;

  outfile.open(path, append ? std::ios::app : std::ios::trunc);

  if (!outfile.is_open()) {
    std::cerr << "ERRO CRÍTICO: Falha ao abrir o arquivo de log: "
              << path.string() << std::endl;
    return;
  }

  outfile << "[" << log.time << "] "
          << "Função: " << log.function << " | "
          << "Arquivo: " << log.arquivo << " | "
          << "Ação: " << log.acao << " | "
          << "Erro: " << ErrorCode_toString(log.error) << "\n";

  if (outfile.fail()) {
    std::cerr << "ERRO CRÍTICO: Falha ao escrever no arquivo de log: "
              << path.string() << std::endl;
  }

  outfile.close();
  if (outfile.fail()) {
    std::cerr << "ERRO CRÍTICO: Falha ao fechar o arquivo de log: "
              << path.string() << std::endl;
  }
}

void report_log(struct _LOG_FORMAT_ log) {
  std::cout << "[" << log.time << "] "
            << "Função: " << log.function << " | "
            << "Arquivo: " << log.arquivo << " | "
            << "Ação: " << log.acao << " | "
            << "Erro: " << ErrorCode_toString(log.error) << std::endl;

  static const std::filesystem::path LOG_FILE = LOG_DIR / "logs.txt";
  report_log_file(log, LOG_FILE, true);
}

void create_report(std::string function, std::string arquivo, std::string acao,
                   ErrorCode error) {
  struct _LOG_FORMAT_ log = {function, arquivo, acao, error, get_time()};

  report_log(log);
}