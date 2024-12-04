#include <iostream>
#include <cmath>

using std::cout;
using fptr = double(double); //function pointer

double function(double x);
double trapezoid_estimation(double vmin, double vmax, long n ,fptr fun);

int main(int argc, char **argv){

    cout.precision(16);
    //cout.setf(std::ios::scientific); 


    if (argc != 4) {

        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " n\n";
        std::cerr << "vmin: the min valoe of the integral, vmax: the max value of the integral,n: the number of particions it is ussed\n";
        
        return 1;
    }

    double vmin = std::stold(argv[1]);
    double vmax = std::stold(argv[2]);
    long n = std::stol(argv[3]); //read input

    //double true_value = define_integral();
    double trapezoid_value = trapezoid_estimation(vmin, vmax, n, function);

    cout << "estimation trapezoid: " << trapezoid_value << "\n";
    //cout << "estimation error: " << compute_error(true_value,trapezoid_value) << "\n";

}


double function(double x){
    double result = x*x ;
    return result;
}

double trapezoid_estimation(double vmin, double vmax, long n ,fptr fun){
    double delta = (vmax - vmin)/(n);
    double sum = 0;

    //add last and firts intem
    sum = sum + fun(vmin);
    sum = sum + fun(vmax);

    for (int i = 1; i<n; i++ ){ //exclude firts and last intem
        sum = sum + 2*fun(vmin + delta*i) ;
    }

    return (delta/2)*sum;
}

