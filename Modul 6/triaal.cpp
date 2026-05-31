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



struct Comit {
    string id;
    string pesan;
    string penulis;
    string stempelWaktu;
};

struct Branch{
    string nama;
    Comit* daftarComit;        
    int jumlahComit;
    int kapasitasComit;
};

struct Repositori {
    string nama;
    Cabang* daftarCabang;      
    int jumlahCabang;
    int kapasitasCabang;
    string namaCabangAktif;
};

void comitKeCabang(Cabang& cabang, const string& pesanComit, const string& namaPenulis, const string& idHash) {
    if (cabang.jumlahComit >= cabang.kapasitasComit) {
        cabang.kapasitasComit = (cabang.kapasitasComit == 0) ? 4 : cabang.kapasitasComit * 2;
        Comit* ComitBaru = new Comit[cabang.kapasitasComit];
        for (int i = 0; i < cabang.jumlahComit; i++) {
            ComitBaru[i] = cabang.daftarComit[i];
        }
        delete[] cabang.daftarComit; 
        cabang.daftarComit = ComitBaru;
    }
    
    cabang.daftarComit[cabang.jumlahComit].id = idHash;
    cabang.daftarComit[cabang.jumlahComit].pesan = pesanComit;
    cabang.daftarComit[cabang.jumlahComit].penulis = namaPenulis;
    cabang.daftarComit[cabang.jumlahComit].stempelWaktu = WaktuSekarang();
    cabang.jumlahComit++;
}


void tambahCabangKeRepo(Repositori& repo, const string& namaCabangBaru, Cabang* cabangAsal = nullptr) {
    if (repo.jumlahCabang >= repo.kapasitasCabang) {
        repo.kapasitasCabang = (repo.kapasitasCabang == 0) ? 2 : repo.kapasitasCabang * 2;
        Cabang* cabangBaru = new Cabang[repo.kapasitasCabang];
        for (int i = 0; i < repo.jumlahCabang; i++) {
            cabangBaru[i] = repo.daftarCabang[i];
        }
        delete[] repo.daftarCabang;
        repo.daftarCabang = cabangBaru;
    }

    Cabang& cbBaru = repo.daftarCabang[repo.jumlahCabang];
    cbBaru.name = namaCabangBaru;
    cbBaru.jumlahComit = 0;
    cbBaru.kapasitasComit = 4;
    cbBaru.daftarComit = new Komit[cbBaru.kapasitasComit];

    
    if (cabangAsal != nullptr) {
        for (int i = 0; i < cabangAsal->jumlahKomit; i++) {
            tambahKomitKeCabang(cbBaru, cabangAsal->daftarComit[i].pesan, cabangAsal->daftarComit[i].penulis, cabangAsal->daftarComit[i].id);
            cbBaru.daftarComit[i].stempelWaktu = cabangAsal->daftarComit[i].stempelWaktu;
        }
    }
    repo.jumlahCabang++;
}


Cabang* ambilCabangAktif(Repositori& repo) {
    for (int i = 0; i < repo.jumlahCabang; i++) {
        if (repo.daftarCabang[i].name == repo.namaCabangAktif) {
            return &repo.daftarCabang[i];
        }
    }
    return nullptr;
}


void bersihkanMemoriRepositori(Repositori& repo) {
    for (int i = 0; i < repo.jumlahCabang; i++) {
        delete[] repo.daftarCabang[i].daftarKomit;
    }
    delete[] repo.daftarCabang;
}
