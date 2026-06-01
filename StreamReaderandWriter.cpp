#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    // deklarasi variabel baris untuk menyimpan data string
    string baris;

    // membuka file dalam mode tulis
    ofstream outfile;
    // menunjukan ke sebuah nama file
    outfile.open("contohfile.txt");

    cout << ">= Menulis file, \'q\' untuk keluar" << endl;

    // unlimited loop untuk menulis file
    while (true)
    {
        cout << "- ";
        // Mendapat setiap karakter udalam satu baris
        getline(cin, baris);
        // kondisi false jika baris hanya berisi karakter q
        if (baris == "q")
            break;
        // menulis dan memasukkan nilai dari variabel baris kedalam file
        outfile << baris << endl;
    }
    // menutup file setelah penulisan selesai
    outfile.close();

    // membuka file dalam mode baca
    ifstream infile;
}