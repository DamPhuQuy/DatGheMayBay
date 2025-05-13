#include "print_menu.h"
#include "selecting_seat.h"
#include "admin.h"

using namespace std;
namespace fs = std::filesystem;

extern void Goto(int x, int y);

void flight_menu() {
	system("cls");

	cout << "----------------------------------------------------\n"; 
	cout << "|           Cac chuyen bay trong he thong          |\n";
	cout << "----------------------------------------------------\n";
	cout << "|  ITF2023                                         |\n";
	cout << "|  ITF2024                                         |\n";
	cout << "|  ITF2025                                         |\n";
	cout << "----------------------------------------------------\n"; 
}

void display_flight(const ticket &flight_info) {
    system("cls");

    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("|                                          THONG TIN CHUYEN BAY                                          |\n");
    printf("+--------------------------------------------------------------------------------------------------------+\n");
    printf("|   Ma so chuyen bay : %s                                                                           |\n", flight_info.flight_code.c_str());
    printf("|                                                                                                        |\n");
    printf("|   Noi xuat phat    : %s -> Noi den: %s                                                   |\n", flight_info.departure.c_str(), flight_info.destination.c_str());
    printf("|                                                                                                        |\n");
    printf("|   Ngay xuat phat   : %s                                                                        |\n", flight_info.date.c_str());
    printf("|                                                                                                        |\n");
    printf("|   Thoi gian        : %s                                                                           |\n", flight_info.time.c_str());
    printf("----------------------------------------------------------------------------------------------------------\n");
}

void input_flight_code(string& flight_code, vector<vector<string>>& first_class, vector<vector<string>>& economy_class, vector<ticket>& passengers) {
	while (true) { 

		flight_menu(); 

		cout << "\n"; 
		cout << "----------------------------------------------------\n";
		cout << "| Nhap ma chuyen bay:                              |\n";
		cout << "----------------------------------------------------\n"; 
		Goto(22, 9); 
		getline(cin, flight_code);

		if (flight_code.empty()) {
			cout << "   \nThong tin khong duoc de trong!\n"; 
		}
		else 
			break; 
	}

	import_passengers_info(flight_code, passengers); 
	import_booked_ticket(flight_code);
	import_seating_chart(flight_code, first_class, economy_class);
}

void output_ticket_info(ostream& os, const vector<ticket> &passengers, int index) {
    os << "Thong tin ve " << passengers[index].ticket_code << " hien tai: " << "\n";
    os << "------------------------------------" << "\n";
    os << " Ma so chuyen bay: " << passengers[index].flight_code << "\n";
    os << " Ma so ve: " << passengers[index].ticket_code << "\n";
    os << " Khach hang: " << passengers[index].customer.names << "\n";
    os << " Ngay sinh: " << passengers[index].customer.DoB << " - Gioi tinh: " << passengers[index].customer.gender << "\n";
    os << " Email: " << passengers[index].customer.email << "\n";
    os << " So dien thoai: " << passengers[index].customer.phone_number << "\n";
    os << " Chuyen bay: " << passengers[index].departure << " -> " << passengers[index].destination << "\n"; 
    os << " Ngay: " << passengers[index].date << " - Gio: " << passengers[index].time << "\n";
    os << " Ma so ghe: " << passengers[index].seat_code << " - Class: " << passengers[index].class_label << "\n";
    os << "------------------------------------" << "\n";
}

void display_info(const set<string>& store_booked_tickets_add_only, const vector<ticket>& passengers) {
	system("cls"); 

	cout << "\n";
    cout << "+--------------------------------------------------------------------------------------------------------+\n";
    cout << "|                                     THONG TIN KHACH HANG VA GHE NGOI                                   |\n";
    cout << "+--------------------------------------------------------------------------------------------------------+\n";

    for (int index = 0; index < passengers.size(); index++) {
    	if (store_booked_tickets_add_only.find(passengers[index].ticket_code) != store_booked_tickets_add_only.end()) {
    		output_ticket_info(cout, passengers, index);
    		cout << "\n"; 
    	}
    }

    cout << "   Nhan phim bat ki de tiep tuc..."; 
    getchar(); 
}

void ticket_output(ofstream& write_file, int index, const vector<ticket>& passengers) {
	if (index < passengers.size()) {
		output_ticket_info(write_file, passengers, index); 
	}
	else {
		write_file << "   Da xay ra loi!\n"; 
	}
}

void print_ticket(const string& flight_code, const vector<ticket>& passengers, const set<string>& store_booked_tickets_add_only) {
    fs::path directory = flight_code;
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        cout << "   Chuyen bay khong ton tai!" << "\n";
        return;
    }
    
	fs::path ticket_info_path = directory / TICKET_INFO;
    ofstream write_file(ticket_info_path, ios::app);
    for (int index = 0; index < passengers.size(); index++) {
        if (store_booked_tickets_add_only.find(passengers[index].ticket_code) != store_booked_tickets_add_only.end()) {
            ticket_output(write_file, index, passengers);
        }
    }

    cout << "   Dang luu thong tin..." << "\n";
    Sleep(800);
    cout << "   Thong tin da duoc luu!" << "\n";
    Sleep(800);
}

