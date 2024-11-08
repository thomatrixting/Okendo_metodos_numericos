#include <iostream>

double sum_squared_divisors(int m);
//double sum_squared_divisors(int  & m); now this a pointer that allows me to change the data direcly
//double sum_squared_divisors(const int  & m); para tener lo bueno de ser mas rapido pero no poderlo cambiar
int main(void){
    int A = 10;
    int B = 2;

    std::cout << sum_squared_divisors(A) << "\n";

    return 0;
}

double sum_squared_divisors(int m){ //def 
    int sumatory = 0;
    for (int ii = 2; ii < m; ii++){
        if (m % ii == 0){
            sumatory += ii;
        }
    }

    return static_cast<double>(sumatory)/2;
}