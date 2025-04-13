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
#include <algorithm> 

const int MaxSeat = 166; 
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
    string seatCode;
    string classLabel; 
} ticket; 

int ticketCount = 1; 

vector<ticket> passengers;
set<string> bookedStore; 
set<string> store; 
vector<vector<string>> firstClass; 
vector<vector<string>> economyClass; 
map<string, string> seatStatus; 

void SetColor(int text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, text_color);
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
	printf("╚════════════════════════════════════════╝\n"); 
}

int findPassengers(const string& code) {
    for (int i = 0; i < passengers.size(); i++) {
        if (passengers[i].ticketCode == code) {
            return i;
        }
   }
   return -1; 
}

// ======================= Seating Chart =======================

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
    cout << "╔════════════════════╦═══════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   First Class      ║                                     Economy Class                                 ║" << endl;
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
         << "                     [--] hay [---]: Ghe dat dat                 1A: Ghe chua dat " << endl; 
}

void notify() {
    cout << endl;
    cout << " ------------------------------------" << endl;
    cout << " Lua chon khong hop le hoac ghe da dat" << endl;
    cout << " Hay chon lai!" << endl;
    cout << " ------------------------------------" << endl;
    cout << endl;
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
        cout << "   → Hay chon ghe: ";
        getline(cin, choice); 

        if (!isValidSeat(choice) && seatStatus.find(choice) != seatStatus.end()) {
            notify(); 
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
                cout << "Ghe chon khong phu hop voi First Class!" << endl; 
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
                cout << "Ghe chon khong phu hop voi Economy Class!" << endl; 
                continue; 
            }
        } 

        if (foundFirstClass == true || foundEconomyClass == true) {
            cout << "Chac chan muon chon " << choice << " (Y/N):";
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
            notify();
            continue;
        }
    }
}

