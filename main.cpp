#include "dependencies.h"
#include <fstream>

int main() {
  setlocale(LC_ALL, "pt_BR.UTF-8");

  std::ofstream create_file("logs.txt");
  create_file.close();

  std::string f = "x*y) + 2";
  struct _VE_RETURN_ expr = make_exp(f);
  if (expr.error) {
    std::string report = report_error(expr.exception.exception);
    std::cout << report;
    exit(1);
  }

  expr.exp.vars_addr[0] = 2;
  expr.exp.vars_addr[1] = 4;
  const double h = te_eval(expr.exp.expr);
  std::cout << "Avaliação: " << h;

  return 0;
}