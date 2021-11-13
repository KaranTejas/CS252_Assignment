#include<stdio.h>
#include<windows.h>

#define NUMBER_OF_THREADS 6

DWORD WINAPI PrintParameters(int i){
    printf("%d\n",i);
    return 0;
}

int main(int argc, char *argv[])
{
    DWORD ThreadId[NUMBER_OF_THREADS];
    HANDLE ThreadHandle[NUMBER_OF_THREADS];
    for(int i = 0 ; i < NUMBER_OF_THREADS ; i++){
        ThreadHandle[i] = CreateThread(
            NULL,
            0,
            PrintParameters,
            atoi(argv[1]),
            0,
            &ThreadId[i]
        );
    }
    WaitForMultipleObjects(NUMBER_OF_THREADS,ThreadHandle,TRUE,INFINITE);
    for(int i = 0 ; i < NUMBER_OF_THREADS ; i++){
        CloseHandle(ThreadHandle[i]);
    }
    printf("%d,%s",argc,argv[1]);
    return 0;
}
