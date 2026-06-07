#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

// Penanganan header OpenCL agar kompatibel dengan berbagai OS
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

using namespace std;

const int N = 1024; // Ukuran matriks N x N

int main() {
    // 1. Inisialisasi Data di RAM CPU (Host Memory)
    size_t bytes = N * N * sizeof(float);
    vector<float> h_A(N * N, 1.5f);
    vector<float> h_B(N * N, 2.0f);
    vector<float> h_C(N * N, 0.0f);

    // 2. Setup OpenCL: Mencari Platform (Driver) dan Device (GPU)
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, NULL);

    cl_device_id device;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);

    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);

    // 3. Membaca file kernel.cl
    ifstream kernelFile("src/kernel.cl");
    string kernelSource((istreambuf_iterator<char>(kernelFile)), istreambuf_iterator<char>());
    const char* sourceCode = kernelSource.c_str();
    size_t sourceSize = kernelSource.size();

    cl_program program = clCreateProgramWithSource(context, 1, &sourceCode, &sourceSize, NULL);
    clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    cl_kernel kernel = clCreateKernel(program, "matrix_multiply", NULL);

    // 4. Alokasi Memori di VRAM GPU (Device Memory) & Transfer Data
    // Tahap ini sering menjadi "Memory Bottleneck" yang menyebabkan speedup tidak linier
    cl_mem d_A = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, bytes, h_A.data(), NULL);
    cl_mem d_B = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, bytes, h_B.data(), NULL);
    cl_mem d_C = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bytes, NULL, NULL);

    // 5. Mengatur Argumen untuk Kernel
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_A);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_B);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_C);
    clSetKernelArg(kernel, 3, sizeof(int), &N);

    // 6. Eksekusi Kernel secara Paralel (Mulai menghitung waktu komputasi)
    size_t globalSize[2] = {(size_t)N, (size_t)N};
    
    cout << "--- Matrix Multiplication " << N << "x" << N << " (OpenCL) ---" << endl;
    
    auto start_time = chrono::high_resolution_clock::now();
    
    // Memerintahkan GPU untuk memproses data dalam workgroup
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalSize, NULL, 0, NULL, NULL);
    clFinish(queue); // Tunggu sampai seluruh core GPU selesai bekerja
    
    // 7. Transfer kembali hasil (Matriks C) dari GPU ke RAM CPU
    clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, bytes, h_C.data(), 0, NULL, NULL);
    
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    // Output diset rapi tanpa karakter aneh
    cout << "[OK] OpenCL Time     : " << elapsed.count() << " seconds" << endl;

    // 8. Bersihkan memori (Sangat penting di C++)
    clReleaseMemObject(d_A);
    clReleaseMemObject(d_B);
    clReleaseMemObject(d_C);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    return 0;
}
