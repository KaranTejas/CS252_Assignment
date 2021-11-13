#include<stdio.h>
#include<windows.h>

#define NUMBER_OF_THREADS 6

DWORD WINAPI PrintParameters1(int i){
    printf("%d\n",i);
    return 0;
}
DWORD WINAPI PrintParameters2(int i){
    printf("%d\n",i + 1);
    return 0;
}
DWORD WINAPI PrintParameters3(int i){
    printf("%d\n",i + 2);
    return 0;
}
DWORD WINAPI PrintParameters4(int i){
    printf("%d\n",i + 3);
    return 0;
}
DWORD WINAPI PrintParameters5(int i){
    printf("%d\n",i + 4);
    return 0;
}
DWORD WINAPI PrintParameters6(int i){
    printf("%d\n",i + 5);
    return 0;
}

DWORD WINAPI (*PrintFunct[NUMBER_OF_THREADS])() = {
    PrintParameters1,
    PrintParameters2,
    PrintParameters3,
    PrintParameters4,
    PrintParameters5,
    PrintParameters6
};

int main(int argc, char *argv[])
{
    DWORD ThreadId[NUMBER_OF_THREADS];
    HANDLE ThreadHandle[NUMBER_OF_THREADS];
    for(int i = 0 ; i < NUMBER_OF_THREADS ; i++){
        ThreadHandle[i] = CreateThread(
            NULL,
            0,
            *PrintFunct[i],
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
