#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <random>
#include <cmath>


//implementacions
void check_args(int argc, char **argv);

void fill_matrix(std::vector<double> &data, const std::vector<int> &dims);

void fill_matrix_random(std::vector<double> & M, const std::vector<int> &dims, const int seed);

void print_matrix(const std::vector<double> &data, const std::vector<int> &dims);

void transpose_matrix(const std::vector<double> &indata, const std::vector<int> &dims_in,
                      std::vector<double> &outdata, std::vector<int> &dims_out);

void multipli_matrix(const std::vector<double> &matrix_1, const std::vector<int> &dims_1,
                            const std::vector<double> &matrix_2, const std::vector<int> &dims_2,
                            std::vector<double> &dataout, std::vector<int> &dims_out);

double compute_trace(const std::vector<double> &matrix, const std::vector<int> &dims);

void fill_matrix_hilbert(std::vector<double> &data, const std::vector<int> &dims);

void multiply_by_transpose(const std::vector<double> &matrix, const std::vector<int> &dims_in,
                      std::vector<double> &outmatrix, std::vector<int> &dims_out);

void matrix_to_the_power(const std::vector<double> &indata, const std::vector<int> &dims_in,
                      std::vector<double> &outdata, std::vector<int> &dims_out, int power);

bool check_inverse(const std::vector<double> &A_matrix, const std::vector<int> &dims_A,
                     std::vector<double> &B_matrix, const std::vector<int> &dims_B,double epsilon);

bool cheeck_idempotent_matrix(const std::vector<double> &A_matrix, const std::vector<int> &dims_A, int power, double epsilon);

int main(int argc, char **argv)
{
    check_args(argc, argv);

    const int M = std::stoi(argv[1]);
    const int N = std::stoi(argv[2]);
    const int seed = std::stoi(argv[3]);
/*
    //fill matrix

    //create ramdom array
    std::vector<double> array2d(M * N, 0.0);
    std::vector<int> dimensions_array2d = {M, N};

    fill_matrix_random(array2d, dimensions_array2d,seed);
    print_matrix(array2d, dimensions_array2d);

    //transpose array
    std::vector<double> array2d_T;
    std::vector<int> dimensions_array2d_T(2,0);
    transpose_matrix(array2d, dimensions_array2d, array2d_T, dimensions_array2d_T);
    print_matrix(array2d_T, dimensions_array2d_T);

    //test multiplication
    std::vector<double> multiply_array;
    std::vector<int> dimensions_multiply_array(2,0);
    multipli_matrix(array2d, dimensions_array2d, array2d_T, dimensions_array2d_T, multiply_array, dimensions_multiply_array);
    print_matrix(multiply_array, dimensions_multiply_array);

    //compute trace
    double trace = compute_trace(multiply_array, dimensions_multiply_array);
    std::cout << "trace multiply matrix: " << trace << "\n";

    //fill matrix with hilbert
    std::vector<double> hilbert_matrix(M*M, 0);
    std::vector<int> dimensions_hilbert = {M, M}; //scuare so i dont have problems
    fill_matrix_hilbert(hilbert_matrix, dimensions_hilbert);
    print_matrix(hilbert_matrix,dimensions_hilbert);
    
    //multipli transpose
    std::vector<double> multiply_tranpose;
    std::vector<int> dimensions_multiply_tranpose(2,0);
    multiply_by_transpose(array2d,dimensions_array2d,multiply_tranpose,dimensions_multiply_tranpose);
    print_matrix(multiply_tranpose,dimensions_multiply_tranpose);

    //check power
    std::vector<double> standar_matrix(M*M,0.0);
    std::vector<int> dimensions_standar_matrix = {M,M};
    fill_matrix(standar_matrix,dimensions_standar_matrix);
    print_matrix(standar_matrix,dimensions_standar_matrix);


    std::vector<double> power_2_matrix;
    std::vector<int> dimensions_power_2_matrix(2,0);
    std::cout << "matrix to the power of 2\n";
    matrix_to_the_power(standar_matrix,dimensions_standar_matrix,power_2_matrix,dimensions_power_2_matrix,2);
    print_matrix(power_2_matrix,dimensions_power_2_matrix);

    std::vector<double> power_4_matrix;
    std::vector<int> dimensions_power_4_matrix(2,0);
    std::cout << "matrix to the power of 4\n";
    matrix_to_the_power(standar_matrix,dimensions_standar_matrix,power_4_matrix,dimensions_power_4_matrix,4);
    print_matrix(power_4_matrix,dimensions_power_4_matrix);

    //check inverse
    std::vector<double> A_matrix = {1,2,3,0,1,4,5,6,0};
    std::vector<int> dims_A_matrix = {3,3};

    std::vector<double> B_matrix = {-24,18,5,20,-15,-4,-5,4,1};
    std::vector<int> dims_B_matrix = {3,3};

    std::vector<double> mul_matrix;
    std::vector<int> dims_mul_matrix(2,0);

    multipli_matrix(A_matrix,dims_A_matrix,B_matrix,dims_B_matrix,mul_matrix,dims_mul_matrix);
    print_matrix(mul_matrix,dims_mul_matrix);


    bool inverse = check_inverse(A_matrix,dims_A_matrix,B_matrix,dims_B_matrix,10e-05);

   std::cout << "inverse: " << inverse << "\n";

    //check is idempotent
    std::vector<double> idempotent_matrix = {3,2,-3,-2};
    std::vector<int> dims_idempotent_matrix = {2,2};

    bool is_idempotent = cheeck_idempotent_matrix(idempotent_matrix,dims_idempotent_matrix, 2, 10e-5);
    std::cout << "is idempotent: " << is_idempotent << "\n";
*/
    
    return 0;
}

