

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <map>

using param_t = std::map<std::string, double> ;

void check_args(int argc, char **argv);
void generate_samples(int seed, int nsamples, param_t &p);

int main(int argc, char **argv)
{
	check_args(argc, argv);
	param_t params; // Store the read params here

	const int SEED = std::stoi(argv[1]);;
	const int SAMPLES = std::stoi(argv[2]);
	params["A"] = std::stod(argv[3]);;
	params["B"] = std::stod(argv[4]);

	generate_samples(SEED, SAMPLES, params);

	return 0;
}

void check_args(int argc, char **argv)
{
	if (5 != argc) {
		std::cerr << "Error. Usage: \n" << argv[0] << " SEED SAMPLES A B\n";
		exit(1);
	}
}

void generate_samples(int seed, int nsamples, param_t &p)
{
    std::mt19937 gen(seed); 
    std::uniform_real_distribution<> dis(p["A"], p["B"]);

    for (int i=0; i < nsamples; i++){
        std::cout << dis(gen) << "\n";
    }
}
