//computes the highest prime number of given positive integer
//c++17
#include <iostream> 
#include <vector> 

using std::cout; //this is not a bad practice the profersor itself say it
using std::cerr;

bool interpret_input(long unsigned int &n,int argc, char **argv);
std::vector<long unsigned int> compute_prime_factors(long unsigned int number);

int main(int argc, char **argv){
    //define variables
    long unsigned int n=0; //just defined as interpret input will handle it

    bool is_valid_input = interpret_input(n,argc,argv);
    if (!is_valid_input){
        return 1; //halt if anything wrong
    }

    std::vector<long unsigned int> factors = compute_prime_factors(n);

    cout << "The highest prime factor is: " << factors.back() << "\n"; //take the last number

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

std::vector<long unsigned int> compute_prime_factors(long unsigned int number) {
    
    std::vector<long unsigned int> factors; //define the vector
    long unsigned int number_instance = number; //it takes more memory but it ensures that any wrong happens

    long unsigned int divider = 2; //start dividing by 2 and then continue

    for (long unsigned int i = 1; i <= number_instance; i++ ) {

        while (number_instance % divider == 0) { //so i put n times 2 for example if i have 8
            factors.push_back(divider); //add a term to de vector
            number_instance /= divider;
        }
        divider = 2*i+1; //much more eficient as i only see odd numbers, even faster is ignorer 6 multiples
    }
    return factors;

}
