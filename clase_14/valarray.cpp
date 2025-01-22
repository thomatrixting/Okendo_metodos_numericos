#include <iostream>
#include <valarray>
#include <cmath>

int main()
{
    std::valarray<int> v = {1,2,3,4,5,6,7,8,9,10};

    v = v.apply([](int ii){
        if(ii%2==0){
            return ii*2;
        }else {
            return ii*3;
        }
    });

    for(auto i : v){
        std::cout << i << " ";
    }
    std::cout << "\n";

    double suma = v.sum();

    std::cout << suma << "\n";



    return 0;
}