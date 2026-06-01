#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <sstream>
using namespace std;

class TokoElektronik
{
private:
    array<string, 3> etalase;

public:
    TokoElektronik()
    {
        etalase[0] = "Smartphone Samsung Galaxy";
        etalase[1] = "Laptop Asus ROG";
        etalase[2] = "Smart TV LG 43 Inch";
    }

    string ambilProduk(size_t nomorRak)
    {
        try
        {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range &e)
        {
            string pesanError = "Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!";
            throw runtime_error(pesanError);
        }
    }
};

const string FILE_NAME = "gudang.txt";

void readGudang()
{
    ifstream file(FILE_NAME);
    string baris;
    cout << "\n=== DAFTAR BARANG DI GUDANG (FILE) ===\n";

    if (!file.is_open())
    {
        cout << "[Info] File gudang belum dibuat atau masih kosong.\n";
        return;
    }

    int nomor = 1;
    bool adaData = false;
    while (getline(file, baris))
    {
        if (!baris.empty())
        {
            cout << nomor << ". " << baris << endl;
            nomor++;
            adaData = true;
        }
    }

    if (!adaData)
    {
        cout << "(Gudang Kosong)\n";
    }
    file.close();
}

void createBarang()
{
    ofstream file(FILE_NAME, ios::app);
    if (!file.is_open())
    {
        cout << "Gagal membuka file gudang!\n";
        return;
    }

    string namaBarang;
    cout << "Masukkan nama barang baru: ";
    cin.ignore();
    getline(cin, namaBarang);

    if (!namaBarang.empty())
    {
        file << namaBarang << "\n";
        cout << "Sukses: Barang \"" << namaBarang << "\" berhasil ditambahkan ke gudang.\n";
    }
    file.close();
}

void updateBarang()
{
    readGudang();
    ifstream fileIn(FILE_NAME);
    if (!fileIn.is_open())
        return;

    string baris;
    array<string, 100> listBarang;
    int totalBarang = 0;

    while (getline(fileIn, baris))
    {
        if (!baris.empty())
        {
            listBarang[totalBarang] = baris;
            totalBarang++;
        }
    }
    fileIn.close();

    if (totalBarang == 0)
        return;

    int pilihan;
    cout << "Pilih nomor barang yang ingin diubah: ";
    cin >> pilihan;

    if (pilihan > 0 && pilihan <= totalBarang)
    {
        string namaBaru;
        cout << "Masukkan nama baru untuk \"" << listBarang[pilihan - 1] << "\": ";
        cin.ignore();
        getline(cin, namaBaru);

        listBarang[pilihan - 1] = namaBaru;

        ofstream fileOut(FILE_NAME);
        for (int i = 0; i < totalBarang; i++)
        {
            fileOut << listBarang[i] << "\n";
        }
        fileOut.close();
        cout << "Sukses: Data barang berhasil diperbarui!\n";
    }
    else
    {
        cout << "Pilihan tidak valid!\n";
    }
}

void deleteBarang()
{
    readGudang();
    ifstream fileIn(FILE_NAME);
    if (!fileIn.is_open())
        return;

    string baris;
    array<string, 100> listBarang;
    int totalBarang = 0;

    while (getline(fileIn, baris))
    {
        if (!baris.empty())
        {
            listBarang[totalBarang] = baris;
            totalBarang++;
        }
    }
    fileIn.close();

    if (totalBarang == 0)
        return;

    int pilihan;
    cout << "Pilih nomor barang yang ingin dihapus: ";
    cin >> pilihan;

    if (pilihan > 0 && pilihan <= totalBarang)
    {
        cout << "Sukses: Barang \"" << listBarang[pilihan - 1] << "\" berhasil dihapus.\n";

        ofstream fileOut(FILE_NAME);
        for (int i = 0; i < totalBarang; i++)
        {
            if (i != (pilihan - 1))
            {
                fileOut << listBarang[i] << "\n";
            }
        }
        fileOut.close();
    }
    else
    {
        cout << "Pilihan tidak valid!\n";
    }
}

void jalankanSimulasiEtalase(TokoElektronik &toko)
{
    cout << "\n=== JALANKAN SIMULASI EXCEPTION HANDLING ===\n";

    cout << "[Skenario 1] Mengambil barang di rak indeks ke-1...\n";
    try
    {
        string barang = toko.ambilProduk(1);
        cout << "Hasil Skenario 1: Berhasil mengambil -> " << barang << "\n\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Hasil Skenario 1 (Gagal Unexpected): " << e.what() << "\n\n";
    }

    cout << "[Skenario 2] Mengambil barang di rak indeks ke-5...\n";
    try
    {
        string barang = toko.ambilProduk(5);
        cout << "Hasil Skenario 2 (Sukses Unexpected): " << barang << "\n\n";
    }
    catch (const runtime_error &e)
    {
        cout << "Hasil Skenario 2 (Diharapkan): " << e.what() << "\n\n";
    }
}

int main()
{
    TokoElektronik tokoGibran;
    int pilihanMenu;

    do
    {
        readGudang();

        cout << "\n=========================================\n";
        cout << "       SISTEM MANAJEMEN GIBRAN JAYA      \n";
        cout << "=========================================\n";
        cout << "1. Tambah Barang Gudang (Create)\n";
        cout << "2. Ubah Barang Gudang (Update)\n";
        cout << "3. Hapus Barang Gudang (Delete)\n";
        cout << "4. Jalankan Simulasi Etalase (Exception Testing)\n";
        cout << "5. Keluar Aplikasi\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihanMenu;

        switch (pilihanMenu)
        {
        case 1:
            createBarang();
            break;
        case 2:
            updateBarang();
            break;
        case 3:
            deleteBarang();
            break;
        case 4:
            jalankanSimulasiEtalase(tokoGibran);
            break;
        case 5:
            cout << "Terima kasih telah menggunakan sistem Gibran Jaya.\n";
            break;
        default:
            cout << "Pilihan tidak valid! Silakan masukkan angka 1-5.\n";
            break;
        }

        cout << "\n";
        system("pause");
        system("clear || cls");

    } while (pilihanMenu != 5);

    return 0;
}