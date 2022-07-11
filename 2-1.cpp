#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
    const int loop = 65536;
    const int n = 65536;
    
    // volatile はレジスタ操作の時に使う
    // 最適化抑制 
    volatile float a = (float)rand();
    volatile float b = (float)rand();
    volatile float c = (float)rand();
 
    float x[n], y[n];
    for (int i=0; i<n; i++) {
        x[i] = (float)rand();
    }

    // 計測開始
    clock_t startTime = clock();

    // 主となる処理
    #pragma omp parallel for
    for (int j=0; j<loop; j++) 
        for (int i=0; i<n; i++) 
            y[i] = a*x[i] + b*x[i] + c*x[i];

    // 計測終了
    clock_t stopTime = clock();

    float etime = (float)(stopTime - startTime) / CLOCKS_PER_SEC;
    printf("elapsed time = %15.7f sec\n", etime);

    return 0;
}
