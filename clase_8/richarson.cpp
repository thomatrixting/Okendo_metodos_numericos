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
double forward_richar(double x, double h);
double central_richar(double x, double h);

int main(int argc, char **argv){

    if (argc != 2) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " x h\n";
        std::cerr << "x: the value were i want the derivate\n";
        
        return 1;
    }

    double x = std::stod(argv[1]);

    std::ofstream fout("datos.txt");

    fout.precision(16);
    fout.setf(std::ios::scientific); 

    fout << "h," << "forward_richard," << "error_forward,"  << "central_richard," << "error_central" << "\n";

    for (double h = 1.0; h >= 1.0e-16;h = h/10.0){

        double fp = fprime(x);

        double idfx = forward_richar(x,h);
        double errr_idfx = std::fabs(1.0 - fp/idfx);

        double idcx = central_richar(x,h);
        double errr_idcx = std::fabs(1.0 - fp/idcx);
        fout << h << ",";
        fout << idfx << ",";
        fout << errr_idfx <<",";
        fout << idcx << ",";
        fout << errr_idcx << "\n";

    }
    fout.close();
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

double forward_richar(double x, double h){
    int p = 1; //for forward 
    //f(x) = sen²x

    double I = forward_deriv(x,h);
    double I_2 = forward_deriv(x,h/2);
    
    double denominator = std::pow(2,p) * I - I_2;
    
    return denominator/( std::pow(2,p)-1 );

}

double central_richar(double x, double h){
    int p = 2; //for central 
    //f(x) = sen²x

    double I = central_deriv(x,h);
    double I_2 = central_deriv(x,h/2);
    
    double denominator = std::pow(2,p) * I - I_2;
    
    return denominator/( std::pow(2,p)-1 );
}