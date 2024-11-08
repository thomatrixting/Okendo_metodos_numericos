#include <iostream>
#include <vector>

using std::cout;
using std::vector;

int main(void){
	int a;
	double b;
	double dec = -9.87e-8;
	std::string name  = "thomas :)";
	vector<double> vec {b,b,b,b,b,b,b,b,b,b};
	
	vec.resize(10);

	cout <<"my name: " <<name << "\n";
       	cout << "my vector: \n"; 	
	
	int counter = 0;
	for (auto i = vec.begin(); i != vec.end(); ++i)
		//counter = counter + 1;
		cout << "[" << counter << "]" << *i << " \n";
	
	return 0;
}
