#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

const int N = 1024; // Ukuran matriks N x N

void multiply_sequential(const vector<float>& A, const vector<float>& B, vector<float>& C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0.0f;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

void multiply_openmp(const vector<float>& A, const vector<float>& B, vector<float>& C) {
    // Pragma OpenMP untuk membagi loop i ke berbagai thread
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0.0f;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

int main() {
    vector<float> A(N * N, 1.5f);
    vector<float> B(N * N, 2.0f);
    vector<float> C_seq(N * N, 0.0f);
    vector<float> C_omp(N * N, 0.0f);

    cout << "--- Matrix Multiplication " << N << "x" << N << " ---" << endl;

    // 1. Sequential Benchmark
    double start_seq = omp_get_wtime();
    multiply_sequential(A, B, C_seq);
    double end_seq = omp_get_wtime();
    cout << "[OK] Sequential Time : " << (end_seq - start_seq) << " seconds" << endl;

    // 2. OpenMP Benchmark
    double start_omp = omp_get_wtime();
    multiply_openmp(A, B, C_omp);
    double end_omp = omp_get_wtime();
    cout << "[OK] OpenMP Time     : " << (end_omp - start_omp) << " seconds" << endl;

    return 0;
}
