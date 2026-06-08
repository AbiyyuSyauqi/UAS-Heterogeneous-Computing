# Implementasi Heterogeneous Computing: Analisis Komparatif Kinerja Perkalian Matriks Menggunakan Sequential, OpenMP, dan OpenCL 3.0

## 👥 Tim Pengembang
* **Abiyyu Syauqi Admaja** (25032014038) - [Pembedahan Arsitektur Kode, Live Demo Eksekusi OpenCL, & Manajemen Repositori]
* **Ilmanza Nafis Adidarma** (25032014030) - [Pemodelan Teori Dasar & Analisis Shared-Memory OpenMP]
* **Evans Lordy Arrow Sarumaha** (25032014046) - [Evaluasi Metrik Speedup & Analisis Bottleneck Bus PCIe]

---

## 📖 Ringkasan Eksekutif
Proyek ini bertujuan untuk mengevaluasi dan membandingkan kinerja komputasi untuk operasi Perkalian Matriks berukuran 1024x1024 elemen. Mengingat operasi ini merupakan fondasi utama dalam algoritma *Artificial Intelligence* yang bersifat *compute-intensive*, kami mengomparasikan tiga pendekatan eksekusi: **Sequential** (1 core CPU), **CPU-parallelism** berbasis *shared-memory* (OpenMP), dan **GPU-parallelism** berbasis arsitektur *Host-Device* (OpenCL 3.0). Fokus utama proyek ini adalah mengukur rasio *speedup* aktual dan menganalisis fenomena non-linearitas akselerasi perangkat keras.

## ⚙️ Metodologi & Pipeline
1. **Sequential (Baseline):** Eksekusi *nested loop* standar pada satu *thread* CPU untuk mendapatkan waktu komputasi acuan.
2. **CPU Parallelism (OpenMP):** Distribusi beban komputasi secara otomatis ke dalam beberapa *thread* CPU menggunakan direktif `#pragma omp parallel for` tanpa transfer data eksplisit.
3. **GPU Parallelism (OpenCL 3.0):** Alokasi *buffer* dan pemindahan komputasi dari RAM sistem (Host) ke VRAM (Device) melalui bus PCIe, dilanjutkan dengan eksekusi *kernel* secara masif menggunakan struktur *workgroup*.
4. **Benchmarking:** Pengukuran waktu eksekusi lokal pada tiap metode untuk kalkulasi *speedup* dan analisis Hukum Amdahl.

## 📊 Hasil dan Kesimpulan Singkat
* **Perbandingan Metrik:** OpenMP menghasilkan *speedup* **2.36x** (26.66 detik), sementara OpenCL 3.0 memberikan akselerasi yang sangat masif hingga **496.18x** (0.127 detik) dibandingkan eksekusi *Sequential* (63.015 detik).
* **Evaluasi Bottleneck:** Meskipun GPU sangat dominan, *speedup* yang dihasilkan tidak linier dengan jumlah *core* teoretisnya. Evaluasi arsitektural menunjukkan bahwa efisiensi GPU dibatasi oleh *memory bottleneck* akibat pola akses non-koalesen, *overhead* transfer data lintas bus PCIe, dan latensi inisialisasi *runtime* OpenCL.

---

## 📄 Laporan Lengkap (PDF)
Untuk pembahasan teoritis yang lebih mendalam, diagram alur eksekusi memori (Host-Device), landasan matematis, tinjauan pustaka, dan dokumentasi arsitektur sistem secara menyeluruh, silakan unduh dan baca laporan lengkap kami pada tautan berikut:

👉 **[Unduh Dokumen Laporan Lengkap (PDF)](https://drive.google.com/drive/folders/1e5UEWTwlbXzRQlF8tZitM8TpmYdr9CEM?usp=sharing)**

---
