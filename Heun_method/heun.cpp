//std= c++17
#include <iostream>
#include <vector>
#include <valarray>
#include <fstream>
#include <functional> //in orther to use function pointers with the & of reference

using std::valarray;
using derivation_funct = std::function<void(const valarray<double>&, valarray<double>&)>;
using solver_funct = std::function<void(const double, valarray<double>&, derivation_funct)>;

void check_args(int argc, char **argv);

void euler(const double delta, std::valarray<double>& state_vec, derivation_funct derivate);
void solve_heun(const double delta, std::valarray<double>& state_vec, derivation_funct derivate);

void simulacion(double T_inicial, double T_final, double dt, std::valarray<double>& state_vec, 
                derivation_funct derivate, solver_funct solver, std::string file_name);


class deriv {
    double angular_vel;

public:
    deriv(double w) : angular_vel(w) {}

    void operator()(const std::valarray<double>& state_vec, std::valarray<double>& dsdt) const {
        dsdt[0] = state_vec[1];
        dsdt[1] = -angular_vel * angular_vel * state_vec[0];
    }
};

void euler(const double delta, std::valarray<double>& state_vec, derivation_funct derivate) {
    std::valarray<double> dsdt(state_vec.size());
    derivate(state_vec, dsdt);
    state_vec += delta * dsdt;
}

int main(int argc, char **argv) {
    check_args(argc, argv);

    try {
        double dt = std::stod(argv[1]);
        double T_inicial = std::stod(argv[2]);
        double T_final = std::stod(argv[3]);
        double w = std::stod(argv[4]);

        std::valarray<double> state_vec(2);
        state_vec[0] = 2.0;
        state_vec[1] = 0.0;

        deriv derivate(w);

        std::valarray<double> state_vec_euler = state_vec;
        std::valarray<double> state_vec_heun = state_vec;

        simulacion(T_inicial, T_final, dt, state_vec_euler, std::ref(derivate), euler, "output-euler.txt");
        simulacion(T_inicial, T_final, dt, state_vec_heun, std::ref(derivate), solve_heun, "output-heun.txt");

    } catch (const std::exception& e) {
        std::cerr << "Error: Argumentos inválidos. Deben ser números." << std::endl;
        return 1;
    }

    return 0;
}

void check_args(int argc, char **argv) {
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " dt T_inicial T_final w" << std::endl;
        std::cerr << "dt: incremento de tiempo, T_inicial: tiempo inicial, T_final: tiempo final, w: velocidad angular" << std::endl;
        std::exit(1);
    }
}

void solve_heun(const double delta, std::valarray<double>& state_vec, derivation_funct derivate) {
    std::valarray<double> k1(state_vec.size()), k2(state_vec.size());
    derivate(state_vec, k1);
    std::valarray<double> temp = state_vec + delta * k1;
    derivate(temp, k2);
    state_vec += delta * 0.5 * (k1 + k2);
}

void simulacion(double T_inicial, double T_final, double dt, std::valarray<double>& state_vec, 
                derivation_funct derivate, solver_funct solver, std::string file_name) {
    
    std::ofstream file(file_name);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << file_name << std::endl;
        std::exit(1);
    }

    file << "time\ty\tv\n";
    file << T_inicial << "\t" << state_vec[0] << "\t" << state_vec[1] << "\n";

    int n = static_cast<int>((T_final - T_inicial) / dt);
    for (int i = 1; i <= n; i++) {
        double time = i * dt + T_inicial;
        solver(dt, state_vec, derivate);
        file << time << "\t" << state_vec[0] << "\t" << state_vec[1] << "\n";
    }

    file.close();
}
