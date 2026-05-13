#include <iostream>

using namespace std;

// Prototipe Fungsi 
void menuUtama(string nama[], int stok[], int harga[], int &total);
void tivaizStore(string nama[], int stok[], int harga[], int &total);
void inputBarang(string nama[], int stok[], int harga[], int &total);
void hapusBarang(string nama[], int stok[], int harga[], int &total);
void editBarang(string nama[], int stok[], int harga[], int &total);
void editHarga(int &hargaLama, string namaBrg);
void tambahStok(int &stokLama, string namaBrg);
void kurangiStok(int &stokLama, string namaBrg);
void lihatBarang(string nama[], int stok[], int harga[], int total);
void kalkulatorTivaiz();
void operasiDasar();
long long hitungFaktorial(int n);
void validasiFaktorial();
void header();
void headerstore();
void headerkalku();
// Fungsi pembantu 
void bersihkanLayar();
void jeda();
bool cekAngka();

int main() {
    
    string namaBarang[100];
    int stokBarang[100];
    int hargaBarang[100];
    int totalBarang = 0;

    menuUtama(namaBarang, stokBarang, hargaBarang, totalBarang);

    return 0;
}


void headerstore(){
	cout<<"#==============================#"<<endl;
	cout<<"|         TIVAIZ STORE         |"<<endl;
	cout<<"#==============================#"<<endl;
}

void header(){
	cout<<"==================================="<<endl;
	cout<<"|                                 |"<<endl;
	cout<<"|                                 |"<<endl;
	cout<<"[       MODULE 4 - FUNCTION       ]"<<endl;
	cout<<"|                                 |"<<endl;
	cout<<"|                                 |"<<endl;
	cout<<"==================================="<<endl;

}

void headerkalku(){
	cout<<"+===========================-"<<endl;
	cout<<"|     TIVAIZ KALKUL4T0R     |"<<endl;
	cout<<"x===========================/"<<endl;
}
	
	
void menuUtama(string nama[], int stok[], int harga[], int &total) {
    int pilih;
    while (true) {
        bersihkanLayar();
        header();
        cout << "MENU UTAMA" << endl;
        cout << "1. TIVAIZ Store" << endl;
        cout << "2. Kalkulator TIVAIZ" << endl;
        cout << "0. Keluar" << endl;
        cout <<"================================="<<endl;
        cout << "Pilih menu: ";
        
        if (!cekAngka()) {
            cout << "[Gagal] Input harus berupa angka!" << endl;
            jeda();
            continue;
        }
        cin >> pilih;

        if (pilih == 1) tivaizStore(nama, stok, harga, total);
        else if (pilih == 2) kalkulatorTivaiz();
        else if (pilih == 0) break;
        else {
            cout << "[Gagal] Menu tidak valid! Pilih antara 0 sampai 2." << endl;
            jeda();
        }
    }
}

void tivaizStore(string nama[], int stok[], int harga[], int &total) {
    int pilih;
    while (true) {
        bersihkanLayar();
        headerstore();
        cout << "1. Input Barang" << endl;
        cout << "2. Hapus Barang" << endl;
        cout << "3. Edit Barang" << endl;
        cout << "4. Lihat Barang" << endl;
        cout << "0. Kembali" << endl;
        cout <<"================================="<<endl;
        cout << "Pilih menu: ";
        
        if (!cekAngka()) {
            cout << "[Gagal] Input harus berupa angka!" << endl;
            jeda();
            continue;
        }
        cin >> pilih;

        if (pilih == 1) inputBarang(nama, stok, harga, total);
        else if (pilih == 2) hapusBarang(nama, stok, harga, total);
        else if (pilih == 3) editBarang(nama, stok, harga, total);
        else if (pilih == 4) {
            lihatBarang(nama, stok, harga, total);
            jeda();
        }
        else if (pilih == 0) break;
        else {
            cout << "[Gagal] Menu tidak valid! Pilih antara 0 sampai 4." << endl;
            jeda();
        }
    }
}

void inputBarang(string nama[], int stok[], int harga[], int &total) {
    bersihkanLayar();
    headerstore();
    cout<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<"          INPUT BARANG           "  << endl;
    cout<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<endl;
    cout<<"--------------------------------"<<endl;
    cout<< "Nama Barang : ";
    cin.ignore(); 
    getline(cin, nama[total]);
    cout<<"--------------------------------"<<endl;
    cout << "Stok (unit) : ";
    if (!(cin >> stok[total])) {
    	cout<<"--------------------------------"<<endl;
        cout << "[Gagal] Stok harus berupa angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        jeda();
        return;
    }

    cout << "Harga (Rp)  : ";
    if (!(cin >> harga[total])) {
    	cout<<"--------------------------------"<<endl;
        cout << "[Gagal] Harga harus berupa angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        jeda();
        return;
    }

    total++; 
    cout << "[Berhasil] " << nama[total-1] << " ditambahkan! (Total barang: " << total << ")" << endl;
    jeda();
}

