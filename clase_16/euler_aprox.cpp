#include<iostream>
#include<vector>
#include<valarray>

void check_args(int argc, char **argv);
void euler (const int i, const double delta, std::valarray<double> &state_vec); 
void print_system (const int i, const double delta, const std::valarray<double> &state_vec);
void deriv(const double time, const std::valarray<double> &state_vec, std::valarray<double> &dsdt);

const double g = 9.81;

int main(int argc, char **argv){

    check_args(argc,argv);

    std::valarray<double> state_vec(2);

    state_vec[0] = std::stod(argv[1]);
    state_vec[1] = std::stod(argv[2]);
    int n = std::stoi(argv[3]);
    
    const double delta = 0.1 ;

    std::cout << "ttime: 0 " << "y: " << state_vec[0] << "v: " << state_vec[1] << "\n";

    for (int i=0; i < n;i++){

        euler(i,delta,state_vec);

        print_system(i,delta,state_vec);

    }


}

void check_args(int argc, char **argv)
{
    // read variables
    if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << "y v i" << std::endl;
    std::cerr << "y: inicial position on y axis v: inicial velociti on y axis, i: #iteracions" << std::endl;
    std::exit(1);
    }
}

void euler (const int i, const double delta, std::valarray<double> &state_vec){

    std::valarray<double> dsdt (state_vec.size());
    double time =  i*delta;

    deriv(time,state_vec,dsdt);

    state_vec = state_vec + delta*dsdt;

}

void deriv(const double time, const std::valarray<double> &state_vec, std::valarray<double> &dsdt){
    dsdt[0] = state_vec[1];
    dsdt[1] = -g;
}

void print_system (const int i, const double delta, const std::valarray<double> &state_vec){

    std::cout << "time: " << i*delta << " ";
    std::cout << "y: " << state_vec[0] << "v: " << state_vec[1] << "\n";

}
