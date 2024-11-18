#include <iostream> 
#include <cmath>
#include <string>

using std::cout;

bool isprime(long unsigned int number);
long unsigned int sum_of_primes(long unsigned int highest_prime);

int main(int argc, char **argv){

    if (argc != 2) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " n\n";
        std::cerr << "n : highest number in prime sum\n";
        return 1;
    }    

    long unsigned int n = std::stoul(argv[1]); // Change to stoul for unsigned long
    long unsigned int sumatory = sum_of_primes(n);

    cout << "The sum is: " << sumatory << "\n";

    return 0;
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
        std::cerr << "ERROR. A negative number cannot be classified as prime\n";
        std::cerr << number << " was given";

        return false;
    }

    if (number == 1) {
        return false;
    }

    if (number <= 3) {
        return true; // As 2 and 3 are prime numbers
    }

    for (long unsigned int i = 2; i <= (std::sqrt(number) + 1); i++) { // Faster loop
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}
