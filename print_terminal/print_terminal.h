#pragma once
#ifndef PRINT_TERMINAL_H
#define PRINT_TERMINAL_H

#include "..\enum\err.h"
#include "..\enum\response.h"
#include "..\exception\error_handling.h"
#include "..\logs\log.h"
#include "..\structs.h"
#include <iostream>
#include <limits> // para std::numeric_limits
#include <string>
#include <variant>

typedef struct {
  Response code;
  std::variant<std::string, int, double> data;
} ResponseData;

// Talvez essas funções deveriam ficar em outro local?
void concat_msg_inf(std::string s) { sit_global.msg += s + '\n'; }
void concat_obs_inf(std::string s) { sit_global.obs += s + '\n'; }

// Toda a informação vai ser acumulada em msg.
void print_terminal() {
  // Fazendo Log
  std::string info;
  info.append(sit_global.msg);
  info.append(sit_global.obs);
  create_report("print_real_time", "print_terminal.h", info, SUCESS);

  std::cout << "---------- Informação ----------" << std::endl;

  std::cout << sit_global.msg << std::endl;

  if (!sit_global.obs.empty())
    std::cout << "############ Observações ############" << std::endl
              << sit_global.obs;

  std::cout << "---------- FIM ----------" << std::endl;
}

// A captura da informação será feita por outra função.
void print_real_time(Response response) {
  // Fazendo Log
  std::string info;
  info.append(sit_global.msg);
  info.append(sit_global.obs);
  create_report("print_real_time", "print_terminal.h", info, SUCESS);

  std::cout << "---------- Situação Atual ----------" << std::endl;
  std::cout << "Ação de usuário necessário. Informação do código retornado: "
            << std::endl;
  // std::cout << ErrorCodeResponse_toString(response);
  std::cout << "---------- Situação Atual ----------" << std::endl;
}

ResponseData treat_code(Response response) {
  ResponseData rd;
  rd.code = response;

  std::string str_input;
  int int_input;
  double double_input;

  switch (response) {
  case WAIT_USER_INPUT_STRING:
    std::cout << "Esperando resposta: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, str_input);

    rd.data = str_input;
    break;

  case WAIT_USER_INPUT_INT:
    std::cout << "Esperando resposta: ";
    while (!(std::cin >> int_input)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada inválida.";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    rd.data = int_input;
    break;

  case WAIT_USER_INPUT_DOUBLE:
    std::cout << "Esperando resposta: ";
    while (!(std::cin >> double_input)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada inválida.";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    rd.data = double_input;
    break;
  default:
    break;
  }

  return rd;
}

#endif