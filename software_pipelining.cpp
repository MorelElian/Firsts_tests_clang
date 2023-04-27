#include <iostream>
#include <vector>
#include <papi.h>
#include <fstream>
template<int size,int epsilon>
[[clang::jit]] void sft_pip()
{
    int a[size],b[size],c[size];
    for(int i = 0 ; i < size; i++)
    {
        a[i] = i+4 -size/2;
    }
    long long values[3];
    int retval,EventSet = PAPI_NULL;
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    retval = PAPI_create_eventset(&EventSet);
    PAPI_add_event(EventSet,PAPI_TOT_CYC);
    PAPI_add_event(EventSet,PAPI_L1_DCM);
    PAPI_add_event(EventSet,PAPI_TOT_INS);
    PAPI_start(EventSet);
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
               a[i]++;
               }
               }
            }

        }
    }
    PAPI_stop(EventSet,values);
    printf("JIT TOT_CYC : %lld L1_DCM : %lld  TOT_INS : %lld \n", values[0], values[1], values[2]);
}
template<typename t>
void sft_pip(int size,int epsilon)
{
    int a[size],b[size],c[size];
    for(int i = 0 ; i < size; i++)
    {
        a[i] = i+4 -size/2;
    }
    long long values[3];
    int retval,EventSet = PAPI_NULL;
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    retval = PAPI_create_eventset(&EventSet);
    PAPI_add_event(EventSet,PAPI_TOT_CYC);
    PAPI_add_event(EventSet,PAPI_L1_DCM);
    PAPI_add_event(EventSet,PAPI_TOT_INS);
    PAPI_start(EventSet);
    for(int j = 0 ; j <30000;j++)
    {
        for (int i = 0 ; i <size - 4; i ++)
        {
            b[i] = a[i] *2 +3;
            if(epsilon > 4)
            {
               b[i+1] = a[i +1] * 3 - 2; 
               if(epsilon > 5)
               {
               b[i+2] = a[i +2] * 3 - 2;  
               if(epsilon >  6)
               {
               b[i+3] = a[i +3] * 3 - 2;
               a[i] ++;
               
               }
               }
            }

        }
    }
    PAPI_stop(EventSet,values);
    printf("NOJIT TOT_CYC : %lld L1_DCM : %lld  TOT_INS : %lld \n", values[0], values[1], values[2]);
}
int main(int argc, char * argv[])
{
    int size = std::atoi(argv[1]), epsilon = std::atoi(argv[2]);
    sft_pip<int>(size,epsilon);
    sft_pip<int>(size,epsilon);
    sft_pip<size,epsilon>();
    sft_pip<size,epsilon>();
}
