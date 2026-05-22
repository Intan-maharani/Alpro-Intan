#include <iostream>
#include <cstdlib>

using namespace std;


struct Character {
    string name;
    int lvl;
    int hp, maxHp;
    int mp, maxMp;
    int atk, baseAtk;
    int def, baseDef;
    int agi, baseAgi;
    int exp, maxExp;
};

struct Enemy {
    string name;
    int hp, maxHp;
    int agi;
    int atk;
    int expReward;
    bool isBoss;
};


bool Defeated[7] = {false, false, false, false, false, false, false};
Character player;

// --- Daftar Nama Musuh per Stage ---
string stageNames[7] = {"Pride", "Greed", "Wrath", "Sloth", "Gluttony", "Envy", "Lust"};
string enemy[7][4] = {
    {"Arrogant Soldier", "Noble Knight", "Fallen Champion", "King of Pride (Boss)"},
    {"Gold Hoarder", "Corrupt Merchant", "Living Treasure", "Dragon of Greed (Boss)"},
    {"Furious Beast", "Berserker", "Flame Demon", "Avatar of Wrath (Boss)"},
    {"Lazy Undead", "Sleeping Giant", "Dream Spirit", "Lord of Sloth (Boss)"},
    {"Hungry Slime", "Devourer Beast", "Endless Maw", "Lord of Gluttony (Boss)"},
    {"Shadow Copy", "Mirror Spirit", "Shapeshifter", "Embodiment of Envy (Boss)"},
    {"Charming Spirit", "Siren", "Succubus", "Queen of Lust (Boss)"}
};


void clear() {
    system("cls");
    
}

void pressEnter() {
    cout << "Press ENTER to continue...";
    cin.ignore();
    cin.get();
}

void banner(){
    cout << "+=======================================================================+" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|      _    _                         _   ____            _             |" << endl;
    cout << "|     / \\  | |__  _   _ ___ ___  __ _| | |  _ \\ ___  __ _| |_ __ ___    |" << endl;
    cout << "|    / _ \\ | '_ \\| | | / __/ __|/ _` | | | |_) / _ \\/ _` | | '_ ` _ \\   |" << endl;
    cout << "|   / ___ \\| |_) | |_| \\__ \\__ \\ (_| | | |  _ <  __/ (_| | | | | | | |  |" << endl;
    cout << "|  /_/   \\_\\_.__/ \\__, |___/___/\\__,_|_| |_| \\_\\___|\\__,_|_|_| |_| |_|  |" << endl;
    cout << "|                 |___/                                                 |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "+=======================================================================+" << endl;
}


void Player(string name) {
    player.name = name;
    player.lvl = 1;
    player.maxHp = 1500; player.hp = 1500;
    player.maxMp = 100;  player.mp = 100;
    player.baseAtk = 50;  player.atk = 50;  
    player.baseDef = 10;  player.def = 10;
    player.baseAgi = 15;  player.agi = 15;
    player.exp = 0;
    player.maxExp = 150;
}

// --- Sistem Level Up ---
void checkLevelUp() {
    if (player.exp >= player.maxExp) {
        player.lvl++;
        player.exp -= player.maxExp;
        player.maxExp += 50; 
        
        int Atk = player.baseAtk * 0.3;
        int Def = player.baseDef * 0.3;
        int Agi = player.baseAgi * 0.3;
        int Hp  = player.maxHp * 0.5;
        int Mp  = player.maxMp * 0.5;

        player.atk += Atk;
        player.def += Def;
        player.agi += Agi;
        player.maxHp += Hp;
        player.maxMp += Mp;

        // Pemulihan HP & MP 
        player.hp = player.maxHp;
        player.mp = player.maxMp;

        cout << "\n+-----------------------------------------------------------------------------+\n";
        cout << "|                             *** LEVEL UP! *** |\n";
        cout << "|  You reached Level " << player.lvl << "                                                        |\n";
        cout << "|  ATK +" << Atk << "  DEF +" << Def << "  AGI +" << Agi << "  MaxHP +" << Hp << "  MaxMP +" << Mp << "  (HP/MP restored)   |\n";
        cout << "+-----------------------------------------------------------------------------+\n";
    }
}

