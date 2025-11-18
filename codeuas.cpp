#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Jadwal
{
    string namaKelas;
    string hari;
    string jamMulai;
    string jamSelesai;
    string ruang;
    bool bentrok = false;
};

// --- Fungsi bantu validasi hari ---
bool validHari(string hari)
{
    string daftarHari[5] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat"};
    for (int i = 0; i < 5; i++)
    {
        if (hari == daftarHari[i])
            return true;
    }
    return false;
}

// --- Fungsi bantu validasi format jam (hh:mm) ---
bool validJam(string jam)
{
    if (jam.size() != 5 || jam[2] != ':')
        return false;
    string hh = jam.substr(0, 2);
    string mm = jam.substr(3, 2);
    for (char c : hh + mm)
    {
        if (!isdigit(c))
            return false;
    }
    int jamInt = stoi(hh);
    int menitInt = stoi(mm);
    return (jamInt >= 0 && jamInt <= 23 && menitInt >= 0 && menitInt <= 59);
}

// --- Fungsi ubah jam ke menit ---
int konversiJamKeMenit(string jam)
{
    int jamInt = stoi(jam.substr(0, 2));
    int menitInt = stoi(jam.substr(3, 2));
    return jamInt * 60 + menitInt;
}

// --- Input jadwal dengan validasi ---
void inputJadwal(Jadwal data[], int &n)
{
    cout << "Masukkan jumlah jadwal: ";
    while (!(cin >> n) || n <= 0)
    {
        cout << "Input tidak valid! Masukkan angka positif: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        cout << "\nData ke-" << i + 1 << endl;

        cout << "Nama Kelas   : ";
        getline(cin, data[i].namaKelas);

        // Validasi hari
        do
        {
            cout << "Hari (Senin-Sabtu): ";
            getline(cin, data[i].hari);
            if (!validHari(data[i].hari))
                cout << "❌ Hari tidak valid! Coba lagi.\n";
        } while (!validHari(data[i].hari));

        // Validasi jam mulai
        do
        {
            cout << "Jam Mulai (hh:mm): ";
            getline(cin, data[i].jamMulai);
            if (!validJam(data[i].jamMulai))
                cout << "❌ Format jam salah! Gunakan format hh:mm (contoh: 08:30)\n";
        } while (!validJam(data[i].jamMulai));

        // Validasi jam selesai
        do
        {
            cout << "Jam Selesai (hh:mm): ";
            getline(cin, data[i].jamSelesai);
            if (!validJam(data[i].jamSelesai))
                cout << " Format jam salah! Gunakan format hh:mm (contoh: 10:00)\n";
            else if (konversiJamKeMenit(data[i].jamSelesai) <= konversiJamKeMenit(data[i].jamMulai))
                cout << " Jam selesai harus lebih besar dari jam mulai!\n";
            else
                break;
        } while (true);

        cout << "Ruang        : ";
        getline(cin, data[i].ruang);
    }
}

// --- Deteksi bentrok ---
void deteksiBentrok(Jadwal data[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (data[i].hari == data[j].hari && data[i].ruang == data[j].ruang)
            {
                int mulai1 = konversiJamKeMenit(data[i].jamMulai);
                int selesai1 = konversiJamKeMenit(data[i].jamSelesai);
                int mulai2 = konversiJamKeMenit(data[j].jamMulai);
                int selesai2 = konversiJamKeMenit(data[j].jamSelesai);

                if (mulai1 < selesai2 && selesai1 > mulai2)
                {
                    data[i].bentrok = true;
                    data[j].bentrok = true;
                }
            }
        }
    }
}

// --- Urutan hari ---
int urutanHari(string hari)
{
    string daftarHari[6] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    for (int i = 0; i < 6; i++)
    {
        if (hari == daftarHari[i])
            return i;
    }
    return 7;
}

// --- Bubble sort berdasarkan hari & jam mulai ---
void bubbleSortJadwal(Jadwal data[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            int hari1 = urutanHari(data[j].hari);
            int hari2 = urutanHari(data[j + 1].hari);

            if (hari1 > hari2 ||
                (hari1 == hari2 && konversiJamKeMenit(data[j].jamMulai) > konversiJamKeMenit(data[j + 1].jamMulai)))
            {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

// --- Tampilkan hasil ---
void tampilJadwal(Jadwal data[], int n)
{
    cout << "\n=== Daftar Jadwal Terurut (Tanpa Bentrok) ===\n";
    int no = 1;
    for (int i = 0; i < n; i++)
    {
        if (!data[i].bentrok)
        {
            cout << no++ << ". " << data[i].namaKelas << " | " << data[i].hari
                 << " | " << data[i].jamMulai << "-" << data[i].jamSelesai
                 << " | " << data[i].ruang << endl;
        }
    }

    cout << "\n=== Jadwal Bentrok Terdeteksi ===\n";
    bool adaBentrok = false;
    for (int i = 0; i < n; i++)
    {
        if (data[i].bentrok)
        {
            cout << "- " << data[i].namaKelas << " (" << data[i].hari << ", "
                 << data[i].ruang << ", " << data[i].jamMulai << "-" << data[i].jamSelesai << ")" << endl;
            adaBentrok = true;
        }
    }
    if (!adaBentrok)
        cout << "Tidak ada bentrok.\n";
}

// --- Main ---
int main()
{
    Jadwal data[50];
    int n;

    inputJadwal(data, n);
    deteksiBentrok(data, n);
    bubbleSortJadwal(data, n);
    tampilJadwal(data, n);

    return 0;
}