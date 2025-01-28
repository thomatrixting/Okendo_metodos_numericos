#include <iostream>
#include <eigen3/Eigen/Dense>
#include <cstdlib> // Para std::atoi
#include <ctime>   // Para tiempo como semilla}
#include <string>
#include <chrono>
#include <fstream>

// Función para establecer la semilla para Eigen::internal
void setEigenRandomSeed(unsigned int seed) {
    srand(seed); // Establecer semilla para las funciones internas de Eigen
}

void check_args(int argc, char* argv[]);

void fill_matrix_random(Eigen::MatrixXd &A);
void fill_vector_random(Eigen::VectorXd &v);

void run_simulation(std::string file_name, int iter);

// Compilar con -O3 porque es la optimización de más alto nivel
int main(int argc, char* argv[]) {

    check_args(argc, argv);
    int n = std::atoi(argv[1]);

    // Leer la semilla desde la línea de cmandos
    unsigned int seed = std::atoi(argv[2]);
    setEigenRandomSeed(seed);

    // Configurar la semilla para Eige

    // Generar la matriz A y el vector b aleatorios
    Eigen::MatrixXd A(n, n);
    Eigen::VectorXd b(n);

    fill_matrix_random(A);
    fill_vector_random(b);

    // Mostrar A y b
    std::cout << "Aquí está la matriz A:\n" << A << std::endl;
    std::cout << "Aquí está el vector b:\n" << b << std::endl;

    // Resolver el sistema de ecuaciones
    Eigen::VectorXd x_Qr = A.colPivHouseholderQr().solve(b);

    // Mostrar la solución
    std::cout << "La solución utilizando QR es:\n" << x_Qr << std::endl;

    // Verificar la solución calculando la norma del residuo
    double residuo_Qr = (A * x_Qr - b).norm();
    std::cout << "Norma del residuo Qr (||Ax - b||): " << residuo_Qr << std::endl;


    //resolver el sistema utilizando LU
   Eigen::VectorXd x_Lu = A.fullPivLu().solve(b);

    std::cout << "La solución utilizando Lu es:\n" << x_Lu << std::endl;

    // Verificar la solución calculando la norma del residuo
    double residuo_Lu = (A * x_Lu - b).norm();
    std::cout << "Norma del residuo Lu (||Ax - b||): " << residuo_Lu << std::endl;

    run_simulation("data.csv",seed);

    return 0;
}

void check_args(int argc, char* argv[]){
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <tamaño de la matriz (n)> <semilla>" << std::endl;
        std::exit(1);
    }

    // Leer el tamaño de la matriz desde la línea de comandos
    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "El tamaño de la matriz debe ser un número entero positivo." << std::endl;
        std::exit(1);
    }

}

void fill_matrix_random(Eigen::MatrixXd &A){

    for (int i = 0; i < A.rows(); ++i) {
        for (int j = 0; j < A.cols(); ++j) {
            A(i, j) = Eigen::internal::random<double>(-1.0, 1.0);
        }
    }
}

void fill_vector_random(Eigen::VectorXd &v){

    for (int j = 0; j < v.size(); ++j) {
            v(j) = Eigen::internal::random<double>(-1.0, 1.0);
    }

}

void run_simulation(std::string file_name, int iter){

    int n=4;
    std::ofstream fout(file_name);
    fout << "n,duracion_Qr,duracion_Lu \n";

    for (int i = 4; i <= iter; i++){
        setEigenRandomSeed(i+27);

        n = i/2;
        Eigen::MatrixXd A(n, n);
        Eigen::VectorXd b(n);

        fill_matrix_random(A);
        fill_vector_random(b);


        std::chrono::high_resolution_clock::time_point start_Qr = std::chrono::high_resolution_clock::now();
        Eigen::VectorXd x_Qr = A.colPivHouseholderQr().solve(b);
        std::chrono::high_resolution_clock::time_point end_Qr = std::chrono::high_resolution_clock::now();

        std::chrono::microseconds duration_Qr = std::chrono::duration_cast<std::chrono::microseconds>(end_Qr - start_Qr);


        std::chrono::high_resolution_clock::time_point start_Lu = std::chrono::high_resolution_clock::now();
        Eigen::VectorXd x_Lu = A.fullPivLu().solve(b);
        std::chrono::high_resolution_clock::time_point end_Lu = std::chrono::high_resolution_clock::now();

        std::chrono::microseconds duration_Lu = std::chrono::duration_cast<std::chrono::microseconds>(end_Lu - start_Lu);

        if((A * x_Lu - b).norm() < 10e-5){
            fout << n << "," << duration_Qr.count() << "," << duration_Lu.count() << "\n";
        }


    }

    fout.close();

}
