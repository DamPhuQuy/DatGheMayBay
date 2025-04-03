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
#include <conio.h> 
#include <cstdlib> 

const int MaxSeat = 180; 
using namespace std;

//======================= Data types =======================

typedef struct person {
    string names;
    string DoB;
    string email;
    string phoneNumber;
    string gender;
} person;

typedef struct ticket {
    person customer;
    string flightCode;
    string ticketCode;
    string departure;
    string destination;
    string time;
    string date;
    int price;
    string seatCode;
} ticket; 

int originalPrice = 0; 
int ticketCount = 1;

vector<ticket> passengers;
set<string> store; 
vector<vector<string>> takenSeatingChart;

void SetColor(int text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, text_color);
}

double ticketPrice(const string& choice) {
    string temp = choice.substr(1, 2);
    int number = stoi(temp);
    if (number >= 1 && number <= 10) {
        return originalPrice * 3;
    }
    else if (number >= 11 && number <= 20) {
        return originalPrice * 1.5;
    }
    else {
        return originalPrice;
    }
}

void displayFlight(const ticket& flightList) {
	printf("\n"); 
	printf("╔════════════════════════════════════════╗\n"); 
	printf("║          THONG TIN CHUYEN BAY          ║\n"); 
	printf("╠════════════════════════════════════════╣\n"); 
	printf("║ Ma so chuyen bay: %s              ║\n", flightList.flightCode.c_str()); 
	printf("║ Noi xuat phat: %s                 ║\n", flightList.departure.c_str()); 
	printf("║ Noi den: %s                   ║\n", flightList.destination.c_str()); 
	printf("║ Ngay xuat phat: %s             ║\n", flightList.date.c_str()); 
	printf("║ Thoi gian: %s                     ║\n", flightList.time.c_str()); 
	printf("║ Gia ve: %d                        ║\n", flightList.price); 
	printf("╚════════════════════════════════════════╝\n"); 
}

// ======================= Seating Chart =======================

void importSeatingChartData() {
    if (!takenSeatingChart.empty()) {
        return;
    }
    ifstream inputFile("BookedSeatingChart.txt");
    if (!inputFile) {
        inputFile.open("SeatingChart.txt");
        if (!inputFile) {
            cout << "Da xay ra loi khi mo file seating chart!";
            return;
        }
    }
    string temp;
    while (getline(inputFile, temp)) {
        stringstream ss(temp);
        string token;
        vector<string> row;
        while (ss >> token) {
            row.push_back(token);
        }
        takenSeatingChart.push_back(row);
    }
    inputFile.close();
}

void displaySeatingChart() {
    cout << endl
         << "   === SO DO GHE NGOI MAY BAY ===" << endl;
    cout << "════════════════════════════════════" << endl;
    for (int i = 0; i < takenSeatingChart.size(); i++) {
        cout << "       ";
        for (int j = 0; j < takenSeatingChart[i].size(); j++) {
            cout << takenSeatingChart[i][j] << " ";
        }
        cout << endl;
    }
    cout << "════════════════════════════════════" << endl;
}

void notify() {
    cout << endl;
    cout << " ------------------------------------" << endl;
    cout << "       LUA CHON KHONG HOP LE HOAC GHE DA BI DAT!" << endl;
    cout << "       Hay chon lai!" << endl;
    cout << " ------------------------------------" << endl;
    cout << endl;
}

string selectSeat(map<string, string> &check) {
    string choice;
    while (true) {
        cout << "  Vi tri ghe se co gia ve khac nhau" << endl;
        cout << "  Tu 01 -> 10: Gia ve goc * 300%" << endl;
        cout << "  Tu 11 -> 20: Gia ve goc * 150%" << endl;
        cout << "  Tu 21 -> 30: Gia ve goc * 100%" << endl;
        cout << "       → Hay chon ghe: ";
        getline(cin, choice);
        
        if (choice.length() < 2 || choice.length() > 3) {
            notify(); 
            continue;
        }
        if (choice[0] < 'A' || choice[0] > 'Z' || choice[1] < '0' || choice[1] > '9') {
            notify(); 
            continue;
        }
        if (check.find(choice) != check.end()) {
            notify();
            continue;
        }

        bool found = false;
        for (int i = 0; i < takenSeatingChart.size(); i++) {
            for (int j = 0; j < takenSeatingChart[i].size(); j++) {
                if (takenSeatingChart[i][j] == choice) {
                    found = true;
                    takenSeatingChart[i][j] = "X";
                    break;
                }
            }
            if (found)
                break;
        }

        if (found) {
            cout << "Chac chan muon chon ghe nay: (Y/N) ";
            string okay;
            getline(cin, okay);
            if (okay[0] == 'Y' || okay[0] == 'y') {
                check.insert({choice, "X"});
                return choice;
            }
            else {
                check.erase(choice);
                continue;
            }
        } 
        else {
            notify();
            continue;
        }
    }
}

