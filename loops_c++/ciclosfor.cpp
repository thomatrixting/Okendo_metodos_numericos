#include <iostream>

using std::cout;
int main(void){

    for (int n = 1; n < 30; ++n){
        if (n%3 != 0 and n%5 != 0){
        std::cout << n << '\n';
        }
    }

    int i = 1;
    while (i<=10){
        std::cout << i << "\n";
        ++i;
    }

    return 0;
}