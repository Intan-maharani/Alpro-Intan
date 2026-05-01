#include <iostream>

using namespace std;

int main() {
    int umur;
    
    // --- GOBLET OF FIRE ---
    cout << "=== GOBLET OF FIRE: TURNAMEN TRIWIZARD ===" << endl;
    cout << "Masukkan umur Anda: ";
    cin >> umur;

    if (umur < 17) {
        cout << "Piala Api menolak Anda! Umur terlalu kecil" << endl;
        cout << "\n------------------------------------------" << endl;
        return 0;
    } else {
        cout << "Piala Api menyala! Anda terpilih sebagai Triwizard Champions." << endl;
        system("pause");
    }

    // --- TUGAS 1: ARENA NAGA ---
    bool tugas1Selesai = false;
    while (!tugas1Selesai) {
        int perlindungan = 3;
        char pilihan;

        while (perlindungan > 0) {
            system("cls"); 
            cout << "--- TUGAS 1: NAGA HUNGARIAN HORNTAIL ---" << endl;
            cout << "Sisa perlindungan sihir: " << perlindungan << " kali." << endl;
            cout << "Pilih strategi (a: Sembunyi, b: Panggil Sapu): ";
            cin >> pilihan;

            if (pilihan == 'b' || pilihan == 'B') {
                cout << "Berhasil! Anda mengambil Telur Emas!" << endl;
                tugas1Selesai = true;
                system("pause");
                break;
            } else if (pilihan == 'a' || pilihan == 'A') {
                perlindungan--;
                cout << "Naga menyemburkan api! Anda terluka." << endl;
                
                if (perlindungan == 0) {
                    cout << ">> KESEMPATAN HABIS! Anda ditarik keluar arena oleh pawang naga." << endl;
                    cout << ">> MENGULANG TUGAS 1 DARI AWAL..." << endl;
                } else {
                    cout << "Sisa perlindungan sihir: " << perlindungan << " kali." << endl;
                }
                
                
                system("pause"); 
                
            } else {
                cout << "Pilihan tidak valid! Ulangi pilihan." << endl;
                system("pause");
            }
        }
    }

    // --- TUGAS 2: DANAU HITAM ---
bool tugas2Selesai = false;
while (!tugas2Selesai) {
    int waktu = 10;
    int grindylowDihindari = 0;
    char pilihan;

    while (waktu <= 60) {
        system("cls");  
        cout << "--- TUGAS 2: DANAU HITAM ---" << endl;
        cout << "Menit " << waktu << "... Ada Grindylow! (l: Lawan, h: Hindari): ";
        cin >> pilihan;

        if (pilihan == 'h' || pilihan == 'H') {
            cout << "Lolos dari Grindylow." << endl; 
            grindylowDihindari++;
            
            if (grindylowDihindari == 6) {
                cout << "Tepat 60 menit! Anda menyelamatkan sandera." << endl;
                tugas2Selesai = true;
                system("pause"); 
                break;
            }
            
            waktu += 10;
            system("pause"); 
            
        } else if (pilihan == 'l' || pilihan == 'L') {
            cout << "Oksigen Anda habis karena kelelahan bertarung!" << endl;
            cout << ">> WAKTU/OKSIGEN HABIS! Putri duyung membawa Anda ke permukaan." << endl;
            cout << ">> MENGULANG TUGAS 2 DARI AWAL..." << endl;
            system("pause");
            break;
        } else {
            cout << "Pilihan tidak valid! Ulangi pilihan." << endl;
            system("pause");
        }
    }
}

    // --- TUGAS 3: LABIRIN HIDUP ---
    bool tugas3Selesai = false;
    while (!tugas3Selesai) {
        int toleransi = 2;
        int langkah = 0;
        int arah;

        while (toleransi > 0) {
            system("cls");
            cout << "--- TUGAS 3: LABIRIN ---" << endl;
            cout << "Sisa toleransi kesalahan: " << toleransi << endl;
            cout << "Langkah ditempuh: " << langkah << endl;
            cout << "Pilih arah (1: Kiri, 2: Kanan, 3: Lurus): ";
            cin >> arah;

            if (arah == 3) {
                cout << "Anda melihat cahaya... Oh tunggu, apa itu..." << endl;
                tugas3Selesai = true;
                system("pause");
                break;
            } else if (arah == 2) {
                langkah++;
                cout << "Jalan aman, Anda semakin dalam." << endl;
                if (langkah == 3) {
                    cout << "Anda melihat cahaya... Oh tunggu, apa itu..." << endl;
                    tugas3Selesai = true;
                    system("pause");
                    break;
                }
                system("pause");
            } else if (arah == 1) {
                toleransi--;
                cout << "Terkena Akar Berbisa! Sisa toleransi kesalahan: " << toleransi << endl;
                if (toleransi == 0) {
                    cout << "\n>> KESEMPATAN HABIS! Labirin berubah bentuk dan menendang Anda ke pintu masuk." << endl;
                    cout << ">> MENGULANG TUGAS 3 DARI AWAL..." << endl;
                }
                system("pause");
            } else {
                cout << "Anda tidak berada di jalur pilihan! Ulangi pilihan!" << endl;
                system("pause");
            }
        }
    }

    // --- JALAN KELUAR ---
    system("cls");
    cout << "--- JALAN KELUAR ---" << endl;
    cout << "Anda melihat sesuatu yang bersinar di tengah arena..." << endl;
    cout << "Terdapat sesuatu yang terkurung di dalamnya, dan terdapat mesin yang meminta Anda untuk memasukkan sebuah angka..." << endl;
    
    int n;
    while (true) {
        cout << "\nMasukkan angka (minimal 5): ";
        cin >> n;
        if (n >= 5) break;
        cout << "Angka terlalu kecil! Mesin tidak bereaksi." << endl;
    }

    cout << "Sebuah cahaya bersinar dan di tanganmu kini terdapat sebuah diamond besar!" << endl;

    // Diamond Atas
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int k = 1; k <= (2 * i - 1); k++) cout << "*";
        cout << endl;
    }

    // Diamond Bawah
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int k = 1; k <= (2 * i - 1); k++) cout << "*";
        cout << endl;
    }

    cout << "\n*** SELAMAT! ANDA ADALAH PEMENANG TURNAMEN TRIWIZARD! ***" << endl;
    cout << "\n------------------------------------------" << endl;

    return 0;
}