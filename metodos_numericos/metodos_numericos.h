#include <stdio.h>
#include <stdlib.h>

struct _vector_ {
  float x;
  float y;
};

struct _solEDO_ {
  struct _vector_ y; // y = x'
  struct _vector_ x;
};

struct _solMATRIZ_ {
  double *sol; // Lista de soluções
  int n;       // Quantidade de soluções
};

// Zeros de funções
double bissec(char *f, double e); // Função e precisão
double NR(char *f, double e);     // Newton-Rhapson (NR)
double MS(char *f, double e);     // Metodo da Secante (MS)

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
struct _solEDO_ euler(struct _vector_ x0, char *f);  // Euler comum
struct _solEDO_ eulerM(struct _vector_ x0, char *f); // Euler melhorado
struct _solEDO_ RK3(struct _vector_ x0, char *f);    // Runge-Kutta(RK)
struct _solEDO_ RK4(struct _vector_ x0, char *f);
struct _solEDO_ taylor2(struct _vector_ x0, char *f); // fx + fyf

// Posteriormente métodos de interpolação.