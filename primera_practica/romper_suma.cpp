#include <iostream>

int main() {
  int x = -2147483648; //porque al sumar esto no entra en overflow
  int y = -2147483648;
  int sum = x + y;
  bool b1 = 1;
  std::cout << sum << "\n";
  return 0;
}