void display_menu() {
    system("cls");

    cout << "\n";
    cout << "----------------------------------------------------------------------------------------------------------" << "\n";
    cout << "|                         CHAO MUNG DEN VOI HE THONG DAT GHE MAY BAY - ITF_AIRWAY                        |" << "\n";
    cout << "+--------------------------------------------------------------------------------------------------------+" << "\n";
    cout << "|   1. Hien thi thong tin chuyen bay                                                                     |" << "\n";
    cout << "|                                                                                                        |" << "\n";
    cout << "|   2. Thong ke so luong ghe                                                                             |" << "\n";
    cout << "|                                                                                                        |" << "\n";
    cout << "|   3. Dat ghe cho khach hang                                                                            |" << "\n";
    cout << "|                                                                                                        |" << "\n";
    cout << "|   0. Thoat chuong trinh                                                                                |" << "\n";
    cout << "----------------------------------------------------------------------------------------------------------" << "\n";
}

void menu() {
	admin_Login(); 

	do {
		string flight_code; 
		vector<vector<string>> first_class; 
		vector<vector<string>> economy_class; 
		set<string> seat_status; 
		set<string> store_booked_tickets; 
		set<string> store_booked_tickets_add_only;
		vector<ticket> passengers;

		flight_code.clear(); 
		first_class.clear(); 
		economy_class.clear(); 
		seat_status.clear(); 
		store_booked_tickets.clear(); 
		store_booked_tickets_add_only.clear(); 
		passengers.clear(); 

		input_flight_code(flight_code, first_class, economy_class, passengers); 

		if (passengers.empty()) {
        	cout << "   Khong co thong tin hanh khach!" << "\n";
        	return;
   		}

	    cout << "   Dang hien thi menu..." << "\n";
	    Sleep(1500);
	    int choice;
	    do {
	        display_menu();
	        while (true) {
	            cout << " → Vui long nhap lua chon: ";
	            cin >> choice;
	            if (cin.fail()) {
	                cin.clear();
	                cin.ignore(1000, '\n');
	                cout << "   Nhap sai!" << "\n";
	            }
	            else
	                break;
	        }
	        cin.ignore();

	        switch (choice) {
	            case 0: {
	                cout << "   Ban da chon thoat chuong trinh." << "\n";
	                break;
	            }
	            case 1: {
	                if (!passengers.empty()) {
	                    display_flight(passengers[0]);
	                    cout << " Nhan phim bat ki de tiep tuc... ";
	                    getchar();
	                }
	                else {
	                    cout << "   Khong co thong tin chuyen bay de hien thi." << "\n";
	                }
	                break;
	            }
	            case 2: {
	                statistics();
	                cout << "   Nhan phim bat ki de tiep tuc...";
	                getchar();
	                break;
	            }
	            case 3: {
	                if (passengers.empty()) {
	                    cout << "   Khong co thong tin hanh khach. Khong the dat ghe." << "\n";
	                }
	                else {
	                    take_seat_code(flight_code, seat_status, store_booked_tickets, store_booked_tickets_add_only, first_class, economy_class, passengers);
	                }

	                if (passengers.empty()) {
	                    cout << "   Khong co thong tin hanh khach de hien thi." << "\n";
	                    break;
	                }
	                display_info(store_booked_tickets_add_only, passengers);
	                cout << "   Ban co muon xuat ve (Y/N): ";
	                string out;
	                getline(cin, out);
	                if (out[0] == 'Y' || out[0] == 'y') {
	                    print_ticket(flight_code, passengers, store_booked_tickets_add_only);
	                }
	                cout << "\n";
	                cout << " Nhan phim bat ki de tiep tuc... ";
	                getchar();
	                break;
	            }
	            default: {
	                cout << "   Lua chon khong hop le. Vui long nhap lai." << "\n";
	                break;
	            }
	        }
	    } while (choice != 0);

	    reset(flight_code); 

	    cout << "   Ban co muon tiep tuc nhap cac chuyen bay khac? (Y/N): ";
	    string out;
	    getline(cin, out);
	   	if (out[0] != 'Y' || out[0] != 'y') {
	   		break; 
	   	}
	} while (true);
}

void end() {
    system("cls");

    cout << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "|                                      Chao tam biet va hen gap lai                                      |" << endl;
    cout << "|                                               ITF-AIRWAYS                                              |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    Sleep(800);
}

void reset_ticket_info(const string& flight_code) {
    fs::path directory = flight_code;

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        cout << "   Chuyen bay khong ton tai!" << endl;
        return;
    }
    fs::path ticket_info_path = directory / TICKET_INFO;
    ofstream ticket_info_files(ticket_info_path);
    ticket_info_files.close();
    cout << "   DU LIEU VE DA DUOC RESET" << endl;
}

void reset(const string& flight_code) {
    cout << "   Reset so do ghe? (Y/N): ";
    string choice;
    getline(cin, choice);
    if (choice[0] == 'y' || choice[0] == 'Y') {
        reset_seating_chart(flight_code);
        cout << "   Reset du lieu ve da dat? (Y/N) ";
        getline(cin, choice);
        if (choice[0] == 'y' || choice[0] == 'Y') {
            reset_ticket_info(flight_code);
        }
    }
}