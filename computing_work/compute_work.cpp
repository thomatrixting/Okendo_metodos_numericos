#include <iostream>
#include <cmath>
#include <vector>
#include <functional> //for ussing the datatpy function on a vector
#include <fstream>
#include <string>

using std::cout;
using std::cerr;
using std::sqrt;
using std::vector;

using fptr = long double(long double); //function f(a)=b
using rfptr = long double (*)(long double); //define datatype of pointer for vectors

const long double OBJECT_MASS = 1.2345;

void run_simuation(long double vmax, long double step, std::string file_name);
long double estimate_velocity(long double x); //make all the esimacion for a given x between 0 and 1

long double compute_y_displacement(const long double x);
long double compute_velocity_given_work(const long double work, const long double mass);
long double integrate_vectorial_function_gauss5(const std::vector<rfptr>& vectorial_function, const vector<vector<long double>> integration_limits);
long double gauss5(fptr fun, const long double a, const long double b);

long double force_x_function(const long double t);
long double force_y_function(const long double t);

int validate_args(int argc, char* argv[]);


int main(int argc, char **argv){

    cout.precision(18);
    cout.setf(std::ios::scientific); 

    if (validate_args(argc, argv) != 0) {
        return 1;
    }

    long double vmax = std::stold(argv[1]);
    long double step = std::stold(argv[2]);
    std::string file_name = argv[3];

    run_simuation(vmax,step,file_name);

    return 0;
}

void run_simuation(long double vmax, long double step, std::string file_name){
    std::ofstream fout(file_name);

    fout.precision(18);
    fout.setf(std::ios::scientific);

    fout<<"x, velocity\n";

    for( long double x=0; x<vmax; x += step){
        long double y = compute_y_displacement(x);

        vector<vector<long double>> integracion_limits =    {{0,x},
                                                            {0,y}};
        //as the interval of x is [0,1] and y also stars at 0 when x=0 the integracion limits stars at 0

        std::vector<rfptr> F_vectorial = {force_x_function, force_y_function};

        long double work = integrate_vectorial_function_gauss5(F_vectorial,integracion_limits);
        long double velocity = compute_velocity_given_work(work, OBJECT_MASS);

        fout << x << ",";
        fout << velocity << "\n";

    }
}

long double estimate_velocity(long double x){
    if ( !( (0<x) and (x <= 1) ) ){ //si x no esta dentreo del intevalo x (0,1] // no se incluye 0 porque genera error
        cerr << "x value is not on interval (0,1] were computacion can be perform returning 0 for the estiamcion of the velocity" << "\n";
        cerr << "value of x: "<< x << "\n";
        return 0;
    }


    long double y = compute_y_displacement(x);

    vector<vector<long double>> integracion_limits =    {{0,x},
                                                         {0,y}};
    //as the interval of x is [0,1] and y also stars at 0 when x=0 the integracion limits stars at 0

    std::vector<rfptr> F_vectorial = {force_x_function, force_y_function}; //safe a vector of functions

    long double work = integrate_vectorial_function_gauss5(F_vectorial,integracion_limits);
    long double velocity = compute_velocity_given_work(work, OBJECT_MASS); 

    return velocity;

}

long double compute_y_displacement(const long double x){
    return x - std::pow(x,2); //y = x(1-x);
}

long double compute_velocity_given_work(const long double work, const long double mass){
    return sqrt((work*2)/mass);
}

long double integrate_vectorial_function_gauss5(const std::vector<rfptr>& vectorial_function, const vector<vector<long double>> integration_limits){
    
    if ( (vectorial_function.size() != integration_limits.size()) or (integration_limits[0].size() != 2) ) { //verify is the number of limits is the same of the function or verify only for the fists entry limit have only 2 values as there is only a and b
        cerr << "ERROR: The size of vectorial_function and integration_limits must match, revise the input before attenting to integrate again returning 0 for the integral.\n";
        cerr << "vectorial function size: " << vectorial_function.size() << " integracion limits: " << integration_limits.size() << "\n";
        cerr << "size of firts element: " << integration_limits[0].size() << "\n";

        return 0;
    }


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
    
    vector<long double> X = { //the point were the integral is perform that is why is call X as it denotated a dataset in stadistics
        - (1./3.)*( sqrt( 5. - 2* ( sqrt(10./7.) ) ) ) ,         
          (1./3.)*( sqrt( 5. - 2* ( sqrt(10./7.) ) ) ) , 
        - (1./3.)*( sqrt( 5. + 2* ( sqrt(10./7.) ) ) ) , 
          (1./3.)*( sqrt( 5. + 2* ( sqrt(10./7.) ) ) ) , 
         0
    };
    
    vector<long double> W = { //for the weights
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


long double force_x_function(const long double t){
    return std::log( sqrt( t +1) );
}
long double force_y_function(const long double t){
    return std::sin( std::pow(t,2) );
}

int validate_args(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " vmax step file_name\n";
        std::cerr << "vmax (0,1]: a non-zero value between 0 and 1 for the ending displacement in which to end the simulation\n";
        std::cerr << "step (0,1): a positive value less than 1 in which x will increase per iteration\n";
        std::cerr << "file_name: the name of the file where to save the simulation data (recommended with .csv extension)\n";
        return 1;
    }

    long double vmax = std::stold(argv[1]);
    long double step = std::stold(argv[2]);


    if (!(0 < vmax && vmax <= 1)) {
        std::cerr << "vmax value is not in the interval (0,1] where computation can be performed\n";
        std::cerr << "Value of vmax: " << vmax << "\n";
        return 1;
    }

    if (!(0 < step && step < 1)) {
        std::cerr << "step value is not in the interval (0,1) where computation can be performed\n";
        std::cerr << "Value of step: " << step << "\n";
        return 1;
    }

    return 0;
}