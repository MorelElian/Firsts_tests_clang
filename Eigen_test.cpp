#include <Eigen/Core>
#include <iostream>
using namespace std;
using namespace Eigen; 
template<typename T>
void test_aot(int size, int repeat)
{
    Matrix<T,Dynamic,Dynamic> I = Matrix<T,Dynamic,Dynamic>::Ones(size,size);
    Matrix<T,Dynamic,Dynamic> m(size,size);
    for(int i = 0;i <size;i++)
    {
        for (int j = 0 ;j < size;j++)
        {
            m(i,j) = i*size + j;
        }
    }
    for(int k = 0 ; k< repeat; k ++)
    {
        m = Matrix<T,Dynamic,Dynamic>::Ones(size,size) + T(0.00005) *(m + (m*m)); 
        std::cout << "Bonjour, monde !" << std::endl;
    }
    
}
void test_aot(std::string &type, int size, int repeat)
{
    if(type  == "float")
    {
        test_aot<float>(size,repeat);
    }
    else if(type == "double")
    {
        test_aot<double>(size,repeat);
    }
    else if(type == "long double")
    {
        test_aot<long double>(size,repeat);
    }
}
int main(int argc, char * argv[])
{
    std::string type(argv[1]);
    int size = std::atoi(argv[2]);
    int repeat = std::atoi(argv[3]);
    test_aot(type,size,repeat);
}