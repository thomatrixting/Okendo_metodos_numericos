#include <iostream>

int main(){
    int m = 100;
    int counter = 0;
    for (int ii = 1; ii < m; ii = ii+1){
        if ((ii % 3 == 0 or ii % 5==0) and (ii%2 != 0)){
            counter ++;
        }

    }
    std::cout << (0%2);
    std::cout << counter << "\n";
}