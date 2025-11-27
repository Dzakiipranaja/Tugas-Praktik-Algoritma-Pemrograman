# 📚 Class Schedule Manager (C++)

Program ini dibuat untuk mengelola jadwal kelas, mendeteksi bentrok, dan menyediakan fitur tambah, hapus, edit, serta pencarian jadwal. Program memastikan jadwal tidak bertabrakan berdasarkan hari, ruang, dan waktu.

---

## ✨ Fitur Utama

### ✔️ Input Jadwal  
Pengguna dapat memasukkan beberapa jadwal dengan data:
- Nama kelas  
- Hari (Senin–Sabtu)  
- Jam mulai (hh:mm)  
- Jam selesai (hh:mm)  
- Ruang kelas  

Semua input telah divalidasi agar sesuai format.

---

### ✔️ Deteksi Bentrok  
Program otomatis mendeteksi bentrok jika:
- Hari sama  
- Ruang sama  
- Rentang waktu bertumpukan  

Contoh bentrok:  
`08:00–10:00` dengan `09:30–11:00`.

---

### ✔️ Sorting Jadwal  
Jadwal akan otomatis diurutkan berdasarkan:
1. Urutan hari (Senin → Sabtu)
2. Jam mulai

---

### ✔️ CRUD Jadwal  
Menu interaktif tersedia:
- Tampilkan jadwal terurut  
- Cari jadwal berdasarkan nama kelas  
- Edit jadwal  
- Tambah jadwal baru  
- Hapus jadwal  
- Tampilkan jadwal bentrok  

---

## 🛠️ Cara Menjalankan Program

1. Pastikan compiler C++ sudah terinstal (GCC/MinGW/Clang/Visual Studio).
2. Simpan file program, misalnya:
