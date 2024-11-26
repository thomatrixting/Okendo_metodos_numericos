#include <iostream>

using std::cout;
using std::cerr;

const int values[8] = {1,2,5,10,20,50,100,200};
const int values_length = 8;

int count_ways(int value,int shift);

int main(int argc, char **argv) {
    
    int n = std::stoi(argv[1]);

    int count = count_ways(n,0);

    cout << "count is: "<<count<< " \n";

    return 0;

}

int count_ways(int value, int shift){

    int count = 0;
    int new_value = 0;
    for (int i = shift; i<values_length; i++) {

        new_value = value - values[i];

        if (new_value>0){
            count = count + count_ways(new_value,i);
        }
        else if (new_value == 0){
            return count + 1; 
        }
        else if (new_value < 0){
            return count + 0;
        }

    }

    return count;

}