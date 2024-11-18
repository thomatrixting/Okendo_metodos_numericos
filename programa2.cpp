#include <iostream> 
#include <vector> //there is literally not other way to handle arrays

using std::cout;
std::vector<long unsigned int> prime_factors(long unsigned int number);

int main(int argc, char **argv){

    if (argc != 2) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " n\n";
        std::cerr << "n : highest number in prime sum\n";
        return 1;
    }    

    long unsigned int n = std::stoul(argv[1]); // Change to stoul for unsigned long
    std::vector<long unsigned int> factors = prime_factors(n);

    cout << "The highest prime factor is: " << factors.back() << "\n";

    return 0;
}

std::vector<long unsigned int> prime_factors(long unsigned int number) {
    
    std::vector<long unsigned int> factors;
    long unsigned int number_instance = number; //it takes more memory but it ensures that any wrong happens

    long unsigned int divider = 2; //start dividing by 2 and then continue

    for (long unsigned int i = 1; i <= number_instance; i++ ) {

        while (number_instance % divider == 0) { //so i put n times 2 for example if i have 8
            factors.push_back(divider);
            number_instance /= divider;
        }
        divider = 2*i+1; //much more eficient as i only see odd numbers, even faster is igner 6 multiples
    }
    return factors;

}
