#include <iostream>
#include <vector>
#include <papi.h>
template<int size,int epsilon>
[[clang::jit]] sft_pip()
{
    int a[size],b[size],c[size];
    for(int i = 0 ; i < size; i++)
    {
        a[i] = i+4 -size/2;
    }
    for(int j = 0 ; j <30000;j++)
    {
        for (int i = 0 ; i <size - 4; i ++)
        {
            b[i] = a[i] *2 + 4;
            
            if(epsilon > 4)
            {
               b[i+1] = a[i +1] * 3 - 2; 
               if(epsilon > 5)
               {
               b[i+2] = a[i +2] * 3 - 2; 
               
               if(epsilon >  6)
               {
               b[i+3] = a[i +3] * 3 - 2; 
               }
               }
            }

        }
    }
}
template<typename t>
sft_pip(int size,int epsilon)
{
    int a[size],b[size],c[size];
    for(int i = 0 ; i < size; i++)
    {
        a[i] = i+4 -size/2;
    }
    for(int j = 0 ; j <30000;j++)
    {
        for (int i = 0 ; i <size - 4; i ++)
        {
            b[i] = a[i] *2 + 4;
            
            if(epsilon > 4)
            {
               b[i+1] = a[i +1] * 3 - 2; 
               if(epsilon > 5)
               {
               b[i+2] = a[i +2] * 3 - 2; 
               
               if(epsilon >  6)
               {
               b[i+3] = a[i +3] * 3 - 2; 
               }
               }
            }

        }
    }
}
int main(int argc, char * argv[])
{
    int size = std::atoi(argv[1]), espilon = std::atoi(argv[2]);
    sft_pip<int>(size,epsilon);
    sft_pip<int>(size,epsilon);
    sft_pip<size,epsilon>();
    sft_pip<size,epsilon>();
}