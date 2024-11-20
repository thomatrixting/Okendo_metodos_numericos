//the problem is that we need to optimize the underflow because the computing of small numbers like a h very litle generate a lo of error for exmple 
#include <iostream>
#include <cmath>

using std::cout;
using std::sin;
using std::cos;

double f(double x); //function 
double forward_deriv(double x, double h);
double central_deriv(double x, double h);
double fprime(double x);

int main(int argc, char **argv){

    if (argc != 3) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " x h\n";
        std::cerr << "x: the value were i want the derivate\n";
        std::cerr << "h: the h to make a estimacion\n";
        
        return 1;
    }
    
    cout.precision(16);
    cout.setf(std::ios::scientific);

    double x = std::stod(argv[1]);
    double h = std::stod(argv[2]);

    double fp = fprime(x);

    double dfx = forward_deriv(x,h);
    double errr_dfx = std::fabs(1.0 - fp/dfx);
    double dcx = central_deriv(x,h);
    double errr_dcx = std::fabs(1.0 - fp/dcx);

    cout<< "the forward deriv is: "<< dfx << "\n";
    cout << "error: " << errr_dfx << "\n";
    cout<< "the central deriv is: "<< dcx << "\n";
    cout << "error: " << errr_dcx << "\n";


    return 0;
}

double function(double x){
    return sin(x*x);
}

double fprime(double x){
    return 2*x*cos(x*x);
}

double forward_deriv(double x, double h){

    //f(x) = sen²x
    double denominator = function(x+h) - function(x);
    return denominator/h;

}

double central_deriv(double x, double h){

    //f(x) = sen²x
    double denominator = function(x+h) - function(x-h) ;
    return denominator/(2*h);
}
