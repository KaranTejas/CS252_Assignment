#include<stdio.h>
#include<windows.h>

DWORD WINAPI PrintParameters(int i){
    printf("%d\n",i);
    return 0;
}

int main(int argc, char *argv[])
{
    DWORD ThreadId;
    HANDLE ThreadHandle;

    ThreadHandle = CreateThread(
        NULL,
        0,
        PrintParameters,
        atoi(argv[1]),
        0,
        &ThreadId
    );
    WaitForSingleObject(ThreadHandle,INFINITE);

    printf("%d,%s",argc,argv[1]);
    return 0;
}
