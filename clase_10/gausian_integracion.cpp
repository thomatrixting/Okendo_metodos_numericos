#include <iostream>
#include <cmath>

using std::cout;
using std::cerr;

using fptr = long double(long double); //function pointer

long double function(long double x);
long double compute_error(long double true_value, long double estimated_value);
long double define_integral(void);

long double gauss2(fptr fun, long double a, long double b);

int main(int argc, char **argv){

    cout.precision(18);
    cout.setf(std::ios::scientific); 


    if (argc != 3) {

        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " vmin vmax\n";
        std::cerr << "vmin: the min valoe of the integral, vmax: the max value of the integral\n";
        
        return 1;
    }

    double a = std::stold(argv[1]);
    double b = std::stold(argv[2]);

    long double integral_value = gauss2(function, a, b);
    long double real_value = define_integral(); //esta definido por 0 a 1

    long double error = compute_error(real_value,integral_value);

    cout <<  "integral: "<< integral_value << "\n";
    cout << "error for the integrla between 0 and 1: " << error << "\n";
    
}


long double function(long double x){
    long double result = std::sin(std::pow(x,2)) ;
    return result;
}

long double define_integral(void){

    return 0.310268301723381101808L;

}

long double compute_error(long double true_value, long double estimated_value){
    return std::fabs(1.0 - true_value/estimated_value);
}

long double gauss2(fptr fun, long double a, long double b){

    long double X[2] = {-1./std::sqrt(3) , 1./std::sqrt(3)};
    long double sum = 0;

    for(int i=0; i <= 1; i++){

        sum = sum + fun(
            ((b-a)/2.0)*X[i] + ((b-a)/2.0)
        );

    }

    return ((b-a)/2.0)*sum;

}