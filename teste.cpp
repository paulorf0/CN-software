#include <iostream>

int main(int argc, char const *argv[]) {
  int i = 1 << 0;
  bool v = 1 & i; // 0001 & 0100 = 0
  std::cout << v;
  return 0;
}