void updateSeatingChartFile() {
    ofstream WriteFile("BookedSeatingChart.txt");
    if (!WriteFile) {
        cout << "Loi khi mo file BookedSeatingChart" << endl;
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
    
    cout << "Dang lay thong tin chuyen bay..." << endl; 
    Sleep(1000);
    cout << "Doc thong tin chuyen bay thanh cong!" << endl;
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
        if (!getline(ss, passenger.classLabel, ',')) {
            cout << "Loi khi doc hang ve" << endl; 
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

void importBookedTicket() { // lay thong tin ve da dat cua nhung khach hang truoc do
	ifstream inputFile("TicketInformation.txt"); 
	string line; 
	vector<string> maSoVe; 
	if (!inputFile.is_open()) {
		cout << "Khong mo duoc file!" << endl; 
		return;
	}
	while (getline(inputFile, line)) {
		int found = line.find("Ma so ve:"); 
		if (found != string::npos) {
			string code = line.substr(found + 10); 
			code.erase(0, code.find_first_not_of(" ")); 
			maSoVe.push_back(code);
		}
	}
	inputFile.close();
	
	cout << endl 
		 << "Kiem tra thong tin ve da dat..." << endl; 
	Sleep(1000); 
	cout << "Kiem tra thanh cong!" << endl; 
	Sleep(1000);
	
	for (string i : maSoVe) {
		bookedStore.insert(i); 
	}
	int bookedTicket = bookedStore.size(); 
	cout << "Tong cong: " << bookedTicket << " khach hang da dat ghe" << endl;
}

void importSeatCode() {
	importSeatingChartData(); 
    displaySeatingChart(); 
	
    cout << endl << "→ So ve may bay can dat: "; 
    
    string num; 
    while(true) {
    	cin >> num;
        if (num.length() != 1) {
            cout << "Nhap sai, vui long nhap lai!: "; 
            continue; 
        } else if (!isdigit(num[0])) {
            cout << "Nhap sai, vui long nhap lai!: "; 
            continue;
        }  
        else break; 
	}
    cin.ignore(); 
    
    int number_of_tickets = stoi(num); 
    while (number_of_tickets > 0) {
        if (ticketCount > MaxSeat) {
            cout << "Het cho!" << endl;
            return; 
        }
        cout << endl
			 << "STT ve may bay: " << ticketCount << endl;
		string code; 
		int index;  
		while (true) {
			cout << "→ Nhap ma so ve may bay: ";
			getline(cin, code); 
            if (bookedStore.find(code) != bookedStore.end()) {
                cout << "Ma so nay da dat ghe" << endl; 
                cout << "Nhap lai!" << endl; 
                continue; 
            }
	        index = findPassengers(code); 
	        if (index == -1) {
	            cout << "Ma so ve may bay khong ton tai" << endl;
	            cout << "Nhap lai!" << endl;  
	        }
	        else break;  
		}
		
    	store.insert(code); 
    	
        string seat = selectSeat(index);
        updateSeatingChartFile();

        passengers[index].seatCode = seat; 

        number_of_tickets--; 
        ticketCount++;
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
		    cout << " Email: " << passengers[index].customer.email << endl;
			cout << " So dien thoai: " << passengers[index].customer.phoneNumber << endl;
		    cout << " Chuyen bay: " << passengers[index].departure << " -> " << passengers[index].destination << endl;
		    cout << " Ngay: " << passengers[index].date << " - Gio: " << passengers[index].time << endl;
		    cout << " Ma so ghe: " << passengers[index].seatCode << endl; 
		    cout << "------------------------------------" << endl;
		}
	}
	Sleep(2000); 
}

void TicketOutput(ofstream& WriteFile, int index) {
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

void printTicket() {
	ofstream WriteFile("TicketInformation.txt", ios::app); 
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
		cout << "Tong so ve luu: " << store.size()<< endl; 
	}
	WriteFile.close(); 
}

void resetTicketInformation() {
	ofstream WriteFile("TicketInformation.txt"); 
	WriteFile.close(); 
	cout << "DU LIEU VE DA DUOC RESET" << endl; 
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
    cout << "║  0. Thoat chuong trinh                 ║" << endl; 
    cout << "╚════════════════════════════════════════╝" << endl; 
}

void initialization() {
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
             << "[ERROR] Sai ma khoi dong! Ket thuc!" << endl;
        exit(0);
    }
    cout << endl 
         << "Dang dang nhap..." << endl;
    Sleep(1000);
    cout << "Dang nhap thanh cong!" << endl;
    Sleep(1000);
}

void inputFlightCode() {
    cout << endl
         << " → Nhap ma chuyen bay: ";
    string flightCode;
    getline(cin, flightCode);
    if (flightCode != "ITF2025" && flightCode != "itf2025" && flightCode != "Itf2025") {
        cout << endl 
             << "[ERROR] Sai ma chuyen bay! Ket thuc!" << endl;
        exit(0);
    }
    importPassengersInformation(); 
    importBookedTicket(); 
}

void menu() {
    initialization(); 
    inputFlightCode(); 
    
    if (passengers.empty()) {
        cout << "Khong co thong tin hanh khach" << endl; 
        return; 
    }
    
	cout << "Dang hien thi menu..." << endl;
    Sleep(1000); 
    int choice;  
    do { 
        displayMenu();
    	while (true) {
    		cout << "→ Vui long nhap lua chon: ";
        	cin >> choice; 
    		if (cin.fail()) {
    			cin.clear(); 
    			cin.ignore(1000, '\n'); 
    			cout << "Nhap sai!" << endl; 
			} 
			else break; 
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
    Sleep(500);
}

void reset() {
	cout << "Reset so do ghe? (Y/N) ";
	string choice; getline(cin, choice); 
	if (choice[0] == 'y' || choice[0] == 'Y') {
    	resetSeatingChart(); 
    	cout << "Reset du lieu ve da dat? (Y/N) "; 
    	getline(cin, choice); 
    	if (choice[0] == 'y' || choice[0] == 'Y') {
    		resetTicketInformation(); 
		} 
	} 
}

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
    menu(); 
    end();
	reset();
    return 0; 
}