//Inisialisasi Musuh
Enemy generateEnemy(int stageIdx, int pathIdx) {
    Enemy e;
    e.name = enemy[stageIdx][pathIdx];
    e.isBoss = (pathIdx == 3);
    
    
    int scale = (stageIdx * 3) + pathIdx + 1;
    e.maxHp = 80 + (scale * 40);
    e.hp = e.maxHp;
    e.agi = 8 + (scale * 2);
    e.atk = 30 + (scale * 15);
    e.expReward = 10 + (scale * 12);
    
    return e;
}


void battle(Enemy enemy, int stageIdx) {
    int turn = 1;
    clear();

    while (player.hp > 0 && enemy.hp > 0) {
        clear();
        cout << "+=============================================================================+\n";
        cout << "| ABYSSAL REALM                                                   TURN " << turn << "      |\n";
        cout << "+=============================================================================+\n";
        cout << "| [" << player.name << "]                                            Level " << player.lvl << "\n";
        cout << "|   HP : " << player.hp << " / " << player.maxHp << "\n";
        cout << "|   MP : " << player.mp << " / " << player.maxMp << "\n";
        cout << "|   AGI: " << player.agi << "\n";
        cout << "|   EXP: " << player.exp << " / " << player.maxExp << "\n";
        cout << "+-----------------------------------------------------------------------------+\n";
        cout << "| [" << enemy.name << "]\n";
        cout << "|   HP : " << enemy.hp << " / " << enemy.maxHp << "\n";
        cout << "|   AGI: " << enemy.agi << "\n";
        cout << "+=============================================================================+\n";
        cout << "| 1. Basic Attack   (No MP | 100% ATK)\n";
        cout << "| 2. Heavy Attack   (30 MP | 160% ATK | lower accuracy)\n";
        cout << "| 3. Heal           (20 MP | Restore 200 HP)\n";
        cout << "| 4. Run Away       (Exit game)\n";
        cout << "+=============================================================================+\n";
        cout << "[Choose action]: ";
        
        int action;
        cin >> action;
        cout << "\n";

        bool Wasted = false;
        int damage = 0;

        
        if (action == 1) {
            
            if ((rand() % 100) < (enemy.agi * 2)) {
                cout << "[" << enemy.name << "] dodged your attack!\n";
            } else {
                damage = player.atk - (rand() % 5);
                if (damage < 5) damage = 5;
                enemy.hp -= damage;
                cout << "[Basic Attack] " << player.name << " hits " << enemy.name << " for " << damage << " damage.\n";
            }
        } 
        else if (action == 2) {
            if (player.mp < 30) {
                cout << "Not enough MP for Heavy Attack. Turn wasted.\n";
                Wasted = true;
            } else {
                player.mp -= 30;
               
                if ((rand() % 100) < 35 || (rand() % 100) < (enemy.agi * 2)) {
                    cout << "[" << player.name << "] missed the Heavy Attack!\n";
                } else {
                    damage = (player.atk * 1.6) - (rand() % 5);
                    enemy.hp -= damage;
                    cout << "[Heavy Attack] " << player.name << " lands a crushing blow on " << enemy.name << " for " << damage << " damage!\n";
                }
            }
        } 
        else if (action == 3) {
            if (player.mp < 20) {
                cout << "Not enough MP for Heal. Turn wasted.\n";
                Wasted = true;
            } else {
                player.mp -= 20;
                player.hp += 200;
                if (player.hp > player.maxHp) player.hp = player.maxHp;
                cout << "[Heal] " << player.name << " restores 200 HP!\n";
            }
        } 
        else if (action == 4) {
            cout << "You fled from the battle... Game Over.\n";
            exit(0);
        } 
        else {
            cout << "Invalid action! Turn wasted.\n";
            Wasted = true;
        }

        
        if (enemy.hp > 0) {
            
            if (!Wasted && ((rand() % 100) < (player.agi * 2))) {
                cout << "[" << enemy.name << "] attacked, but " << player.name << " dodged!\n";
            } else {
                int damage = enemy.atk - (player.def / 2) - (rand() % 5);
                if (damage < 5) damage = 5;
                player.hp -= damage;
                cout << "[" << enemy.name << "] attacks " << player.name << " for " << damage << " damage.\n";
            }
        }

        if (player.hp <= 0) {
            cout << "\nYou have been defeated in battle... Game Over.\n";
            exit(0);
        }

        turn++;
        cout << "+-----------------------------------------------------------------------------+\n";
        pressEnter();
    }

   
    if (enemy.hp <= 0) {
        clear();
        cout << "+-----------------------------------------------------------------------------+\n";
        cout << " " << enemy.name << " has been defeated!\n";
        cout << " EXP gained: " << enemy.expReward << "\n";
        cout << "+-----------------------------------------------------------------------------+\n";
        player.exp += enemy.expReward;
        
        if (enemy.isBoss) {
            Defeated[stageIdx] = true;
            cout << " [STAGE CLEAR] You have conquered the Sin of " << stageNames[stageIdx] << "!\n";
            cout << "+-----------------------------------------------------------------------------+\n";
        }
        
        checkLevelUp();
        pressEnter();
    }
}


