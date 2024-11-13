#include <iostream>
#include <cmath>

using std::cout;
using std::cin;

bool isprime(long int number);

int main(void){
	/*
	for (int i=1;i<=150;i++){
		cout << "el numero " << i << " ";

		bool prime = isprime(i);
	 	if (prime) {
			cout << "primo"<<"\n";
		}
		else {
			cout << "no es primo"<<"\n";
		}
	
	}
	*/
	long int a = 2147483647;
	cout << a << "\n";
	cout << isprime(a)<< "\n";
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
