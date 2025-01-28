#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    // Define two vectors
    std::vector<double> v1 = {1, 2, 3, 4, 5, 6};
    std::vector<double> v2 = {1, 2, 3, 4, 5, 6};

    // Use std::inner_product to compute the dot product
    double dot_product = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);

    // Output the result
    std::cout << "The dot product is: " << dot_product << std::endl;


    //norm of a vector
    double norm_result = 0;
    auto norm = [&norm_result]( double &x){norm_result+=x*x;};
    std::for_each(v1.begin(),v1.end(),norm);

    std::cout << norm_result << "\n";

    // print the array
    auto print = [](const double & x){ std::cout << x << "  ";};
    std::for_each(v1.begin(), v1.end(), print);
    std::cout << "\n";

    //product again 
    auto square_next = [](double a,double b){
        std::cout << a << "," << b << "\n";
        return a + b*b;
        };
    double product = std::accumulate(v1.begin(), v1.end(), 0, square_next);
    std::cout << product << "\n";

}
