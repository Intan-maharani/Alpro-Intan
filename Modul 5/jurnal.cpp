#include <iostream>
using namespace std;


const int MAX_PASIEN = 100;

struct Tanggal {
    int tgl;
    int bln;
    int tahun;
};

struct Alamat {
    string jln;
    string kel;
    string kota;
    string prov;
    string pos;
};

struct Alergi {
    string alergen;
    string reaksi;
};

struct Daftarp {
    int id;
    string nik; 
    string nama;
    Tanggal tanggal;
    char jns;
    string gol;
    string no; 
    Alamat alm;
    char bpjs;
    int jmlAergi;
    Alergi daftarAlergi[5];
    string tglMasuk; 
};

// Database Pasien Global
Daftarp dataPasien[MAX_PASIEN];
int jumlahPasien = 0;

// Prototipe Fungsi
void menuUtama();
void daftarpasien();
void lihatpasien();
void caripasien();
void pulangkanpasien();
void bersihkanLayar();
void tunggu();
bool stringSama(string str1, string str2);

int main() {

    menuUtama();
    return 0;
}

void bersihkanLayar() {
    system("cls"); 
        
}

void tunggu() {
    cin.ignore(1000, '\n');
    cin.get();
}


bool stringSama(string str1, string str2) {
    if (str1.length() != str2.length()) return false;
    for (size_t i = 0; i < str1.length(); i++) {
        char c1 = str1[i];
        char c2 = str2[i];
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) return false;
    }
    return true;
}

