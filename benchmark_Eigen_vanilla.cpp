#include<iostream>
#include<Eigen/Core>
#include <string>
#include <chrono>
#include <cstdlib>
#include<fstream>
using namespace std;
using namespace Eigen;
/* template <int size>
[[clang::jit]]Eigen::Matrix<double,size,size> multiply_matrices(const Eigen::Matrix<double,size,size> &mat1, const Eigen::Matrix<double,size,size> &mat2){
    // Multiplication qui minimise les caches misses.
    Eigen::Matrix<double, size, size> result;

   
        for (int i = 0 ; i <size ; i ++)
        {
            for (int j = 0 ;j<size; j++)
            {
                result(i,j) = 0.0 ;
            }
        }
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                double tmp = mat2(i,k);
                for (int j = 0; j < size; j++) {
                    result(i,j) += tmp * mat1(k,j);
                }
            }
        }
    
    return result;
    
} */

template <int size>
[[clang::jit]]double benchmark(int repeat)
{
    Eigen::Matrix<double,size,size> mat,tmp_mul;
    for(int i = 0 ;i < size; i++)
    {
        for(int j = 0 ; j<size ; j++)
        {
            mat(i,j) = i * size + j;
        }}
    auto start = chrono::system_clock::now();
    for(int l = 0; l< repeat; l++)
    {
        Eigen::Matrix<double,size,size> tmp;
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                double tmp = mat(i,k);
                for (int j = 0; j < size; j++) {
                    tmp_mul(i,j) += tmp * mat(k,j);
                }
            }
        }
        mat  = Eigen::Matrix<double,size,size>::Ones() + int(0.00005) * (mat+ tmp_mul);
    }
    auto end = chrono::system_clock::now();
    return chrono::duration<double>(end - start).count();
}

double call_template(int size,int repeat)
{
    
    double result = benchmark<size>(repeat);
    return result;
}
int main(int arcg, char * argv[])
{
    int size = std::atoi(argv[1]);
    int repeat = std::atoi(argv[2]);
    double result = call_template(size,repeat);
    std::ofstream csv_file("Eigen_bm_jit.csv", std::ios::app);
    cle
    // Ecriture de la première colonne
    csv_file << "eigen_vanilla_jit;" <<size <<";";
    
    // Ecriture de la deuxième colonne avec la valeur de la variable x
    
    csv_file << result << "\n";
    
    // Fermeture du fichier
    csv_file.close();
}