void stageMenu(int stageIdx) {
    while (true) {
        clear();
        banner();
       	cout << "+=======================================================================+" << endl;
    	cout << "| [???]     : Fufufu, human. Are you strong enough to fight me?         \n";
        cout << "| [???]     : I am " << stageNames[stageIdx] << ", and you dare to challenge me? \n";
        cout << "| [" << stageNames[stageIdx] << "]  : But first, prove your worth.      \n";
        cout << "+=======================================================================+" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "   " << (i + 1) << ". " << enemy[stageIdx][i] << "\n";
        }
        cout << "   5. Retreat\n";
        cout << "+=======================================================================+" << endl;
        cout << "[Which path will you take?]: ";
        
        int choice;
        cin >> choice;
        
        if (choice >= 1 && choice <= 4) {
            Enemy target = generateEnemy(stageIdx, choice - 1);
            battle(target, stageIdx);
            if (Defeated[stageIdx]) {
                break; // Kembali ke menu utama jika boss stage tuntas
            }
        } else if (choice == 5) {
            break; // jika Mundur kembali ke pemilihan stage utama
        }
    }
}


int main() {
    
   srand(123);
    
    void clear();
    banner();
    cout << "+=======================================================================+" << endl;
    cout << "|       Welcome to Abyssal Realm, adventurer.                           |\n";
    cout << "|       The seven deadly sins await your challenge.                     |\n";
   	cout << "+=======================================================================+" << endl;
    
    cout << "[Enter your name]: ";
    string pName;
    cin >> pName;
    Player(pName);
    
    cout << "Press ENTER to continue...";
    cin.ignore();
    cin.get();

    
    while (true) {
        
        bool menang = true;
        for (int i = 0; i < 7; i++) {
            if (!Defeated[i]) menang = false;
        }

        if (menang) {
            clear();
            cout << "+=============================================================================+\n";
            cout << "|            *** CONGRATULATIONS, CHAMPION OF THE ABYSS! *** |\n";
            cout << "|                                                                             |\n";
            cout << "|            You have defeated all Seven Deadly Sins!                         |\n";
            cout << "|                                                                             |\n";
            for (int i = 0; i < 7; i++) {
                cout << "|            " << stageNames[i] << " \t - DEFEATED                        |\n";
            }
            cout << "|                                                                             |\n";
            cout << "|   The Abyssal Realm trembles before your name, " << player.name << "!       |\n";
            cout << "|   You are the true master of the Abyss!                                     |\n";
            cout << "+=============================================================================+\n";
            pressEnter();
            break;
        }

        clear();
        banner();
         cout << "+=======================================================================+" << endl;
        cout <<  "|                     THE 7 DEADLY SINS ARE WAITING FOR YOU             |\n";
         cout << "+=======================================================================+" << endl;
        
        for (int i = 0; i < 7; i++) {
        cout << "|                             " << (i + 1) << ". " << stageNames[i];
        
        
        int panjangTeks = stageNames[i].length() + 25; 
        if (Defeated[i]) {
            cout << " [BOSS DEFEATED]";
            panjangTeks += 16;
        }
        for (int s = panjangTeks; s < 64; s++) cout << " ";
        cout << "|" << endl;
    }
        cout << "|                             8. EXIT                                   |\n";
         cout << "+=======================================================================+" << endl;
        cout <<  "|             The deeper you go, the stronger they are                  |\n";
         cout << "+=======================================================================+" << endl;
        cout << "[Choose your desired stage]: ";
        
        int stageChoice;
        cin >> stageChoice;
        
        if (stageChoice >= 1 && stageChoice <= 7) {
            if (Defeated[stageChoice - 1]) {
                cout << "\nThis stage boss has already been crushed! Choose another sin.\n";
                pressEnter();
            } else {
                stageMenu(stageChoice - 1);
            }
        } else if (stageChoice == 8) {
            cout << "\nThank you for playing Abyssal Realm!\n";
            break;
        }
    }

    return 0;
}