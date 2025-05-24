#include "admin.h"
#include "log_check.h"

using namespace std;

void loginFrame() {
    system("cls");

    cout << "\n";
    cout << short_space << "----------------------------------------------------------------------------------------------------------\n"; 
    cout << short_space << "|                         CHAO MUNG DEN VOI HE THONG DAT GHE MAY BAY - ITF_AIRWAY                        |\n"; 
    cout << short_space << "----------------------------------------------------------------------------------------------------------\n"; 

    cout << long_space << "----------------------------------------------------\n"; 
    cout << long_space << "|                    ADMIN LOGIN                   |\n";
    cout << long_space << "+--------------------------------------------------+\n";
    cout << long_space << "|  Tai khoan:                                      |\n";
    cout << long_space << "|  Mat khau :                                      |\n";
    cout << long_space << "|  Nhap lai mat khau:                              |\n";
    cout << long_space << "----------------------------------------------------\n";
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
      cout << long_space << "Khong truy xuat duoc thong tin he thong\n";
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
        Goto(47, 7);
        getline(cin, username);
        Goto(47, 8);
        password1 = input_hidden_pass();
        Goto(55, 9);
        password2 = input_hidden_pass();

        if (username.empty() || password1.empty() || password2.empty()) { 
            cout << "\n\n\n"; 
            cout << long_space << "Khong duoc de trong thong tin!";
            Sleep(1000); 
        }
    } while (username.empty() || password1.empty() || password2.empty());
}

void admin_Login(string& username) {
    unordered_map<string, string> accounts;
    load_accounts(accounts);

    string password1, password2;
    int attempts = 0; 
    bool success = false; 
    do {
        input(username, password1, password2); 
        auto it = accounts.find(username);
        if (it == accounts.end()) {
            cout << "\n\n\n"; 
            cout << long_space << "Tai khoan khong ton tai!\n"; 
            Sleep(1000); 
            continue; 
        }

        if (password1 != password2) {
            cout << "\n\n\n";
            cout << long_space << "Mat khau khong khop!\n"; 
            attempts++;
            Sleep(1000); 
            continue; 
        }

        if (password1 != it->second) {
            cout << "\n\n\n";
            cout << long_space << "Mat khau sai!\n"; 
            attempts++; 
            Sleep(1000); 
            continue; 
        }

        success = true; 
        break; 

    } while (attempts < 3);


    if (success) {
        cout << "\n\n\n"; 
        cout << long_space << "Dang nhap thanh cong!\n";
        logLogin(username); 
        Sleep(1000);
    }
    else {
        cout << "\n\n\n"; 
        cout << long_space << "Qua nhieu lan thu, dang nhap that bai.\n"; 
        exit(0);
    }
}

bool checkLogout() {
    system("cls"); 

    string password;
    cout << "\n";
    cout << long_space << "----------------------------------------------------\n";
    cout << long_space << "|                     LOG OUT                      |\n";
    cout << long_space << "+--------------------------------------------------+\n";
    cout << long_space << "|  Mat khau :                                      |\n";
    cout << long_space << "----------------------------------------------------\n"; 
    cout << "\n"; 

    Goto(47, 4); 
    password = input_hidden_pass(); 
    return password == "close"; 
}

bool admin_Logout(const string& username) {
    system("cls"); 

    bool check = false; 
    int attempts = 0; 
    while (attempts < 3) {
        if (checkLogout()) {
            logLogout(username); 
            cout << "\n\n"; 
            cout << long_space << "Dang xuat...\n"; 
            Sleep(1000); 
            return check = true; 
        }
        else {
            cout << "\n\n"; 
            cout << long_space << "Sai mat khau!\n"; 
            Sleep(1000); 
            attempts++; 
        }
    }
    cout << "\n";
    cout << long_space << "Vuot qua so lan cho phep. Khong the dang xuat.\n"; 
    Sleep(1000); 
    return check; 
}
