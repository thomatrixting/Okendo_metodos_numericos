// Implements a simple linear congruential generator (LCG)
// to generate random numbers.

#include <string>
#include <fstream>
#include <iostream>

struct LCG {
	unsigned long long x;
	unsigned long long a;
	unsigned long long c;
	unsigned long long m;
};

int main(int argc, char **argv) {

	if (argc != 7) {
		std::cerr << "Usage: " << argv[0] << " <seed> <a> <c> <m> <NSAMPLES> <OUT_FNAME>" << std::endl;
		return 1;
	}

	LCG lcg;
	lcg.x = 2*std::stoull(argv[1]); // the seed acts as initial value
	lcg.a = std::stoull(argv[2]);
	lcg.c = std::stoull(argv[3]);
	lcg.m = std::stoull(argv[4]);
	const int NSAMPLES = std::stoull(argv[5]);
	const std::string fname = std::string(argv[6]);
	const int NCOLS = 3;

	std::ofstream fout(fname);
	
    unsigned long long x_1 = lcg.x;

    for(int i = 0; i < NSAMPLES; i++){
        for(int j = 0; j < NCOLS; j++){

            fout << x_1 << "\t";
            x_1 = (lcg.a*x_1 + lcg.c)%lcg.m;

        }
        fout << "\n";
    }

	fout.close();

	return 0;
}