void hapusBarang(string nama[], int stok[], int harga[], int &total) {
    if (total == 0) {
        cout << "Toko kosong!" << endl;
        jeda();
        return;
    }

    bersihkanLayar();
    headerstore();
    cout<<endl;
    cout<<"-------------------------------"<<endl;
    cout << "        HAPUS BARANG         " << endl;
    cout<<endl;
    cout<<"-------------------------------"<<endl;
    for (int i = 0; i < total; i++) {
        cout << "No          : " << i + 1 << endl;
        cout << "Nama Barang : " << nama[i] << endl;
        cout << "Stok Barang : " << stok[i] << endl;
        cout << "Harga/Stok  : Rp " << harga[i] << endl;
        cout<<"----------------------------"<<endl;
    }

    int no;
    cout << "Pilih nomor barang yang dihapus (1-" << total << "): ";
    if (!(cin >> no) || no < 1 || no > total) {
        if (cin.fail()) {
            cout << "[Gagal] Input harus berupa angka!" << endl;
        } else {
            cout << "[Gagal] Nomor " << no << " tidak valid!" << endl;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        jeda();
        return;
    }

    string namaDihapus = nama[no-1];
    
    for (int i = no - 1; i < total - 1; i++) {
        nama[i] = nama[i+1];
        stok[i] = stok[i+1];
        harga[i] = harga[i+1];
    }
    total--; 
    cout << "[Berhasil] " << namaDihapus << " dihapus! (Total barang: " << total << ")" << endl;
    jeda();
}

void editBarang(string nama[], int stok[], int harga[], int &total) {
    if (total == 0) {
        cout << "Toko kosong!" << endl;
        jeda();
        return;
    }

    while (true) {
        bersihkanLayar();
        headerstore();
        cout<<endl;
    	cout<<"-----------------------------------"<<endl;
        cout << "EDIT BARANG" << endl;
        cout<<endl;
    	cout<<"-----------------------------------"<<endl;
        for (int i = 0; i < total; i++) {
            cout << "No          : " << i + 1 << endl;
            cout << "Nama Barang : " << nama[i] << endl;
            cout << "Stok Barang : " << stok[i] << endl;
            cout << "Harga/Stok  : Rp " << harga[i] << endl;
            cout<<endl;
            cout<<"-----------------------------------"<<endl;
        }

        int no;
        cout << "Pilih nomor barang yang diedit (1-" << total << "): ";
        if (!(cin >> no)) {
            cout << "[Gagal] Input harus berupa angka!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            jeda();
            return;
        }

        if (no < 1 || no > total) {
            cout << "[Gagal] Nomor " << no << " tidak valid!" << endl;
            jeda();
            return;
        }

        int idx = no - 1;
        int subPilih;
        while (true) {
            bersihkanLayar();
            headerstore();
            cout<<endl;
            cout<<"-----------------------------------"<<endl;
            cout << "EDIT BARANG" << endl;
            cout<<endl;
            cout<<"-----------------------------------"<<endl;
            cout << "Barang: " << nama[idx] << endl;
            cout<<endl;
            cout<<"-----------------------------------"<<endl;
            cout << "1. Edit Harga" << endl;
            cout << "2. Tambah Stok" << endl;
            cout << "3. Kurangi Stok" << endl;
            cout << "0. Kembali" << endl;
            cout<<endl;
            cout<<"-----------------------------------"<<endl;
            cout << "Pilih opsi: ";
            cin >> subPilih;

            if (subPilih == 1) editHarga(harga[idx], nama[idx]);
            else if (subPilih == 2) tambahStok(stok[idx], nama[idx]);
            else if (subPilih == 3) kurangiStok(stok[idx], nama[idx]);
            else if (subPilih == 0) return;
        }
    }
}

void editHarga(int &hargaLama, string namaBrg) {
    int baru;
    cout << "Harga baru (Rp): ";
    cout<<endl;
    cout<<"-----------------------------------"<<endl;
    cin >> baru;
    cout << "[Berhasil] Harga " << namaBrg << ": Rp " << hargaLama << " -> Rp " << baru << endl;
    hargaLama = baru;
    jeda();
}

void tambahStok(int &stokLama, string namaBrg) {
    int tambah;
    cout << "Jumlah tambah: ";
    cout<<endl;
    cout<<"-----------------------------------"<<endl;
    cin >> tambah;
    cout << "[Berhasil] Stok " << namaBrg << ": " << stokLama << " -> " << stokLama + tambah << endl;
    stokLama += tambah;
    jeda();
}

void kurangiStok(int &stokLama, string namaBrg) {
    int kurang;
    cout << "Jumlah kurang: ";
    cout<<endl;
    cout<<"-----------------------------------"<<endl;
    cin >> kurang;
   
    if (stokLama - kurang < 1) {
        cout << "[Gagal] Stok minimal 1" << endl;
        cout << "Stok saat ini: " << stokLama << endl;
        cout << "Maks dikurangi: " << stokLama - 1 << endl;
    } else {
        cout << "[Berhasil] Stok " << namaBrg << ": " << stokLama << " -> " << stokLama - kurang << endl;
        stokLama -= kurang;
    }
    jeda();
}

void lihatBarang(string nama[], int stok[], int harga[], int total) {
    bersihkanLayar();
    headerstore();
    cout<<endl;
    cout<<"-----------------------------------"<<endl;
    cout <<"          LIHAT BARANG            "<< endl;
    cout<<endl;
    cout<<"-----------------------------------"<<endl;
    for (int i = 0; i < total; i++) {
        cout << "No          : " << i + 1 << endl;
        cout << "Nama Barang : " << nama[i] << endl;
        cout << "Stok Barang : " << stok[i] << endl;
        cout << "Harga/Stok  : Rp " << harga[i] << endl;
        cout << "Total Harga : Rp " << stok[i] * harga[i] << endl;
        cout<<endl;
    	cout<<"-----------------------------------"<<endl;
    }
    cout << "Total barang: " << total << " jenis" << endl;
    cout<<endl;
    cout<<"-----------------------------------"<<endl;
}

void kalkulatorTivaiz() {
    int pilih;
    while (true) {
        bersihkanLayar();
        headerkalku();
        cout << "1. Operasi Dasar (+, -, *, /)" << endl;
        cout << "2. Faktorial" << endl;
        cout << "0. Kembali" << endl;
        cout <<"============================"<<endl;
        cout << "Pilih menu: ";
        
        if (!cekAngka()) {
            cout << "[Gagal] Input harus berupa angka!" << endl;
            jeda();
            continue;
        }
        cin >> pilih;

        if (pilih == 1) operasiDasar();
        else if (pilih == 2) validasiFaktorial();
        else if (pilih == 0) break;
        else {
            cout << "[Gagal] Menu tidak valid!" << endl;
            jeda();
        }
    }
}

void operasiDasar() {
    double a, b;
    char op;
    headerkalku();
    cout<<endl;
    cout<<"-----------------------------"<<endl;
    cout << "Pilih operator (+, -, *, /): "; cin >> op;
    cout<<endl;
    cout<<"-----------------------------"<<endl;
    cout << "Masukkan angka pertama: "; cin >> a;
    cout<<endl;
    cout<<"-----------------------------"<<endl;
    cout << "Masukkan angka kedua: "; cin >> b;
    cout<<endl;
    cout<<"-----------------------------"<<endl;

    if (op == '+') cout << a << " + " << b << " = " << a + b << endl;
    else if (op == '-') cout << a << " - " << b << " = " << a - b << endl;
    else if (op == '*') cout << a << " * " << b << " = " << a * b << endl;
    else if (op == '/') {
        if (b != 0) cout << a << " / " << b << " = " << a / b << endl;
        else cout << "Error: Pembagian nol!" << endl;
    }
    
    jeda();
}

long long hitungFaktorial(int n) {
    if (n <= 1) return 1;
    return n * hitungFaktorial(n - 1);
}

void validasiFaktorial() {
    int n;
    headerkalku();
    cout<<endl;
    cout<<"-----------------------------"<<endl;
    cout << "N : "; cin >> n;
    cout<<endl;
    cout<<"-----------------------------"<<endl;
    if (n < 0) cout << "Angka harus positif!" << endl;
    else cout << "Hasil " << n << "! adalah " << hitungFaktorial(n) << endl;
    jeda();
}


void bersihkanLayar() {
    system("cls"); 
}

void jeda() {
    system("pause"); 
}



bool cekAngka() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    return true;
}