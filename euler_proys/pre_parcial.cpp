#include <iostream>
#include <cmath>

bool isprime(long int number);
bool isCousingPrimeWithiNext(long int number);
void nth_twin_primes(long int index);

int main(int argc, char **argv) {
    // Write C++ code here
    //long int n = std::stol(argv[1]);
    for (int i = 1;i<=100 ;i++)
        nth_twin_primes(i);

    return 0;
}

void nth_twin_primes(long int index){
    long int curent_twins[2] = {};  
    int count = 0;
    for (int i = 3; index > count; i=i+2){ //loop only the odd numbers
        if (isprime(i)){
            if (isCousingPrimeWithiNext(i)){
                curent_twins[0] = i;
                curent_twins[1] = i+2;
                count++;
            }
        }
    }

    //std::cout << "(" << curent_twins[0] << ", " << curent_twins[1] << ")\n";
    std::cout << curent_twins[0] << "," << curent_twins[1] << "\n";

}

bool isCousingPrimeWithiNext(long int number){
	long int next_number = number + 2;
	bool next_is_prime = isprime(next_number);

	if (next_is_prime){
		return true;
 	}
	else {
		return false;
	}
}

bool isprime(long int number){
	if (number == 1){
		return false;
	}

	//for (int i=2;i<=number-1;i++){
	for (long int i=2;i <= std::sqrt(number); i++){
		if (number % i == 0){
			return false;
		}
	}
	return true;
}