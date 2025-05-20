#include "..\enum\err.h"
#include "..\enum\functions.h"
#include "..\exception\CN_error.h"
#include "..\structs.h"
#include <stdio.h>
#include <stdlib.h>

// Em todos os métodos a precisão relativa vai ser utilizada como critério de
// parada.

bool master(Vector x, double e, int routine); // Função que faz o gerenciamento.

// Zeros de funções
double bissec(Vector x, double e); // Função e precisão
double NR(Vector x, double e);     // Newton-Rhapson (NR)
double MS(Vector x, double e);     // Metodo da Secante (MS)

// Sistemas Lineares
struct _solMATRIZ_ MEG(double *matriz, int row,
                       int col); // Método de Eliminação de Gauss (MG)
struct _solMATRIZ_ MCL(double *matriz, int row,
                       int col); // Método de Cholesky (MCL)
struct _solMATRIZ_ MGJ(double *matriz, int row,
                       int col); // Método Gauss-Jacobi (MGJ)
struct _solMATRIZ_ MGS(double *matriz, int row,
                       int col); // Método Gauss-Seidel (MGS)

// EDOs
struct _solEDO_ euler(struct _vector_ x0, struct _EXPR_ exp); // Euler comum
struct _solEDO_ eulerM(struct _vector_ x0,
                       struct _EXPR_ exp);                  // Euler melhorado
struct _solEDO_ RK3(struct _vector_ x0, struct _EXPR_ exp); // Runge-Kutta(RK)
struct _solEDO_ RK4(struct _vector_ x0, struct _EXPR_ exp);
struct _solEDO_ taylor2(struct _vector_ x0, struct _EXPR_ exp); // fx + fyf

// Posteriormente métodos de interpolação.