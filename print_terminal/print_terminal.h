#pragma once
#ifndef PRINT_TERMINAL_H
#define PRINT_TERMINAL_H

#include "..\enum\response.h"
#include "..\exception\error_handling.h"
#include <iostream>
#include <limits> // para std::numeric_limits
#include <string>

typedef struct {
  std::string msg;
  std::string obs;
} info;

#include <variant>

typedef struct {
  Response code;
  std::variant<std::string, int, double> data;
} ResponseData;

void print_terminal() {
  std::cout << "---------- Informação ----------" << std::endl;

  //   std::cout <<

  std::cout << "---------- Informação ----------" << std::endl;
}

void print_real_time(Response response) {
  std::cout << "---------- Situação Atual ----------" << std::endl;
  std::cout << "Ação de usuário necessário. Informação do código retornado: "
            << std::endl;
  std::cout << ErrorCodeResponse_toString(response);
  ResponseData data = treat_code(response);
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