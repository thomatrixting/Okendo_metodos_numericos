#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using std::cos;
using std::sin;

void check_args(int argc, char **argv);

void print_matrix(const std::vector<double> &data, const std::vector<int> &dims);


void multipli_matrix(const std::vector<double> &matrix_1, const std::vector<int> &dims_1,
                            const std::vector<double> &matrix_2, const std::vector<int> &dims_2,
                            std::vector<double> &dataout, std::vector<int> &dims_out);

void Compute_new_posicion_robotic_arm(const std::vector<double> &inicial_posicion_vector, 
                                      const std::vector<double> &theta_vector, 
                                      std::vector<double> &final_posicion_vector);

int main(int argc, char **argv)
{
    check_args(argc, argv);

    const double vx = std::stod(argv[1]);
    const double vy = std::stod(argv[2]);
    const double vz = std::stod(argv[3]);
    
    const double theta_x = std::stod(argv[4]);
    const double theta_y = std::stod(argv[5]);
    const double theta_z = std::stod(argv[6]);

    const std::vector<int> vector_dims = {1,3};

    const std::vector<double> origin_vector = {vx,vy,vz}; 
    const std::vector<double> theta_vector = {theta_x,theta_y,theta_z};

    std::vector<double> output_vector(3,0.0);

    Compute_new_posicion_robotic_arm(origin_vector,theta_vector,output_vector);

    print_matrix(output_vector,vector_dims);
    
    return 0;
}

void check_args(int argc, char **argv)
{
    // read variables
    if (argc != 7) {
    std::cerr << "Usage: " << argv[0] << " vx vy vz theta_x theta_y theta_z " << std::endl;
    std::cerr << "vx: origin vector x cordinate vy: origin vector y cordinate  vz: origin vector z cordinate  theta_x: rotacion angle in respect to x-axis theta_y: rotacion angle in respect to y-axis theta_z: rotacion angle in respect to z-axis" << std::endl;
    std::exit(1);
    }
}

// Print the matrix
void print_matrix(const std::vector<double> &data, const std::vector<int> &dims)
{
    int m = dims[0];
    int n = dims[1];
    for (int ii = 0; ii < m; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            std::cout << data[ii * n + jj] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Matrix multiplication
void multipli_matrix(const std::vector<double> &matrix_1, const std::vector<int> &dims_1,
                            const std::vector<double> &matrix_2, const std::vector<int> &dims_2,
                            std::vector<double> &dataout, std::vector<int> &dims_out)
{
    int m_1 = dims_1[0];
    int n_1 = dims_1[1];
    int m_2 = dims_2[0];
    int n_2 = dims_2[1];

    // Verify that the operation can be performed
    if (!(n_1 == m_2)) {
        std::cerr << "Matrices with shapes " << m_1 << "x" << n_1 << " and " << m_2 << "x" << n_2
                  << " cannot be multiplied.\n";
        std::cerr << "halting execusion.\n";
        std::exit(1);
        return;
    }

    dataout.resize(m_1 * n_2, 0.0);
    dims_out = {m_1, n_2}; // Set output dimensions

    double sum = 0.0;

    for (int ii = 0; ii < m_1; ++ii) {
        for (int jj = 0; jj < n_2; ++jj) {
            sum = 0.0;
            for (int kk = 0; kk < n_1; ++kk) {
                sum += matrix_1[ii * n_1 + kk] * matrix_2[kk * n_2 + jj];
            }
            dataout[ii * n_2 + jj] = sum;
        }
    }
}

//computing the posicion of the robotic arm
void Compute_new_posicion_robotic_arm(const std::vector<double> &inicial_posicion_vector, 
                                      const std::vector<double> &theta_vector, 
                                      std::vector<double> &final_posicion_vector) {
    // Define dimensions for matrices 
    //due to the context this values are set beacuse thsi implementacion only works on those cases
    assert(
        (inicial_posicion_vector.size() == 3) && 
        ("Error: inicial_posicion_vector debe tener exactamente 3 cordenadas.")
    );

    final_posicion_vector.resize(3); //is better to be explicit 

    std::vector<int> dims_matrix = {3, 3};
    std::vector<int> dims_vector = {3, 1};

    //operated matrix that como from Rz * Ry * Rx as matrix multiplicacion is associative
    std::vector<double> R_convine = {
        cos(theta_vector[1]) * cos(theta_vector[2]),
        sin(theta_vector[0]) * sin(theta_vector[1]) * cos(theta_vector[2]) - sin(theta_vector[2]) * cos(theta_vector[0]),
        sin(theta_vector[0]) * sin(theta_vector[2]) + sin(theta_vector[1]) * cos(theta_vector[0]) * cos(theta_vector[2]),

        cos(theta_vector[1]) * sin(theta_vector[2]),
        sin(theta_vector[0]) * sin(theta_vector[1]) * sin(theta_vector[2]) + cos(theta_vector[0]) * cos(theta_vector[2]),
        -sin(theta_vector[0]) * cos(theta_vector[2]) + sin(theta_vector[1]) * sin(theta_vector[2]) * cos(theta_vector[0]),

        -sin(theta_vector[1]),
        sin(theta_vector[0]) * cos(theta_vector[1]),
        cos(theta_vector[0]) * cos(theta_vector[1])
    };

    //perform the operacion Rz * Ry * Rx * vi
    multipli_matrix(R_convine, dims_matrix, inicial_posicion_vector, dims_vector, final_posicion_vector, dims_vector);
}
    
