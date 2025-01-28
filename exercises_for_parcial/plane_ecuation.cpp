#include <iostream>
#include <vector>
#include <cassert>
#include <valarray>
#include <cmath>
# include <eigen3/Eigen/Dense>

using std::valarray;
using std::vector;


void check_args(int argc, char **argv);

void print_matrix(const std::vector<double> &data, const std::vector<int> &dims);


void multipli_matrix(const std::vector<double> &matrix_1, const std::vector<int> &dims_1,
                            const std::vector<double> &matrix_2, const std::vector<int> &dims_2,
                            std::vector<double> &dataout, std::vector<int> &dims_out);

vector<double> compute_plane(const valarray<double> A, const valarray<double> B,const valarray<double> C);
vector<double> compute_plane_eigen(const Eigen::Vector3d A, const Eigen::Vector3d B,Eigen::Vector3d C);


int main(int argc, char **argv)
{
    const double Ax = std::stod(argv[1]);
    const double Ay = std::stod(argv[2]);
    const double Az = std::stod(argv[3]);
    const double Bx = std::stod(argv[4]);
    const double By = std::stod(argv[5]);
    const double Bz = std::stod(argv[6]);
    const double Cx = std::stod(argv[7]);
    const double Cy = std::stod(argv[8]);
    const double Cz = std::stod(argv[9]);
    
    std::valarray<double>A = {Ax,Ay,Az};
    std::valarray<double>B = {Bx,By,Bz};
    std::valarray<double>C = {Cx,Cy,Cz};
    
    Eigen::Vector3d Ae = {Ax,Ay,Az};
    Eigen::Vector3d Be = {Bx,By,Bz};
    Eigen::Vector3d Ce = {Cx,Cy,Cz};

    vector<double> normal = compute_plane(A,B,C);
    vector<double> normal_2 = compute_plane_eigen(Ae,Be,Ce);
    vector<int> dims ={1,4};

    print_matrix(normal,dims);
    print_matrix(normal_2,dims);


}

void check_args(int argc, char **argv)
{
    // read variables
    if (argc != 10) {
    std::cerr << "Usage: " << argv[0] << " Ax Ay Az Bx By Bc Cx Cy Cz " << std::endl;
    std::cerr << "Ax: firts cordinate point A Ay: second cordinate point A Az: tird cordinate point A Bx: firts cordinate point B By: second cordinate point B Bz: tird cordinate point B Cx: uk Cy: uk Cz:uk" << std::endl;
    std::exit(1);
    }
}

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


vector<double> compute_plane(const valarray<double> A, const valarray<double> B,const valarray<double> C){

    valarray<double> dV = A - B; //diference vector
    valarray<double> dU = A - C; //diference vector

    vector<double> normal(4,0.0);
    normal[0] = (dV[1]*dU[2]-dV[2]*dU[1]);
    normal[1] = -(dV[0]*dU[2]-dV[2]*dU[0]);
    normal[2] = (dV[0]*dU[1]-dV[1]*dU[0]);

    double d = 0;
    for(int i=0; i < normal.size() -1 ; i++){
      d += A[i]* normal[i];  
    }

    normal[3] = d;//d

    return normal;

}

vector<double> compute_plane_eigen(const Eigen::Vector3d A, const Eigen::Vector3d B,Eigen::Vector3d C){

    Eigen::Vector3d v = A -B;
    Eigen::Vector3d u = A -C;

    Eigen::Vector3d normal = v.cross(u);

    double d = normal.dot(A);

    std::vector<double> out;

    for (int i = 0; i < normal.size(); ++i) {
        out.push_back(normal[i]); // Apply the lambda and store the result
    }

    out.push_back(d);

    return out;


}
