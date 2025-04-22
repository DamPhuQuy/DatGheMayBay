#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <cctype>
#include <sstream>
#include <set>
#include <windows.h>
#include <iomanip>
#include "global.h"
#include "importdata.h"
#include "seatingchart.h" 
#include "admin.h"
using namespace std; 

void displayFlight(const ticket &flightList)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                          THONG TIN CHUYEN BAY                                          ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║   Ma so chuyen bay : %s                                                                           ║\n", flightList.flightCode.c_str());
    printf("║                                                                                                        ║\n");
    printf("║   Noi xuat phat    : %s -> Noi den: %s                                                   ║\n", flightList.departure.c_str(), flightList.destination.c_str());
    printf("║                                                                                                        ║\n");
    printf("║   Ngay xuat phat   : %s                                                                        ║\n", flightList.date.c_str());
    printf("║                                                                                                        ║\n");
    printf("║   Thoi gian        : %s                                                                           ║\n", flightList.time.c_str());
    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}

void inputFlightCode()
{
    cout << endl
         << " → Nhap ma chuyen bay: ";
    string flightCode;
    getline(cin, flightCode);
    if (flightCode != "ITF2025" && flightCode != "itf2025" && flightCode != "Itf2025")
    {
        cout << endl
             << "   [ERROR] Sai ma chuyen bay! Ket thuc!" << endl;
        exit(0);
    }
    importPassengersInformation();
    importBookedTicket();
}

void displayInformation()
{
    cout << endl
         << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl
         << "║                                     THONG TIN KHACH HANG VA GHE NGOI                                   ║" << endl
         << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;

    Sleep(800);

    for (int index = 0; index < passengers.size(); index++)
    {
        if (store.find(passengers[index].ticketCode) != store.end())
        {
            cout << endl
                 << "Thong tin ve " << passengers[index].ticketCode << " hien tai: " << endl;
            cout << "------------------------------------" << endl;
            cout << " Ma so chuyen bay: " << passengers[index].flightCode << endl;
            cout << " Ma so ve: " << passengers[index].ticketCode << endl;
            cout << " Khach hang: " << passengers[index].customer.names << endl;
            cout << " Ngay sinh: " << passengers[index].customer.DoB << " - Gioi tinh: " << passengers[index].customer.gender << endl;
            cout << " Email: " << passengers[index].customer.email << endl;
            cout << " So dien thoai: " << passengers[index].customer.phoneNumber << endl;
            cout << " Chuyen bay: " << passengers[index].departure << " -> " << passengers[index].destination << endl;
            cout << " Ngay: " << passengers[index].date << " - Gio: " << passengers[index].time << endl;
            cout << " Ma so ghe: " << passengers[index].seatCode << endl;
            cout << "------------------------------------" << endl;
        }
    }

    Sleep(800);
}

void TicketOutput(ofstream &WriteFile, int index)
{
    WriteFile << endl;
    WriteFile << "Thong tin ve " << passengers[index].ticketCode << " hien tai: " << endl;
    WriteFile << "------------------------------------" << endl;
    WriteFile << " Ma so chuyen bay: " << passengers[index].flightCode << endl;
    WriteFile << " Ma so ve: " << passengers[index].ticketCode << endl;
    WriteFile << " Khach hang: " << passengers[index].customer.names << endl;
    WriteFile << " Ngay sinh: " << passengers[index].customer.DoB << " - Gioi tinh: " << passengers[index].customer.gender << endl;
    WriteFile << " Email: " << passengers[index].customer.email << endl;
    WriteFile << " So dien thoai: " << passengers[index].customer.phoneNumber << endl;
    WriteFile << " Chuyen bay: " << passengers[index].departure << " -> " << passengers[index].destination;
    WriteFile << " Ngay: " << passengers[index].date << " - Gio: " << passengers[index].time << endl;
    WriteFile << " Ma so ghe: " << passengers[index].seatCode << endl;
    WriteFile << "------------------------------------" << endl;
    WriteFile << endl;
}

