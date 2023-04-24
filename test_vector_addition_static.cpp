#include <iostream>
#include <chrono>
#include <fstream>
#include "papi.h"
using namespace std;

template <typename T>
double add_arrays(int size,int repeat) {

    int a[size]; int b[size]; int c[size];
    long long values[4],values_inter[4];
    int retval,EventSet = PAPI_NULL;
	retval = PAPI_library_init(PAPI_VER_CURRENT);
	retval = PAPI_create_eventset(&EventSet);
	PAPI_add_event(EventSet,PAPI_TOT_CYC);
	PAPI_add_event(EventSet,PAPI_L1_DCM);
	PAPI_add_event(EventSet,PAPI_VEC_SP);
	PAPI_add_event(EventSet,PAPI_TOT_INS);
	PAPI_start(EventSet);

    for (int i = 0 ; i <size; i++)
    {
        a[i] = i*2*size;
        b[i] = 3*i-size;
    }
   PAPI_read(EventSet,values_inter);
    auto start = chrono::system_clock::now();
    for(int j = 0 ; j < repeat; j++)
    {
        for (int i = 0; i < size; i++) {
            c[i] = a[i] + b[i];
            b[i] = c[i];
        }
    }
    PAPI_read(EventSet,values);
    auto end = chrono::system_clock::now();
    printf("STATIC\nAfter %d additions size %d:\nTOT_CYC :%lld\nL1 CACHE_MISSES  %lld\nSIMD_INS : %lld\nTOT_INS : %lld\n",repeat,size, values[0], values[1],values[2],values[3]);
	 printf("STATIC\nAfter Initialisation  size %d:\nTOT_CYC :%lld\nL1 CACHE_MISSES  %lld\nSIMD_INS : %lld\n",size, values_inter[0], values_inter[1],values_inter[2]);
/*    for(int i = 0; i < size ; i++)
	{
		printf("%d ",c[i]);
	}
*/  std::ofstream csv_file("addition_papi.csv", std::ios::app);
    csv_file << "test_addition_static;" <<size <<";"<< repeat <<";";

    csv_file << values[0] << ";" << values[1] << ";" << values[3] << "\n";
    // Fermeture du fichier
    csv_file.close();

return chrono::duration<double>(end - start).count();
}

int main(int argc, char* argv[]) {
    int size = atoi(argv[1]);
    int repeat = atoi(argv[2]);
    double time = add_arrays<int>(size,repeat);
    std::ofstream csv_file("test_addition.csv", std::ios::app);
    // Ecriture de la première colonne
    csv_file << "test_addition;" <<size <<";";
    // Ecriture de la deuxième colonne avec la valeur de la variable x
    csv_file << time << "\n";
    // Fermeture du fichier
    csv_file.close();
    return 0;
}
 
