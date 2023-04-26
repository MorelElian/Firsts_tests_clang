#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
template <int size,int epsilon>
[[clang::jit]]void tilling_loop()
{
    int a[size]; int b[size]; int c[size],d[size],e[size];
    long long values[3];
    int retval,EventSet = PAPI_NULL;
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    retval = PAPI_create_eventset(&EventSet);
    PAPI_add_event(EventSet,PAPI_TOT_CYC);
    PAPI_add_event(EventSet,PAPI_L1_DCM);
    PAPI_add_event(EventSet,PAPI_TOT_INS);
    for (int i = 0 ; i <size; i++)
    {
        a[i] = i*2*size;
        b[i] = 3*i-size;
        c[i] = 2;
        d[i] = 2*a[i];
        e[i] = 1;
    }
    PAPI_start(EventSet);
    for(int i = 0 ;i< size; i++)
    {
        a[i] = b[i] + c[i];
        if(epsilon < 4)
        {
            e[i] = e[i] + rand();
        }
        d[i] = rand()*d[i];
    }
    PAPI_stop(EventSet,values);
    printf("JIT \n TOT_CYC : %lld L1_DCM  : %lld TOT_INS : %lld \n",values[0],values[1],values[2]);
}
template <typename T>
void tilling_loop_static(int size, double espilon)
{

    int a[size]; int b[size]; int c[size],d[size],e[size];
    long long values[3];
    int retval,EventSet = PAPI_NULL;
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    retval = PAPI_create_eventset(&EventSet);
    PAPI_add_event(EventSet,PAPI_TOT_CYC);
    PAPI_add_event(EventSet,PAPI_L1_DCM);
    PAPI_add_event(EventSet,PAPI_TOT_INS);
    
    for (int i = 0 ; i <size; i++)
    {
        a[i] = i*2*size;
        b[i] = 3*i-size;
        c[i] = 2;
        d[i] = 2*a[i];
        e[i] = 1;
    }
   PAPI_start(EventSet);
    for(int i = 0 ;i< size; i++)
    {
        a[i] = b[i] + c[i];
        if(epsilon < 4)
        {
            for(int j  = 0 ; j < 100000; j++)
            {
                e[i] = e[i] + rand() ;
            }
        }
        for(int j = 0; j < 50000, j++)
        {
            d[i] = 2*d[i] + rand();
        }
    }
    PAPI_stop(EventSet,values);
    printf("JIT \n TOT_CYC : %lld L1_DCM  : %lld TOT_INS : %lld \n",values[0],values[1],values[2]);
}

int main(int argc, char * argv[])
{

    int size = std::atoi(argv[1]);
    int epsilon = std::atoi(argv[2]);
    tilling_loop<size,epsilon>();
    tilling_loop_static<int>(size,epsilon);


}
