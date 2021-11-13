#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<limits.h>

#define NUMBER_OF_THREADS 50

// Assumption that given N < 1000000 to implement the Sieve of Eratosthenes algorithm to find Prime Numbers
int prime[1000000];

DWORD WINAPI IsPrime(long int N){
    for(int i = 2 ; i <= (int)sqrt(N); i++){
        if(N % 2 == 0){
            prime[N] = 0;
            return 0;
        }
    }
    prime[N] = 1;
    return 0;
}

DWORD WINAPI Multiple(long int N,long int MAX){
    for(int i = 2; N * i <= MAX ; i++){
        prime[i * N] = 0;
    }
    return 0;
}


int main(int argc, char *argv[])
{
    long int N = atoi(argv[1]);
    for(long int i = 0 ; i < 1000000; i++){
        prime[i] = -1;
    }
    DWORD ThreadId[NUMBER_OF_THREADS];
    HANDLE ThreadHandle[NUMBER_OF_THREADS];
    for(long int i = 2 ; i <= N ; i += NUMBER_OF_THREADS ){
        for(long int j = i ; j < i + NUMBER_OF_THREADS && j <= N ; j++){
            if(prime[j] == -1){
                IsPrime(j);
                Multiple(j,N);
            }
        }
    }
    printf("Prime Numbers less than or equal to %ld :\n",N);
    int count = 0;
    for(long int i = 0 ; i <= N; i++){
        if(prime[i] == 1){
            count++;
            printf("%ld ",i);
        }
    }
    printf("\nThere are a total of %d prime numbers\n",count);
    return 0;
}