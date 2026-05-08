#include <iostream>

using namespace std;
extern "C" int system(const char* command);


int hitungPanjang(char teks[]) {
    int len = 0;
    while (teks[len] != '\0') len++;
    return len;
}

void printLeadingZero(int n) {
    if (n < 10) cout << "0";
    cout << n;
}

void bersihkanBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}

// --- TASK 1: DECODE SIGNAL ---
void task1() {
    system("cls");
    cout << "[TASK 1/3] DECODE SIGNAL - Communication Room" << endl;
    cout << ">> Kirim Sinyal terenkripsi dan dekripsi balasan dari Bumi!." << endl << endl;

    int key;
    while (true) {
        cout << "Masukkan key             : ";
        if (cin >> key && key > 0) break;
        cout << " [!] Key harus bilangan bulat positif. Coba lagi." << endl;
        bersihkanBuffer();
    }

    cin.ignore();
    char teksAsli[500];
    while (true) {
        cout << "Masukkan teks            : ";
        cin.getline(teksAsli, 500);
        if (hitungPanjang(teksAsli) > 0) break;
        cout << " [!] Input tidak boleh kosong. Coba lagi." << endl;
    }

    cout << endl << "[ ENKRIPSI ]" << endl << endl;
    int len = hitungPanjang(teksAsli);
    const int KOLOM = 4;
    int baris = (len + KOLOM - 1) / KOLOM;
    char matriksE[100][KOLOM];

    int k = 0;
    cout << "Matriks enkripsi:" << endl << endl;
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < KOLOM; j++) {
            matriksE[i][j] = (k < len) ? teksAsli[k++] : '_';
            cout << matriksE[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "Enkripsi sebelum ditambah key : ";
    char tempE[500];
    int idx = 0;
    for (int j = 0; j < KOLOM; j++) {
        for (int i = 0; i < baris; i++) {
            tempE[idx++] = matriksE[i][j];
            cout << tempE[idx - 1];
        }
    }
    cout << "\nEnkripsi setelah ditambah key : ";
    for (int i = 0; i < idx; i++) cout << (char)(tempE[i] + key);
    cout << endl << endl;

    cout << "[ DEKRIPSI ]" << endl << endl;
    char teksTerenkripsi[500];
    while (true) {
        cout << "Masukkan teks terenkripsi     : ";
        cin.getline(teksTerenkripsi, 500);
        if (hitungPanjang(teksTerenkripsi) > 0) break;
        cout << " [!] Input tidak boleh kosong. Coba lagi." << endl;
    }

    cout << "Dekripsi setelah dikurang key : ";
    int lenT = hitungPanjang(teksTerenkripsi);
    char tempD[500];
    for (int i = 0; i < lenT; i++) {
        tempD[i] = teksTerenkripsi[i] - key;
        cout << tempD[i];
    }
    
    int barisD = lenT / KOLOM;
    char matriksD[100][KOLOM];
    idx = 0;
    for (int j = 0; j < KOLOM; j++) {
        for (int i = 0; i < barisD; i++) matriksD[i][j] = tempD[idx++];
    }

    cout << "\n\nHasil Dekripsi final          : ";
    for (int i = 0; i < barisD; i++) {
        for (int j = 0; j < KOLOM; j++) if (matriksD[i][j] != '_') cout << matriksD[i][j];
    }
    cout << "\n\n>> [TASK 1/3] COMPLETE - Signal channel restored." << endl;
    system("pause");
}

// --- TASK 2: REPAIR TEXT CONSOLE ---
void task2() {
    char pilihan = 'y';
    while (pilihan == 'y' || pilihan == 'Y') {
        system("cls");
        cout << "[TASK 2/3] REPAIR TEXT CONSOLE - Captain's Bridge" << endl;
        cout << ">> Konsol teks mengalami interferensi kosmik." << endl;
        cout << "[ Verifikasi Teks ]" << endl << endl;

        for (int k = 1; k <= 3; k++) {
            char input[500], tanpaSpasi[500];
            cout << "Masukkan Kalimat ke-" << k << "   : ";
            if (k == 1) ;
            cin.getline(input, 500);

            int idx = 0, j = 0;
            while (input[idx] != '\0') {
                if (input[idx] != ' ') tanpaSpasi[j++] = input[idx];
                idx++;
            }
            tanpaSpasi[j] = '\0';

            cout << "---------------------------------------------" << endl;
            cout << "Hasil untuk Kalimat ke-" << k << ":" << endl;
            cout << "Jumlah Huruf       : " << j << endl;
            cout << "1. Asli            : ";
            for (int i = 0; i < j; i++) cout << tanpaSpasi[i] << (i == j - 1 ? "" : ", ");
            cout << "\n2. Inverse         : ";
            for (int i = j - 1; i >= 0; i--) cout << tanpaSpasi[i] << (i == 0 ? "" : ", ");
            cout << "\n3. Swap Awal-Akhir : ";
            if (j > 0) {
                char tempS[500];
                for(int i=0; i<=j; i++) tempS[i] = tanpaSpasi[i];
                char t = tempS[0]; tempS[0] = tempS[j-1]; tempS[j-1] = t;
                cout << tempS;
            }
            cout << "\n4. Palindrome?     : ";
            bool isPalin = (j > 0);
            for (int i = 0; i < j / 2; i++) if (tanpaSpasi[i] != tanpaSpasi[j-1-i]) isPalin = false;
            cout << (isPalin ? "YES" : "NO") << endl << endl;
        }

        cout << "=============================================" << endl;
        while (true) {
            cout << "Verifikasi Teks Lain? (y/n): ";
            cin >> pilihan;
            if (pilihan == 'y' || pilihan == 'n' || pilihan == 'Y' || pilihan == 'N') break;
            cout << " [!] Input tidak valid. Masukkan y atau n." << endl;
        }
        cin.ignore();
    }
    cout << "\n>> [TASK 2/3] COMPLETE - Text console back online." << endl;
    system("pause");
}

// --- TASK 3: ALIGN NAVIGATION MATRIX ---
void task3() {
    system("cls");
    cout << "[TASK 3/3] ALIGN NAVIGATION MATRIX - Engine Core" << endl;
    cout << "[ MATRIX NAVIGATION ]" << endl << endl;

    int n;
    while (true) {
        cout << "Masukkan ukuran Navigation Matrix (min 3, max 5): ";
        if (cin >> n && n >= 3 && n <= 5) break;
        cout << " [!] Input tidak valid. Masukkan ukuran antara 3 sampai 5." << endl;
        bersihkanBuffer();
    }

    int odd[5][5], even[5][5], comb[5][5], oV = 1, eV = 2;
    cout << "---------------------------------------------\nOdd Coordinate Matrix (Ganjil):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { odd[i][j] = oV; printLeadingZero(oV); cout << " "; oV += 2; }
        cout << endl;
    }
    cout << "\nEven Coordinate Matrix (Genap):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { even[i][j] = eV; printLeadingZero(eV); cout << " "; eV += 2; }
        cout << endl;
    }
    cout << "---------------------------------------------" << endl;
    system("pause");

    cout << "\nCOORDINATE MATRIX INTEGRATION:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { comb[i][j] = odd[i][j] + even[i][j]; printLeadingZero(comb[i][j]); cout << " "; }
        cout << endl;
    }
    
    cout << "\nMATRIX TRANSPOSE:\n";
    int trans[5][5];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) trans[j][i] = comb[i][j];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { printLeadingZero(trans[i][j]); cout << " "; }
        cout << endl;
    }

    cout << "\nSNAKE TRAVERSE:\n";
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) for (int j = 0; j < n; j++) { printLeadingZero(trans[i][j]); cout << " "; }
        else for (int j = n - 1; j >= 0; j--) { printLeadingZero(trans[i][j]); cout << " "; }
        cout << endl;
    }
    cout << "\n>> [TASK 3/3] COMPLETE - Navigation matrix aligned.\n";
    cout << "==========================================================\n";
    cout << "   ALL TASKS COMPLETE - SHIP SYSTEMS RESTORED\n";
    cout << "==========================================================\n";
    system("pause");
}

int main() {
    task1();
    task2();
    task3();
    return 0;
}