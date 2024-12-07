#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <fstream>

using std::cout;
using std::cerr;
using std::sqrt;
using std::vector;

using fptr = long double(long double); //function f(a)=b
using rfptr = long double (*)(long double); //define datatype of pointer for vectors

const long double object_mass = 1.2345;

long double compute_y_displacement(const long double x);
long double integrate_vectorial_function_gauss5(const std::vector<rfptr>& vectorial_function, const vector<vector<long double>> integration_limits);
long double gauss5(fptr fun, const long double a, const long double b);
long double compute_velocity(const long double work, const long double mass);

long double force_x_function(long double t);
long double force_y_function(long double t);


int main(int argc, char **argv){

    if (argc != 1) {

        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << "\n";
        std::cerr << "no argument\n";
        
        return 1;
    }

    std::ofstream fout("datos.csv");

    fout.precision(18);
    fout.setf(std::ios::scientific);

    fout<<"x, velocity\n";

    for( long double x=0.01; x<1; x += 0.01){
        long double y = compute_y_displacement(x);

        vector<vector<long double>> integracion_limits =    {{0,x},
                                                            {0,y}};
        //as the interval of x is [0,1] and y also stars at 0 when x=0 the integracion limits stars at 0

        std::vector<rfptr> F_vectorial = {force_x_function, force_y_function};

        long double work = integrate_vectorial_function_gauss5(F_vectorial,integracion_limits);
        long double velocity = compute_velocity(work, object_mass);

        fout << x << ",";
        fout << velocity << "\n";

    }

    return 0;
}


long double compute_y_displacement(const long double x){
    return x - std::pow(x,2); //y = x(1-x);
}

long double integrate_vectorial_function_gauss5(const std::vector<rfptr>& vectorial_function, const vector<vector<long double>> integration_limits){
    //TODO veryfy bopth vector have the same size
    long double sum = 0;
    long double value = 0; 
    for (int i=0; i <= integration_limits.size()-1; i++){
        value = gauss5(vectorial_function[i],integration_limits[i][0], integration_limits[i][1]);
        //integracion limits its formated as each line is the corresponding [a,b] limits of the integracion
        sum = sum + value;
    }
    return sum;
}


long double gauss5(fptr fun, long double a, long double b){
    
    vector<long double> X = {
        - (1./3.)*( sqrt( 5. - 2* ( sqrt(10./7.) ) ) ) ,         
          (1./3.)*( sqrt( 5. - 2* ( sqrt(10./7.) ) ) ) , 
        - (1./3.)*( sqrt( 5. + 2* ( sqrt(10./7.) ) ) ) , 
          (1./3.)*( sqrt( 5. + 2* ( sqrt(10./7.) ) ) ) , 
         0
    };
    
    vector<long double> W = {
        (322. + 13.* sqrt(70))/900. ,
        (322. + 13.* sqrt(70))/900. ,
        (322. - 13.* sqrt(70))/900. ,
        (322. - 13.* sqrt(70))/900. ,
        128./225.
    };

    long double sum = 0;

    const long double aux1 = (a+b)/2.;
    const long double aux2 = (b-a)/2.;

    for(int i=0; i <= X.size()-1; i++){

        sum = sum + W[i]*fun(
            (aux2)*X[i] + (aux1)
        );

    }

    return (aux1)*sum;
}

long double compute_velocity(const long double work, const long double mass){
    return sqrt((work*2)/mass);
}

long double force_x_function(long double t){
    return std::log( sqrt(t+1) );
}
long double force_y_function(long double t){
    return std::sin( std::pow(t,2) );
}