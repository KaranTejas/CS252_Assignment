#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<limits.h>

double Average = 0;
int Maximum = INT_MIN;
int Minimum = INT_MAX;
int Median = 0;
double StandardDeviationMean = 0;
double StandardDeviationMedian = 0;

DWORD WINAPI AverageFunc(int *arr){
    int N = *arr;
    int sum = 0;

    for(int i = 1 ; i <= N ; i++){
        sum += *(arr + i);
    }

    Average = ((double) sum) / N;
    printf("Average = %lf\n",Average);
    return 0;
}

DWORD WINAPI MaximumFunc(int *arr){
    int N = *arr;

    for(int i = 1 ; i <= N ; i++){
        Maximum = Maximum > *(arr + i) ? Maximum : *(arr + i);
    }

    printf("Maximum = %d\n",Maximum);
    return 0;
}

DWORD WINAPI MinimumFunc(int *arr){
    int N = *arr;

    for(int i = 1 ; i <= N ; i++){
        Minimum = Minimum < *(arr + i) ? Minimum : *(arr + i);
    }

    printf("Minimum = %d\n",Minimum);
    return 0;
}

DWORD WINAPI MedianFunc(int *arr){
    int N = *arr;
    int temp;

    for(int i = N ; i >= 1 ; i--){
        for(int j = 1 ; j < i ; j++ ){
            if(*(arr+j) > *(arr + i)){
                temp = *(arr + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = temp;
            }
        }
    }

    if(N % 2){
        Median = *(arr + (int)(N + 1)/2 );
    }
    else{
        Median = (*(arr + (int)N/2) + *(arr + (int)N/2 + 1))/2;
    }

    printf("Median = %d\n",Median);
    return 0;
}

DWORD WINAPI StandardDeviationMeanFunc(int *arr){
    int N = *arr;
    double Var = 0;

    for(int i = 1 ; i <= N ; i++){
        Var += pow((Average - (double)*(arr + i)),2);
    }

    StandardDeviationMean = sqrt(Var/N);
    printf("Standard deviation about Mean = %.4lf\n",StandardDeviationMean);
    return 0;
}

DWORD WINAPI StandardDeviationMedianFunc(int *arr){
    int N = *arr;
    double Var = 0;

    for(int i = 1 ; i <= N ; i++){
        Var += pow((Median - (double)*(arr + i)),2);
    }

    StandardDeviationMedian = sqrt(Var/N);
    printf("Standard deviation about Median = %.4lf\n",StandardDeviationMedian);
    return 0;
}

// Storing the function addresses to use as callback functions while creating threads

DWORD WINAPI (*PrintFunct[6])() = {
    AverageFunc,
    MaximumFunc,
    MinimumFunc,
    MedianFunc,
    StandardDeviationMeanFunc,
    StandardDeviationMedianFunc
};

int main(int argc, char *argv[])
{
    DWORD QuantityThreadId[4],DeviationThreadId[2];
    HANDLE QuantityThreadHandle[4],DeviationThreadHandle[2];
    int *arr = (int*) malloc(argc * sizeof(int));

    // arr(0) stores the size of the given array
    *arr = argc - 1;
    for(int i = 1 ; i < argc ; i++)
    {
        *(arr + i) = atoi(argv[i]);
    }

    // First 4 callbacks functions are passed to 4 different threads

    for(int i = 0 ; i < 4 ; i++){
        QuantityThreadHandle[i] = CreateThread(
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)*PrintFunct[i],
            arr,
            0,
            &QuantityThreadId[i]
        );
    }

    WaitForMultipleObjects(4,QuantityThreadHandle,TRUE,INFINITE);
    for(int i = 0 ; i < 4 ; i++){
        CloseHandle(QuantityThreadHandle[i]);
    }

    // Last 2 functions calculate the Standard deviation using the previous functions
    // Two separate threads are used

    for(int i = 0 ; i < 2 ; i++){
        QuantityThreadHandle[i] = CreateThread(
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)*PrintFunct[i + 4],
            arr,
            0,
            &QuantityThreadId[i]
        );
    }

    WaitForMultipleObjects(2,QuantityThreadHandle,TRUE,INFINITE);
    for(int i = 0 ; i < 2 ; i++){
        CloseHandle(QuantityThreadHandle[i]);
    }

    return 0;
}
