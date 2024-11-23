#include <stdio.h>
#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>

__global__ void vector_add(int* A, int* B, int* C, int N) {
    int id = threadIdx.x;
    C[id] = A[id] + B[id];
}



int main( int argc, char** argv )
{
    int N = 3;
    int a[N] = {7, 2 , 3};
    int b[N] = {6, 4, 5};
    int c[N];
    int* A, *B, *C;
    cudaMalloc((void**)&A, sizeof(int) * N);
    cudaMalloc((void**)&B, sizeof(int) * N);
    cudaMalloc((void**)&C, sizeof(int) * N);

    cudaMemcpy(A, a, sizeof(int) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(B, b, sizeof(int) * N, cudaMemcpyHostToDevice);

    vector_add<<<1, 3>>>(A, B, C, N);

    cudaMemcpy(c, C, sizeof(int) * N, cudaMemcpyDeviceToHost);
    for (int i = 0; i < N; ++i) {
        printf("Index %d is %d\n", i, c[i]);
    }

    cudaFree(A);cudaFree(B);cudaFree(C);

    cudaDeviceSynchronize();

    return 0;
}
