#include <iostream>

int main (){
    int bound;
    std::cout << "ester pos: ";
    std::cin >> bound;
    double sum = 0.0;
    int i = 1;
    while (i <= bound){
        sum += 1/i;
        i += 1; 
    }
    std::cout << sum << "\n";
    return 0;
}