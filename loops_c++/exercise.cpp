#include <iostream>

using std::cout;
int main(void){

    int min = 0;
    int max = 3;
    double total = 0;

    for (int n = min; n <= max; n++){
        if (n%2 == 0){
            total += n/2;
        } else {
            total = total + static_cast<double>(n)/3 ;
        }
    }

    std::cout << total << "\n";

}