#include <iostream>
#include <cmath>
#include <string>

# define M_PIl 3.141592653589793238462643383279502884L //difine pi as a long double with 18 decimal places

using std::cout;
using std::cin;

const unsigned int PRECISION = 18; // Max presicion corresponding a long double

long double pi_aprox(unsigned int n);
long double compute_error(long double computed_value, long double true_value);

int main() {

    cout.precision(PRECISION);
    cout.setf(std::ios::scientific);
    
    for (int n = 0; n <= 20; n++) {
        long double pi_estimation = pi_aprox(n);
        long double error = compute_error(pi_estimation, M_PIl);

        cout << "pi estimation for n: " << n << " ";

        // Print pi_estimation in scientific notation with the given decimal places
        cout << pi_estimation << " ";

        // Print error with 8 decimal places 
        cout.precision(8);
        cout << "error: " << error * 100 << "%\n";
    }
    
    return 0;
}

long double pi_aprox(unsigned int n) {
    long double pi_estimation = 0;
    long double instance_value = 0;
    for (unsigned int k = 0; k <= n; k++) { //depends on the procesor but adding the values this ways reduces the error but takes more memory
        long double f1 = 4.0 / (8.0 * k + 1.0); 
        long double f2 = 2.0 / (8.0 * k + 4.0);
        long double f3 = 1.0 / (8.0 * k + 5.0);
        long double f4 = 1.0 / (8.0 * k + 6.0);
        
        long double multiplier = 1.0 / std::pow(16.0, k);
        instance_value = multiplier * (f1 - f2 - f3 - f4);

        pi_estimation += instance_value;
    }

    return pi_estimation;
}

long double compute_error(long double computed_value, long double true_value) {

    long double error = std::abs(computed_value - true_value) / true_value;

    return error;
}
