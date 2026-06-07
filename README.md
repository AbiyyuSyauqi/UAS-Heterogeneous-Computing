# Matrix Multiplication: Heterogeneous Computing (OpenMP & OpenCL)

## 👥 Nama Penyusun Proyek
Proyek ini disusun oleh kelompok (S1 Kecerdasan Artifisial 2025):
1. Abiyyu Syauqi Admaja 25032014038
2. Ilmanza Nafis Adidarma 25032014030
3. Evans Lordy Arrow Sarumaha 25032014046

## 👥 Nama Dosen Mata Kuliah Arsitektur dan Sistem Komputer
1. Harmon Prayogi, M.Sc.
2. Dr. Widi Aribowo, S.T., M.T.

## 📝 Deskripsi Singkat Proyek dan Fiturnya
Proyek ini mendemonstrasikan implementasi *Heterogeneous Computing* dengan membandingkan tiga metode komputasi dalam melakukan operasi Perkalian Matriks (Matrix Multiplication):
1. **Sequential:** Eksekusi standar menggunakan 1 *core* CPU.
2. **OpenMP (CPU Parallelism):** Membagi beban kerja ke dalam beberapa *thread* pada *multi-core* CPU.
3. **OpenCL (GPU/Accelerator Parallelism):** Memanfaatkan arsitektur *workgroup* untuk mengeksekusi *kernel* secara masif paralel di GPU.

Fitur utama dari proyek ini adalah kemampuan *benchmarking* (pengukuran waktu) secara *real-time* untuk menganalisis efisiensi, *speedup*, dan limitasi sistem.

## 🚀 Langkah-langkah Cara Menjalankan
Pastikan *compiler* GCC (`g++`) dan *driver* OpenCL sudah terinstal.

1. **Kompilasi Kode Sequential & OpenMP:**
   g++ -fopenmp src/matrix_omp.cpp -o test/run_omp

2. **Kompilasi Kode OpenCL:**
   g++ src/matrix_ocl.cpp -lOpenCL -o test/run_ocl

3. **Jalankan Simulasi:**
   ./test/run_omp
   ./test/run_ocl

*(Catatan: Output terminal dibuat menggunakan karakter standar ASCII untuk menghindari isu encoding karakter yang corrupt pada console).*

## 🎥 Link Video Penjelasan Proyek
[Masukkan Link YouTube Kalian di Sini]
