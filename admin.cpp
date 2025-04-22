#pragma once 
#include <iostream>
#include <string>
#include <windows.h> 

using namespace std;

void admin()
{
    cout << endl
         << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                           DANG NHAP HE THONG                                           ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;

    string username; 
    while (true) {
        cout << endl
             << " → Nhap ten dang nhap: ";
        getline(cin, username); 
        
        if (username.length() > 0) {
            if (username == "phuquy06" || username == "vinhquang0411") break;
            else {
                cout << endl
                     << "   [ERROR] Ten dang nhap khong hop le!" << endl;
            }
        } else {
            cout << endl
                 << "   [ERROR] Ten dang nhap khong duoc de trong!" << endl;
        }
    }

    int incorrectCount = 0;
    string openCode;
    while (true) {
        cout << endl
             << " → Nhap mat khau de khoi dong chuong trinh: ";
        getline(cin, openCode);
        if (openCode == "open" || openCode == "Open" || openCode == "OPEN") break; 
        else {
            cout << endl
                 << "   [ERROR] Mat khau khong hop le!" << endl;
            incorrectCount++;
        }

        if (incorrectCount == 3) {
            cout << endl
                 << "   [ERROR] Sai mat khau qua 3 lan!" << endl;
            cout << endl
                 << "   Chuong trinh ket thuc!" << endl;
            exit(0); 
        }
    }

    string openCode2; 
    while (true) {
        cout << endl
             << " → Nhap lai mat khau de khoi dong chuong trinh: ";
        getline(cin, openCode2);
        if (openCode2 == openCode) break;
        else cout << endl
                  << "   [ERROR] Mat khau khong khop!" << endl;
    }

    cout << endl
         << "   Dang dang nhap..." << endl;
    Sleep(800);
    cout << "   Chao mung den voi he thong dat ghe!" << endl;
    Sleep(800);
}
