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
#include <filesystem>
#include "global.h"
#include "importdata.h"

using namespace std;
using namespace std::filesystem;

bool openInputFiles(ifstream &inputFile1, ifstream &inputFile2)
{
    path directorypath = "./" + flightCode;
    if (!exists(directorypath))
    {
        cout << "   Thu muc khong ton tai!" << endl;
        return false;
    }

    path personalInfoPath = directorypath / PERSONAL_INFO;
    path flightInfoPath = directorypath / FLIGHT_INFO;
    inputFile1.open(personalInfoPath);
    if (!inputFile1.is_open())
    {
        cout << "   Khong mo duoc file PersonalInformation.txt" << endl;
        return false;
    }
    inputFile2.open(flightInfoPath);
    if (!inputFile2.is_open())
    {
        cout << "   Khong mo duoc file FlightInformation.txt" << endl;
        inputFile1.close();
        return false;
    }
    return true;
}

bool readFlightInformation(ifstream &inputFile2, ticket &data)
{
    cout << endl
         << "   Doc thong tin chuyen bay..." << endl;
    Sleep(800);

    if (!getline(inputFile2, data.flightCode))
    {
        cout << "   Loi khi doc ma chuyen bay" << endl;
        return false;
    }

    if (!getline(inputFile2, data.departure))
    {
        cout << "   Loi khi doc noi di" << endl;
        return false;
    }

    if (!getline(inputFile2, data.destination))
    {
        cout << "   Loi khi doc noi den" << endl;
        return false;
    }

    if (!getline(inputFile2, data.date))
    {
        cout << "   Loi khi doc ngay" << endl;
        return false;
    }

    if (!getline(inputFile2, data.time))
    {
        cout << "   Loi khi doc gio" << endl;
        return false;
    }

    cout << "   Dang lay thong tin chuyen bay..." << endl;
    Sleep(800);
    cout << "   Lay thong tin chuyen bay thanh cong!" << endl;
    Sleep(800);

    return true;
}

void readPassengerInformation(ifstream &inputFile1, const ticket &flightData)
{
    cout << endl
         << "   Doc thong tin hanh khach..." << endl;
    Sleep(800);

    string line;
    while (getline(inputFile1, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        ticket passenger;

        passenger.flightCode = flightData.flightCode;
        passenger.departure = flightData.departure;
        passenger.destination = flightData.destination;
        passenger.date = flightData.date;
        passenger.time = flightData.time;
        passenger.seatCode = "Chua dat ghe";

        if (!getline(ss, passenger.customer.names, ','))
        {
            cout << "   Loi khi doc ten hanh khach" << endl;
            continue;
        }
        if (!getline(ss, passenger.customer.DoB, ','))
        {
            cout << "   Loi khi doc ngay sinh" << endl;
            continue;
        }
        if (!getline(ss, passenger.customer.email, ','))
        {
            cout << "   Loi khi doc email" << endl;
            continue;
        }
        if (!getline(ss, passenger.customer.phoneNumber, ','))
        {
            cout << "   Loi khi doc so dien thoai" << endl;
            continue;
        }
        if (!getline(ss, passenger.customer.gender, ','))
        {
            cout << "   Loi khi doc gioi tinh" << endl;
            continue;
        }
        if (!getline(ss, passenger.ticketCode, ','))
        {
            cout << "   Loi khi doc ma ve" << endl;
            continue;
        }
        if (!getline(ss, passenger.classLabel, ','))
        {
            cout << "   Loi khi doc hang ve" << endl;
            continue;
        }

        passengers.push_back(passenger);
    }

    cout << "   Dang lay thong tin khach hang..." << endl;
    Sleep(800);
    cout << "   Doc thong tin hanh khach thanh cong!" << endl;
    Sleep(800);

    cout << "   Co tat ca " << passengers.size() << " hanh khach trong he thong" << endl;
    cout << "   Ket thuc doc thong tin..." << endl;
    Sleep(800);
}

void importPassengersInformation()
{
    ifstream inputFile1, inputFile2;
    if (!openInputFiles(inputFile1, inputFile2))
    {
        return;
    }
    ticket flightData;
    if (!readFlightInformation(inputFile2, flightData))
    {
        inputFile1.close();
        inputFile2.close();
        return;
    }
    readPassengerInformation(inputFile1, flightData);
    inputFile1.close();
    inputFile2.close();
}

void importBookedTicket() // lay thong tin ve da dat cua nhung khach hang truoc do
{ 
    path directorypath = "./" + flightCode;
    if (!exists(directorypath))
    {
        cout << "   Thu muc khong ton tai!" << endl;
        return;
    }
    path bookedTicketPath = directorypath / TICKET_INFO;

    ifstream inputFile(bookedTicketPath);
    string line;
    vector<string> maSoVe;
    if (!inputFile.is_open())
    {
        cout << "   Khong mo duoc file!" << endl;
        return;
    }
    while (getline(inputFile, line))
    {
        int found = line.find("Ma so ve:");
        if (found != string::npos)
        {
            string code = line.substr(found + 10);
            code.erase(0, code.find_first_not_of(" "));
            maSoVe.push_back(code);
        }
    }
    inputFile.close();

    cout << endl
         << "   Kiem tra thong tin ve da dat..." << endl;
    Sleep(800);
    cout << "   Kiem tra thanh cong!" << endl;
    Sleep(800);

    for (string i : maSoVe)
    {
        bookedStore.insert(i);
    }
    int bookedTicket = bookedStore.size();
    cout << "   Tong cong: " << bookedTicket << " khach hang da dat ghe" << endl;
}