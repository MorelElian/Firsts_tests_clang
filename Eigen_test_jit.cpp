#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;
template <int size>
[[clang::jit]] void test_jit_sz(int repeat) {
  Matrix<int,size,size> I = Matrix<int,size,size>::Ones();
  Matrix<int,size,size> m;
  cout << "aaaaa\n";
  for(int i = 0; i < size; i++)
  for(int j = 0; j < size; j++) {
    m(i,j) = (i+size*j);
  }

  auto start = chrono::system_clock::now();

  for (int r = 0; r < repeat; ++r) {
    m = Matrix<int,size,size>::Ones() + int(0.00005) * (m + (m*m));
  }

  auto end = chrono::system_clock::now();
  cout << "JIT: " << chrono::duration<double>(end - start).count() << " s\n";
}
template<> 
[[clang::jit]] void test_jit_sz<20>(int repeat)
{
    const int size = 20;
    Matrix<int,size,size> I = Matrix<int,size,size>::Ones();
    Matrix<int,size,size> m;

  for(int i = 0; i < size; i++)
  for(int j = 0; j < size; j++) {
    m(i,j) = (i+size*j);
  }

  auto start = chrono::system_clock::now();

  for (int r = 0; r < repeat; ++r) {
    m = Matrix<int,size,size>::Ones() + int(0.00005) * (m + (m*m));
  }

  auto end = chrono::system_clock::now();
  cout << "JIT: " << chrono::duration<double>(end - start).count() << " s\n";
}

void test_jit(int size, int repeat) {
  return test_jit_sz<size>(repeat);
}

    int main(int argc, char * argv[])
    {
        std::string t(argv[1]);
        int size = std::atoi(argv[2]);
        int repeat = (std::atoi(argv[3]));

        test_jit(size,repeat);
        
    }
