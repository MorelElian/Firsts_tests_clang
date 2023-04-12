#include <iostream>
#include <cstdlib>
template <int x>
[[clang::jit]] void run(){
    std::cout << "Hello world compiled at run time :  " << x << "\n";
}
int main(int argc, char *argv[])
{
    int a = std::atoi(argv[1]);
    run<a>();
    
}