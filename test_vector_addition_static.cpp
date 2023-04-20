#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

template <typename T>
double add_arrays(int size,int repeat) {

    int a[size]; int b[size]; int c[size];
    for (int i = 0 ; i <size; i++)
    {
        a[i] = i*2*size;
        b[i] = 3*i-size;
    }
    auto start = chrono::system_clock::now();
    for(int j = 0 ; j < repeat; j++)
    {
        for (int i = 0; i < size; i++) {
            c[i] = a[i] + b[i];
            b[i] = c[i];
        }
    }
    auto end = chrono::system_clock::now();
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
