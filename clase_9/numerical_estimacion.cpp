#include <iostream>
#include <cmath>

using std::cout;
using std::cerr;
using fptr = long double(long double); //function pointer
using algptr = long double(long double, long double, long,fptr);

long double function(long double x);
long double compute_error(long double true_value, long double estimated_value);
long double define_integral(long double vmin,long double vmax);
long double trapezoid_estimation(long double vmin, long double vmax, long n ,fptr fun);
long double simpsom_estimation(long double vmin, long double vmax, long n ,fptr fun);
long double richardson(const double vmin, const double vmax,const int p, const long n, fptr fun, algptr alg);

int main(int argc, char **argv){

    cout.precision(18);
    cout.setf(std::ios::scientific); 


    if (argc != 4) {

        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " n\n";
        std::cerr << "vmin: the min valoe of the integral, vmax: the max value of the integral,n: the number of particions it is ussed\n";
        
        return 1;
    }

    double vmin = std::stold(argv[1]);
    double vmax = std::stold(argv[2]);
    long n = std::stol(argv[3]); //read input

    long double true_value = define_integral(vmin,vmax);
    long double trapezoid_value = trapezoid_estimation(vmin, vmax, n, function);
    long double simpsom_value = simpsom_estimation(vmin, vmax, n, function);

    cout << "estimation trapezoid: " << trapezoid_value << "\n";
    cout << "estimation error: " << compute_error(true_value,trapezoid_value) << "\n";

    cout << "estimation simpsom: " << simpsom_value << "\n";
    cout << "estimation error: " << compute_error(true_value,simpsom_value) << "\n";
    
}


long double function(long double x){
    long double result = std::pow(x,2) ;
    return result;
}

long double define_integral(long double vmin,long double vmax){

    return (1./3.)*(std::pow(vmax,3) - std::pow(vmin,3));

}

long double compute_error(long double true_value, long double estimated_value){
    return std::fabs(1.0 - true_value/estimated_value);
}

long double trapezoid_estimation(long double vmin, long double vmax, long n ,fptr fun){
    long double delta = (vmax - vmin)/(n);
    long double sum = 0;

    //add last and firts intem
    sum = sum + fun(vmin);
    sum = sum + fun(vmax);

    for (int i = 1; i<n; i++ ){ //exclude firts and last intem
        sum = sum + 2*fun(vmin + delta*i) ;
    }

    return (delta/2)*sum;
}

long double simpsom_estimation(long double vmin, long double vmax, long n ,fptr fun){
    if (n%2 != 0){
        cerr << "Warning: trying to use n with odd n: " << n << "truncating value to n+1" << "\n";
        n = n+1;
    }

    long double delta = (vmax - vmin)/(n);
    long double sum = 0;

    //add last and firts intem
    sum = sum + fun(vmin);
    sum = sum + fun(vmax);

    for (int i = 1; i<n; i=i+2 ){ //exclude firts and last intem and iterate in odd numbers
        sum = sum + 4*fun(vmin + delta*i) ;
    }
    for (int i = 2; i<n; i=i+2 ){ //exclude firts and last intem and iterate in even numbers
        sum = sum + 2*fun(vmin + delta*i) ;
    }

    return (delta/3)*sum; 

}

long double richardson(const double vmin, const double vmax,const int p, const long n, fptr fun, algptr alg){
    long double aux = std::pow(p,2);
    
}