#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <random>
#include <cmath>
#include <complex>

void print_matrix_complex(const std::vector<std::complex<double>> &data, const std::vector<int> &dims);

void multipli_matrix_complex(const std::vector<std::complex<double>> &matrix_1, const std::vector<int> &dims_1,
                            const std::vector<std::complex<double>> &matrix_2, const std::vector<int> &dims_2,
                            std::vector<std::complex<double>> &dataout, std::vector<int> &dims_out);

bool matrix_is_hermian(const std::vector<std::complex<double>> &matrix, const std::vector<int> &dims_matrix, double epsilon);
int main(void)
{

    const std::vector<std::complex<double>> A = { 
        { -1, 0 }, { 2, 1 }, { 5, -3 },
        { 2, -1 }, { 7, 0 }, { 0, 5 },
        { 5, 3 }, { 0, -5 }, { 2, 0 }
    };
    const std::vector< int > dims_A = {3,3};

    print_matrix_complex(A,dims_A);

    bool is_hermian = matrix_is_hermian(A,dims_A,10e-5);

    std::cout << "matrix is hermian: " << is_hermian << "\n";
    
    return 0;

}

void print_matrix_complex(const std::vector<std::complex<double>> &data, const std::vector<int> &dims)
{
    int m = dims[0];
    int n = dims[1];
    for (int ii = 0; ii < m; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            std::cout << "[";
            std::cout << std::real(data[ii * n + jj]) << " ";
            std::cout << "i" << std::imag(data[ii * n + jj]) << " ";
            std::cout << "]";

        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void multipli_matrix_complex(const std::vector<std::complex<double>> &matrix_1, const std::vector<int> &dims_1,
                            const std::vector<std::complex<double>> &matrix_2, const std::vector<int> &dims_2,
                            std::vector<std::complex<double>> &dataout, std::vector<int> &dims_out)
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

    std::complex<double> sum = 0.0;

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

void transpose_conjugate_complex_matrix(const std::vector<std::complex<double>> &indata, const std::vector<int> &dims_in,
                      std::vector<std::complex<double>> &outdata, std::vector<int> &dims_out)
{
    int m = dims_in[0];
    int n = dims_in[1];
    outdata.resize(m * n); 
    dims_out = {n, m}; // Transposed dimensions

    for (int ii = 0; ii < m; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            outdata[jj * m + ii] = std::conj(indata[ii * n + jj]);
        }
    }
}

bool matrix_is_hermian(const std::vector<std::complex<double>> &matrix, const std::vector<int> &dims_matrix, double epsilon){

    int m = dims_matrix[0];
    int n = dims_matrix[1];

    std::vector< std::complex<double> > transpose(m*n,(0,0));
    std::vector< int > dims_tranpose(2);

    transpose_conjugate_complex_matrix(matrix,dims_matrix,transpose,dims_tranpose);

    for (int ii = 0; ii < m; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            double identiy = (ii==jj) ? 1.0 : 0.0;
            if (
                 ( std::abs( std::real(transpose[jj + ii*n]) - std::real(matrix[jj + ii*n]) ) > epsilon ) or  
                 ( std::abs( std::imag(transpose[jj + ii*n]) - std::imag(matrix[jj + ii*n]) ) > epsilon )
                ){
                return false;
            }

        }
    }
    return true;

}
