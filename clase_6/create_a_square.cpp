#include <iostream>
#include <string>

using std::cout;
using std::cin;

void printNchar(int n, char character);

int main(int nargs, char **args) {
    if (nargs != 3) {
        cout << "error you must enter only 2 arguments" << "\n";
        cout << nargs << "were entered" << "\n";
        return 1;
    }
    else {
        char character = args[1][0]; //why is this
	
        int length = std::stoi(args[2]);
        
        printNchar(length, character);
        cout << "\n";

        for (int i = 0; i < length - 2; i++) { 
            cout << character;
            printNchar(length - 2, ' ');
            cout << character << "\n";
        }

        printNchar(length, character);
        cout << "\n";
    }
}

void printNchar(int n, char character) {
    for (int i = 0; i < n; i++) {
        cout << character;
    }
}
