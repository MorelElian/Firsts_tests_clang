#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <x86intrin.h>

#define DEFAULTM 16
#define DEFAULTN 16
#define DEFAULTK 16
#define NBREP    100

template <typename T> void initRand( T**, int, int );
template <typename T> void printMatrix( T**, int, int );

/* C <- A*B + C */
template <typename T, int M, int N, int K>
[[clang::jit]] void matmult( T** C, T** A, T** B ){
  for( auto i = 0 ; i < M ; i++ ){
    for( auto k = 0 ; k < K ; k++ ){
      for( auto j = 0 ; j < N ; j++ ){
	C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
}

template <typename T, int M, int N, int K>
[[clang::jit]] void matmult1( T** C, T** A, T** B ){
  for( auto i = 0 ; i < M ; i++ ){
    for( auto j = 0 ; j < N ; j++ ){
      //#pragma clang loop unroll(full)
      //#pragma clang loop unroll_count( K )
      //#pragma clang loop vectorize( enable )
      for( auto k = 0 ; k < K ; k++ ){
	C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
}

template <typename T>
void matmult2( T** C, T** A, T** B, int M, int N, int K ){
  for( auto i = 0 ; i < M ; i++ ){
    for( auto k = 0 ; k < K ; k++ ){
      for( auto j = 0 ; j < N ; j++ ){
	C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
}

template <typename T>
void matmult3( T** C, T** A, T** B, int M, int N, int K ){
  for( auto i = 0 ; i < M ; i++ ){
    for( auto j = 0 ; j < N ; j++ ){
      for( auto k = 0 ; k < K ; k++ ){
	C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
}

int main( int argc, char** argv ){
  int M = DEFAULTM, N = DEFAULTN, K = DEFAULTK;
  if( argc >= 2 ){
    M = atoi( argv[1] );
    if( argc >= 3 ){
      N = atoi( argv[2] );
      if( argc >= 4 ){
	K = atoi( argv[3] );
      }
    }
  }
  std::cout << "A: " << M << "x" << N << " ";
  std::cout << "B: " << N << "x" << K << " ";
  std::cout << "C: " << M << "x" << K << std::endl;

  double** A = new double*[M];
  for( auto i = 0 ; i < M ; i++ ) A[i] = new double[N];
  double** B = new double*[N];
  for( auto i = 0 ; i < N ; i++ ) B[i] = new double[K];
  double** C = new double*[M];
  for( auto i = 0 ; i < M ; i++ ) C[i] = new double[K];

  srand( 0 );
  initRand( A, M, N );
  initRand( B, N, K );
  initRand( C, M, K );
  //  printMatrix( A, M, N );

  unsigned long long start, end;

  /* warm-up */
  matmult<double, M, N, K>( C, A, B ); 

  /* Actual measurement */
  start = __rdtsc();
  for( auto i = 0 ; i < NBREP ; i++ ){	 
    matmult<double, M, N, K>( C, A, B );
  }
  end = __rdtsc();

  std::cout << "JIT\t" << M << "\t" << N << "\t" << K << "\t" << ( end - start ) / NBREP << std::endl;

  /* warm-up */
  matmult1<double, M, N, K>( C, A, B ); 

  /* Actual measurement */
  start = __rdtsc();
  for( auto i = 0 ; i < NBREP ; i++ ){	 
    matmult1<double, M, N, K>( C, A, B );
  }
  end = __rdtsc();

  std::cout << "JIT\t" << M << "\t" << N << "\t" << K << "\t" << ( end - start ) / NBREP << std::endl;

  /* warm-up */
  matmult2<double>( C, A, B, M, N, K ); 

  /* Actual measurement */
  start = __rdtsc();
  for( auto i = 0 ; i < NBREP ; i++ ){	 
    matmult2<double>( C, A, B, M, N, K );
  }
  end = __rdtsc();

  std::cout << "NOJIT\t" << M << "\t" << N << "\t" << K << "\t" << ( end - start ) / NBREP << std::endl;

  /* warm-up */
  matmult3<double>( C, A, B, M, N, K ); 

  /* Actual measurement */
  start = __rdtsc();
  for( auto i = 0 ; i < NBREP ; i++ ){	 
    matmult3<double>( C, A, B, M, N, K );
  }
  end = __rdtsc();

  std::cout << "NOJIT\t" << M << "\t" << N << "\t" << K << "\t" << ( end - start ) / NBREP << std::endl;

  for( auto i = 0 ; i < M ; i++ ) delete A[i];
  delete[] A;
  for( auto i = 0 ; i < N ; i++ ) delete B[i];
  delete[] B;
  for( auto i = 0 ; i < M ; i++ ) delete C[i];
  delete[] C;
  return EXIT_SUCCESS;
}

/*****************************************************************/

template <typename T>
void initRand( T** mat, int lines, int cols ){
  for( auto i = 0 ; i < lines ; i++ ){
    for( auto j = 0 ; j < cols ; j++ ){
      mat[i][j] = 100 - 200 * (T) rand () / (T) RAND_MAX;
    }
  }
}
  
template <typename T>
void printMatrix( T** mat, int lines, int cols ){
  for( auto i = 0 ; i < lines ; i++ ){
    for( auto j = 0 ; j < cols ; j++ ){
      std::cout << std::setprecision( 4 ) <<  mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
