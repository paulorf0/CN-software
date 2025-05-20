#include "metodos_numericos.h"

// Privado //
// Tenta encontrar um intervalo que tenha uma raiz.
// Vector find_interval(Vector x) { for () }

// Verifica se tem uma raiz no intervalo.
bool valid_interval(Vector x) {
  expr_global.vars_addr[0] = x.a;
  const double fa = te_eval(expr_global.expr);
  expr_global.vars_addr[0] = x.b;
  const double fb = te_eval(expr_global.expr);

  if (fa * fb < 0)
    return true;
  return false;
}
// Privado //

bool master(Vector x, double e, int routine) {

  switch ((function)routine) {
  case BISSEC:
    if (!valid_interval(x))
      throw CNError(
          "O intervalo digitado não possuí uma raiz.",
          "Executar uma rotina para encontrar um novo intervalo com raiz.",
          INVALID_INTERVAL, NEW_INTERVAL);
        
        
    break;

  default:
    throw CNError("Nenhuma função válida foi selecionada.",
                  "Digitar nova entrada.", INVALID_FUNCTION, GET_INPUT);
    break;
  }
}

double bissec(Vector x, double e) {



}
double NR(Vector x, double e); // Newton-Rhapson (NR)
double MS(Vector x, double e); // Metodo da Secante (MS)
