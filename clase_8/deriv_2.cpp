//the problem is that we need to optimize the underflow because the computing of small numbers like a h very litle generate a lo of error for exmple 
#include <iostream>
#include <cmath>
#include <fstream>

using std::cout;
using std::sin;
using std::cos;

double function(double x); //function 
double forward_deriv(double x, double h);
double central_deriv(double x, double h);
double fprime(double x);

int main(int argc, char **argv){

    if (argc != 2) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " x\n";
        std::cerr << "x: the value were i want the derivate\n";
        
        return 1;
    }
    
    std::ofstream fout("datos.txt");

    fout.precision(16);
    fout.setf(std::ios::scientific);

    double x = std::stod(argv[1]);

    for (double h = 1.0; h >= 1.0e-16;h = h/10.0){
        double fp = fprime(x);

        double dfx = forward_deriv(x,h);
        double errr_dfx = std::fabs(1.0 - fp/dfx);
        double dcx = central_deriv(x,h);
        double errr_dcx = std::fabs(1.0 - fp/dcx);

        fout<< "the forward deriv is: "<< dfx << "\n";
        fout << "error: " << errr_dfx << "\n";
        fout<< "the central deriv is: "<< dcx << "\n";
        fout << "error: " << errr_dcx << "\n";
    }

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