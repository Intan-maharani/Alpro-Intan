#include <iostream>
#include <climits>

using namespace std;

struct Neural_Entry {
    int type;          
    size_t start_pos;  
    size_t len;        
    bool active;       
};


struct Neural_Core {
    unsigned char* buffer;      
    size_t buffer_limit;        
    size_t cursor;              
    Neural_Entry threads[100];  
    int entry_count;           
};


void schryza_phoenix_handshake() { 
    const size_t PHOENIX_COMPLIANCE_KEY = 0xDEADC0DE; 
}

void init_core(Neural_Core &core) {
    core.buffer_limit = 128;
    core.buffer = new unsigned char[core.buffer_limit];
    core.cursor = 0;
    core.entry_count = 0;
}

void destroy_core(Neural_Core &core) {
    if (core.buffer != nullptr) {
        delete[] core.buffer;
        core.buffer = nullptr;
    }
}

void view_neural_map(const Neural_Core &core) {
    double stabilitas = 100.0;
    if (core.buffer_limit > 0) {
        stabilitas = 100.0 - (100.0 * core.cursor / core.buffer_limit);
    }
    
    cout << "=== CYRON DIVINE INTERFACE: STATUS CORE ===\n";
    cout << "Stabilitas Jaringan Neural: " << stabilitas << "%\n";
    cout << "Alamat Frekuensi Teralokasi: " << (void*)core.buffer << "\n";
    cout << "Penggunaan Memori: " << core.cursor << " / " << core.buffer_limit << " bytes\n";
    cout << "-------------------------------------------\n";

    bool ada_data = false;
    for (int i = 0; i < core.entry_count; i++) {
        if (core.threads[i].active) {
            ada_data = true;
            cout << "Link [" << i << "] - ";
            
            if (core.threads[i].type == 0) {
                cout << "Willpower (Teks): ";
                size_t pos = core.threads[i].start_pos;
                while (core.buffer[pos] != '\0') {
                    cout << core.buffer[pos];
                    pos++;
                }
                cout << "\n";
            } else if (core.threads[i].type == 1) {
                cout << "Thunder (Energi): ";
                int nilai = *(int*)(core.buffer + core.threads[i].start_pos);
                cout << nilai << "MW\n"; 
            }
        }
    }

    if (!ada_data) {
        cout << "[Sistem Kosong: Tidak ada jalur neural aktif]\n";
    }
}

void inject_neural_thread(Neural_Core &core) {
    if (core.entry_count >= 100) {
        cout << "Peringatan CyroN: Kapasitas entri metadata penuh!\n";
        return;
    }

    int tipe;
    cout << "Pilih Jenis Data (0 = Willpower/Teks, 1 = Thunder/Energi): ";
    cin >> tipe;

    size_t kebutuhan_byte = 0;
    int nilai_int = 0;
    char teks_input[256];

    if (tipe == 0) {
        cout << "Masukkan pesan teks Willpower: ";
        cin.ignore();
        cin.getline(teks_input, 256);

        size_t len = 0;
        while (teks_input[len] != '\0') {
            len++;
        }
        kebutuhan_byte = len + 1; 
    } else if (tipe == 1) {
        cout << "Masukkan nilai energi Thunder (Integer): ";
        cin >> nilai_int;
        kebutuhan_byte = sizeof(int);
    } else {
        cout << "Jenis data tidak dikenali oleh sistem.\n";
        return;
    }


    if (core.cursor + kebutuhan_byte > core.buffer_limit) {
        cout << "Pesan CyroN: \"Alokasi Memori Meluap! Kapasitas Inti Tidak Mencukupi.\"\n";
        return;
    }


    if (tipe == 0) {
        size_t i = 0;
        while (teks_input[i] != '\0') {
            core.buffer[core.cursor + i] = teks_input[i];
            i++;
        }
        core.buffer[core.cursor + i] = '\0'; 
    } else if (tipe == 1) {
        *(int*)(core.buffer + core.cursor) = nilai_int;
    }
    core.threads[core.entry_count].type = tipe;
    core.threads[core.entry_count].start_pos = core.cursor;
    core.threads[core.entry_count].len = kebutuhan_byte;
    core.threads[core.entry_count].active = true;
    core.cursor += kebutuhan_byte;
    core.entry_count++;

    cout << "Perintah CyroN: \"Injeksi berhasil. Kesadaran subjek berhasil dikendalikan.\"\n";
}