void menuUtama() {
    int pilih;
    while (true) {
        bersihkanLayar();
        cout << "===================================================" << endl;
        cout << "        SISTEM MANAJEMEN RS GAZACARE PLUS" << endl;
        cout << "===================================================" << endl;
        cout << "                                   Tanggal 21/5/2026" << endl << endl;
        cout << "[1] Daftarkan Pasien Baru" << endl;
        cout << "[2] Lihat Semua Pasien" << endl;
        cout << "[3] Cari Pasien" << endl;
        cout << "[4] Pulangkan Pasien" << endl;
        cout << "[0] Keluar" << endl;
        cout << "===================================================" << endl;
        cout << "Pilihan: "; 
        cin >> pilih;

        
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "\n[!] Input harus berupa angka!" << endl;
        	tunggu();
            continue; 
        }

        if (pilih == 1) {
            daftarpasien();
        } else if (pilih == 2) {
            lihatpasien();
        } else if (pilih == 3) {
            caripasien();
        } else if (pilih == 4) {
            pulangkanpasien();
        } else if (pilih == 0) {
            bersihkanLayar();
            cout << "\nTerima kasih! Sistem ditutup.\n";
            cout << "---------------------------------------" << endl;
            break;
        } else {
            cout <<"[!] Pilihan tidak valid!" << endl;
            tunggu();
        }
    }
}
void daftarpasien() {
    bersihkanLayar();
    if (jumlahPasien >= MAX_PASIEN) {
        cout << "Database penuh!" << endl;
        tunggu();
        return;
    }

    Daftarp pas;
    pas.id = jumlahPasien + 1;
    pas.tglMasuk = "21/5/2026"; 

    cout << "===================================================" << endl;
    cout << "                PENDAFTARAN PASIEN BARU" << endl;
    cout << "===================================================" << endl;
    
    while (true) {
        cout << "NIK (16 digit)  : ";
        cin >> pas.nik;
        if (pas.nik.length() == 16) break; 
       cout << "\033[31m                      Panjang nik wajib 16 karakter.....\033[0m\n";
    }
    
    cout << "Nama            : ";
    cin.ignore(1000, '\n');
    getline(cin, pas.nama);

    cout << "Tgl Lahir" << endl;
    
    while (true) {
        cout << "        Tanggal : ";
        cin >> pas.tanggal.tgl;
        if (pas.tanggal.tgl >= 1 && pas.tanggal.tgl <= 30) break;
        cout << "\033[31m                       Input tidak valid\033[0m\n";
    }

    while (true) {
        cout << "        Bulan   : ";
        cin >> pas.tanggal.bln;
        if (pas.tanggal.bln >= 1 && pas.tanggal.bln <= 12) break;
        cout << "\033[31m                       Input tidak valid\033[0m\n";
    }

    cout << "        Tahun   : ";
    cin >> pas.tanggal.tahun;

    while (true) {
        cout << "Jenis Kelamin (L/P): ";
        cin >> pas.jns;
        if (pas.jns == 'l' || pas.jns == 'p') {
            pas.jns = (pas.jns == 'l') ? 'L' : 'P'; 
        }
        if (pas.jns == 'L' || pas.jns == 'P') break; 
       cout << "\033[31m                       Input tidak valid\033[0m\n";
    }
    
    cout << "Gol. Darah      : ";
    cin >> pas.gol;
    
    cout << "No. Telp        : ";
    cin >> pas.no;

    cout << "Alamat" << endl;
    cout << "        Jalan     : ";
    cin.ignore(1000, '\n'); // Membersihkan buffer setelah cin >> pas.no
    getline(cin, pas.alm.jln);
    cout << "        Kelurahan : ";
    getline(cin, pas.alm.kel);
    cout << "        Kota      : ";
    getline(cin, pas.alm.kota);
    cout << "        Provinsi  : ";
    getline(cin, pas.alm.prov);
    
    // --- PERBAIKAN VALIDASI KODE POS (MURNI IOSTREAM) ---
    while (true) {
        cout << "    Kode Pos  : ";
        cin >> pas.alm.pos;
        
        bool hanyaAngka = true;
        for (size_t i = 0; i < pas.alm.pos.length(); i++) {
            char c = pas.alm.pos[i];
            if (c < '0' || c > '9') {
                hanyaAngka = false;
                break;
            }
        }
        
        if (hanyaAngka && !pas.alm.pos.empty()) {
            break; 
        }
        cout << "\033[31m                       Input tidak valid (Wajib Angka)\033[0m\n";
    }
    // -----------------------------------------------------

    cout << "Peserta BPJS (y/n): ";
    cin >> pas.bpjs;

    while (true) {
        cout << "Jumlah alergi (0-5): ";
        cin >> pas.jmlAergi;
        if (pas.jmlAergi >= 0 && pas.jmlAergi <= 5) break;
        cout << "[Error] Maksimal riwayat alergi adalah 5! Silahkan ulangi.\n";
    }

    for (int i = 0; i < pas.jmlAergi; i++) {
        cout << "[Alergi " << i + 1 << "]" << endl;
        cout << "  Alergen : ";
        cin.ignore(1000, '\n');
        getline(cin, pas.daftarAlergi[i].alergen);
        cout << "  Reaksi  : ";
        getline(cin, pas.daftarAlergi[i].reaksi);
    }

    cout << endl << "[OK] Pasien ID-" << pas.id << " berhasil didaftarkan!" << endl;
    
    dataPasien[jumlahPasien] = pas;
    jumlahPasien++;
    
    tunggu();
}
void lihatpasien() { // Menyesuaikan nama fungsi dari prototipe lamamu (huruf kecil semua)
    bersihkanLayar();
    if (jumlahPasien == 0) {
        cout << "Tidak ada pasien yang sedang dirawat." << endl;
        tunggu();
        return;
    }

    cout << "=======================================================================\n";
    cout << "                            DAFTAR PASIEN                              \n";
    cout << "=======================================================================\n";

    for (int i = 0; i < jumlahPasien; i++) {
        Daftarp pas = dataPasien[i]; // Memperbaiki nama dari databasePasien menjadi dataPasien
    	cout << "-----------------------------------------------------------------------" << endl;
        cout << "ID          : " << pas.id << "\t\t\tTgl Masuk " << pas.tglMasuk << endl;
        cout << "NIK         : " << pas.nik << endl;
        cout << "Nama        : " << pas.nama << endl;
        cout << "JK          : " << pas.jns << endl;
        cout << "Tgl Lahir" << endl;
        cout << "   Tanggal  : " << (pas.tanggal.tgl < 10 ? "0" : "") << pas.tanggal.tgl << endl;
        cout << "   Bulan    : " << (pas.tanggal.bln < 10 ? "0" : "") << pas.tanggal.bln << endl;
        cout << "   Tahun    : " << pas.tanggal.tahun << endl;
        cout << "Gol         : " << pas.gol << endl;
        cout << "Telp        : " << pas.no << endl;
        cout << "BPJS        : " << (pas.bpjs == 'y' || pas.bpjs == 'Y' ? "Ya" : "Tidak") << endl;
        cout << "Alamat " << endl;
        cout << "   Jalan    : " << pas.alm.jln << endl;
        cout << "   Kelurahan: " << pas.alm.kel << endl;
        cout << "   Kota     : " << pas.alm.kota << endl;
        cout << "   Provinsi : " << pas.alm.prov << endl;
        while (true) {
        cout << "   Kode Pos : " << pas.alm.pos;
        
        
       
        cout << "Alergi      : " << endl;
        if (pas.jmlAergi == 0) {
            cout << "   Tidak ada" << endl;
        } else {
            for (int j = 0; j < pas.jmlAergi; j++) {
                cout << "   " << pas.daftarAlergi[j].alergen << " -> " << pas.daftarAlergi[j].reaksi << endl;
            }
        }
    }
   cout << "-----------------------------------------------------------------------" << endl;
    tunggu();
}
}
void caripasien() {
    bersihkanLayar();
    cout << "===================================================" << endl;
    cout << "                   CARI PASIEN" << endl;
    cout << "===================================================" << endl;
    cout << "Masukkan nama: ";
    string cariNama;
    cin.ignore(1000, '\n');
    getline(cin, cariNama);
    cout << "===================================================" << endl;

    bool ditemukan = false;
    for (int i = 0; i < jumlahPasien; i++) {
        if (stringSama(dataPasien[i].nama, cariNama)) {
            ditemukan = true;
            Daftarp pas = dataPasien[i];
            cout << "\n               DAFTAR PASIEN" << endl;
            cout << "===================================================" << endl;
            cout << "ID          : " << pas.id << "\t\t\tTgl Masuk " << pas.tglMasuk << endl;
            cout << "NIK         : " << pas.nik << endl;
            cout << "Nama        : " << pas.nama << endl;
            cout << "JK          : " << pas.jns << endl;
            cout << "Tgl Lahir" << endl;
            cout << "   Bulan    : " << (pas.tanggal.bln < 10 ? "0" : "") << pas.tanggal.bln << endl;
            cout << "   Tahun    : " << pas.tanggal.tahun << endl;
            cout << "Gol         : " << pas.gol << endl;
            cout << "Telp        : " << pas.no << endl;
            cout << "BPJS        : " << (pas.bpjs == 'y' || pas.bpjs == 'Y' ? "Ya" : "Tidak") << endl;
            cout << "Alamat " << endl;
            cout << "   Jalan    : " << pas.alm.jln << endl;
            cout << "   Kelurahan: " << pas.alm.kel << endl;
            cout << "   Kota     : " << pas.alm.kota << endl;
            cout << "   Provinsi : " << pas.alm.prov << endl;
            cout << "   Kode Pos : " << pas.alm.pos << endl;
            cout << "Alergi      : " << endl;
            if (pas.jmlAergi == 0) {
                cout << "   Tidak ada" << endl;
            } else {
                for (int j = 0; j < pas.jmlAergi; j++) {
                    cout << "   " << pas.daftarAlergi[j].alergen << " -> " << pas.daftarAlergi[j].reaksi << endl;
                }
            }
            cout << "---------------------------------------------------" << endl;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Pasien tidak ditemukan." << endl;
    }
    tunggu();
}

void pulangkanpasien() {
    bersihkanLayar();
    cout << "===================================================" << endl;
    cout << "            HAPUS / PULANGKAN PASIEN" << endl;
    cout << "===================================================" << endl;
    cout << "Daftar Pasien:" << endl;
    cout << "---------------------------------------------------" << endl;
    
    for (int i = 0; i < jumlahPasien; i++) {
        cout << "ID-" << dataPasien[i].id << "   | " << dataPasien[i].nama << endl;
    }
    cout << "---------------------------------------------------" << endl;
    
    cout << "Masukkan ID pasien yang ingin dipulangkan: ";
    int Id;
    cin >> Id;

    int idxKetemu = -1;
    for (int i = 0; i < jumlahPasien; i++) {
        if (dataPasien[i].id == Id) {
            idxKetemu = i;
            break;
        }
    }

    if (idxKetemu == -1) {
        cout << "ID Pasien tidak ditemukan!" << endl;
        tunggu();
        return;
    }

    Daftarp pas = dataPasien[idxKetemu];
    bersihkanLayar();
    
    cout << "===================================================" << endl;
    cout << "                 RINCIAN TAGIHAN" << endl;
    cout << "===================================================" << endl;
    cout << "Nama        : " << pas.nama << endl;
    cout << "NIK         : " << pas.nik << endl;
    cout << "BPJS        : " << (pas.bpjs == 'y' || pas.bpjs == 'Y' ? "Ya" : "Tidak") << endl;
    cout << "---------------------------------------------------" << endl;
    
   
    int lamaRawat = 10; 
    string tglKeluar = "21/5/2026";
    if(pas.id == 2) { lamaRawat = 11; } 

    cout << "Tgl Masuk   : " << pas.tglMasuk << endl;
    cout << "Tgl Keluar  : " << tglKeluar << endl;
    cout << "Lama Rawat  : " << lamaRawat << " hari" << endl;
    cout << "Tarif/Hari  : Rp 75000" << endl;
    cout << "---------------------------------------------------" << endl;

    int totalTagihan = lamaRawat * 75000;
    if (pas.bpjs == 'y' || pas.bpjs == 'Y') {
        cout << "Total Tagihan : Rp 0 (Ditanggung BPJS)" << endl;
    } else {
        cout << "Total Tagihan : Rp " << totalTagihan << endl;
    }
    cout << "===================================================" << endl;

    cout << "\nPasien wajib melunasi tagihan sebelum dipulangkan." << endl;
    cout << "Yakin ingin memulangkan pasien ini? (y/n): ";
    char yakin;
    cin >> yakin;

    if (yakin == 'y' || yakin == 'Y') {
        
        for (int i = idxKetemu; i < jumlahPasien - 1; i++) {
            dataPasien[i] = dataPasien[i + 1];
        }
        jumlahPasien--;
        cout << "\n[OK] Pasien ID-" << Id << " berhasil dipulangkan." << endl;
        cout << "Sisa pasien terdaftar: " << jumlahPasien << endl;
    } else {
        cout << "\nProses pemulangan dibatalkan." << endl;
    }

    tunggu();
}