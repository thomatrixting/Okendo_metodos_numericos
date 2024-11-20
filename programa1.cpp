//makes the sum of the prime numbers less than a given positive integer
//c++17
#include <iostream> 
#include <cmath>

using std::cout; //this is not a bad practice the profersor itself say it
using std::cerr;

bool interpret_input(long unsigned int &n,int argc, char **argv);
bool isprime(long unsigned int number);
long unsigned int sum_of_primes(long unsigned int highest_prime);

int main(int argc, char **argv){

    long unsigned int n;  //just defined as interpret input will handle it

    bool is_valid_input = interpret_input(n,argc,argv);
    if (!is_valid_input){
        return 1; //halt if anything wrong
    }

    long unsigned int sumatory = sum_of_primes(n);

    cout << "The sum is: " << sumatory << "\n";

    return 0;
}

bool interpret_input(long unsigned int &n,int argc, char **argv){

    if (argc != 2) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " n\n";
        std::cerr << "n : highest integer in Fibonacci sequence\n";
        return false;
    }

    //interpret input
    std::string input = argv[1];
    if (input[0] == '-'){ //if it have a - 
        cerr << "ERROR: Input cannot be negative.\n";
        return false; //halt if nuber is negative
    }

    n = std::stoul(input);  // stoul for unsigned long   
    //define n globaly

    return true;
}

long unsigned int sum_of_primes(long unsigned int highest_prime) {
    if (highest_prime < 2) {
        return 0; // No primes below 2
    }

    long unsigned int sum = 0;

    for (long unsigned int i = 2; i <= highest_prime; i++) { // Iterate upwards
        if (isprime(i)) {
            sum += i; // Add prime number to the sum
        }
    }

    return sum;
}

bool isprime(long unsigned int number) {
    if (number <= 0) {
        cerr << "ERROR. A negative number cannot be classified as prime\n";
        cerr << number << " was given";

        return false;
    }

    if (number == 1) {
        return false; 
    }

    if (number <= 3) {
        return true; // As 2 and 3 are prime numbers
    }

    for (long unsigned int i = 2; i <= (std::sqrt(number)); i++) { // Faster loop
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}
