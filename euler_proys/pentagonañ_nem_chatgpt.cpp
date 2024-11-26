#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <limits>

using std::cout;
using std::cerr;
using std::vector;
using std::unordered_set;

// Function to calculate the n-th pentagonal number
long calculate_pentagonal(long n) {
    return (n * (3 * n - 1)) / 2;
}

// Function to compute a list of pentagonal numbers up to a limit
vector<long> compute_pentagonal_list(long limit) {
    vector<long> pentagonal_list;
    for (long n = 1;; ++n) {
        long pentagonal = calculate_pentagonal(n);
        if (pentagonal > limit) break;
        pentagonal_list.push_back(pentagonal);
    }
    return pentagonal_list;
}

// Function to check if a number is pentagonal using a mathematical approach
bool is_pentagonal(long num) {
    if (num <= 0) return false;
    double n = (1 + sqrt(1 + 24 * num)) / 6;
    return n == (long)n;
}

// Function to find the pair of pentagonal numbers that satisfy the conditions
std::pair<long, long> find_pentagonal_pair() {
    long min_d = std::numeric_limits<long>::max();
    long pk_min = 0, pj_min = 0;

    for (long j = 1; ; ++j) {
        long pj = calculate_pentagonal(j);

        for (long k = j - 1; k > 0; --k) {
            long pk = calculate_pentagonal(k);
            long sum = pj + pk;
            long diff = pj - pk;

            if (is_pentagonal(sum) && is_pentagonal(diff)) {
                if (diff < min_d) {
                    min_d = diff;
                    pj_min = pj;
                    pk_min = pk;
                }
            }
        }
        if (pj - calculate_pentagonal(j - 1) > min_d) break; // Stop early if difference exceeds current min_d
    }
    return {pj_min, pk_min};
}

int main() {
    std::pair<long, long> result = find_pentagonal_pair();

    if (result.first != 0 && result.second != 0) {
        cout << "The pentagonal pair is: " << result.first << ", " << result.second << "\n";
        cout << "Their difference is: " << result.first - result.second << "\n";
    } else {
        cout << "No pentagonal pair found.\n";
    }

    return 0;
}
