//Compute the sum of the prime numbers between 500 and 1234.
#include <iostream>
#include <cmath>

using std::cout;
using std::cin;

bool isprime(long int number);

int main(void){
    long int sum = 0;
    for(long int i=500; i<=1234; i++){
        if (isprime(i)){
            sum = i + sum;
        }
    } 
    
    cout << "the sum is: " << sum << "\n";
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
