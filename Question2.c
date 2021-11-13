#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<limits.h>

#define NUMBER_OF_THREADS 50

typedef struct {
    int i;
    int Max;
} MyData;

// Assumption that given N < 1000000 to implement the Sieve of Eratosthenes algorithm to find Prime Numbers
int prime[1000000];

DWORD WINAPI IsPrimeSieve(PVOID num_max_){
    MyData num_max = *(MyData *)num_max_;
    long int num = num_max.i;
    long int max = num_max.Max;
    for(int i = num; i <= max ; i++ ){
        if(prime[i] == -1){
            prime[i] = 1;
            for(int j = 2; i * j <= max ; j++){
                prime[i * j] = 0;
            }
        }
    }
}


int main(int argc, char *argv[])
{
    long int N = atoi(argv[1]);
    for(long int i = 0 ; i < 1000000; i++){
        prime[i] = -1;
    }
    MyData PARAMETER[NUMBER_OF_THREADS];
    DWORD ThreadId[NUMBER_OF_THREADS];
    HANDLE ThreadHandle[NUMBER_OF_THREADS];
    for(int i = 0 ; i < NUMBER_OF_THREADS ; i++){
        PARAMETER[i].i = i + 2;
        PARAMETER[i].Max = N;
        ThreadHandle[i] = CreateThread(
            NULL,
            0,
            IsPrimeSieve,
            &PARAMETER[i],
            0,
            &ThreadId[i]
        );
    }
    WaitForMultipleObjects(NUMBER_OF_THREADS,ThreadHandle,TRUE,INFINITE);
    for(int i = 0 ; i < NUMBER_OF_THREADS ; i++){
        CloseHandle(ThreadHandle[i]);
    }

    printf("Prime Numbers less than or equal to %ld :\n",N);
    long int count = 0;
    for(long int i = 0 ; i <= N; i++){
        if(prime[i] == 1){
            count++;
            printf("%ld ",i);
        }
    }
    printf("\nThere are a total of %d prime numbers\n",count);
    return 0;
}