#include <iostream>
#include <limits>

int main() {
    std::cout << "Minimum value of long unsigned int: " 
              << std::numeric_limits<long unsigned int>::min() << "\n";
    std::cout << "Maximum value of long unsigned int: " 
              << std::numeric_limits<long unsigned int>::max() << "\n";
    return 0;
}