void check_args(int argc, char **argv)
{
    // read variables
    if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " N M seed" << std::endl;
    std::cerr << "M: number of rows , N: number of columns, seed: ramdom integer" << std::endl;
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

void fill_matrix_random(std::vector<double> & M, const std::vector<int> &dims, const int seed){

    int m = dims[0];
    int n = dims[1];

    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(-1, 1);
    for (int ii = 0; ii < m; ii++){
        for (int jj = 0; jj < n; jj++){
            M[ii*n + jj] = dis(gen);
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

double compute_trace(const std::vector<double> &matrix, const std::vector<int> &dims)
{
    //ensure that is a scuare matrix
    int m = dims[0];
    int n = dims[1];

    if (m != n){
        std::cerr << "cannot compute the trace of a non scuare matrix: dimecions given "<< m << "X" << n << "\n";
        std::cerr << "halting program";
        std::exit(1);
    }
    double sum = 0;
    for(int ii=0; ii<m; ++ii){
        sum += matrix[ii*n + ii];
    }

    return sum;
}

void fill_matrix_hilbert(std::vector<double> &data, const std::vector<int> &dims)
{
    int m = dims[0];
    int n = dims[1];
    for (int ii = 0; ii < m; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            data[ii * n + jj] = 1./(ii + jj + 1); // A_(i, j) = i*n + j = id
        }
    }
}

void multiply_by_transpose(const std::vector<double> &matrix, const std::vector<int> &dims_in,
                      std::vector<double> &outmatrix, std::vector<int> &dims_out)
{
    // A * A^t
    int m = dims_in[0];
    int n = dims_in[1];
    outmatrix.resize(m * m); 
    dims_out = {m, m}; // m X n * n X m = m X m

    //transpose matrix
    std::vector<double> matrix_T(m*n,0.0);
    std::vector<int> dimensions_matrix_T(2,0);
    transpose_matrix(matrix, dims_in, matrix_T, dimensions_matrix_T);

    //multipli with its transpose

    multipli_matrix(matrix, dims_in, matrix_T, dimensions_matrix_T, outmatrix, dims_out);
}

void matrix_to_the_power(const std::vector<double> &in_matrix, const std::vector<int> &dims_in,
                      std::vector<double> &out_matrix, std::vector<int> &dims_out, int power)
{
    //ensure that is a scuare matrix
    int m = dims_in[0];
    int n = dims_in[1];

    if (m != n){
        std::cerr << "cannot compute the power of a matrix of a non scuare matrix: dimecions given "<< m << "X" << n << "\n";
        std::cerr << "halting program";
        std::exit(1);
    }
    if (power<2){

        std::cerr << "The power of the funcion cannot be less than 2, power given: "<< power << "\n";
        std::cerr << "halting program";
        std::exit(1);
    } 

    out_matrix.resize(m * m); 

    //TODO make this more eficient by using a recursive function that calls itset whenerber the power is hishgt enought so that i can be withern as (M²)^n

    std::vector<double> matrix_container(m * m, 0.0);
    std::vector<int> dims_matrix_container = {m, m};

    bool power_even = (power % 2 == 0);

    std::vector<double>& container_A = (power_even) ? out_matrix : matrix_container;
    std::vector<int>& dims_container_A = (power_even) ? dims_out : dims_matrix_container;

    std::vector<double>& container_B = (power_even) ? matrix_container : out_matrix;
    std::vector<int>& dims_container_B = (power_even) ? dims_matrix_container : dims_out;

    multipli_matrix(in_matrix,dims_in,in_matrix,dims_in,container_A,dims_container_A);//compute the scuare


    for(int ii = 1; ii < power-1; ii++){
        if (ii%2 != 0){
            multipli_matrix(in_matrix,dims_in,container_A,dims_container_A,container_B,dims_container_B); //be carefull with the definicion of multiplicacion so to not overrite values while computing
        } else {
            multipli_matrix(in_matrix,dims_in,container_B,dims_container_B,container_A,dims_container_A); //be carefull with the definicion of multiplicacion so to not overrite values while computing
        }
    }       

}

bool check_inverse(const std::vector<double> &A_matrix, const std::vector<int> &dims_A, std::vector<double> &B_matrix, const std::vector<int> &dims_B,double epsilon){
    //ensure that is a scuare matrix
    int m_A = dims_A[0];
    int n_A = dims_A[1];
    int m_B = dims_B[0];
    int n_B = dims_B[1];

    if (n_A != m_B){
        std::cerr << "cannot multiply A and B so it can be the inverse, dimensions given "<< m_A << "X" << n_A << " " <<m_B << "X" << n_B<< "\n";
        std::cerr << "halting program";
        std::exit(1);
    } else if( !((m_A == n_A) and (n_B == m_B)) ){
        std::cerr << "1 of the two matrix is non-scuare, dimensions given "<< m_A << "X" << n_A << " " <<m_B << "X" << n_B<< "\n";
        std::cerr << "halting program";
        std::exit(1);
    }

    std::vector<double> mul_matrix(m_A * n_B, 0.0);
    std::vector<int> dims_mul_matrix = {m_A, n_B};

    multipli_matrix(A_matrix,dims_A,B_matrix,dims_B,mul_matrix,dims_mul_matrix);

    bool is_inverse = true;

    for (int ii = 0; ii < m_A; ++ii) {
        for (int jj = 0; jj < n_B; ++jj) {
            double identiy = (ii==jj) ? 1.0 : 0.0;
            is_inverse = (std::abs(mul_matrix[ii * n_B + jj] - identiy) < epsilon);

            if (!is_inverse){
                return is_inverse;
            }

        }
    }

    return is_inverse;

}

bool cheeck_idempotent_matrix(const std::vector<double> &in_matrix, const std::vector<int> &dims_in, int power, double epsilon){
    //if only powers of two and it needs to be fast a posibility is to make the multiplicacion of the matrix A while saving data on matrix A it shoud remain equal and that could be a criteria

    int m = dims_in[0];
    int n = dims_in[1];

    if (m != n){
        std::cerr << "cannot compute the power  of a matrix of a non scuare matrix and therefore detemine is it is idempotent: dimecions given "<< m << "X" << n << "\n";
        std::cerr << "halting program";
        std::exit(1);
    }
    if (power<2){

        std::cerr << "The power to check if the matrix is idempotent of the funcion cannot be less than 2, power given: "<< power << "\n";
        std::cerr << "halting program";
        std::exit(1);
    } 

    std::vector<double> power_matrix(m * n, 0.0);
    std::vector<int> dims_power_matrix = {m, n};

    matrix_to_the_power(in_matrix,dims_in,power_matrix,dims_power_matrix,power);

    bool is_idempotent = true;

    for (int ii = 0; ii < m; ++ii) {
        for (int jj = 0; jj < n; ++jj) {

            is_idempotent = (std::abs(power_matrix[ii * n + jj] - in_matrix[ii * n + jj]) < epsilon);

            if (!is_idempotent){
                return is_idempotent;
            }

        }
    }

    return is_idempotent;


}
