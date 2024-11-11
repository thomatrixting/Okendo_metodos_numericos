#include <iostream>
#include <cmath>
#include <numbers>
#include <string>
#include <stdexcept>
#include <algorithm>

using std::cout;
using std::cin;

const unsigned int PRECISION = 15; //as MI_PI is a double and have a precision of 15 decimal places

unsigned int ask_valid_n(void);
double pi_aprox(unsigned int n, bool print_values);
double compute_error(double computed_value, double true_value, unsigned int relevant_decimal_places, bool print_values);

int main(void) {
    double scale_factor = std::pow(10, 15);
    for (int n = 0; n <= 20; n++) {
        double pi_estimation = pi_aprox(n, false);
        double error = compute_error(pi_estimation, M_PI, PRECISION,false);

        cout << "pi estimation for n: " << n << "\n";

        // Print pi_estimation in scientific notation with the given decimal places
        cout.precision(PRECISION);
        cout.setf(std::ios::scientific);
        cout << pi_estimation << " ";

        // Print error with 2 decimal places truncate it
        cout.precision(5);
        cout << "error: " << error << "%\n";

    }
    return 0;
}


unsigned int ask_valid_n(void){
    bool valid_input = false;
    std::string input;
    unsigned int number;


    while (!valid_input){ //while inoput is valid
        cout << "please type a positive integer for the number of sums to estimate pi: " << "\n";
        cin >> input;

        if (input.length() > 20){
                  cout << "maximun lenght for the input reach please try again " << "\n\n";
                continue;
        }

        input.erase(std::remove(input.begin(), input.end(), '-'), input.end()); //remove a - in case there are

        try {
            number = std::stoi(input);
        }
        catch (const std::exception& e) {
            cout << "error while interpreting input please try again \n what(): " << e.what() << "\n\n";
            continue;
        }


        cout << "your input was interpreted as : " << number << "\n\n";
        valid_input = true;
    }

    return number;
} 

double pi_aprox(unsigned int n, bool print_values) {
    double pi_estimation = 0;
    
    double instance_value = 0;
    for (float k = 0; k <= n; k++){

        double f1 = 4 / (8*k+1);
        double f2 = 2 / (8*k+4);
        double f3 = 1 / (8*k+5);
        double f4 = 1 / (8*k+6);
        
        double multiplier = 1 / std::pow(16,k);

        instance_value = multiplier*(f1-f2-f3-f4); //is beter to declare the computacion in steps or make it all at once?

        pi_estimation += instance_value;
    }
    if (print_values){
        cout.precision(PRECISION); //as pi have a presicion of 15 decimal numbers on c++ ussing double
        cout.setf(std::ios::scientific);
        cout << "the estimation of pi is: " << pi_estimation << "\n";

    }


    return pi_estimation;
}

#include <cmath>

double compute_error(double computed_value, double true_value, unsigned int relevant_decimal_places, bool print_values) {
    // Scale values by 10^relevant_decimal_places and truncate by casting to int
    double scale_factor = std::pow(10, relevant_decimal_places);
    double scaled_computed = static_cast<long int>(computed_value * scale_factor) ;
    double scaled_true = static_cast<long int>(true_value * scale_factor) ;

    // Compute error
    double error = std::abs(scaled_computed - scaled_true) / scaled_true;

    // Print error if requested
    if (print_values) {
        std::cout.precision(relevant_decimal_places);
        std::cout << std::fixed;
        std::cout << "The error of the estimation is: " << error << "\n";
    }

    return error;
}
