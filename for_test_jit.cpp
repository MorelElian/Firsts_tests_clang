#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;
template <typename T,int size>
[[clang::jit]]double test_boucle()
{
    float j = 2.0;
    
    auto start = chrono::system_clock::now();
    for (int k = 0; k < 200000; k++)
    {
        for(int i = 0; i < size; i++)
        {
            j = (j+4) *2 * j /5;
        
        }
    }
    auto end = chrono::system_clock::now();
    return chrono::duration<double>(end - start).count();
    
}

int main(int argc, char* argv[])
{
    
    int size = std::atoi(argv[1]);
    double result = test_boucle<int,size>();
    
    std::ofstream csv_file("test_boucle.csv", std::ios::app);
    
    // Ecriture de la première colonne
    csv_file << "for_test_jit;" <<size <<";";
    
    // Ecriture de la deuxième colonne avec la valeur de la variable x
    
    csv_file << result << "\n";
    
    // Fermeture du fichier
    csv_file.close();


}