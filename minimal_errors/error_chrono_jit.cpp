// When chrono is called after a jited portion of code, doesn't work well. 


#include<iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include<fstream>
#include<Eigen/Core>

using namespace std;
using namespace Eigen;
template <int size>
[[clang::jit]]double multiply_matrices(int repeat ){
    // Multiplication qui minimise les caches misses.
    Matrix<double, size, size> mat1, result;

    for (int i = 0; i <size;i++)
    {
        for(int j = 0 ; j< size ; j++)
        {
            mat1(i,j) = i*size + j;
        }
    }
    
    for (int l = 0 ; l < repeat; l++)
    {
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                double tmp = mat1(i,k);
                for (int j = 0; j < size; j++) {    
                    result(i,j) += tmp * mat1(k,j);
                }
            }
        }
    }
    
    return chrono::duration<double>(end - start).count();
    
}

void call_multiply(int size,int repeat)
{
    auto start = chrono::system_clock::now();
    double result = multiply_matrices<size>(repeat);
    auto end = chrono::system_clock::now();
    std::ofstream csv_file("test_Mat_mul.csv", std::ios::app);
    
    // Ecriture de la première colonne
    csv_file << "for_test_jit;" <<size <<";";
    
    // Ecriture de la deuxième colonne avec la valeur de la variable x
    
    csv_file << result << "\n";
    
    // Fermeture du fichier
    csv_file.close();
}
int main(int arcg, char * argv[])
{
    int size = std::atoi(argv[1]);
    int repeat = std::atoi(argv[2]);
    call_multiply(size,repeat);
}