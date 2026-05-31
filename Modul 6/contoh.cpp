#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Warna untuk output kode
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
        hasilHash = Hex[nilai & 0xF] + hasilHash; 
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


struct Cabang {
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
    cbBaru.nama = namaCabangBaru; 
    cbBaru.jumlahComit = 0;
    cbBaru.kapasitasComit = 4;
    cbBaru.daftarComit = new Comit[cbBaru.kapasitasComit];

    if (cabangAsal != nullptr) {
        for (int i = 0; i < cabangAsal->jumlahComit; i++) { 
            comitKeCabang(cbBaru, cabangAsal->daftarComit[i].pesan, cabangAsal->daftarComit[i].penulis, cabangAsal->daftarComit[i].id);
            cbBaru.daftarComit[i].stempelWaktu = cabangAsal->daftarComit[i].stempelWaktu;
        }
    }
    repo.jumlahCabang++;
}

Cabang* ambilCabangAktif(Repositori& repo) {
    for (int i = 0; i < repo.jumlahCabang; i++) {
        if (repo.daftarCabang[i].nama == repo.namaCabangAktif) {
            return &repo.daftarCabang[i];
        }
    }
    return nullptr;
}

void bersihkanMemoriRepositori(Repositori& repo) {
    for (int i = 0; i < repo.jumlahCabang; i++) {
        delete[] repo.daftarCabang[i].daftarComit;
    }
    delete[] repo.daftarCabang;
}

