#include <iostream>
#include <cmath>
#include <fstream>

using std::cout;
using std::sin;


using dfptr = double(double, double, double(double)); //deriv function pointer
using fptr = double(double); //function pointer

//function declaracions
double forward_deriv(double x, double h, fptr fun);
double central_deriv(double x, double h, fptr fun);
double richar(double x, double h, int p, dfptr deriv_algorithm, fptr fun); //recibe un puntereto a una funcion que come un double

double function(double x);
double fprime(double x);

double compute_error(double true_value, double estimated_value);

int main(int argc, char **argv){

    cout.precision(16);
    cout.setf(std::ios::scientific); 


    if (argc != 3) {

        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " x h\n";
        std::cerr << "x: the value were to perform de derivate h: the value of h for the estimacion of f\n";
        
        return 1;
    }

    double x = std::stod(argv[1]); //read input
    double h = std::stod(argv[2]);

    double df = fprime(x);

    double fd = forward_deriv(x,h,function);
    double fd_error = compute_error(df, fd);
    cout << "forward deriv: " << fd << "\n";
    cout << "error forward deriv: " << fd_error << "\n";    

    double cd = central_deriv(x,h,function);
    double cd_error = compute_error(df, cd);
    cout << "central deriv: " << cd << "\n";
    cout << "error central deriv: " << cd_error << "\n";    

    double fd_richar = richar(x,h,1,forward_deriv,function); //use P=1 as is the forward deriv
    double fd_richar_error = compute_error(df, fd_richar);
    cout << "forward richar deriv: " << fd_richar << "\n";
    cout << "error forward richar deriv: " << fd_richar_error << "\n";

    double cd_richar = richar(x,h,2,central_deriv,function); //use p=2 as is the central deriv
    double cd_richar_error = compute_error(df, cd_richar);
    cout << "central richar deriv: " << cd_richar << "\n";
    cout << "error central richar deriv: " << cd_richar_error << "\n";


}


double function(double x){
    return sin(x*x);
}

double fprime(double x){
    return 2*x*cos(x*x);
}


double forward_deriv(double x, double h, fptr fun){

    double denominator = fun(x+h) - fun(x);
    return denominator/h;

}
double central_deriv(double x, double h, fptr fun){

    double denominator = fun(x+h) - fun(x-h) ;
    return denominator/(2*h);

}


double richar(double x, double h, int p, dfptr deriv_algorithm, fptr fun) {

    double I = deriv_algorithm(x, h, fun );
    double I_2 = deriv_algorithm(x, h/2, fun );

    double denominator = std::pow(2,p) * I_2 - I;
    
    return denominator/( std::pow(2,p)-1 );

}

double compute_error(double true_value, double estimated_value){
    return std::fabs(1.0 - true_value/estimated_value);
}