void updateSeatingChartFile() {
    ofstream WriteFile("BookedSeatingChart.txt");
    if (!WriteFile) {
        cout << "Loi khi mo file BookedSeatingChart de cap nhat so do ghe!" << endl;
        return;
    }
    for (int i = 0; i < takenSeatingChart.size(); i++) {
        for (int j = 0; j < takenSeatingChart[i].size(); j++) {
            WriteFile << takenSeatingChart[i][j] << " ";
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
    cout << "SO DO GHE DA DUOC RESET" << endl;
}

// ======================= Import =======================

bool openInputFiles(ifstream& inputFile1, ifstream& inputFile2) {
    inputFile1.open("PersonalInformation.txt");
    if (!inputFile1.is_open()) {
        cout << "Khong mo duoc file PersonalInformation.txt" << endl;
        return false;
    }
    inputFile2.open("FlightInformation.txt");
    if (!inputFile2.is_open()) {
        cout << "Khong mo duoc file FlightInformation.txt" << endl;
        inputFile1.close();
        return false;
    }
    return true;
}

bool readFlightInformation(ifstream& inputFile2, ticket& data) {
    cout << endl << "Doc thong tin chuyen bay..." << endl;
    Sleep(1000);
    
    if (!getline(inputFile2, data.flightCode)) {
        cout << "Loi khi doc ma chuyen bay" << endl;
        return false;
    }

    if (!getline(inputFile2, data.departure)) {
        cout << "Loi khi doc noi di" << endl;
        return false;
    }

    if (!getline(inputFile2, data.destination)) {
        cout << "Loi khi doc noi den" << endl;
        return false;
    }

    if (!getline(inputFile2, data.date)) {
        cout << "Loi khi doc ngay" << endl;
        return false;
    }

    if (!getline(inputFile2, data.time)) {
        cout << "Loi khi doc gio" << endl;
        return false;
    }

    if (!(inputFile2 >> data.price)) {
        cout << "Loi khi doc gia ve" << endl;
        return false;
    }
    
    originalPrice = data.price;
    
    cout << "Dang lay thong tin chuyen bay..." << endl; 
    Sleep(1000);
    cout << "Doc thong tin chuyen bay thanh cong!" << endl;
    Sleep(1000);
    cout << "Gia ve goc: " << originalPrice << "vnd" << endl;
    Sleep(1000);
    
    return true;
}

void readPassengerInformation(ifstream& inputFile1, const ticket& flightData) {
    cout << endl << "Doc thong tin hanh khach..." << endl;
    Sleep(1000);
    
    string line;
    while (getline(inputFile1, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        ticket passenger;
        
        passenger.flightCode = flightData.flightCode;
        passenger.departure = flightData.departure;
        passenger.destination = flightData.destination;
        passenger.date = flightData.date;
        passenger.time = flightData.time;
        passenger.price = flightData.price;
        passenger.seatCode = "Chua dat ghe";

        if (!getline(ss, passenger.customer.names, ',')) {
            cout << "Loi khi doc ten hanh khach" << endl;
            continue;
        }
        if (!getline(ss, passenger.customer.DoB, ',')) {
            cout << "Loi khi doc ngay sinh" << endl;
            continue;
        }
        if (!getline(ss, passenger.customer.email, ',')) {
            cout << "Loi khi doc email" << endl;
            continue;
        }
        if (!getline(ss, passenger.customer.phoneNumber, ',')) {
            cout << "Loi khi doc so dien thoai" << endl;
            continue;
        }
        if (!getline(ss, passenger.customer.gender, ',')) {
            cout << "Loi khi doc gioi tinh" << endl;
            continue;
        }
        if (!getline(ss, passenger.ticketCode, ',')) {
            cout << "Loi khi doc ma ve" << endl;
            continue;
        }
        
        passengers.push_back(passenger);
    }

    cout << "Dang lay thong tin khach hang..." << endl; 
    Sleep(1000);
    cout << "Doc thong tin hanh khach thanh cong!" << endl;
    Sleep(1000);
    
    cout << "Co tat ca " << passengers.size() << " hanh khach trong he thong" << endl;
    cout << "Ket thuc doc thong tin..." << endl; 
    Sleep(1000);
}

void importPassengersInformation() {
    ifstream inputFile1, inputFile2;
    if (!openInputFiles(inputFile1, inputFile2)) {
        return;
    }
    ticket flightData;
    if (!readFlightInformation(inputFile2, flightData)) {
        inputFile1.close();
        inputFile2.close();
        return;
    }
    readPassengerInformation(inputFile1, flightData);
    inputFile1.close();
    inputFile2.close();
}

int findPassengers(const string& code) {
    for (int i = 0; i < passengers.size(); i++) {
        if (passengers[i].ticketCode == code) {
            return i;
        }
   }
   return -1; 
}

void importSeatCode() {
    cout << endl << "→ So ve may bay can dat: "; 
    int number_of_tickets; cin >> number_of_tickets; 
    cin.ignore(); 
    int count = 1; 
    while (number_of_tickets > 0) {
        if (count > MaxSeat) {
            cout << "Het cho!" << endl;
            return; 
        }
        cout << "STT ve may bay: " << count << endl;
        cout << "→ Nhap ma so ve may bay: ";
        string code; getline(cin, code);
        int index = findPassengers(code); 
        if (index == -1) {
            cout << "Ma so ve may bay khong ton tai" << endl;
            return; 
        }
    	store.insert(code); 
        
        importSeatingChartData(); 
        displaySeatingChart(); 

        map<string, string> check; 
        string seat = selectSeat(check);
        updateSeatingChartFile();

        passengers[index].price = ticketPrice(seat); 
        passengers[index].seatCode = seat; 

        number_of_tickets--; 
        count++;
    }
}

void displayInformation() {
    cout << endl
         << "THONG TIN KHACH HANG VA GHE NGOI:" << endl;
	cout << "═══════════════════════════════════════════" << endl;
    for (int index = 0; index<passengers.size(); index++) {
    	if (store.find(passengers[index].ticketCode) != store.end()) {
		    cout << endl
		         << "Thong tin ve " << passengers[index].ticketCode << " hien tai: " << endl;
		    cout << "------------------------------------" << endl;
		    cout << " Ma so chuyen bay: " << passengers[index].flightCode << endl; 
		    cout << " Ma so ve: " << passengers[index].ticketCode << endl; 
		    cout << " Khach hang: " << passengers[index].customer.names << endl; 
            cout << " Ngay sinh: " << passengers[index].customer.DoB << " - Gioi tinh: " << passengers[index].customer.gender << endl;
		    cout << " Email: " << passengers[index].customer.email << " - So dien thoai: " << passengers[index].customer.phoneNumber << endl;
		    cout << " Chuyen bay: " << passengers[index].departure << " -> " << passengers[index].destination << endl;
		    cout << " Ngay: " << passengers[index].date << " - Gio: " << passengers[index].time << endl;
		    cout << " Gia ve: " << passengers[index].price << " - Ma ghe: " << passengers[index].seatCode << endl; 
		    cout << "------------------------------------" << endl;
		}
	}
}

void TicketOutput(ofstream& WriteFile, int index) {
	WriteFile << endl; 
	WriteFile << "Thong tin ve " << passengers[index].ticketCode << " hien tai: " << endl;
	WriteFile << "------------------------------------" << endl;
	WriteFile << " Ma so chuyen bay: " << passengers[index].flightCode << endl; 
	WriteFile << " Ma so ve: " << passengers[index].ticketCode << endl; 
	WriteFile << " Khach hang: " << passengers[index].customer.names << endl; 
    WriteFile << " Ngay sinh: " << passengers[index].customer.DoB << " - Gioi tinh: " << passengers[index].customer.gender << endl;
	WriteFile << " Email: " << passengers[index].customer.email << " - So dien thoai: " << passengers[index].customer.phoneNumber << endl;
	WriteFile << " Chuyen bay: " << passengers[index].departure << " -> " << passengers[index].destination;
	WriteFile << " Ngay: " << passengers[index].date << " - Gio: " << passengers[index].time << endl;
	WriteFile << " Gia ve: " << passengers[index].price << " - Ma ghe: " << passengers[index].seatCode << endl; 
	WriteFile << "------------------------------------" << endl;
	WriteFile << endl; 
}

void printTicket() {
	ofstream WriteFile("TicketInformation.txt"); 
	cout << "Ban muon xuat mot hay toan bo ve da dat: "; 
	string choice; getline(cin, choice); 
	if (choice == "mot" || choice == "Mot") {
		cout << "→ Nhap vao ma so ve: "; 
		string code; getline(cin, code); 
		int index = findPassengers(code); 
		TicketOutput(WriteFile, index); 
		cout << "Dang luu thong tin..." << endl; 
		Sleep(1000); 
		cout << "Thong tin da duoc luu!" << endl;
		Sleep(1000); 
	} else {
		for (int index = 0; index<passengers.size(); index++) {
			if (store.find(passengers[index].ticketCode) != store.end()) { 
				TicketOutput(WriteFile, index); 
			}
		}
		cout << "Dang luu thong tin..." << endl; 
		Sleep(1000); 
		cout << "Thong tin da duoc luu!" << endl;
		Sleep(1000); 
		cout << "Tong so ve luu: " << store.size() << endl; 
	}
	WriteFile.close(); 
}

// ======================= Menu =======================

void displayMenu() {
    cout << endl
		 << "╔════════════════════════════════════════╗" << endl; 
    cout << "║  CHAO MUNG DEN VOI HE THONG DAT GHE    ║" << endl; 
    cout << "║              ITF_AIRWAY                ║" << endl; 
    cout << "╠════════════════════════════════════════╣" << endl; 
    cout << "║  1. Hien thi thong tin chuyen bay      ║" << endl; 
    cout << "║  2. Dat ghe cho khach hang             ║" << endl; 
    cout << "║  3. Hien thi thong tin va Xuat ve      ║" << endl; 
    cout << "║  0. Thoat chuong trinh                 ║" << endl; 
    cout << "╚════════════════════════════════════════╝" << endl; 
    cout << "→ Vui long nhap lua chon: ";
}

void check() {
    cout << endl 
		 << "╔════════════════════════════════════════╗" << endl;
    cout << "║           DANG NHAP HE THONG           ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;

    cout << endl 
		 << " → Nhap ma de bat dau: ";
    string openCode;
    getline(cin, openCode);
    if (openCode != "Open" && openCode != "open" && openCode != "OPEN") {
        cout << endl
             << "[ERROR] Sai ma khoi dong! Khong the tiep tuc" << endl;
        exit(0);
    }
    cout << " → Nhap ma chuyen bay: ";
    string flightCode;
    getline(cin, flightCode);
    if (flightCode != "ITF2025" && flightCode != "itf2025" && flightCode != "Itf2025") {
        cout << endl 
			 << "Sai ma chuyen bay! Khong the tiep tuc" << endl;
        exit(0);
    }
    cout << endl 
		 << "Dang dang nhap..." << endl;
    Sleep(1000);
    cout << "Dang nhap thanh cong!" << endl;
    Sleep(1000);
}

void menu() {
	check();     

    importPassengersInformation(); 
    if (passengers.empty()) {
        cout << "Khong co thong tin hanh khach" << endl; 
        return; 
    }
    
	cout << "Dang hien thi menu..." << endl;
    Sleep(1000); 
    int choice;  
    do { 
        displayMenu();

        cin >> choice; 
        if (!choice) {
            cout << "Nhap khong hop le" << endl;
            cout << "Thoat chuong trinh..." << endl;
            exit(0);
        }
        cin.ignore(); 

        switch(choice) {
            case 0: {
                cout << "Ban da chon thoat chuong trinh." << endl;
                break;
            }
            case 1: {
                if (!passengers.empty()) {
                    displayFlight(passengers[0]);
                    cout << "Nhan phim bat ki de tiep tuc..." << endl; 
                    getchar(); 
                } else {
                    cout << "Khong co thong tin chuyen bay de hien thi." << endl;
                }
                break; 
            }
            case 2: {
                if (passengers.empty()) {
                    cout << "Khong co thong tin hanh khach. Khong the dat ghe." << endl;
                } else {
                    importSeatCode(); 
                }
                break; 
            }
            case 3: {
                if (passengers.empty()) {
                    cout << "Khong co thong tin hanh khach de hien thi." << endl;
                    break;
                }
                displayInformation(); 
				
				cout << "Ban co muon xuat ve: (Y/N) ";  
				string out; getline(cin, out); 
				if (out[0] == 'Y' || out[0] == 'y') {
					printTicket(); 
				}
				cout << "Nhan phim bat ki de tiep tuc..." << endl; 
				getchar(); 
                break;
            }
            default: {
                cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                break;
            }
        }
    } while (choice != 0); 
}

void end() {
    cout << endl;
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║   Cam on quy khach da su dung dich vu    ║" << endl;
    cout << "║               ITF-AIRWAYS                ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;
}

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
    menu(); 
    end(); 
    resetSeatingChart(); 
    return 0; 
}