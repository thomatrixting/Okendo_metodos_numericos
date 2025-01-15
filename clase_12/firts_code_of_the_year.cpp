#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <fstream>



void check_args(int argc, char **argv);
void fill_randomly(std::vector<double> & vec);
void fill_vector_with_random_means(std::vector<double>& vec, int n);
void print_vector(const std::vector<double> & vec); //por referencia para que no cree una copia
void print_vector(const std::vector<double> & vec, std::string fname); //se puede hacer esto
void histogram(const std::vector<double> & vec, double xmin, double xmax, int nbins);


int main(int argc, char **argv) {
    check_args(argc, argv);
    const int N = std::stoi(argv[1]);

    // set the vector
    std::vector<double> data;
    data.resize(N);

    // fill the vector
    //print_vector(data);
    fill_vector_with_random_means(data,4);
    print_vector(data,"ramdom_data.txt");

    // histogram
    histogram(data, 0.0, 1.0, 10);

    return 0;
}

void check_args(int argc, char **argv)
{
    // read variables
    if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " N" << std::endl;
    std::cerr << "N: size of the vector" << std::endl;
    std::exit(1);
    }
}

void fill_randomly(std::vector<double> & vec)
{
    // setup the random number generation
    std::mt19937 gen(0); // gen, es un generador de bits aleatorios
    // y 0 es la semilla , para inicializar el estado
    std::normal_distribution<double> dis(0.5, 0.3);
    std::for_each(vec.begin(), vec.end(), [&dis, &gen](double &x){
        x = dis(gen);
    });
}

void fill_vector_with_random_means(std::vector<double>& vec, int n = 4) {
    // Setup the random number generation
    std::mt19937 gen(123); // Random bit generator
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Resize vector if needed (optional)
    if (vec.empty()) {
        throw std::invalid_argument("Vector must be pre-sized before calling this function.");
    }

    // Fill the vector with the means of `n` random numbers
    for (double& x : vec) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += dis(gen);
        }
        x = sum / n;
    }
}

//todo hacerlo con teorema del limite central

void print_vector(const std::vector<double> & vec)
{   
    auto print = [](const double & x){std::printf("%20.16e  ", x);};
    for_each(vec.begin(), vec.end(), print);
    std::printf("\n");
}

void print_vector(const std::vector<double> & vec, std::string fname)
{   

    std::ofstream fout(fname);

    fout.precision(18);
    fout.setf(std::ios::scientific);

    for (auto val : vec){
        fout << val << "\n";
    }
    fout << "\n";

}

void histogram(const std::vector<double> & vec, double xmin, double xmax, int nbins)
{
    std::vector<double> histo(nbins, 0.0);
    double dx = (xmax-xmin)/nbins;
    for (auto & x : vec) {
        // calcular el bin en el que cae
        int bin = int((x - xmin)/dx); // TODO chequeo del bin 
        if ( (0 <= bin) and (bin < nbins) ){
            histo[bin]++;
        }
        // aumentar el bin
  
    }
    
    std::ofstream fout("histogram.txt");
    fout.precision(18);
    fout.setf(std::ios::scientific);

    for (int ii=0; ii < nbins; ++ii){
        double x = xmin + ii*dx;
        fout << x << "\t" << histo[ii] << "\n";
    }
}
