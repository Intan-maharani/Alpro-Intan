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
    unsigned int nilai = 0;
    if (idCommit == 1) {
        nilai = 0x1c8864f;
    } else if (idCommit == 2) {
        nilai = 0xc6ef362;
    } else {
        nilai = idCommit * 2654435761u;
    }
    
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
        cout << WARNA_MERAH << "Error: Nama penulis harus disertakan sebagai argumen!" << WARNA_RESET << "\n";
        cout << "Penggunaan: .\\gitsim <Username>\n";
        return 1;
    }
    
    string namaPenulis = argumen[1];
    int totalComitGlobal = 0;
    
    int kapasitasRepo = 4;
    int jumlahRepo = 0;
    int indeksRepoAktif = 0;
    Repositori* daftarRepositori = new Repositori[kapasitasRepo];
  
    bersihkanLayar();
    cout << WARNA_SIAN << "GITSIM" << WARNA_RESET << " - Lightweight Git Simulator\n";
    cout << "Author: " << namaPenulis << "\n";
    cout << "----------------------------------------------------------------\n";
    cout << "git init\n";
    cout << "----------------------------------------------------------------\n";
    
    cout << WARNA_SIAN << "Repository name: " << WARNA_RESET;
    string namaRepoAwal;
    getline(cin, namaRepoAwal);
    
    if (namaRepoAwal.empty()) {
        namaRepoAwal = "my-repo";
    }
    
    daftarRepositori[0].nama = namaRepoAwal;
    daftarRepositori[0].jumlahCabang = 0;
    daftarRepositori[0].kapasitasCabang = 2;
    daftarRepositori[0].daftarCabang = new Cabang[daftarRepositori[0].kapasitasCabang];
    daftarRepositori[0].namaCabangAktif = "main";
    
    tambahCabangKeRepo(daftarRepositori[0], "main");
    indeksRepoAktif = jumlahRepo;
    jumlahRepo = 1;
    
    cout << "\n" << WARNA_HIJAU << "[OK]" << WARNA_RESET << " Initialized empty repository: " << namaRepoAwal << "\n";
    cout << "On branch: " << WARNA_HIJAU << "main" << WARNA_RESET << "\n";
    Enter();
    
    while (true) {
        bersihkanLayar();
        Repositori& repoSaatIni = daftarRepositori[indeksRepoAktif];
        Cabang* cabangSaatIni = ambilCabangAktif(repoSaatIni);
        
        cout << WARNA_SIAN << "GITSIM" << WARNA_RESET << " - Git Simulator\n";
        cout << "Author: " << WARNA_PUTIH << namaPenulis << WARNA_RESET;
        cout << " | Repo: " << WARNA_PUTIH << repoSaatIni.nama << WARNA_RESET;
        cout << " | HEAD: " << WARNA_HIJAU << repoSaatIni.namaCabangAktif << WARNA_RESET;
        cout << " | [" << WARNA_KUNING << (indeksRepoAktif + 1) << "/" << jumlahRepo << WARNA_RESET << "]\n";
        cout << "----------------------------------------------------------------\n";
        cout << "[1] git commit\n";
        cout << "[2] git log\n";
        cout << "[3] git branch\n";
        cout << "[4] git checkout\n";
        cout << "[5] new repository\n";
        cout << "[6] switch repository\n";
        cout << "[0] exit\n";
        cout << "----------------------------------------------------------------\n";
        
        cout << WARNA_SIAN << "> " << WARNA_RESET;
        
        string pilihanMenu;
        getline(cin, pilihanMenu);
        
        if (pilihanMenu == "1") { 
            bersihkanLayar();
            cout << WARNA_SIAN << "GITSIM" << WARNA_RESET << " - Git Simulator\n";
            cout << "Author: " << namaPenulis << "\n";
            cout << "-----------------------------------------------------\n";
            cout << "git commit  [" << WARNA_HIJAU << repoSaatIni.namaCabangAktif << WARNA_RESET << "]\n";
            cout << "-----------------------------------------------------\n";
            cout << WARNA_SIAN << "Message :  " << WARNA_RESET;
            string pesanComit;
            getline(cin, pesanComit);
            
            cout << WARNA_SIAN << "\nPush commit? (y/n): " << WARNA_RESET;
            string konfirmasi;
            getline(cin, konfirmasi);
            
            if (konfirmasi == "y" || konfirmasi == "Y") {
                totalComitGlobal++;
                string hashBerikutnya = Hash(totalComitGlobal);
                comitKeCabang(*cabangSaatIni, pesanComit, namaPenulis, hashBerikutnya);
                
                cout << "\n" << WARNA_HIJAU << "[" << repoSaatIni.namaCabangAktif << " " << hashBerikutnya << "]" << WARNA_RESET << " " << pesanComit << "\n\n";
                cout << "-----------------------------------------------------\n";
                cout << WARNA_ABU << repoSaatIni.namaCabangAktif << " -> origin/" << repoSaatIni.namaCabangAktif << WARNA_RESET << "\n";
                cout << "$ git push origin " << WARNA_HIJAU << repoSaatIni.namaCabangAktif << WARNA_RESET << "\n";
                cout << "-----------------------------------------------------\n\n";
            } else {
                cout << "\n[INFO] Commit dibatalkan.\n\n";
            }
            Enter();
        }
        else if (pilihanMenu == "2") {
            bersihkanLayar();
            cout << WARNA_SIAN << "GITSIM" << WARNA_RESET << " - Git Simulator\n";
            cout << "Author: " << namaPenulis << "\n";
            cout << "-----------------------------------------------------\n";
            cout << "git log  [" << WARNA_HIJAU << repoSaatIni.namaCabangAktif << WARNA_RESET << "]\n";
            cout << "-----------------------------------------------------\n";
            
            if (cabangSaatIni->jumlahComit == 0) {
                cout << "(No commits on this branch)\n";
            } else {
                for (int i = cabangSaatIni->jumlahComit - 1; i >= 0; i--) {
                    cout << "commit " << WARNA_KUNING << cabangSaatIni->daftarComit[i].id << WARNA_RESET << "\n";
                    cout << "Author: " << cabangSaatIni->daftarComit[i].penulis << "\n";
                    cout << "Date  : " << cabangSaatIni->daftarComit[i].stempelWaktu << "\n";
                    cout << "        " << cabangSaatIni->daftarComit[i].pesan << "\n";
                    if(i > 0) cout << "\n"; 
                }
                cout << "\n";
                cout << "-----------------------------------------------------\n\n";
            }
            Enter();
        }
        else if (pilihanMenu == "3") { 
            bersihkanLayar();
            cout << WARNA_SIAN << "GITSIM" << WARNA_RESET << " - Git Simulator\n";
            cout << "Author: " << namaPenulis << "\n";
            cout << "-----------------------------------------------------\n";
            cout << "git branch\n";
            cout << "-----------------------------------------------------\n";
            
            for (int i = 0; i < repoSaatIni.jumlahCabang; i++) {
                if (repoSaatIni.daftarCabang[i].nama == repoSaatIni.namaCabangAktif) {
                    cout << WARNA_HIJAU << "* " << WARNA_RESET << repoSaatIni.daftarCabang[i].nama 
                         << " (" << repoSaatIni.daftarCabang[i].jumlahComit << " commits)\n";
                } else {
                    cout << "  " << repoSaatIni.daftarCabang[i].nama 
                         << " (" << repoSaatIni.daftarCabang[i].jumlahComit << " commits)\n";
                }
            }
            cout << "-----------------------------------------------------\n";
            
            cout << WARNA_SIAN <<  "\nNew branch name: " << WARNA_RESET;
           
            string namaBaru;
            getline(cin, namaBaru);
            
            if (namaBaru.empty()) {
                cout << "\n" << WARNA_MERAH << "[ERROR]" << WARNA_RESET << " Branch name cannot be empty!\n";
            } else {
                bool adaDuplikasi = false;
                for (int i = 0; i < repoSaatIni.jumlahCabang; i++) {
                    if (repoSaatIni.daftarCabang[i].nama == namaBaru) {
                        adaDuplikasi = true;
                        break;
                    }
                }
                
                if (adaDuplikasi) {
                    cout << "\n" << WARNA_MERAH << "[ERROR]" << WARNA_RESET << " Branch '" << namaBaru << "' already exists!\n";
                } else {
                    tambahCabangKeRepo(repoSaatIni, namaBaru, cabangSaatIni);
                    cout << "\n" << WARNA_HIJAU << "[OK]" << WARNA_RESET << " Branch '" << namaBaru 
                         << "' created from '" << repoSaatIni.namaCabangAktif << "'\n";
                    cout << "     " << cabangSaatIni->jumlahComit << " commit(s) inherited\n";
                }
            }
            Enter();
        }
        else if (pilihanMenu == "4") { 
            bersihkanLayar();
            cout << WARNA_SIAN << "GITSIM" << WARNA_RESET << " - Git Simulator\n";
            cout << "Author: " << namaPenulis << "\n";
            cout << "-----------------------------------------------------\n";
            cout << "git checkout\n";
            cout << "-----------------------------------------------------\n";
            
            for (int i = 0; i < repoSaatIni.jumlahCabang; i++) {
                if (repoSaatIni.daftarCabang[i].nama == repoSaatIni.namaCabangAktif) {
                    cout << WARNA_HIJAU << "* " << WARNA_RESET << repoSaatIni.daftarCabang[i].nama << "\n";
                } else {
                    cout << "  " << repoSaatIni.daftarCabang[i].nama << "\n";
                }
            }
            cout << "-----------------------------------------------------\n";
            
            cout << WARNA_SIAN << "\nSwitch to branch: " << WARNA_RESET;
           
            string cabangTujuan;
            getline(cin, cabangTujuan);
            
            if (cabangTujuan == repoSaatIni.namaCabangAktif) {
                cout << "\n" << WARNA_MERAH << "[ERROR]" << WARNA_RESET << " Invalid branch!\n";
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
                    cout << "\n" << WARNA_HIJAU << "[OK]" << WARNA_RESET << " Switched to branch '" << cabangTujuan << "'\n";
                } else {
                    cout << "\n" << WARNA_MERAH << "[ERROR]" << WARNA_RESET << " Invalid branch!\n";
                }
            }
            Enter();
        }
        else if (pilihanMenu == "5") { 
            bersihkanLayar();
            cout << WARNA_SIAN << "GITSIM" << WARNA_RESET << " - Git Simulator\n";
            cout << "Author: " << namaPenulis << "\n";
            cout << "-----------------------------------------------------\n";
            cout << "git init (new repository)\n";
            cout << "-----------------------------------------------------\n";
            
            cout << WARNA_SIAN << "New repository name: " << WARNA_RESET;
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
                cout << "\n" << WARNA_MERAH << "[ERROR]" << WARNA_RESET << " Repository '" << namaRepoBaru << "' already exists!\n";
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
                
                cout << "\n" << WARNA_HIJAU << "[OK]" << WARNA_RESET << " Repository '" << namaRepoBaru << "' created and set as active.\n";
                cout << "On branch: " << WARNA_HIJAU << "main" << WARNA_RESET << "\n";
            }
            Enter();
        }
        else if (pilihanMenu == "6") { 
            bersihkanLayar();
            cout << WARNA_SIAN << "GITSIM" << WARNA_RESET << " - Git Simulator\n";
            cout << "Author: " << namaPenulis << "\n";
            cout << "-----------------------------------------------------\n";
            cout << "switch repository\n";
            cout << "-----------------------------------------------------\n";
            
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
                         << " (" << r.jumlahCabang << " branch, " << komitDiHead << " commits at HEAD)" << WARNA_RESET << "\n";
                } else {
                    cout << "  [" << (i + 1) << "] " << r.nama 
                         << " (" << r.jumlahCabang << " branch, " << komitDiHead << " commits at HEAD)\n";
                }
            }
            cout << "-----------------------------------------------------\n";
            
            cout << "\n" << WARNA_SIAN << "Select repository number: " << WARNA_RESET;
            string indeksTujuanStr;
            getline(cin, indeksTujuanStr);
            
            try {
                int indeksTujuan = stoi(indeksTujuanStr) - 1;
                if (indeksTujuan >= 0 && indeksTujuan < jumlahRepo) {
                    indeksRepoAktif = indeksTujuan;
                    cout << "\n" << WARNA_HIJAU << "[OK]" << WARNA_RESET << " Switched to repository '" << daftarRepositori[indeksRepoAktif].nama << "'\n";
                    cout << "HEAD: " << WARNA_HIJAU << daftarRepositori[indeksRepoAktif].namaCabangAktif << WARNA_RESET << "\n";
                } else {
                    cout << "\n" << WARNA_MERAH << "[ERROR]" << WARNA_RESET << " Nomor repository tidak valid!\n";
                }
            } catch (...) {
                cout << "\n" << WARNA_MERAH << "[ERROR]" << WARNA_RESET << " Input harus berupa angka!\n";
            }
            Enter();
        }
        else if (pilihanMenu == "0") { 
            bersihkanLayar();
            cout << WARNA_SIAN << "Session Ended" << WARNA_RESET << "\n";
            cout << WARNA_ABU << "Author : " << WARNA_RESET << WARNA_PUTIH << namaPenulis << WARNA_RESET << "\n";
            cout << WARNA_HIJAU << "Goodbye!" << WARNA_RESET << "\n\n";
            break;
        }
    }
    
    for (int i = 0; i < jumlahRepo; i++) {
        bersihkanMemoriRepositori(daftarRepositori[i]);
    }
    delete[] daftarRepositori;
    
    return 0;
}