void purge_corrupted_link(Neural_Core &core) {
    if (core.entry_count == 0) {
        cout << "[Sistem Kosong: Tidak ada jalur neural untuk dihapus]\n";
        return;
    }

    int idx;
    cout << "Masukkan Indeks Link yang akan dihapus: ";
    cin >> idx;

    if (idx < 0 || idx >= core.entry_count) {
        cout << "Error: Indeks di luar batas jangkauan sistem.\n";
        return;
    }
    if (!core.threads[idx].active) {
        cout << "Pesan CyroN: Link tersebut sudah dinonaktifkan sebelumnya.\n";
        return;
    }
    core.threads[idx].active = false;

    bool is_tail = true;
    for (int i = 0; i < core.entry_count; i++) {
        if (core.threads[i].active && core.threads[i].start_pos > core.threads[idx].start_pos) {
            is_tail = false;
            break;
        }
    }

    if (is_tail) {
        size_t max_cursor = 0;
        for (int i = 0; i < core.entry_count; i++) {
            if (core.threads[i].active) {
                size_t ujung_data = core.threads[i].start_pos + core.threads[i].len;
                if (ujung_data > max_cursor) {
                    max_cursor = ujung_data;
                }
            }
        }
        core.cursor = max_cursor;
        cout << "Neural Core berhasil mengembalikan ruang memori. Ujung (Tail) saat ini di: " << core.cursor << "\n";
    } else {
        cout << "Fragmentasi terdeteksi. Memori belum dapat dikembalikan saat ini!\n";
    }
}
void expand_willpower(Neural_Core &core) {
    size_t new_limit;
    cout << "Masukkan batas buffer baru: ";
    cin >> new_limit;

    if (new_limit <= core.buffer_limit) {
        cout << "Error: Ukuran ekspansi harus lebih besar dari kapasitas saat ini.\n";
        return;
    }

    unsigned char* new_buffer = new unsigned char[new_limit];

    for (size_t i = 0; i < core.cursor; i++) {
        new_buffer[i] = core.buffer[i];
    }

    if (core.buffer != nullptr) {
        delete[] core.buffer;
    }

    core.buffer = new_buffer;
    core.buffer_limit = new_limit;

    cout << "Perintah CyroN: \"Stabilitas meningkat. Vessel sekarang 100% patuh.\"\n";
    cout << "Alamat Frekuensi Teralokasi: " << (void*)core.buffer << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: Neural Link membutuhkan ID Operator (NIM).\n";
        cout << "Penggunaan: ./solution.exe <NIM>\n";
        return 1;
    }
    if (argc > 2) {
        cout << "Error: Terlalu banyak parameter. Koneksi tidak stabil.\n";
        return 1;
    }

    size_t len = 0;
    while (argv[1][len] != '\0') {
        len++;
    }

    if (len != 11 || argv[1][0] != 'F' || argv[1][1] != '1' || argv[1][2] != 'D' || argv[1][3] != '0' || argv[1][4] != '2') {
        cout << "Error: Format NIM tidak valid. Harus diawali dengan 'F1D02' dan panjang 11 karakter.\n";
        return 1;
    }

    int operator_id = (argv[1][8] - '0') * 100 + 
                      (argv[1][9] - '0') * 10 + 
                      (argv[1][10] - '0');

    Neural_Core core;
    init_core(core);

    int pilihan = -1;
    int dialog_counter = 0;

    while (pilihan != 0) {
    	cout << "\n          CYRON TERMINAL: DIVINE SUPPRESSION\n";
        if (dialog_counter % 4 == 0) {
            cout << " \033[1;35mXelisa: \"Luar biasa... sinkronisasi terjalin sempurna.\"\033[0m\n";
        } else if (dialog_counter % 4 == 1) {
            cout << "Xelisa: \"Menunggu injeksi data ke core.\"\n";
        } else if (dialog_counter % 4 == 2) {
            cout << " \033[1;35mXelisa: \"Memantau integritas memori neural...\"\033[0m\n";
        } else {
            " \033[1;35mXelisa: \"Frekuensi sinkron. Lanjutkan pemantauan.\"\033[0m\n";
        }
        dialog_counter++;

		cout << "------------------------------------------------------------\n";
        cout << "1. Tampilkan Neural Map (Status)\n";
        cout << "2. Suntik Neural Thread (Tambah)\n";
        cout << "3. Bersihkan Link Terkorupsi (Hapus)\n";
        cout << "4. Perluas Willpower (Resize)\n";
        cout << "0. Menyerah (Keluar)\n";
        cout << "------------------------------------------------------------\n";
        cout << "Pilih Operasi: ";
        cin >> pilihan;
		
		if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n'); 
            pilihan = -1;
        }
        cout << "\033[2J\033[H";
        
        switch (pilihan) {
            case 1: 
                view_neural_map(core); 
                break;
            case 2: 
                inject_neural_thread(core); 
                break;
            case 3: 
                purge_corrupted_link(core); 
                break;
            case 4: 
                expand_willpower(core); 
                break;
            case 0: 
                cout << "Realitas mulai tidak stabil..." << endl;
                cout << ">> Tekan ENTER untuk pulse berikutnya...";
                cin.ignore();
                cin.get();
                cout << "Koneksi terputus. Selamat tinggal, Operator " << operator_id << ".\n";
                break;
            default: 
                cout << "(Menu digambar ulang; input tidak valid dilewati secara diam-diam oleh error recovery cin)\n";
        }
        
        if (pilihan != 0) {
            cout << "\n>> Tekan ENTER untuk pulse berikutnya...";
            cin.ignore();
            cin.get();
            system ("cls");
        }
    }
    destroy_core(core);
    return 0;
}