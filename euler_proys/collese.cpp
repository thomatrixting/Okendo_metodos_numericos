#include <iostream>
#include <vector>

using std::cout;
using std::cerr;

const unsigned int vmin = 1;

// Function to compute Collatz sequence steps for a number
unsigned int collatz_sequence(unsigned long n, std::vector<unsigned long>& steps_dictionary);


int main(int argc, char **argv) {

    unsigned int vmax = std::stoi(argv[1]);

    // Initialize the steps dictionary and its size
    std::vector<unsigned long> steps_dictionary(vmax + 1); // Pre-allocate memory

    unsigned int max_steps_n = 0;
    unsigned int max_steps_value = 0;

    unsigned int current_steps_value;
    for (unsigned int i = vmin; i <= vmax; i++) {
        current_steps_value = collatz_sequence(i, steps_dictionary);

        if (current_steps_value > max_steps_value) {
            max_steps_n = i;
            max_steps_value = current_steps_value;
        }
    }

    cout << "Max steps: " << max_steps_value << " with n: " << max_steps_n << "\n";

    return 0;
}

unsigned int collatz_sequence(unsigned long n, std::vector<unsigned long>& steps_dictionary) {
    unsigned long original_n = n; // Save the original value of n
    unsigned int steps = 0;

    while (n > 1) {
        if (n < steps_dictionary.size() && steps_dictionary[n] != 0) {
            // If the value is precomputed, add it and break
            steps += steps_dictionary[n];
            break;
        }

        if (n % 2 == 0) {
            n = n / 2; // Even case
        } else {
            n = 3 * n + 1; // Odd case
        }

        steps++;
    }

    // Store the computed steps for the original number
    if (original_n < steps_dictionary.size()) {
        steps_dictionary[original_n] = steps;
    }

    return steps;
}