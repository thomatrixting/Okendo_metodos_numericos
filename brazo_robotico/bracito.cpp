#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <random>
#include <cmath>


//implementacions
void check_args(int argc, char **argv);

void fill_matrix(std::vector<double> &data, const std::vector<int> &dims);

void print_matrix(const std::vector<double> &data, const std::vector<int> &dims);

void transpose_matrix(const std::vector<double> &indata, const std::vector<int> &dims_in,
                      std::vector<double> &outdata, std::vector<int> &dims_out);

void multipli_matrix(const std::vector<double> &matrix_1, const std::vector<int> &dims_1,
                            const std::vector<double> &matrix_2, const std::vector<int> &dims_2,
                            std::vector<double> &dataout, std::vector<int> &dims_out);

void Compute_new_posicion_robotic_arm(const std::vector<double> &inicial_posicion_vector, 
                                      const int &column_vector_size, 
                                      const std::vector<double> &theta_vector, 
                                      std::vector<double> &final_posicion_vector);

int main(int argc, char **argv)
{
    check_args(argc, argv);

    const double vx = std::stoi(argv[1]);
    const double vy = std::stoi(argv[2]);
    const double vz = std::stoi(argv[3]);
    
    const double theta_x = std::stoi(argv[4]);
    const double theta_y = std::stoi(argv[5]);
    const double theta_z = std::stoi(argv[6]);

    std::vector<double> origin_vector = {vx,vy,vz};
    std::vector<int> origin_vector_dims = {3,1};

    std::vector<double> theta_vector = {theta_x,theta_y,theta_z}; //todo safe as reference
    std::vector<double> output_vector(3,0.0);

    Compute_new_posicion_robotic_arm(origin_vector,3,theta_vector,output_vector);
     
    print_matrix(origin_vector,origin_vector_dims);
    print_matrix(output_vector,origin_vector_dims);
    
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

// Fill the matrix
void fill_matrix(std::vector<double> &data, const std::vector<int> &dims)
{
    int m = dims[0];
    int n = dims[1];
    for (int ii = 0; ii < m; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            data[ii * n + jj] = ii * n + jj; // A_(i, j) = i*n + j = id
        }
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

// Transpose the matrix
void transpose_matrix(const std::vector<double> &indata, const std::vector<int> &dims_in,
                      std::vector<double> &outdata, std::vector<int> &dims_out)
{
    int m = dims_in[0];
    int n = dims_in[1];
    outdata.resize(m * n); 
    dims_out = {n, m}; // Transposed dimensions

    for (int ii = 0; ii < m; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            outdata[jj * m + ii] = indata[ii * n + jj];
        }
    }
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
        std::cerr << "Returning zero matrix.\n";
        dataout.clear();
        dims_out = {0, 0};
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

void Compute_new_posicion_robotic_arm(const std::vector<double> &inicial_posicion_vector, 
                                      const int &column_vector_size, 
                                      const std::vector<double> &theta_vector, 
                                      std::vector<double> &final_posicion_vector) {
    // Define dimensions for matrices
    std::vector<int> dims_matrix = {3, 3};
    std::vector<int> dims_vector = {3, 1};

    // Rotation matrix Rx(theta)
    std::vector<double> R_x_theta = {
        1, 0, 0,
        0, std::cos(theta_vector[0]), -std::sin(theta_vector[0]),
        0, std::sin(theta_vector[0]), std::cos(theta_vector[0])
    };

    // Rotation matrix Ry(theta)
    std::vector<double> R_y_theta = {
        std::cos(theta_vector[1]), 0, std::sin(theta_vector[1]),
        0, 1, 0,
        -std::sin(theta_vector[1]), 0, std::cos(theta_vector[1])
    };

    // Rotation matrix Rz(theta)
    std::vector<double> R_z_theta = {
        std::cos(theta_vector[2]), -std::sin(theta_vector[2]), 0,
        std::sin(theta_vector[2]), std::cos(theta_vector[2]), 0,
        0, 0, 1
    };

    // Combine rotation matrices: R_combined = Rz * Ry * Rx
    std::vector<double> R_combined_temp;
    std::vector<int> dims_combined_temp;
    multipli_matrix(R_z_theta, dims_matrix, R_y_theta, dims_matrix, R_combined_temp, dims_combined_temp);

    std::vector<double> R_combined;
    std::vector<int> dims_combined;
    multipli_matrix(R_combined_temp, dims_combined_temp, R_x_theta, dims_matrix, R_combined, dims_combined);

    // Compute final position vector: final_posicion = R * inicial_posicion_vector
    multipli_matrix(R_combined, dims_combined, inicial_posicion_vector, dims_vector, final_posicion_vector, dims_vector);
}