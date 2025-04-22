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
#include "seatingchart.h" 
using namespace std;

void importSeatingChartData() {
    ifstream inputFile("BookedSeatingChart.txt"); 
    if (!inputFile) {
        inputFile.open("SeatingChart.txt"); 
        if (!inputFile) {
            cout << "Da xay ra loi khi mo file" << endl; 
            return; 
        }
    }
    string line;
    bool isFirstClass = false, isEconomyClass = false;  
    while (getline(inputFile, line)) {
        if (line == "First Class:") {
            isFirstClass = true; 
            isEconomyClass = false; 
            continue; 
        }
        if (line == "Economy Class:") {
            isFirstClass = false; 
            isEconomyClass = true; 
            continue; 
        }
        if (!line.empty()) {
            stringstream ss(line); 
            vector<string> row; 
            string token; 
            while (ss >> token) {
                row.push_back(token); 
            }
            if (isFirstClass) {
                firstClass.push_back(row); 
            } 
            else if (isEconomyClass) {
                economyClass.push_back(row); 
            }
        }
    }
    inputFile.close(); 
}

void displaySeatingChart() { 
	cout << endl; 
    cout << "╔════════════════════╦═══════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║    First Class     ║                                     Economy Class                                 ║" << endl;
    cout << "╠════════════════════╬═══════════════════════════════════════════════════════════════════════════════════╣" << endl;
    
    cout << "║                    ║ ";
    for (const auto& seat : economyClass[0]) {
        cout << seat << " ";
    }
    cout << "   ║" << endl;
    
    cout << "║ " << firstClass[0][0] << " " << firstClass[1][0] << " " << firstClass[2][0] << " " << firstClass[3][0] << "        ║ ";
    for (const auto& seat : economyClass[1]) {
        cout << seat << " ";
    }
    cout << "   ║" << endl;
    
    cout << "║ " << firstClass[0][1] << " " << firstClass[1][1] << " " << firstClass[2][1] << " " << firstClass[3][1] << "        ║ ";
    for (const auto& seat : economyClass[2]) {
        cout << seat << " ";
    }
    cout << "   ║" << endl;
    
    cout << "╠════════════════════╬═══════════════════════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║ ------Loi di------ ║ ------------------------------------Loi di--------------------------------------- ║" << endl; 
    cout << "╠════════════════════╬═══════════════════════════════════════════════════════════════════════════════════╣" << endl;
    
    cout << "║ " << firstClass[0][2] << " " << firstClass[1][2] << " " << firstClass[2][2] << " " << firstClass[3][2] << "        ║ ";
    for (const auto& seat : economyClass[3]) {
        cout << seat << " ";
    }
    cout << "   ║" << endl;
    
    cout << "║ " << firstClass[0][3] << " " << firstClass[1][3] << " " << firstClass[2][3] << " " << firstClass[3][3] << "        ║ ";
    for (const auto& seat : economyClass[4]) {
        cout << seat << " ";
    }
    cout << "   ║" << endl;
    
    cout << "║                    ║ ";
    for (const auto& seat : economyClass[5]) {
        cout << seat << " ";
    }
    cout << "   ║" << endl;
    
    cout << "╚════════════════════╩═══════════════════════════════════════════════════════════════════════════════════╝" << endl; 

    cout << endl 
         << "                  [--] hay [---]: Ghe dat dat                 1A: Ghe chua dat " << endl; 
}

bool isValidSeat(const string& seat) {
    bool check = false;

    if (!isalpha(seat[seat.length() - 1])) {
        return check; 
    }

    string number = "";
    for (char c : seat) {
        if (isdigit(c)) {
            number += c; 
        }
    }

    int num = stoi(number); 
    if (!(num < 1 || num > 25)) check = true; 
    return check; 
}

