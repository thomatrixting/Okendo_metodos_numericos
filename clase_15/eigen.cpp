#include <iostream>
#include <eigen3/Eigen/Dense>
#include <cstdlib> // Para std::atoi
#include <ctime>   // Para tiempo como semilla

// Función para establecer la semilla para Eigen::internal
void setEigenRandomSeed(unsigned int seed) {
    srand(seed); // Establecer semilla para las funciones internas de Eigen
}

// Compilar con -O3 porque es la optimización de más alto nivel
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <tamaño de la matriz (n)> <semilla>" << std::endl;
        return 1;
    }

    // Leer el tamaño de la matriz desde la línea de comandos
    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "El tamaño de la matriz debe ser un número entero positivo." << std::endl;
        return 1;
    }

    // Leer la semilla desde la línea de comandos
    unsigned int seed = std::atoi(argv[2]);

    // Configurar la semilla para Eigen
    setEigenRandomSeed(seed);

    // Generar la matriz A y el vector b aleatorios
    Eigen::MatrixXd A(n, n);
    Eigen::VectorXd b(n);

    for (int i = 0; i < n; ++i) {
        b(i) = Eigen::internal::random<double>(-1.0, 1.0); // Generar valores en [-1, 1]
        for (int j = 0; j < n; ++j) {
            A(i, j) = Eigen::internal::random<double>(-1.0, 1.0);
        }
    }

    // Mostrar A y b
    std::cout << "Aquí está la matriz A:\n" << A << std::endl;
    std::cout << "Aquí está el vector b:\n" << b << std::endl;

    // Resolver el sistema de ecuaciones
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

    // Mostrar la solución
    std::cout << "La solución es:\n" << x << std::endl;

    // Verificar la solución calculando la norma del residuo
    double residuo = (A * x - b).norm();
    std::cout << "Norma del residuo (||Ax - b||): " << residuo << std::endl;

    return 0;
}