int main(int jumlahArgumen, char* argumen[]) {
    if (jumlahArgumen < 2) {
        cout << "[ERROR] Format jalankan program salah!" << endl;
        cout << "Gunakan: .\\gitsim <Username>" << endl; 
        return 1;
    }

    string namaPenulis = argumen[1]; 
    int totalComitGlobal = 0; 

    int jumlahRepo = 0;
    int kapasitasRepo = 4;
    Repositori* daftarRepositori = new Repositori[kapasitasRepo];
    int indeksRepoAktif = -1;

    bersihkanLayar();
    cout << "GITSIM" << endl; 
    cout << "Lightweight Git Simulator" << endl; 
    cout << "Author: " << namaPenulis << endl; 
    cout << "git init" << endl; 
    cout << "Repository name: "; 
    
    string namaRepoAwal;
    getline(cin, namaRepoAwal); 
    if (namaRepoAwal.empty()) {
        namaRepoAwal = "my-repo"; 
    }

    daftarRepositori[jumlahRepo].nama = namaRepoAwal;
    daftarRepositori[jumlahRepo].jumlahCabang = 0;
    daftarRepositori[jumlahRepo].kapasitasCabang = 2;
    daftarRepositori[jumlahRepo].daftarCabang = new Cabang[daftarRepositori[jumlahRepo].kapasitasCabang];
    daftarRepositori[jumlahRepo].namaCabangAktif = "main"; 
    
    tambahCabangKeRepo(daftarRepositori[jumlahRepo], "main");
    indeksRepoAktif = jumlahRepo;
    jumlahRepo++;

    cout << WARNA_HIJAU << "[OK] Initialized empty repository: " << namaRepoAwal << WARNA_RESET << endl; 
    cout << "On branch: " << WARNA_HIJAU << "main" << WARNA_RESET << endl; 
    Enter(); // Perbaikan: tekanEnter() -> Enter()

    while (true) {
        bersihkanLayar();
        Repositori& repoSaatIni = daftarRepositori[indeksRepoAktif];
        Cabang* cabangSaatIni = ambilCabangAktif(repoSaatIni);

        cout << "GITSIM Git Simulator" << endl; 
        cout << "Author: " << WARNA_HIJAU << namaPenulis << WARNA_RESET 
             << "   Repo: " << WARNA_HIJAU << repoSaatIni.nama << WARNA_RESET 
             << "   HEAD: " << WARNA_HIJAU << repoSaatIni.namaCabangAktif << WARNA_RESET 
             << " | [" << (indeksRepoAktif + 1) << "/" << jumlahRepo << "]" << endl; 
        
        cout << "[1] git commit" << endl; 
        cout << "[2] git log" << endl; 
        cout << "[3] git branch" << endl; 
        cout << "[4] git checkout" << endl; 
        cout << "[5] new repository" << endl; 
        cout << "[6] switch repository" << endl; 
        cout << "[0] exit" << endl; 
        cout << ">> ";

        string pilihanMenu;
        getline(cin, pilihanMenu);

        if (pilihanMenu == "1") {
            bersihkanLayar();
            cout << "GITSIM" << endl;
            cout << "Git Simulator" << endl;
            cout << "Author: " << namaPenulis << endl;
            cout << "git commit [" << WARNA_HIJAU << repoSaatIni.namaCabangAktif << WARNA_RESET << "]" << endl; 
            
            cout << "Message: "; 
            string pesanComit;
            getline(cin, pesanComit);
            
            cout << "Push commit? (y/n): "; 
            string konfirmasi;
            getline(cin, konfirmasi);

            if (konfirmasi == "y" || konfirmasi == "Y") {
                totalComitGlobal++;
                string hashBerikutnya = Hash(totalComitGlobal); // Perbaikan: buatHashPendek -> Hash
                comitKeCabang(*cabangSaatIni, pesanComit, namaPenulis, hashBerikutnya); // Perbaikan: ComitKeCabang -> comitKeCabang
                
                cout << "[" << WARNA_HIJAU << repoSaatIni.namaCabangAktif << " " << hashBerikutnya << WARNA_RESET << "] " << pesanComit << endl; 
                cout << WARNA_HIJAU << repoSaatIni.namaCabangAktif << WARNA_RESET << " -> " << WARNA_HIJAU << "origin/" << repoSaatIni.namaCabangAktif << WARNA_RESET << endl; 
                cout << "   git push origin " << repoSaatIni.namaCabangAktif << endl; 
            } else {
                cout << "[INFO] Commit dibatalkan." << endl;
            }
            Enter(); // Perbaikan: tekanEnter() -> Enter()
        } 
        else if (pilihanMenu == "2") {
            bersihkanLayar();
            cout << "GITSIM" << endl; 
            cout << "Git Simulator" << endl; 
            cout << "Author: " << namaPenulis << endl; 
            cout << "git log [" << WARNA_HIJAU << repoSaatIni.namaCabangAktif << "]" << endl << endl; 

            if (cabangSaatIni->jumlahComit == 0) {
                cout << "(No commits on this branch)" << endl; 
            } else {
                for (int i = cabangSaatIni->jumlahComit - 1; i >= 0; i--) {
                    cout << WARNA_KUNING << "commit " << cabangSaatIni->daftarComit[i].id << WARNA_RESET << endl; 
                    cout << "Author: " << cabangSaatIni->daftarComit[i].penulis << endl; 
                    cout << "Date  : " << cabangSaatIni->daftarComit[i].stempelWaktu << endl << endl; 
                    cout << "    " << cabangSaatIni->daftarComit[i].pesan << endl << endl; 
                }
            }
            Enter(); // Perbaikan: tekanEnter() -> Enter()
        } 
        else if (pilihanMenu == "3") {
            bersihkanLayar();
            cout << "GITSIM" << endl; 
            cout << "Git Simulator" << endl; 
            cout << "Author: " << namaPenulis << endl; 
            cout << "git branch" << endl; 

            for (int i = 0; i < repoSaatIni.jumlahCabang; i++) {
                if (repoSaatIni.daftarCabang[i].nama == repoSaatIni.namaCabangAktif) {
                    cout << WARNA_HIJAU << "* " << repoSaatIni.daftarCabang[i].nama 
                         << " (" << repoSaatIni.daftarCabang[i].jumlahComit << " commits)" << WARNA_RESET << endl; 
                } else {
                    cout << "  " << repoSaatIni.daftarCabang[i].nama 
                         << " (" << repoSaatIni.daftarCabang[i].jumlahComit << " commits)" << endl; 
                }
            }

            cout << "New branch name: "; 
            string namaBaru;
            getline(cin, namaBaru);

            if (namaBaru.empty()) {
                cout << WARNA_MERAH << "[ERROR] Branch name cannot be empty!" << WARNA_RESET << endl; 
            } else {
                bool adaDuplikasi = false;
                for (int i = 0; i < repoSaatIni.jumlahCabang; i++) {
                    if (repoSaatIni.daftarCabang[i].nama == namaBaru) {
                        adaDuplikasi = true;
                        break;
                    }
                }

                if (adaDuplikasi) {
                    cout << WARNA_MERAH << "[ERROR] Branch '" << namaBaru << "' already exists!" << WARNA_RESET << endl; 
                } else {
                    tambahCabangKeRepo(repoSaatIni, namaBaru, cabangSaatIni);
                    cout << WARNA_HIJAU << "[OK] Branch '" << namaBaru << "' created from '" 
                         << repoSaatIni.namaCabangAktif << "'" << WARNA_RESET << endl; 
                    cout << "     " << cabangSaatIni->jumlahComit << " commit(s) inherited" << endl; 
                }
            }
            Enter(); // Perbaikan: tekanEnter() -> Enter()
        } 
        else if (pilihanMenu == "4") {
            bersihkanLayar();
            cout << "GITSIM" << endl; 
            cout << "Git Simulator" << endl; 
            cout << "Author: " << namaPenulis << endl; 
            cout << "git checkout" << endl; 

            for (int i = 0; i < repoSaatIni.jumlahCabang; i++) {
                if (repoSaatIni.daftarCabang[i].nama == repoSaatIni.namaCabangAktif) {
                    cout << WARNA_HIJAU << "* " << repoSaatIni.daftarCabang[i].nama << WARNA_RESET << endl; 
                } else {
                    cout << "  " << repoSaatIni.daftarCabang[i].nama << endl; 
                }
            }

            cout << "Switch to branch: "; 
            string cabangTujuan;
            getline(cin, cabangTujuan);

            if (cabangTujuan == repoSaatIni.namaCabangAktif) {
                cout << WARNA_MERAH << "[ERROR] Invalid branch!" << WARNA_RESET << endl; 
            } else {
                bool ditemukan = false;
                for (int i = 0; i < repoSaatIni.jumlahCabang; i++) {
                    if (repoSaatIni.daftarCabang[i].nama == cabangTujuan) {
                        repoSaatIni.namaCabangAktif = cabangTujuan;
                        ditemukan = true;
                        break;
                    }
                }

                if (ditemukan) {
                    cout << WARNA_HIJAU << "[OK] Switched to branch '" << cabangTujuan << "'" << WARNA_RESET << endl; 
                } else {
                    cout << WARNA_MERAH << "[ERROR] Invalid branch!" << WARNA_RESET << endl; 
                }
            }
            Enter(); // Perbaikan: tekanEnter() -> Enter()
        } 
        else if (pilihanMenu == "5") {
            bersihkanLayar();
            cout << "GITSIM" << endl; 
            cout << "Git Simulator" << endl; 
            cout << "Author: " << namaPenulis << endl; 
            cout << "git init (new repository)" << endl; 
            cout << "New repository name: "; 
            
            string namaRepoBaru;
            getline(cin, namaRepoBaru);

            if (namaRepoBaru.empty()) {
                namaRepoBaru = "repo-" + to_string(jumlahRepo + 1); 
            }

            bool repoDuplikat = false;
            for (int i = 0; i < jumlahRepo; i++) {
                if (daftarRepositori[i].nama == namaRepoBaru) {
                    repoDuplikat = true;
                    break;
                }
            }

            if (repoDuplikat) {
                cout << WARNA_MERAH << "[ERROR] Repository '" << namaRepoBaru << "' already exists!" << WARNA_RESET << endl; 
            } else {
                if (jumlahRepo >= kapasitasRepo) {
                    kapasitasRepo *= 2;
                    Repositori* wadahSementara = new Repositori[kapasitasRepo];
                    for (int i = 0; i < jumlahRepo; i++) {
                        wadahSementara[i] = daftarRepositori[i];
                    }
                    delete[] daftarRepositori;
                    daftarRepositori = wadahSementara;
                }

                daftarRepositori[jumlahRepo].nama = namaRepoBaru;
                daftarRepositori[jumlahRepo].jumlahCabang = 0;
                daftarRepositori[jumlahRepo].kapasitasCabang = 2;
                daftarRepositori[jumlahRepo].daftarCabang = new Cabang[daftarRepositori[jumlahRepo].kapasitasCabang];
                daftarRepositori[jumlahRepo].namaCabangAktif = "main"; 
                
                tambahCabangKeRepo(daftarRepositori[jumlahRepo], "main");
                
                indeksRepoAktif = jumlahRepo; 
                jumlahRepo++;

                cout << WARNA_HIJAU << "[OK] Repository '" << namaRepoBaru << "' created and set as active." << WARNA_RESET << endl; 
                cout << "On branch: " << WARNA_HIJAU << "main" << WARNA_RESET << endl; 
            }
            Enter(); // Perbaikan: tekanEnter() -> Enter()
        } 
        else if (pilihanMenu == "6") {
            bersihkanLayar();
            cout << "GITSIM" << endl; 
            cout << "Git Simulator" << endl; 
            cout << "Author: " << namaPenulis << endl; 
            cout << "switch repository" << endl; 

            for (int i = 0; i < jumlahRepo; i++) {
                Repositori& r = daftarRepositori[i];
                Cabang* cabangHead = nullptr;
                for (int j = 0; j < r.jumlahCabang; j++) {
                    if (r.daftarCabang[j].nama == r.namaCabangAktif) {
                        cabangHead = &r.daftarCabang[j];
                        break;
                    }
                }
                
                int komitDiHead = cabangHead ? cabangHead->jumlahComit : 0;
                
                if (i == indeksRepoAktif) {
                    cout << WARNA_HIJAU << "* [" << (i + 1) << "] " << r.nama 
                         << " (" << r.jumlahCabang << " branch, " << komitDiHead << " commits at HEAD)" << WARNA_RESET << endl; 
                } else {
                    cout << "  [" << (i + 1) << "] " << r.nama 
                         << " (" << r.jumlahCabang << " branch, " << komitDiHead << " commits at HEAD)" << endl; 
                }
            }

            cout << "Select repository number: "; 
            string indeksTujuanStr;
            getline(cin, indeksTujuanStr);
            
            try {
                int indeksTujuan = stoi(indeksTujuanStr) - 1;
                if (indeksTujuan >= 0 && indeksTujuan < jumlahRepo) {
                    indeksRepoAktif = indeksTujuan;
                    cout << WARNA_HIJAU << "[OK] Switched to repository '" << daftarRepositori[indeksRepoAktif].nama << "'" << WARNA_RESET << endl; 
                    cout << "HEAD: " << WARNA_HIJAU << daftarRepositori[indeksRepoAktif].namaCabangAktif << WARNA_RESET << endl; 
                } else {
                    cout << WARNA_MERAH << "[ERROR] Nomor repository tidak valid!" << WARNA_RESET << endl;
                }
            } catch (...) {
                cout << WARNA_MERAH << "[ERROR] Input harus berupa angka!" << WARNA_RESET << endl;
            }
            Enter(); 
        } 
        else if (pilihanMenu == "0") {
            bersihkanLayar();
            cout << "Session Ended" << endl; 
            cout << "Author: " << namaPenulis << endl; 
            cout << "Goodbye!" << endl; 
            break;
        }
    }

    for (int i = 0; i < jumlahRepo; i++) {
        bersihkanMemoriRepositori(daftarRepositori[i]);
    }
    delete[] daftarRepositori;

    return 0;
}