__global__ void dot_product(int* A, int* B, int* C, int N) {
    __shared__ int tmp[3];
    int i = threadIdx.x;
    tmp[i] = A[i] * B[i];

    __syncthreads();
    int sum = 0;
    if (i == 0) {
        for (int j = 0; j < 3; ++j) sum += tmp[j];

        *C = sum;
    }
    // split the data into smaller tiles.
    // 
}
