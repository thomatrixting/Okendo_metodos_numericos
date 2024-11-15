//Compute the sum of the prime numbers between n and m.
#include <iostream>
#include <cmath>
#include <string>

using std::cout;
using std::cin;

bool isprime(long int number);
bool isCousingPrimeWithiNext(long int number);

int main(int argc, char **argv){ //sabe in an argv all the argumen|ts

	long vmin = std::stol(argv[1]); //acces to second arg and tranform ir from char to 
	long vmax = std::stol(argv[2]);

	    for(int i=vmin; i<=vmax; i++){
		if (isprime(i)){
		    bool isCousingWithNext = isCousingPrimeWithiNext(i);
			if (isCousingWithNext && i + 4 < 400){
				cout << "(" << i << "," << i+4 << ")" << "\n";
			}
		}
	    } 
	    
    return 0;
}

bool isprime(long int number){
	if (number == 1){
		return false;
	}
	if(number <= 3){
		return true; //as 2 and 3 are prime numbers
	}
	//for (int i=2;i<=number-1;i++){ //slower
	for (long int i=2;i <= (std::sqrt(number)+1); i++){ //faster
		if (number % i == 0){
			return false;
		}
	}
	return true;
}
bool isCousingPrimeWithiNext(long int number){
	long int next_number = number + 4;
	bool next_is_prime = isprime(next_number);

	if (next_is_prime){
		return true;
 	}
	else {
		return false;
	}
}
