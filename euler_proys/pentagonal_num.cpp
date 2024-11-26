#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::cerr;

std::vector<long> compute_pentagonal_list_with_extra(long n); // compute until the list contains a number hieger that the sum of p_n + p_n-1
bool vector_contains(std::vector<long> vec, long target);

bool is_pentagonal(long i, std::vector<long> &pentagonal_list);
std::vector<long> search_pentagonal_pair(long n , std::vector<long> &pentagonal_list);

int main(int argc, char **argv) {

    long n = std::stoi(argv[1]);
    std::vector<long> pentagonal_list = compute_pentagonal_list_with_extra(n);
    std::vector<long> pair = search_pentagonal_pair(n,pentagonal_list);

    if ((pair[0] != 0) and (pair[1] != 0)){ //veryfy no error happenen

        cout << "the pentagonal pair is: " << pair[0] << " " <<pair[1]<<"\n";

    }
    else {
        cout << "no pentagonal peir found"<<"\n";
    }

    




}

std::vector<long> compute_pentagonal_list_with_extra(long n){

    std::vector<long> pentagonal_list;

    long limit = (6*(n*n) - 4*n + 2)/6;
    long term = 0;

    for (int i = 1; term <= limit; i++){
        term = (i * (3*i-1))/2;
        pentagonal_list.push_back( term );
    }



    return pentagonal_list;

}

bool vector_contains(std::vector<long> vec, long target){
    bool flag = 0;

    for (auto i : vec) {
      
        // If the target element found set the
      	// flag value 1 and break
        if (i == target) {
            flag = 1;
            break;
        }
    }

    // Check if the target value was found
    if (flag)
        return true;
    else
        return false;
}

bool is_pentagonal(long num) {
    if (num <= 0) return false;
    double n = (1 + sqrt(1 + 24 * num)) / 6;
    return n == (long)n;
}

std::vector<long> search_pentagonal_pair(long n , std::vector<long> &pentagonal_list){

    long count = 0;
    std::vector<long> pairs = {0,0};
    long diff = 1; 

    while (count < 100000){ //max interacion just in case

        for (long i = 0; i <= n-diff; i++){ //va hasta n porque los otros valores son solo para is pentagonal apra funcionar

            long sum_with_next = pentagonal_list[i] + pentagonal_list[i+diff];

            if (is_pentagonal(sum_with_next)){

                long delta = ( pentagonal_list[i+diff] - pentagonal_list[i] ); //todo add negative verificacion
                
                //cout << sum_with_next << " " << delta << "\n";

               if (is_pentagonal(delta)){
                    
                    pairs[0] = pentagonal_list[i];
                    pairs[1] = pentagonal_list[i+diff];

                    return pairs; //you found it

                }


            }
            
            count ++;

        }
        diff ++;

        if (diff > n-1){
            pairs = {0,0};
            return pairs;
        }

    }

    cerr << "error iteracion limit reach" << "\n";
    pairs = {0,0};
    return pairs;

}
