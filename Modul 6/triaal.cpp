#include <iostream>
#include <string>
#include <ctime>

using namespace std;

//warna untuk output kode
#define WARNA_RESET   "\033[0m"
#define WARNA_HIJAU   "\033[1;32m"
#define WARNA_KUNING  "\033[1;33m"
#define WARNA_MERAH   "\033[1;31m"
#define WARNA_SIAN    "\033[1;36m"
#define WARNA_ABU     "\033[0;90m"
#define WARNA_PUTIH   "\033[1;37m"


string Hash(int idCommit) {
    const char Hex[] = "0123456789abcdef";
    string hasilHash = "";
    unsigned int nilai = idCommit * 2654435761u; 
    for (int i = 0; i < 7; i++) {
        hasilHash = karakterHex[nilai & 0xF] + hasilHash;
        nilai >>= 4;
    }
    return hasilHash;
}


string WaktuSekarang() {
    char wadah[20];
    time_t sekarang = time(nullptr); 
    strftime(wadah, sizeof(wadah), "%Y-%m-%d %H:%M", localtime(&sekarang));
    return string(wadah);
}

void bersihkanLayar() {
    cout << "\033[2J\033[H"; 
}

void Enter() {
    cout << "Press Enter..."; 
    cin.get();
}



struct Komit {
    string id;
    string pesan;
    string penulis;
    string stempelWaktu;
};
