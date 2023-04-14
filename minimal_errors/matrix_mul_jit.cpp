#include<iostream>
#include <string>
#include <chrono>
#include<fstream>

#include <Eigen/Core>

using namespace Eigen;
template<int size>
[[clang::jit]]void test()
{
 Matrix<double,size,size> mat;
 for(int i = 0 ; i <size; i++)
 {
    for (int j = 0 ; j< size ; j++)
    {
    mat(i,j) = 2;
    }
 }
    mat = mat * mat;
}
void call_test(int size)
{
    test<size>();
}
int main(int argc, char * argv[])
{
    int size = std::atoi(argv[1]);
    call_test(size);
}