string selectSeat(int index) {
    string choice;
    while (true) {
        cout << " → Hay chon ghe: ";
        getline(cin, choice); 

        if (!isValidSeat(choice) && seatStatus.find(choice) != seatStatus.end()) {
            cout << endl;
            cout << "   ════ Lua chon khong phu hop hoac ghe da dat ═════";
            cout << endl;
            continue; 
        }
        
        bool foundFirstClass = false, foundEconomyClass = false;  
        if (passengers[index].classLabel == "First Class") {
            for (int i = 0; i < firstClass.size(); i++) {
                for (int j = 0; j < firstClass[i].size(); j++) {
                    if (firstClass[i][j] == choice) {
                    	if (choice.length() == 2) firstClass[i][j] = "--";
						else if (choice.length() == 3) firstClass[i][j] = "---";  
                        foundFirstClass = true;
                        break; 
                    }
                }
                if (foundFirstClass) break; 
            }
            if (!foundFirstClass) {
                cout << "   Ghe chon khong phu hop voi First Class!" << endl; 
                continue; 
            }
        } 

        if (passengers[index].classLabel == "Economy Class") {
            for (int i = 0; i < economyClass.size(); i++) {
                for (int j = 0; j < economyClass[i].size(); j++) {
                    if (economyClass[i][j] == choice) {
                    	if (choice.length() == 2) economyClass[i][j] = "--";
						else if (choice.length() == 3) economyClass[i][j] = "---";  
                        foundEconomyClass = true; 
                        break; 
                    }
                }
                if (foundEconomyClass) break; 
            }
            if (!foundEconomyClass) {
                cout << "   Ghe chon khong phu hop voi Economy Class!" << endl; 
                continue; 
            }
        } 

        if (foundFirstClass == true || foundEconomyClass == true) {
            cout << "   Chac chan muon chon " << choice << " (Y/N): ";
            string okay;
            getline(cin, okay);
            if (okay[0] == 'Y' || okay[0] == 'y') {
                seatStatus.insert({choice, "X"});
                return choice;
            }
            else {
                seatStatus.erase(choice);
                continue;
            }
        } 
        else {
            cout << endl;
            cout << "   ════ Lua chon khong phu hop hoac ghe da dat ═════";
            cout << endl;
            continue;
        }
    }
}

void updateSeatingChartFile() {
    ofstream WriteFile("BookedSeatingChart.txt");
    if (!WriteFile) {
        cout << "   Loi khi mo file BookedSeatingChart" << endl;
        return;
    }
    WriteFile << "First Class:" << endl; 
    for (int i = 0; i < firstClass.size(); i++) {
        for (int j = 0; j < firstClass[i].size(); j++) {
            WriteFile << firstClass[i][j] << " "; 
        }
        WriteFile << endl; 
    }
    WriteFile << endl; 
    WriteFile << "Economy Class:" << endl;
    for (int i = 0; i < economyClass.size(); i++) {
        for (int j = 0; j < economyClass[i].size(); j++) {
            WriteFile << economyClass[i][j] << " "; 
        }
        WriteFile << endl; 
    } 
    WriteFile.close();
}

void resetSeatingChart() {
    ifstream ReadFile("SeatingChart.txt");
    if (!ReadFile) {
        cout << "  Khong the mo file SeatingChart.txt" << endl;
        return;
    }
    ofstream WriteFile("BookedSeatingChart.txt", ios::trunc);
    if (!WriteFile) {
        cout << "  Khong the mo file BookedSeatingChart.txt" << endl;
        return;
    }
    string line;
    while (getline(ReadFile, line)) {
        WriteFile << line << endl;
    }
    ReadFile.close();
    WriteFile.close();
    cout << "   SO DO GHE DA DUOC RESET" << endl;
}

void importSeatCode()
{
    importSeatingChartData();
    displaySeatingChart();

    cout << endl
         << " → So ve may bay can dat: ";

    string num;
    while (true)
    {
        cin >> num;
        if (num.length() != 1)
        {
            cout << "   Nhap sai, vui long nhap lai!: ";
            continue;
        }
        else if (!isdigit(num[0]))
        {
            cout << "    Nhap sai, vui long nhap lai!: ";
            continue;
        }
        else
            break;
    }
    cin.ignore();

    int number_of_tickets = stoi(num);
    while (number_of_tickets > 0)
    {
        if (ticketCount > MaxSeat)
        {
            cout << "   Het cho!" << endl;
            return;
        }
        cout << endl
             << "   STT ve may bay: " << ticketCount << endl;
        string code;
        int index;
        while (true)
        {
            cout << " → Nhap ma so ve may bay: ";
            getline(cin, code);
            if (bookedStore.find(code) != bookedStore.end())
            {
                cout << "   Ma so nay da dat ghe" << endl;
                cout << "   Nhap lai!" << endl;
                continue;
            }
            index = findPassengers(code);
            if (index == -1)
            {
                cout << "   Ma so ve may bay khong ton tai" << endl;
                cout << "   Nhap lai!" << endl;
            }
            else
                break;
        }

        store.insert(code);

        string seat = selectSeat(index);
        updateSeatingChartFile();

        passengers[index].seatCode = seat;

        number_of_tickets--;
        ticketCount++;
    }
}

int findPassengers(const string &code)
{
    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].ticketCode == code)
        {
            return i;
        }
    }
    return -1;
}