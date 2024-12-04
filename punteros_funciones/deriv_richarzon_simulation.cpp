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

void make_simulation(double x);

int main(int argc, char **argv){

    if (argc != 2) {

        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " x\n";
        std::cerr << "x: the value were to perform de derivate \n";
        
        return 1;
    }

    double x = std::stod(argv[1]); //read input

    make_simulation(x);
}

void make_simulation(double x){

    std::ofstream fout("datos.txt");

    fout.precision(16);
    fout.setf(std::ios::scientific); 

    double df = fprime(x);

    fout << "h,forward_deriv,error_forward_deriv,central_deriv,error_central_deriv,forward_richard_deriv,error_forward_richard_deriv,central_richard_deriv,error_central_richard_deriv"<< "\n"; //header

    for (double h = 1.0; h >= 1.0e-16;h = h/10.0){
        fout << h << ",";

        double fd = forward_deriv(x,h,function);
        double fd_error = compute_error(df, fd);
        fout << fd << ",";
        fout << fd_error << ",";    

        double cd = central_deriv(x,h,function);
        double cd_error = compute_error(df, cd);
        fout << cd << ",";
        fout << cd_error << ",";    

        double fd_richar = richar(x,h,1,forward_deriv,function); //use P=1 as is the forward deriv
        double fd_richar_error = compute_error(df, fd_richar);
        fout << fd_richar << ",";
        fout << fd_richar_error << ",";

        double cd_richar = richar(x,h,2,central_deriv,function); //use p=2 as is the central deriv
        double cd_richar_error = compute_error(df, cd_richar);
        fout <<  cd_richar << ",";
        fout <<  cd_richar_error << "\n";
    }

    fout.close();
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

