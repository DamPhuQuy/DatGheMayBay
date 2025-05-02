#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "logCheck.h"

using namespace std;

string username;

void loginFrame()
{
    system("cls");

    cout << endl
         << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                         CHAO MUNG DEN VOI HE THONG DAT GHE MAY BAY - ITF_AIRWAY                        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║                  ADMIN DANG NHAP                 ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║ Tai khoan:                                       ║" << endl;
    cout << "║ Mat khau :                                       ║" << endl;
    cout << "║ Nhap lai mat khau:                               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
}

void Goto(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int checkUser() 
{
    Goto(13, 7); 
    getline(cin , username); 
    if (username == "phuquy06") return 1; 
    else if (username == "vinhquang0411") return 2;
    else return 0; 
}

void checkPassword(string& password) {
    password.clear(); 
    while (true) 
    {
        char temp; 
        temp = _getch();
        if (temp == '\r') break; 
        else if (temp == '\b' && !password.empty()) 
        {
            password.pop_back(); 
            cout << "\b \b"; 
        }
        else if (isprint(temp)) 
        {
            password += temp; 
            cout << "*"; 
        }
    }
}

bool checkLogin() {
    loginFrame(); 

    int check = checkUser();

    string password1, password2; 
    Goto(13, 8); 
    checkPassword(password1);
    Goto(21, 9); 
    checkPassword(password2); 

    if (check == 0) return false; 
    else if (check == 1) return (password1 == "open" && password1 == password2); 
    else return (password1 == "ITFopen" && password1 == password2); 
}

void adminLogin()
{
    int incorrectCount = 0;
    while (incorrectCount < 3)
    {
        if (checkLogin())
        {
            logLogin(username);
            cout << "   Dang dang nhap..." << endl;
            Sleep(800);
            cout << "   Chao mung den voi he thong dat ghe!" << endl;
            Sleep(800);
            return;
        }
        else
        {
            cout << endl
                 << endl;
            cout << "   Tai khoan hoac mat khau sai!" << endl;
            cout << "   Vui long nhap lai!" << endl;
            incorrectCount++;
            Sleep(1500);
        }
    }
    cout << endl;
    cout << "   Sai mat khau qua " << incorrectCount << " lan!" << endl;
    cout << "   Dung chuong trinh..." << endl;
    exit(0);
}

bool checkLogout()
{
    string password;
    cout << endl;
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║                     LOG OUT                      ║" << endl;
    cout << "╠══════════════════════════════════════════════════╣" << endl;
    cout << "║ Mat khau :                                       ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    Goto(13, 4);
    char temp;
    while (true)
    {
        temp = _getch();
        if (temp == 13)
            break;
        else if (temp == 8 && !password.empty())
        {
            password.pop_back();
            cout << "\b \b";
        }
        else if (isprint(temp))
        {
            password += temp;
            cout << "*";
        }
    }
    return (password == "close");
}

void adminLogout()
{
    system("cls");

    int incorrectCount = 0;
    while (incorrectCount < 3)
    {
        if (checkLogout())
        {
            logLogout(username);
            cout << endl
                 << endl
                 << "   Dang xuat... " << endl;
            Sleep(800);
            return;
        }
        else
        {
            cout << endl
                 << endl
                 << "   Sai mat khau!" << endl;
            Sleep(800);
            incorrectCount++;
        }
    }
}