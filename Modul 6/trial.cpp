#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Makro Pewarnaan ANSI Escape Codes
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_GRAY    "\033[0;90m"
#define COLOR_WHITE   "\033[1;37m"

// Fungsi Helper bawaan dari Modul
string generateShortHash(int commitId) {
    const char hexChars[] = "0123456789abcdef";
    string hash = "";
    // Menggunakan konstanta pengali untuk distribusi hash
    unsigned int value = commitId * 2654435761u; 
    for (int i = 0; i < 7; i++) {
        hash = hexChars[value & 0xF] + hash;
        value >>= 4;
    }
    return hash;
}

string getCurrentTimestamp() {
    char buffer[20];
    time_t now = time(nullptr);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", localtime(&now));
    return string(buffer);
}

void clearScreen() {
    cout << "\033[2J\033[H";
}

void pressEnter() {
    cout << "Press Enter...";
    cin.get();
}

// ================= STRUKTUR DATA (POINTER & DYNAMIC ARRAY) =================

struct Commit {
    string id;
    string message;
    string author;
    string timestamp;
};

struct Branch {
    string name;
    Commit* commits; // Array dinamis untuk menyimpan commit
    int commitCount;
    int commitCapacity;
};

struct Repository {
    string name;
    Branch* branches; // Array dinamis untuk menyimpan branch
    int branchCount;
    int branchCapacity;
    string activeBranchName;
};

// ================= FUNGSI MANAJEMEN REPOSITORY & BRANCH =================

// Menambahkan commit ke sebuah branch
void addCommitToBranch(Branch& branch, const string& msg, const string& auth, const string& hashId) {
    if (branch.commitCount >= branch.commitCapacity) {
        // Resize array commit jika penuh
        branch.commitCapacity = (branch.commitCapacity == 0) ? 4 : branch.commitCapacity * 2;
        Commit* newCommits = new Commit[branch.commitCapacity];
        for (int i = 0; i < branch.commitCount; i++) {
            newCommits[i] = branch.commits[i];
        }
        delete[] branch.commits;
        branch.commits = newCommits;
    }
    
    branch.commits[branch.commitCount].id = hashId;
    branch.commits[branch.commitCount].message = msg;
    branch.commits[branch.commitCount].author = auth;
    branch.commits[branch.commitCount].timestamp = getCurrentTimestamp();
    branch.commitCount++;
}

// Menambahkan branch baru ke dalam repository
void addBranchToRepo(Repository& repo, const string& branchName, Branch* sourceBranch = nullptr) {
    if (repo.branchCount >= repo.branchCapacity) {
        // Resize array branch jika penuh
        repo.branchCapacity = (repo.branchCapacity == 0) ? 2 : repo.branchCapacity * 2;
        Branch* newBranches = new Branch[repo.branchCapacity];
        for (int i = 0; i < repo.branchCount; i++) {
            newBranches[i] = repo.branches[i];
        }
        delete[] repo.branches;
        repo.branches = newBranches;
    }

    Branch& newB = repo.branches[repo.branchCount];
    newB.name = branchName;
    newB.commitCount = 0;
    newB.commitCapacity = 4;
    newB.commits = new Commit[newB.commitCapacity];

    // Jika diwarisi dari branch lain (git branch <name>)
    if (sourceBranch != nullptr) {
        for (int i = 0; i < sourceBranch->commitCount; i++) {
            addCommitToBranch(newB, sourceBranch->commits[i].message, sourceBranch->commits[i].author, sourceBranch->commits[i].id);
            // Salin timestamp asli agar histori identik
            newB.commits[i].timestamp = sourceBranch->commits[i].timestamp;
        }
    }
    repo.branchCount++;
}

// Mendapatkan pointer branch aktif saat ini
Branch* getActiveBranch(Repository& repo) {
    for (int i = 0; i < repo.branchCount; i++) {
        if (repo.branches[i].name == repo.activeBranchName) {
            return &repo.branches[i];
        }
    }
    return nullptr;
}

// Deep clean memory saat keluar program
void freeRepositoryMemory(Repository& repo) {
    for (int i = 0; i < repo.branchCount; i++) {
        delete[] repo.branches[i].commits;
    }
    delete[] repo.branches;
}

// ================= MAIN PROGRAM LOGIC =================

