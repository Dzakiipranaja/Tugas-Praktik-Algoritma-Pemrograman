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


int cekHari(string hari)
{
    string d[6] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    for (int i = 0; i < 6; i++)
        if (hari == d[i])
            return i;
    return -1;
}


int parseMenit(string jam)
{
    if (jam.size() != 5 || jam[2] != ':')
        return -1;
    if (!isdigit(jam[0]) || !isdigit(jam[1]) ||
        !isdigit(jam[3]) || !isdigit(jam[4]))
        return -1;

    int hh = stoi(jam.substr(0, 2));
    int mm = stoi(jam.substr(3, 2));

    if (hh < 0 || hh > 23 || mm < 0 || mm > 59)
        return -1;

    return hh * 60 + mm;
}



void inputSatuJadwal(Jadwal &x)
{

    do
    {
        cout << "Nama Kelas (contoh TI K): ";
        getline(cin, x.namaKelas);

        if (x.namaKelas.empty())
            cout << "Nama kelas tidak boleh kosong!\n";

    } while (x.namaKelas.empty());

    do
    {
        cout << "Hari (contoh : Senin): ";
        getline(cin, x.hari);
        if (cekHari(x.hari) == -1)
            cout << "Hari tidak valid!\n";
    } while (cekHari(x.hari) == -1);

    do
    {
        cout << "Jam Mulai (hh:mm): ";
        getline(cin, x.jamMulai);
    } while (parseMenit(x.jamMulai) == -1);

    do
    {
        cout << "Jam Selesai (hh:mm): ";
        getline(cin, x.jamSelesai);

        int mulai = parseMenit(x.jamMulai);
        int selesai = parseMenit(x.jamSelesai);

        if (selesai == -1 || selesai <= mulai)
            cout << "Jam selesai tidak valid!\n";

    } while (parseMenit(x.jamSelesai) == -1 ||
             parseMenit(x.jamSelesai) <= parseMenit(x.jamMulai));

    do
    {
        cout << "Ruang (contoh : RF 7): ";
        getline(cin, x.ruang);

        if (x.ruang.empty())
            cout << "Ruang tidak boleh kosong!\n";

    } while (x.ruang.empty());
}



void inputJadwal(Jadwal data[], int &n)
{
    cout << "Masukkan jumlah jadwal: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        cout << "\nData ke-" << i + 1 << endl;
        inputSatuJadwal(data[i]);
    }
}



int findIndex(Jadwal data[], int n, string key)
{
    for (int i = 0; i < n; i++)
        if (data[i].namaKelas == key)
            return i;
    return -1;
}



void deteksiBentrok(Jadwal data[], int n)
{
    for (int i = 0; i < n; i++)
        data[i].bentrok = false;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {

            if (data[i].hari == data[j].hari && data[i].ruang == data[j].ruang)
            {

                int m1 = parseMenit(data[i].jamMulai);
                int s1 = parseMenit(data[i].jamSelesai);
                int m2 = parseMenit(data[j].jamMulai);
                int s2 = parseMenit(data[j].jamSelesai);

                if (m1 < s2 && s1 > m2)
                {
                    data[i].bentrok = true;
                    data[j].bentrok = true;
                }
            }
        }
    }
}



void bubbleSortJadwal(Jadwal data[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {

            int h1 = cekHari(data[j].hari);
            int h2 = cekHari(data[j + 1].hari);

            if (h1 > h2 ||
                (h1 == h2 && parseMenit(data[j].jamMulai) >
                                 parseMenit(data[j + 1].jamMulai)))
                swap(data[j], data[j + 1]);
        }
    }
}



void tampilJadwal(Jadwal data[], int n)
{
    deteksiBentrok(data, n);
    bubbleSortJadwal(data, n);

    cout << "\n=== JADWAL TERURUT ===\n";
    int no = 1;
    for (int i = 0; i < n; i++)
        if (!data[i].bentrok)
            cout << no++ << ". " << data[i].namaKelas << " | " << data[i].hari
                 << " | " << data[i].jamMulai << "-" << data[i].jamSelesai
                 << " | " << data[i].ruang << endl;

    cout << "\n=== JADWAL BENTROK ===\n";
    bool ada = false;
    for (int i = 0; i < n; i++)
        if (data[i].bentrok)
        {
            cout << "- " << data[i].namaKelas << " (" << data[i].hari << ", "
                 << data[i].ruang << ", " << data[i].jamMulai << "-"
                 << data[i].jamSelesai << ")\n";
            ada = true;
        }
    if (!ada)
        cout << "Tidak ada bentrok.\n";
}


void searchJadwal(Jadwal data[], int n)
{
    cin.ignore();
    string key;
    cout << "Masukkan nama kelas: ";
    getline(cin, key);

    int idx = findIndex(data, n, key);
    if (idx == -1)
        cout << "Tidak ditemukan.\n";
    else
        cout << "- " << data[idx].namaKelas << " | " << data[idx].hari
             << " | " << data[idx].jamMulai << "-" << data[idx].jamSelesai
             << " | " << data[idx].ruang << endl;
}


void editJadwal(Jadwal data[], int n)
{
    cin.ignore();
    string key;
    cout << "Masukkan nama kelas yang ingin diedit: ";
    getline(cin, key);

    int idx = findIndex(data, n, key);
    if (idx == -1)
    {
        cout << "Tidak ditemukan!\n";
        return;
    }

    inputSatuJadwal(data[idx]);
    cout << "Berhasil diperbarui!\n";
}


void tambahJadwal(Jadwal data[], int &n)
{
    cin.ignore();
    cout << "\n=== Tambah Jadwal ===\n";
    inputSatuJadwal(data[n]);
    n++;
    cout << "Jadwal berhasil ditambahkan!\n";
}


void hapusJadwal(Jadwal data[], int &n)
{
    cin.ignore();
    string key;
    cout << "Masukkan nama kelas yang akan dihapus: ";
    getline(cin, key);

    int idx = findIndex(data, n, key);
    if (idx == -1)
    {
        cout << "Tidak ditemukan!\n";
        return;
    }

    for (int i = idx; i < n - 1; i++)
        data[i] = data[i + 1];

    n--;
    cout << "Jadwal berhasil dihapus!\n";
}


int main()
{
    Jadwal data[50];
    int n;
    int pilihan;

    inputJadwal(data, n);

    do
    {
        cout << "\n=== MENU ===\n";
        cout << "1. Tampilkan Jadwal\n";
        cout << "2. Cari Jadwal\n";
        cout << "3. Edit Jadwal\n";
        cout << "4. Tambah Jadwal\n";
        cout << "5. Hapus Jadwal\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tampilJadwal(data, n);
            break;
        case 2:
            searchJadwal(data, n);
            break;
        case 3:
            editJadwal(data, n);
            break;
        case 4:
            tambahJadwal(data, n);
            break;
        case 5:
            hapusJadwal(data, n);
            break;
        case 0:
            cout << "Keluar...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }

    } while (pilihan != 0);

    return 0;
}