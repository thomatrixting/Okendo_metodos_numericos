#include <iostream> 
#include <cmath>
#include <fstream>

# define LOG_2 0.6931471805599453094172321L //with enought decimal places

using std::cout; //this is not a bad practice the profersor itself say it
using std::cerr;

double sumn(int limit);
double tn1(int n);
double tn2(int n);
long double compute_error(long double computed_value, long double true_value);

int main(){
    
    cout.setf(std::ios::scientific);
    cout.precision(10);

    cout << sumn(400) << "\n";
    cout << tn1(400) << "\n";
    cout << tn2(400) << "\n";

    cout << sumn(800) << "\n";
    cout << tn1(800) << "\n";
    cout << tn2(800) << "\n";

    cout << sumn(3200) << "\n";
    cout << tn1(3200) << "\n";
    cout << tn2(3200) << "\n";
    
    cout << "printing values from 100 to 10000";

    std::ofstream fout("datos.csv");
    fout << "n," << "error_sumn," << "error_tn1," << "error_tn2," << "\n";

    for (int n = 100; n <= 10000; n = n + 100){

        long double sumn_value = sumn(n);
        long double sumn_error = compute_error(sumn_value,LOG_2);   

        long double tn1_value = tn1(n);
        long double tn1_error = compute_error(tn1_value,LOG_2);   

        long double tn2_value = tn2(n);
        long double tn2_error = compute_error(tn2_value,LOG_2);   

        fout << n << "," << sumn_error << "," << tn1_error << "," << tn2_error << "\n";

    }
    fout.close();



    return 0;    
}


double sumn(int limit){
    long double sumatory = 0.0;//to have more exact calulus
    int sign = 1;
    for(int i = 0; i <= limit; i++){

        if (i%2 == 0){ //if it is odd
            sign = 1; //denominates the sign
        } else {
            sign = -1;
        }

        sumatory  = sumatory + sign*(1./(i+1)); //1. denotades the division as double

    }
    

    return sumatory;

}

double tn1(int n) {
    //make the aprox
    long double sum_n = sumn(n);
    long double sum_n_1 = sumn(n+1);
    long double sum_n_2 = sumn(n+2);
    //make the computing
    long double numerator = ( std::pow( (sum_n_1 - sum_n) ,2) ); //²
    long double denominator = ( sum_n_2 - 2*sum_n_1 + sum_n);

    return sum_n - (numerator/denominator);

}
double tn2(int n) {
    //make the aproximations
    long double t_n = tn1(n);
    long double t_n_1 = tn1(n+1);
    long double t_n_2 = tn1(n+2);
    //make the computing
    long double numerator = ( std::pow( ( t_n_1 - t_n) ,2) ); //²
    long double denominator = ( t_n_2 - 2*t_n_1 + t_n);

    return t_n - (numerator/denominator);

}

long double compute_error(long double computed_value, long double true_value) {

    long double error = std::abs(computed_value - true_value) / true_value; //compute the relative error
    //the error will get stuck at the max presicion as each new sum from this point cannot be represented accurally so it cannot inpact meaningfully the computing

    return error;
}