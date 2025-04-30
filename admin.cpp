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
    coord.X = x; coord.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}

bool checkLogin() 
{
    string password1, password2; 
    loginFrame(); 

    Goto(13, 7); 
    getline(cin, username); 

    Goto(13, 8); 
    char temp; 
    password1.clear(); 
    while (true) {
        temp = _getch(); 
        if (temp == 13) break; // \n = 13 
        else if (temp == 8 && !password1.empty()) // \b = 8 
        {
            password1.pop_back();
            cout << "\b \b"; 
        } 
        else if (isprint(temp)) 
        {
            password1 += temp; 
            cout << "*"; 
        }
    }

    Goto(21, 9); 
    while (true) 
    {
        temp = _getch(); 
        if (temp == 13) break; 
        else if (temp == 8 && !password2.empty()) 
        {
            password2.pop_back(); 
            cout << "\b \b"; 
        }
        else if (isprint(temp)) 
        {
            password2 += temp; 
            cout << "*";
        }
    }

    if (username == "phuquy06") 
    {
        return (password1 == "open" && password2 == password1);    
    } 
    else if (username == "vinhquang0411") 
    {   
        return (password1 == "ITFopen" && password2 == password1);
    } 
    else {
        return false; 
    }
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
            cout << endl << endl; 
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
    while (true) {
        temp = _getch(); 
        if (temp == 13) break; 
        else if (temp == 8 && !password.empty()) 
        {
            password.pop_back();
            cout << "\b \b";
        }
        else if (isprint(temp)) {
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
            cout << endl << endl 
                 << "   Dang xuat... " << endl;
            Sleep(800); 
            return; 
        } 
        else
        {
            cout << endl << endl
                 << "   Sai mat khau!" << endl; 
            Sleep(800);
            incorrectCount++;
        }
    }
}