int main(int argc, char* argv[]) {
    // Validasi argumen pemanggilan program
    if (argc < 2) {
        cout << "[ERROR] Format jalankan program salah!" << endl;
        cout << "Gunakan: .\\gitsim <Username>" << endl;
        return 1;
    }

    string authorName = argv[1];
    int totalCommitsGlobal = 0; // Untuk ID unik hash generator

    // Inisialisasi daftar repository dinamis
    int repoCount = 0;
    int repoCapacity = 4;
    Repository* repositories = new Repository[repoCapacity];
    int activeRepoIndex = -1;

    // ---------------- STEP 1: GIT INIT UTAMA ----------------
    clearScreen();
    cout << "GITSIM" << endl;
    cout << "Lightweight Git Simulator" << endl;
    cout << "Author: " << authorName << endl;
    cout << "git init" << endl;
    cout << "Repository name: ";
    
    string initialRepoName;
    getline(cin, initialRepoName);
    if (initialRepoName.empty()) {
        initialRepoName = "my-repo";
    }

    repositories[repoCount].name = initialRepoName;
    repositories[repoCount].branchCount = 0;
    repositories[repoCount].branchCapacity = 2;
    repositories[repoCount].branches = new Branch[repositories[repoCount].branchCapacity];
    repositories[repoCount].activeBranchName = "main";
    
    // Default branch: main
    addBranchToRepo(repositories[repoCount], "main");
    activeRepoIndex = repoCount;
    repoCount++;

    cout << COLOR_GREEN << "[OK] Initialized empty repository: " << initialRepoName << COLOR_RESET << endl;
    cout << "On branch: " << COLOR_GREEN << "main" << COLOR_RESET << endl;
    pressEnter();

    // ---------------- MAIN LOOP MENU GITSIM ----------------
    while (true) {
        clearScreen();
        Repository& currentRepo = repositories[activeRepoIndex];
        Branch* currentBranch = getActiveBranch(currentRepo);

        cout << "GITSIM Git Simulator" << endl;
        cout << "Author: " << COLOR_GREEN << authorName << COLOR_RESET 
             << "  Repo: " << COLOR_GREEN << currentRepo.name << COLOR_RESET 
             << "  HEAD: " << COLOR_GREEN << currentRepo.activeBranchName << COLOR_RESET 
             << " | [" << (activeRepoIndex + 1) << "/" << repoCount << "]" << endl;
        
        cout << "[1] git commit" << endl;
        cout << "[2] git log" << endl;
        cout << "[3] git branch" << endl;
        cout << "[4] git checkout" << endl;
        cout << "[5] new repository" << endl;
        cout << "[6] switch repository" << endl;
        cout << "[0] exit" << endl;
        cout << ">> ";

        string menuChoice;
        getline(cin, menuChoice);

        if (menuChoice == "1") {
            // ---------------- [1] GIT COMMIT ----------------
            clearScreen();
            cout << "GITSIM" << endl;
            cout << "Git Simulator" << endl;
            cout << "Author: " << authorName << endl;
            cout << "git commit [" << COLOR_GREEN << currentRepo.activeBranchName << COLOR_RESET << "]" << endl;
            
            cout << "Message: ";
            string commitMsg;
            getline(cin, commitMsg);
            
            cout << "Push commit? (y/n): ";
            string confirmation;
            getline(cin, confirmation);

            if (confirmation == "y" || confirmation == "Y") {
                totalCommitsGlobal++;
                string nextHash = generateShortHash(totalCommitsGlobal);
                addCommitToBranch(*currentBranch, commitMsg, authorName, nextHash);
                
                cout << "[" << COLOR_GREEN << currentRepo.activeBranchName << " " << nextHash << COLOR_RESET << "] " << commitMsg << endl;
                cout << COLOR_GREEN << currentRepo.activeBranchName << COLOR_RESET << " -> " << COLOR_GREEN << "origin/" << currentRepo.activeBranchName << COLOR_RESET << endl;
                cout << " $ git push origin " << currentRepo.activeBranchName << endl;
            } else {
                cout << "[INFO] Commit dibatalkan." << endl;
            }
            pressEnter();
        } 
        else if (menuChoice == "2") {
            // ---------------- [2] GIT LOG ----------------
            clearScreen();
            cout << "GITSIM" << endl;
            cout << "Git Simulator" << endl;
            cout << "Author: " << authorName << endl;
            cout << "git log [" << COLOR_GREEN << currentRepo.activeBranchName << "]" << endl << endl;

            if (currentBranch->commitCount == 0) {
                cout << "(No commits on this branch)" << endl;
            } else {
                // Menampilkan riwayat secara kronologis terbalik (dari yang terbaru)
                for (int i = currentBranch->commitCount - 1; i >= 0; i--) {
                    cout << COLOR_YELLOW << "commit " << currentBranch->commits[i].id << COLOR_RESET << endl;
                    cout << "Author: " << currentBranch->commits[i].author << endl;
                    cout << "Date  : " << currentBranch->commits[i].timestamp << endl << endl;
                    cout << "    " << currentBranch->commits[i].message << endl << endl;
                }
            }
            pressEnter();
        } 
        else if (menuChoice == "3") {
            // ---------------- [3] GIT BRANCH ----------------
            clearScreen();
            cout << "GITSIM" << endl;
            cout << "Git Simulator" << endl;
            cout << "Author: " << authorName << endl;
            cout << "git branch" << endl;

            // List branch terdaftar
            for (int i = 0; i < currentRepo.branchCount; i++) {
                if (currentRepo.branches[i].name == currentRepo.activeBranchName) {
                    cout << COLOR_GREEN << "* " << currentRepo.branches[i].name 
                         << " (" << currentRepo.branches[i].commitCount << " commits)" << COLOR_RESET << endl;
                } else {
                    cout << "  " << currentRepo.branches[i].name 
                         << " (" << currentRepo.branches[i].commitCount << " commits)" << endl;
                }
            }

            cout << "New branch name: ";
            string newBranchName;
            getline(cin, newBranchName);

            if (newBranchName.empty()) {
                cout << COLOR_RED << "[ERROR] Branch name cannot be empty!" << COLOR_RESET << endl;
            } else {
                // Cek duplikasi
                bool isDuplicate = false;
                for (int i = 0; i < currentRepo.branchCount; i++) {
                    if (currentRepo.branches[i].name == newBranchName) {
                        isDuplicate = true;
                        break;
                    }
                }

                if (isDuplicate) {
                    cout << COLOR_RED << "[ERROR] Branch '" << newBranchName << "' already exists!" << COLOR_RESET << endl;
                } else {
                    // Membuat branch baru dengan mewarisi seluruh isi branch saat ini
                    addBranchToRepo(currentRepo, newBranchName, currentBranch);
                    cout << COLOR_GREEN << "[OK] Branch '" << newBranchName << "' created from '" 
                         << currentRepo.activeBranchName << "'" << COLOR_RESET << endl;
                    cout << "     " << currentBranch->commitCount << " commit(s) inherited" << endl;
                }
            }
            pressEnter();
        } 
        else if (menuChoice == "4") {
            // ---------------- [4] GIT CHECKOUT ----------------
            clearScreen();
            cout << "GITSIM" << endl;
            cout << "Git Simulator" << endl;
            cout << "Author: " << authorName << endl;
            cout << "git checkout" << endl;

            for (int i = 0; i < currentRepo.branchCount; i++) {
                if (currentRepo.branches[i].name == currentRepo.activeBranchName) {
                    cout << COLOR_GREEN << "* " << currentRepo.branches[i].name << COLOR_RESET << endl;
                } else {
                    cout << "  " << currentRepo.branches[i].name << endl;
                }
            }

            cout << "Switch to branch: ";
            string targetBranch;
            getline(cin, targetBranch);

            if (targetBranch == currentRepo.activeBranchName) {
                cout << COLOR_RED << "[ERROR] Invalid branch!" << COLOR_RESET << endl;
            } else {
                bool found = false;
                for (int i = 0; i < currentRepo.branchCount; i++) {
                    if (currentRepo.branches[i].name == targetBranch) {
                        currentRepo.activeBranchName = targetBranch;
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << COLOR_GREEN << "[OK] Switched to branch '" << targetBranch << "'" << COLOR_RESET << endl;
                } else {
                    cout << COLOR_RED << "[ERROR] Invalid branch!" << COLOR_RESET << endl;
                }
            }
            pressEnter();
        } 
        else if (menuChoice == "5") {
            // ---------------- [5] NEW REPOSITORY ----------------
            clearScreen();
            cout << "GITSIM" << endl;
            cout << "Git Simulator" << endl;
            cout << "Author: " << authorName << endl;
            cout << "git init (new repository)" << endl;
            cout << "New repository name: ";
            
            string newRepoName;
            getline(cin, newRepoName);

            // Penanganan Auto-Naming kegagalan/kosong
            if (newRepoName.empty()) {
                newRepoName = "repo-" + to_string(repoCount + 1);
            }

            // Periksa Duplikasi Nama Proyek
            bool duplicateRepo = false;
            for (int i = 0; i < repoCount; i++) {
                if (repositories[i].name == newRepoName) {
                    duplicateRepo = true;
                    break;
                }
            }

            if (duplicateRepo) {
                cout << COLOR_RED << "[ERROR] Repository '" << newRepoName << "' already exists!" << COLOR_RESET << endl;
            } else {
                // Resize array repository jika penuh
                if (repoCount >= repoCapacity) {
                    repoCapacity *= 2;
                    Repository* temp = new Repository[repoCapacity];
                    for (int i = 0; i < repoCount; i++) {
                        temp[i] = repositories[i];
                    }
                    delete[] repositories;
                    repositories = temp;
                }

                repositories[repoCount].name = newRepoName;
                repositories[repoCount].branchCount = 0;
                repositories[repoCount].branchCapacity = 2;
                repositories[repoCount].branches = new Branch[repositories[repoCount].branchCapacity];
                repositories[repoCount].activeBranchName = "main";
                
                // Tambahkan branch 'main' kosong bawaan
                addBranchToRepo(repositories[repoCount], "main");
                
                activeRepoIndex = repoCount; // Set langsung aktif
                repoCount++;

                cout << COLOR_GREEN << "[OK] Repository '" << newRepoName << "' created and set as active." << COLOR_RESET << endl;
                cout << "On branch: " << COLOR_GREEN << "main" << COLOR_RESET << endl;
            }
            pressEnter();
        } 
        else if (menuChoice == "6") {
            // ---------------- [6] SWITCH REPOSITORY ----------------
            clearScreen();
            cout << "GITSIM" << endl;
            cout << "Git Simulator" << endl;
            cout << "Author: " << authorName << endl;
            cout << "switch repository" << endl;

            for (int i = 0; i < repoCount; i++) {
                Repository& r = repositories[i];
                Branch* headBranch = nullptr;
                for (int j = 0; j < r.branchCount; j++) {
                    if (r.branches[j].name == r.activeBranchName) {
                        headBranch = &r.branches[j];
                        break;
                    }
                }
                
                int headCommits = headBranch ? headBranch->commitCount : 0;
                
                if (i == activeRepoIndex) {
                    cout << COLOR_GREEN << "* [" << (i + 1) << "] " << r.name 
                         << " (" << r.branchCount << " branch, " << headCommits << " commits at HEAD)" << COLOR_RESET << endl;
                } else {
                    cout << "  [" << (i + 1) << "] " << r.name 
                         << " (" << r.branchCount << " branch, " << headCommits << " commits at HEAD)" << endl;
                }
            }

            cout << "Select repository number: ";
            string targetIdxStr;
            getline(cin, targetIdxStr);
            
            try {
                int targetIdx = stoi(targetIdxStr) - 1;
                if (targetIdx >= 0 && targetIdx < repoCount) {
                    activeRepoIndex = targetIdx;
                    cout << COLOR_GREEN << "[OK] Switched to repository '" << repositories[activeRepoIndex].name << "'" << COLOR_RESET << endl;
                    cout << "HEAD: " << COLOR_GREEN << repositories[activeRepoIndex].activeBranchName << COLOR_RESET << endl;
                } else {
                    cout << COLOR_RED << "[ERROR] Nomor repository tidak valid!" << COLOR_RESET << endl;
                }
            } catch (...) {
                cout << COLOR_RED << "[ERROR] Input harus berupa angka!" << COLOR_RESET << endl;
            }
            pressEnter();
        } 
        else if (menuChoice == "0") {
            // ---------------- [0] EXIT ----------------
            clearScreen();
            cout << "Session Ended" << endl;
            cout << "Author: " << authorName << endl;
            cout << "Goodbye!" << endl;
            break;
        }
    }

    // Pembersihan seluruh memory heap sebelum program selesai
    for (int i = 0; i < repoCount; i++) {
        freeRepositoryMemory(repositories[i]);
    }
    delete[] repositories;

    return 0;
}