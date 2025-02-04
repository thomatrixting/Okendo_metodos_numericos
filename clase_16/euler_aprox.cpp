#include <iostream>
#include <vector>
#include <valarray>
#include <fstream>

void check_args(int argc, char **argv);
void euler(const int i, const double delta, std::valarray<double> &state_vec);
void deriv(const double time, const std::valarray<double> &state_vec, std::valarray<double> &dsdt);
double compute_mecanical_energy(const std::valarray<double> &state_vec);
void simulacion(double T_inicial, double T_final, double dt, const std::string &filename, std::valarray<double> &state_vec);

const double G = 9.81;
const double MASS = 1;

int main(int argc, char **argv) {
    check_args(argc, argv);

    double T_inicial = std::stod(argv[1]);
    double T_final = std::stod(argv[2]);
    double dt = std::stod(argv[3]);
    std::string filename = argv[4];

    // Inicialización del estado
    std::valarray<double> state_vec(2);
    state_vec[0] = 2.0;  // Posición inicial en y
    state_vec[1] = 10.0; // Velocidad inicial

    simulacion(T_inicial, T_final, dt, filename, state_vec);

    return 0;
}

void check_args(int argc, char **argv) {
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " T_inicial T_final dt archivo_salida.csv" << std::endl;
        std::cerr << "T_inicial: tiempo inicial, T_final: tiempo final" << std::endl;
        std::cerr << "dt: incremento de tiempo, archivo_salida.csv: nombre del archivo donde se guardarán los datos" << std::endl;
        std::exit(1);
    }
}

void euler(const int i, const double delta, std::valarray<double> &state_vec) {
    std::valarray<double> dsdt(state_vec.size());
    double time = i * delta;

    deriv(time, state_vec, dsdt);

    state_vec = state_vec + delta * dsdt;
}

void deriv(const double time, const std::valarray<double> &state_vec, std::valarray<double> &dsdt) {
    dsdt[0] = state_vec[1];
    dsdt[1] = -G;
}

double compute_mecanical_energy(const std::valarray<double> &state_vec) {
    return MASS * (state_vec[0] * G + 0.5 * state_vec[1] * state_vec[1]);
}

void simulacion(double T_inicial, double T_final, double dt, const std::string &filename, std::valarray<double> &state_vec) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        std::exit(1);
    }

    file << "time,y,v,energy\n";

    double mecanical_energy = compute_mecanical_energy(state_vec);
    file << "0," << state_vec[0] << "," << state_vec[1] << "," << mecanical_energy << "\n";

    int n = (T_final - T_inicial) / dt;

    for (int i = 0; i < n; i++) {
        euler(i, dt, state_vec);
        mecanical_energy = compute_mecanical_energy(state_vec);
        file << (i + 1) * dt << "," << state_vec[0] << "," << state_vec[1] << "," << mecanical_energy << "\n";
    }

    file.close();
}
