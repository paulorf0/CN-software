#include "VE.h"

bool check_expr(std::string f) {
  create_report("check_expr", "VE.cpp", "Inicializando função. Expressão: " + f,
                SUCESS);
  std::stack<char> pilha;

  for (int i = 0; i < f.length(); i++) {
    if (f[i] == '{' || f[i] == '[' || f[i] == '(')
      pilha.push(f[i]);
    else {
      if (f[i] == '}' || f[i] == ']' || f[i] == ')')
        if (!pilha.empty() && abs(f[i] - pilha.top()) <= 2)
          pilha.pop();
        else {
          create_report(
              "check_expr", "VE.cpp",
              "Em algum ponto da função matemática digitada, o delimitador não "
              "está corretamente posto.",
              WRONG_SYNTAX);

          return false;
        }
    }
  }

  if (pilha.empty()) {
    create_report("check_expr", "VE.cpp",
                  "A expressão digitada foi verificada e está correta.",
                  SUCESS);
    return true;
  } else {
    create_report(
        "check_expr", "VE.cpp",
        "Em algum ponto da função matemática digitada, o delimitador não "
        "está corretamente posto.",
        WRONG_SYNTAX);
    return false;
  }
}

struct _VARS_ find_vars(std::string f) {
  std::list<char> list;
  create_report("find_vars", "VE.cpp", "Iniciando a busca de variáveis.",
                SUCESS);

  for (int i = 0; i < f.length(); i++)
    if ((f[i] >= 65 && f[i] <= 90) || (f[i] >= 97 && f[i] <= 122))
      list.push_back(f[i]);

  create_report("find_vars", "VE.cpp",
                "Busca Terminada. Total de variaveis: " +
                    std::to_string(list.size()),
                SUCESS);

  struct _VARS_ vars;
  vars.vars = list;
  vars.exist_vars = list.empty() ? false : true;

  return vars;
}

struct _ADDR_VARS_ make_vars(struct _VARS_ vars) {
  create_report("make_vars", "VE.cpp", "Iniciando a função.", SUCESS);

  if (vars.vars.size() <= 0) {
    create_report("find_vars", "VE.cpp", "Não existem variáveis. Erro.",
                  NOT_EXIST_VARS);

    throw ExprException("Não existem variáveis na expressão.", "VE.cpp",
                        "make_vars", NOT_EXIST_VARS);
  }

  create_report("make_vars", "VE.cpp", "Inicializando criação de endereços.",
                SUCESS);

  std::list<char> list_vars = vars.vars;
  const int size = list_vars.size();

  struct _ADDR_VARS_ VARS_ADDR;
  VARS_ADDR.vars_addr = (double *)malloc(sizeof(double) * size);
  if (!VARS_ADDR.vars_addr) {
    create_report("make_vars", "VE.cpp",
                  "Falha em alocar memória para os endereços.", MALLOC_ERROR);
    throw ExprException("Falha em alocar memória", "VE.cpp", "make_vars",
                        MALLOC_ERROR);
  }
  create_report("make_vars", "VE.cpp", "Alocação OK.", SUCESS);
  VARS_ADDR.size = size;
  double *addr = VARS_ADDR.vars_addr;

  te_variable *variables = (te_variable *)calloc(size + 1, sizeof(te_variable));
  if (!variables) {
    create_report("make_vars", "VE.cpp", "Falha em alocar as variáveis.",
                  MALLOC_ERROR);
    throw ExprException("Falha em alocar memória", "VE.cpp", "make_vars",
                        MALLOC_ERROR);
  }

  int i = 0;
  for (auto it = list_vars.begin(); it != list_vars.end(); ++it, ++i) {
    char *name = (char *)malloc(2);
    name[0] = *it;
    name[1] = '\0';
    variables[i].name = name;
    variables[i].address = &addr[i];
  }
  VARS_ADDR.vars = variables;
  create_report("make_vars", "VE.cpp", "Finalizando função.", SUCESS);

  return VARS_ADDR;
}

struct _EXPR_ compile_exp(const char *f, struct _ADDR_VARS_ vars) {
  create_report("compile_exp", "VE.cpp", "Inicializando função.", SUCESS);
  int err;

  create_report("compile_exp", "VE.cpp", "Inicializando compilação.", SUCESS);

  te_expr *exp = te_compile(f, vars.vars, vars.size, &err);

  create_report("compile_exp", "VE.cpp", "Verificando erros de compilação.",
                SUCESS);

  if (err != 0) {
    create_report("compile_exp", "VE.cpp",
                  "Erro no método te_compile. Error: " + std::to_string(err),
                  UNKNOW_ERROR);
    throw ExprException("Houve um erro inesperado com a criação das variáveis.",
                        "VE.cpp", "make_vars", EXPR_COMPILATION_ERROR);
  }

  struct _EXPR_ expr;
  expr.expr = exp;
  expr.vars_addr = vars.vars_addr;
  expr.n = vars.size;
  create_report("compile_exp", "VE.cpp", "Expressão compilada.", SUCESS);
  return expr;
}

// O fluxo de execução é:
// check_expr -> find_vars -> make_vars -> compile_exp
struct _VE_RETURN_ make_exp(std::string f) {
  create_report("make_exp", "VE.cpp", "Inicializando função.", SUCESS);

  create_report("make_exp", "VE.cpp", "Executando check_expr.", SUCESS);
  if (!check_expr(f)) {
    ExprException e = ExprException(
        "Existe delimitador inserido incorretamente na expressão.", "VE.cpp",
        "check_expr", WRONG_SYNTAX);
    return _VE_RETURN_{/* exp       */ {nullptr, nullptr},
                       /* exception */ _EXPR_EXCEPTION_{e},
                       /* success   */ 1};
  }

  create_report("make_exp", "VE.cpp", "Executando find_vars.", SUCESS);
  struct _VARS_ vars = find_vars(f);
  if (!vars.exist_vars) {
    ExprException e = ExprException("Não existem variáveis na expressão",
                                    "VE.cpp", "make_exp", NOT_EXIST_VARS);
    return _VE_RETURN_{{nullptr, nullptr}, _EXPR_EXCEPTION_{e}, 1};
  }

  struct _ADDR_VARS_ addr;

  try {
    create_report("make_exp", "VE.cpp", "Executando make_vars.", SUCESS);

    addr = make_vars(vars);
  } catch (ExprException e) {
    return _VE_RETURN_{{nullptr, nullptr}, _EXPR_EXCEPTION_{e}, 1};
  }

  struct _EXPR_ exp;
  try {
    create_report("make_exp", "VE.cpp", "Executando compile_exp.", SUCESS);

    exp = compile_exp(f.c_str(), addr);
  } catch (ExprException e) {
    return _VE_RETURN_{{nullptr, nullptr}, _EXPR_EXCEPTION_{e}, 1};
  }

  create_report("make_exp", "VE.cpp", "Terminando fluxo de criação da função.",
                SUCESS);

  return _VE_RETURN_{exp, _EXPR_EXCEPTION_{}, 0};
}