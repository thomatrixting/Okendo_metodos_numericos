#include <iostream> 
#include <vector> //there is literally not other way to handle arrays

using std::cout;
std::vector<long unsigned int> fibonachi(long unsigned int number);
long unsigned int sum_odd_terms(std::vector<long unsigned int> vector);

int main(int argc, char **argv){

    if (argc != 2) {
        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " n\n";
        std::cerr << "n : highest term in fibonachi secuence\n";
        return 1;
    }    

    long unsigned int n = std::stoul(argv[1]); // Change to stoul for unsigned long
    if (n < 2) {//negacion of i >=2
        std::cerr << "ERROR. index of fiboncachi succecion shoud be more or equal to 2\n";
        std::cerr << "index: "<< n << " were given\n";

    }


    std::vector<long unsigned int> fibonachi_secuence = fibonachi(n);
    long unsigned int sumatory_of_odd_fibonachi = sum_odd_terms(fibonachi_secuence);


    cout << "Sum of odds numbers on fibonachi secuence: " << sumatory_of_odd_fibonachi << "\n";

    return 0;
}

std::vector<long unsigned int> fibonachi(long unsigned int limit){

    std::vector<long unsigned int> fibonachi_secuecne = {1,2};
    int i = 0;
    unsigned long int sum;

    while (i <= 94){ //acording to wolfran alpha on the 94th index of the fibonachi succecion the value is greater than the numeric limit of long unsign int
        sum = fibonachi_secuecne[i] + fibonachi_secuecne[i+1];

        if (sum<=limit){
            fibonachi_secuecne.push_back(sum);
        }
        else{
            return fibonachi_secuecne;
        }

        i = i + 1;
    }

    std::cerr << "ERROR. Numeric limit reach for fibonachi secuence:\n";
    std::cerr << "hieghest term computed: "<< sum << " \n"; 
    return fibonachi_secuecne;
}

long unsigned int sum_odd_terms(std::vector<long unsigned int> vector){
    long unsigned int sum = 0;
    auto limit = vector.size();

    for (long unsigned int i=0; i< limit; i++){
        if (vector[i] % 2 != 0){
            sum = vector[i] + sum;
        }
    }
    return sum;
}