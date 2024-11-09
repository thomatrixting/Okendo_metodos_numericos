#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>
#include <algorithm>

using std::cout ;
using std::cin;

unsigned int ask_valid_n(void);
double pi_aprox(unsigned int);

int main(void){

    unsigned int n = ask_valid_n();


    return 0;
}

unsigned int ask_valid_n(void){
    bool valid_input = false;
    std::string input;
    unsigned int number;


    while (!valid_input){ //mientras el input  no sea valido
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

//double pi_aprox(unsigned int) {
   // unsigned double pi_estimation = 0;

   // for ()
//}
