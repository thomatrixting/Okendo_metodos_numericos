//sum of the odd fibonachi terms that are lesser than a given positive integer
//c++17
#include <iostream>
#include <vector>

using std::cout; //this is not a bad practice the profersor itself say it
using std::cerr;

// Declaracion of functions
std::vector<long unsigned int> generate_fibonachi_secience(long unsigned int limit, int &size);
long unsigned int sum_odd_terms(std::vector<long unsigned int> vector, int size);

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " n\n";
        std::cerr << "n : highest integer in Fibonacci sequence\n";
        return 1;
    }

    //interpret input
    std::string input = argv[1];
    if (input[0] == '-'){ //if it have a - 
        cerr << "ERROR: Input cannot be negative.\n";
        return 1; //halt if nuber is negative
    }

    long unsigned int n = std::stoul(input);  // stoul for unsigned long   

    if (n < 2) { // validacion to make sure is ok
        std::cerr << "ERROR. Index of Fibonacci sequence should be more or equal to 2\n";
        std::cerr << "Index: " << n << " was given\n";
        return 1;
    }

    int size = 0;

    // call to the function fibonachi and returns a vector
    std::vector<long unsigned int> fibonacci_sequence = generate_fibonachi_secience(n, size);

    // sum of odd terms of the fibonachi secuecne
    long unsigned int sum_of_odd_fibonacci = sum_odd_terms(fibonacci_sequence, size);

    // print result
    cout << "Sum of odd numbers in Fibonacci sequence: " << sum_of_odd_fibonacci << "\n";

    return 0;
}

// Function that calculates the Fibonacci sequence and returns a pointer to the array.
std::vector<long unsigned int> generate_fibonachi_secience(long unsigned int limit, int &size) { //size is used so that only the &size function has to be calculated in this function and can be used globally.
    
    std::vector<long unsigned int> fibonachi_secuecne = {1,2}; //are defined to facilitate summation and simplify coding.

    int i = 0;

    unsigned long int sum=0;

    while (i < 94) { //  94th term exceeds the numerical limit of long unsigned in

        sum = fibonachi_secuecne[i] + fibonachi_secuecne[i+1];

        if (sum <= limit) {
            fibonachi_secuecne.push_back(sum);
        } else {
            size = i+2; //note that size will be the same as i + 2 because the vector will be defined with the two original values of the fibonach series
            return fibonachi_secuecne; // return vector
        }

        i++;
    }

    std::cerr << "ERROR. Numeric limit reached for Fibonacci sequence:\n";
    std::cerr << "Highest term computed: " << sum << "\n";
    return fibonachi_secuecne;
}

// Function that makes the sum of the odd terms
long unsigned int sum_odd_terms(std::vector<long unsigned int> vector, int size) {
    long unsigned int sum = 0;

    for (int i = 0; i < size; i++) { //here size is ussed as it was declared glovaly
        if (vector[i] % 2 != 0) {
            sum += vector[i]; // Sum odd terms
        }
    }

    return sum;
}
