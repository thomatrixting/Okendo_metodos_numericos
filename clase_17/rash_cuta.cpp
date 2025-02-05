//std= c++17
#include <iostream>
#include <vector>
#include <valarray>
#include <fstream>

void check_args(int argc, char **argv);
void euler(const int i, const double delta, std::valarray<double> &state_vec);
void deriv(const std::valarray<double> &state_vec, std::valarray<double> &dsdt);
void runge_kutta4(double delta_t, std::valarray<double> &state_vec);
double compute_mecanical_energy(const std::valarray<double> &state_vec);
void simulacion(double T_inicial, double T_final, double dt, const std::string &filename, std::valarray<double> &state_vec);

const double G = 9.81;
const double MASS = 1;
const double W = 1;


int main(int argc, char **argv) {
    check_args(argc, argv);

    double T_inicial = std::stod(argv[1]);
    double T_final = std::stod(argv[2]);
    double dt = std::stod(argv[3]);
    std::string filename = argv[6];

    // Inicialización del estado
    std::valarray<double> state_vec(2);
    state_vec[0] = std::stod(argv[4]);  // Posición inicial en x
    state_vec[1] = std::stod(argv[5]); // Velocidad inicial

    simulacion(T_inicial, T_final, dt, filename, state_vec);

    return 0;
}

void check_args(int argc, char **argv) {
    if (argc != 7) {
        std::cerr << "Uso: " << argv[0] << " T_inicial T_final dt x_incial V_incial archivo_salida.csv" << std::endl;
        std::cerr << "T_inicial: tiempo inicial, T_final: tiempo final, Y_incial: altura inicial, V_incial: velocidad incial" << std::endl;
        std::cerr << "dt: incremento de tiempo, archivo_salida.csv: nombre del archivo donde se guardarán los datos" << std::endl;
        std::exit(1);
    }
}

void euler(const int i, const double delta, std::valarray<double> &state_vec) {
    std::valarray<double> dsdt(state_vec.size());
    deriv(state_vec, dsdt);

    state_vec = state_vec + delta * dsdt;
}


// Function to compute derivatives
void deriv(const std::valarray<double> &state_vec, std::valarray<double> &dsdt) {
    dsdt[0] = state_vec[1]; // dx/dt = velocity
    dsdt[1] = -W*W * state_vec[0];           // dv/dt = acceleration due to gravity
}

// Runge-Kutta 4th Order Method
void runge_kutta4(double delta_t, std::valarray<double> &state_vec) {
    std::valarray<double> k1(state_vec.size()), k2(state_vec.size()), 
                          k3(state_vec.size()), k4(state_vec.size());

    deriv(state_vec, k1); // Compute k1
    std::valarray<double> temp = state_vec + (delta_t / 2.0) * k1;
    deriv(temp, k2); // Compute k2
    
    temp = state_vec + (delta_t / 2.0) * k2;
    deriv(temp, k3); // Compute k3

    temp = state_vec + delta_t * k3;
    deriv(temp, k4); // Compute k4

    // Update state
    state_vec += (delta_t / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
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

    file << "time,y_k4,v_k4,y_euler,v_euler\n";

    file << "0," << state_vec[0] << "," << state_vec[1] << "," << state_vec[0] << "," << state_vec[1] << "\n";

    int n = (T_final - T_inicial) / dt;

    for (int i = 0; i <= n; i++) {
        double time = i * dt + T_inicial;

        file << time << ",";

        std::valarray<double> state_vec_for_euler = state_vec;

        runge_kutta4(dt,state_vec);
        file << state_vec[0] << "," << state_vec[1]<< ",";

        euler(i,dt,state_vec_for_euler);
        file << state_vec_for_euler[0] << "," << state_vec_for_euler[1] << "\n";

    }

    file.close();
}