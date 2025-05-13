#include "admin.h"
#include "log_check.h"

using namespace std;

void loginFrame() {
    system("cls");

    cout << "\n"; 
    cout << "----------------------------------------------------------------------------------------------------------\n"; 
    cout << "|                         CHAO MUNG DEN VOI HE THONG DAT GHE MAY BAY - ITF_AIRWAY                        |\n"; 
    cout << "----------------------------------------------------------------------------------------------------------\n"; 

    cout << "----------------------------------------------------\n"; 
    cout << "|                    ADMIN LOGIN                   |\n";
    cout << "+--------------------------------------------------+\n";
    cout << "| Tai khoan:                                       |\n";
    cout << "| Mat khau :                                       |\n";
    cout << "| Nhap lai mat khau:                               |\n";
    cout << "----------------------------------------------------\n";
}

void Goto(const int x, const int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void load_accounts(unordered_map<string, string> &accounts) {
    ifstream readFile("accounts.txt");
    if (!readFile.is_open()) {
      cout << "   Khong truy xuat duoc thong tin he thong\n";
      exit(0);
    }
    string line;
    while (getline(readFile, line)) {
          stringstream ss(line);
          string user, pass;
          while (getline(ss, user, ',') && getline(ss, pass)) {
            accounts[user] = pass;
          }
    }
    readFile.close();
}

string input_hidden_pass() {
    string pass;
    char temp;
    while ((temp = _getch()) != '\r') {
        if (temp == '\b') {
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else if (isprint(temp)) {
            pass.push_back(temp);
            cout << "*";
        }
    }
    return pass;
}

void input(string& username, string& password1, string& password2) {
    do {
        loginFrame();
        Goto(13, 7);
        getline(cin, username);
        Goto(13, 8);
        password1 = input_hidden_pass();
        Goto(21, 9);
        password2 = input_hidden_pass();
    } while (username.empty() || password1.empty() || password2.empty());
}

void admin_Login() {
    unordered_map<string, string> accounts;
    load_accounts(accounts);

    string username, password1, password2;
    int attempts = 0; 
    bool success = false; 
    do {
        input(username, password1, password2); 
        auto it = accounts.find(username);
        if (it == accounts.end()) {
            cout << "   Tai khoan khong ton tai!\n"; 
            Sleep(800); 
            continue; 
        }

        if (password1 != password2) {
            cout << "   Mat khau khong khop!\n"; 
            attempts++;
            Sleep(800); 
            continue; 
        }

        if (password1 != it->second) {
            cout << "   Mat khau sai!\n"; 
            attempts++; 
            Sleep(800); 
            continue; 
        }

        success = true; 
        break; 

    } while (attempts < 3);


    if (success) {
        cout << "   \n\n\nDang nhap thanh cong!\n";
        logLogin(username); 
    }
    else {
        cout << "   Qua nhieu lan thu, dang nhap that bai.\n"; 
        exit(0);
    }
}

bool checkLogout() {
    string password;
    cout << "\n";
    cout << "----------------------------------------------------\n";
    cout << "|                     LOG OUT                      |\n";
    cout << "+--------------------------------------------------+\n";
    cout << "| Mat khau :                                       |\n";
    cout << "----------------------------------------------------\n"; 

    Goto(13, 4); 
    password = input_hidden_pass(); 
    return password == "close"; 
}

void admin_Logout(const string& username) {
    system("cls"); 

    int attempts = 0; 
    while (attempts < 3) {
        if (checkLogout()) {
            logLogout(username); 
            cout << "\n" << "   Dang xuat...\n"; 
            Sleep(800); 
            return; 
        }
        else {
            cout << "\n" << "   Sai mat khau!\n"; 
            Sleep(800); 
            attempts++; 
        }
    }
    cout << "\n" << "   Vuot qua so lan cho phep. Khong the dang xuat.\n"; 
    Sleep(800); 
}
