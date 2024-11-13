#include <iostream>

using std::cout;
using std::cin;

bool isprime(int number);

int main(void){
	int a = 0;
	cout << "please enter the number: ";
	cin >> a;
	bool prime = isprime(a);
	if (prime) {
		cout << "el numero es primo"<<"\n";
	}
	else {
		cout << "el numero no es primo"<<"\n";
	}
}

bool isprime(int number){
	for (int i=number-1;i>1;i--){
		if (number % i == 0){
			return false;
		}
	}
	return true;
}