void printTicket()
{
    ofstream WriteFile("TicketInformation.txt", ios::app);
    for (int index = 0; index < passengers.size(); index++)
    {
        if (store.find(passengers[index].ticketCode) != store.end())
        {
            TicketOutput(WriteFile, index);
        }
    }
    cout << "   Dang luu thong tin..." << endl;
    Sleep(800);
    cout << "   Thong tin da duoc luu!" << endl;
    Sleep(800);
    cout << "   Tong so ve luu: " << store.size() << endl;
    WriteFile.close();
}

void resetTicketInformation()
{
    ofstream WriteFile("TicketInformation.txt");
    WriteFile.close();
    cout << "   DU LIEU VE DA DUOC RESET" << endl;
}

void displayMenu()
{
    cout << endl;
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                         CHAO MUNG DEN VOI HE THONG DAT GHE MAY BAY - ITF_AIRWAY                        ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║   1. Hien thi thong tin chuyen bay                                                                     ║" << endl;
    cout << "║                                                                                                        ║" << endl;
    cout << "║   2. Dat ghe cho khach hang                                                                            ║" << endl;
    cout << "║                                                                                                        ║" << endl;
    cout << "║   0. Thoat chuong trinh                                                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
}


void menu()
{
    admin();
    cout << endl
         << "   ---------------------------------------------" << endl;
    inputFlightCode();

    if (passengers.empty())
    {
        cout << "   Khong co thong tin hanh khach!" << endl;
        return;
    }

    cout << "   Dang hien thi menu..." << endl;
    Sleep(800);
    int choice;
    do
    {
        displayMenu();
        while (true)
        {
            cout << " → Vui long nhap lua chon: ";
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "   Nhap sai!" << endl;
            }
            else
                break;
        }
        cin.ignore();

        switch (choice)
        {
        case 0:
        {
            cout << "   Ban da chon thoat chuong trinh." << endl;
            cout << "   Nhap mat khau de tien hanh ket thuc chuong trinh: ";
            string endCode;
            while (true)
            {
                getline(cin, endCode);
                if (endCode != "close" && endCode != "CLOSE" && endCode != "Close")
                {
                    cout << "   Nhap sai mat khau, hay nhap lai: ";
                    continue;
                }
                else
                {
                    break;
                }
            }
            break;
        }
        case 1:
        {
            if (!passengers.empty())
            {
                displayFlight(passengers[0]);
                cout << " Nhan phim bat ki de tiep tuc... ";
                getchar();
            }
            else
            {
                cout << "   Khong co thong tin chuyen bay de hien thi." << endl;
            }
            break;
        }
        case 2:
        {
            if (passengers.empty())
            {
                cout << "   Khong co thong tin hanh khach. Khong the dat ghe." << endl;
            }
            else
            {
                importSeatCode();
            }

            if (passengers.empty())
            {
                cout << "   Khong co thong tin hanh khach de hien thi." << endl;
                break;
            }
            displayInformation();
            cout << "   Ban co muon xuat ve (Y/N): ";
            string out;
            getline(cin, out);
            if (out[0] == 'Y' || out[0] == 'y')
            {
                printTicket();
            }
            cout << " Nhan phim bat ki de tiep tuc... ";
            getchar();
            break;
        }
        default:
        {
            cout << "   Lua chon khong hop le. Vui long nhap lai." << endl;
            break;
        }
        }
    } while (choice != 0);
}

void end()
{
    cout << endl;
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                    Cam on quy khach da su dung dich vu                                 ║" << endl;
    cout << "║                                               ITF-AIRWAYS                                              ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;
    Sleep(800);
}

void reset()
{
    cout << "   Reset so do ghe? (Y/N) ";
    string choice;
    getline(cin, choice);
    if (choice[0] == 'y' || choice[0] == 'Y')
    {
        resetSeatingChart();
        cout << "   Reset du lieu ve da dat? (Y/N) ";
        getline(cin, choice);
        if (choice[0] == 'y' || choice[0] == 'Y')
        {
            resetTicketInformation();
        }
    }
}