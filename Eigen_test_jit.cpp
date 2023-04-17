#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <Eigen/Core>
#include <x86intrin.h>

using namespace std;
using namespace Eigen;

template <typename T, int size>
[[clang::jit]] void test_jit_sz(int repeat) {
  Matrix<T,size,size> I = Matrix<T,size,size>::Ones();
  Matrix<T,size,size> m;
  
  for(int i = 0; i < size; i++)
  for(int j = 0; j < size; j++) {
    m(i,j) = (i+size*j);
  }

  auto start = __rdtsc();

  for (int r = 0; r < repeat; ++r) {
    auto t = I + T(0.00005) * ( m + (m*m) );
  }

  auto end = __rdtsc();
  
  cout << "JIT: " << (end - start)/1e6 << "\n";
}

template <typename T>
void test_jit_sz(int size, int repeat) {
  Matrix<T, Dynamic, Dynamic> I( size, size );
  Matrix<T, Dynamic, Dynamic> m( size, size );

  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++) {
      I(i,j) = ( i == j ) ? 1 : 0;
  }

  for(int i = 0; i < size; i++)
  for(int j = 0; j < size; j++) {
    m(i,j) = (i+size*j);
  }

  auto start = __rdtsc();

  for (int r = 0; r < repeat; ++r) {
    auto t = I + T(0.00005) * ( m + (m*m) );
  }

  auto end = __rdtsc();
  cout << "NOJIT: " << (end - start) / 1e6 << "\n";
}

template <typename T>
void test_jit(int size, int repeat) {
  return test_jit_sz<T, size>(repeat);
}

template <typename T>
void test_nojit(int size, int repeat) {
  return test_jit_sz<T>(repeat, size);
}

int main(int argc, char * argv[])
  {
      std::string t(argv[1]);
      int size = std::atoi(argv[2]);
      int repeat = (std::atoi(argv[3]));

      if( t == "float" or t == "f" ) test_jit<float>(size,repeat);
      if( t == "double" or t == "d" ) test_jit<double>(size,repeat);
      if( t == "int" or t == "i" ) test_jit<int>(size,repeat);
        
      if( t == "float" or t == "f" ) test_nojit<float>(size,repeat);
      if( t == "double" or t == "d" ) test_nojit<double>(size,repeat);
      if( t == "int" or t == "i" ) test_nojit<int>(size,repeat);
      
  }
