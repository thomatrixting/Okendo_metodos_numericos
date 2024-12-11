//the problem is that we need to optimize the underflow because the computing of small numbers like a h very litle generate a lo of error for exmple 
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;
using std::for_each;

int main(){
    cout.precision(16);
    cout.setf(std::ios::scientific);

    vector<double> data = {2.0,4.0,52.0,7.4,3.4,3.145,5.2,4.3,9.0,10.0};

    auto multiply = []( double &n){
        n = n*2;
    };

    auto print = [](double i){
        cout << i << "\n"; 
    };

    auto print_mem = [](double i){
        cout << &i << "\n"; 
    };

    cout << "original vec:" << "\n";
    for_each(data.begin(), data.end(), print);
    for_each(data.begin(), data.end(), print_mem);
    cout << "edited vec:" << "\n";
    for_each(data.begin(), data.end(), multiply);

    for_each(data.begin(), data.end(), print);
    for_each(data.begin(), data.end(), print_mem);



    return 0;
}
