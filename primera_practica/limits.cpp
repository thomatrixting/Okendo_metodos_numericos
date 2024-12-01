#include <iostream>
#include <limits>
#include <typeindex>
#include <typeinfo>
#include <string>

int main() {
  //const int myType = typeid(int).name();

  //std::cout << myType << "\n";
  std::cout << std::numeric_limits<double>::min() << "\n";
  std::cout << std::numeric_limits<double>::epsilon() << "\n"; //es la maxima presicion

  return 0;
}
