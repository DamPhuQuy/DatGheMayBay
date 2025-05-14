#include "print_menu.h"
#include "selecting_seat.h"
#include "admin.h"

using namespace std;
namespace fs = std::filesystem;

extern void Goto(int x, int y);

void flight_menu() {
	system("cls");

	cout << "\n"; 
	cout << short_space << "--------------------------------------------Nhap ma chuyen bay--------------------------------------------\n"; 

	cout << "\n"; 
	cout << long_space << "----------------------------------------------------\n"; 
	cout << long_space << "|           Cac chuyen bay trong he thong          |\n";
	cout << long_space << "----------------------------------------------------\n";
	cout << long_space << "|  ITF2023                                         |\n";
	cout << long_space << "|  ITF2024                                         |\n";
	cout << long_space << "|  ITF2025                                         |\n";
	cout << long_space << "----------------------------------------------------\n"; 
}

void display_flight(const ticket &flight_info) {
    system("cls");

    printf("\n");
    printf("       ----------------------------------------------------------------------------------------------------------\n");
    printf("       |                                          THONG TIN CHUYEN BAY                                          |\n");
    printf("       +--------------------------------------------------------------------------------------------------------+\n");
    printf("       |   Ma so chuyen bay : %s                                                                           |\n", flight_info.flight_code.c_str());
    printf("       |                                                                                                        |\n");
    printf("       |   Noi xuat phat    : %s -> Noi den: %s                                                   |\n", flight_info.departure.c_str(), flight_info.destination.c_str());
    printf("       |                                                                                                        |\n");
    printf("       |   Ngay xuat phat   : %s                                                                        |\n", flight_info.date.c_str());
    printf("       |                                                                                                        |\n");
    printf("       |   Thoi gian        : %s                                                                           |\n", flight_info.time.c_str());
    printf("       ----------------------------------------------------------------------------------------------------------\n");
}

void input_flight_code(string& flight_code, vector<vector<string>>& first_class, vector<vector<string>>& economy_class, vector<ticket>& passengers) {
	while (true) {

		flight_menu(); 

		cout << "\n"; 
		cout << long_space << "----------------------------------------------------\n";
		cout << long_space << "| Nhap ma chuyen bay:                              |\n";
		cout << long_space << "----------------------------------------------------\n"; 
		Goto(55, 12); 
		getline(cin, flight_code);

		fs::path directory = flight_code; 
		if (flight_code.empty()) {
			cout << "\n"; 
			cout << long_space << "Thong tin khong duoc de trong!\n"; 
			Sleep(800); 
		}
		else if (!fs::exists(directory) || !fs::is_directory(directory)) {
			cout << "\n"; 
			cout << long_space << "Chuyen bay khong ton tai!\n";
			Sleep(800);
		}
		else 
			break; 
	}

	import_passengers_info(flight_code, passengers); 
	import_booked_ticket(flight_code);
	import_seating_chart(flight_code, first_class, economy_class);
}

void output_ticket_info(
    std::ostream& os,
    const std::vector<ticket> &passengers,
    int index,
    bool delete_space 
) {
    string print_space = delete_space 
                         ? "" 
                         : long_space;

    os << "\n";
    os << print_space << "Thong tin ve " 
       << passengers[index].ticket_code 
       << " hien tai:\n";
    os << print_space << "------------------------------------\n";
    os << print_space << "Ma so chuyen bay: " 
       << passengers[index].flight_code << "\n";
    os << print_space << "Ma so ve: " 
       << passengers[index].ticket_code << "\n";
    os << print_space << "Khach hang: " 
       << passengers[index].customer.names << "\n";
    os << print_space << "Ngay sinh: " 
       << passengers[index].customer.DoB 
       << " - Gioi tinh: " 
       << passengers[index].customer.gender << "\n";
    os << print_space << "Email: " 
       << passengers[index].customer.email << "\n";
    os << print_space << "So dien thoai: " 
       << passengers[index].customer.phone_number << "\n";
    os << print_space << "Chuyen bay: " 
       << passengers[index].departure 
       << " -> " 
       << passengers[index].destination << "\n";
    os << print_space << "Ngay: " 
       << passengers[index].date 
       << " - Gio: " 
       << passengers[index].time << "\n";
    os << print_space << "Ma so ghe: " 
       << passengers[index].seat_code 
       << " - Class: " 
       << passengers[index].class_label << "\n";
    os << print_space << "------------------------------------\n";
}

void display_info(const set<string>& store_booked_tickets_add_only, const vector<ticket>& passengers) {
	system("cls"); 

	cout << "\n";
    cout << short_space << "----------------------------------------------------------------------------------------------------------\n";
    cout << short_space << "|                                     THONG TIN KHACH HANG VA GHE NGOI                                   |\n";
    cout << short_space << "----------------------------------------------------------------------------------------------------------\n";
       
    for (int index = 0; index < passengers.size(); index++) {
    	if (store_booked_tickets_add_only.find(passengers[index].ticket_code) != store_booked_tickets_add_only.end()) {
    		output_ticket_info(cout, passengers, index);
    		cout << "\n"; 
    	}
    }
}

void ticket_output(ofstream& write_file, int index, const vector<ticket>& passengers) {
	if (index < passengers.size()) {
		output_ticket_info(write_file, passengers, index, true); 
	}
	else {
		write_file << long_space << "Da xay ra loi!\n"; 
	}
}

void print_ticket(const string& flight_code, const vector<ticket>& passengers, const set<string>& store_booked_tickets_add_only) {
    fs::path directory = flight_code;
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        cout << long_space << "Chuyen bay khong ton tai!" << "\n";
        return;
    }
    
	fs::path ticket_info_path = directory / TICKET_INFO;
    ofstream write_file(ticket_info_path, ios::app);
    for (int index = 0; index < passengers.size(); index++) {
        if (store_booked_tickets_add_only.find(passengers[index].ticket_code) != store_booked_tickets_add_only.end()) {
            ticket_output(write_file, index, passengers);
        }
    }

    cout << long_space << "Dang luu thong tin..." << "\n";
    Sleep(800);
    cout << long_space << "Thong tin da duoc luu!" << "\n";
    Sleep(800);
}

void display_menu() {
    system("cls");

    cout << "\n";
    cout << short_space << "----------------------------------------------------------------------------------------------------------" << "\n";
    cout << short_space << "|                         CHAO MUNG DEN VOI HE THONG DAT GHE MAY BAY - ITF_AIRWAY                        |" << "\n";
    cout << short_space << "+--------------------------------------------------------------------------------------------------------+" << "\n";
    cout << short_space << "|   1. Hien thi thong tin chuyen bay                                                                     |" << "\n";
    cout << short_space << "|                                                                                                        |" << "\n";
    cout << short_space << "|   2. Thong ke so luong ghe                                                                             |" << "\n";
    cout << short_space << "|                                                                                                        |" << "\n";
    cout << short_space << "|   3. Dat ghe cho khach hang                                                                            |" << "\n";
    cout << short_space << "|                                                                                                        |" << "\n";
    cout << short_space << "|   0. Thoat chuong trinh                                                                                |" << "\n";
    cout << short_space << "----------------------------------------------------------------------------------------------------------" << "\n";
}

void menu() {
	string username; 
	admin_Login(username); 

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
        	cout << long_space << "Khong co thong tin hanh khach!" << "\n";
        	return;
   		}

	    cout << long_space << "Dang hien thi menu..." << "\n";
	    Sleep(1500);

	    int choice;
	    do {
	        display_menu();
	        while (true) {
	            cout << long_space << "Vui long nhap lua chon: ";
	            cin >> choice;
	            if (cin.fail()) {
	                cin.clear();
	                cin.ignore(1000, '\n');
	                cout << long_space << "Nhap sai!" << "\n";
	            }
	            else
	                break;
	        }
	        cin.ignore();

	        switch (choice) {
	            case 0: {
	                cout << long_space << "Ban da chon thoat chuong trinh." << "\n";
	                break;
	            }
	            case 1: {
	                if (!passengers.empty()) {
	                    display_flight(passengers[0]);
	                    cout << long_space << "Nhan phim bat ki de tiep tuc... ";
	                    _getch(); 
	                }
	                else {
	                    cout << long_space << "Khong co thong tin chuyen bay de hien thi." << "\n";
	                }
	                break;
	            }
	            case 2: {
	                statistics();
	                cout << long_space << "Nhan phim bat ki de tiep tuc...";
	                _getch();
	                break;
	            }
	            case 3: {
	                take_seat_code(flight_code, seat_status, store_booked_tickets, store_booked_tickets_add_only, first_class, economy_class, passengers);

	                // xuat ve 
	                display_info(store_booked_tickets_add_only, passengers);

	                cout << long_space << "Ban co muon xuat ve (Y/N): ";
	                string check;
	                getline(cin, check); 
	                if (!check.empty() && (check[0] == 'Y' || check[0] == 'y')) {
	                    print_ticket(flight_code, passengers, store_booked_tickets_add_only);
	                }
	                else {
	                	// xoa cac phan tu da them vao trong store_booked_tickets cua cac phan tu add_only
	                	// dat lai ghe neu khong dong y xuat ve
	                	for (const auto& code : store_booked_tickets_add_only) {
	                		store_booked_tickets.erase(code); 
	                	}
	                }

	                store_booked_tickets_add_only.clear(); // xoa het phan tu, de display lai cac phan tu moi 

	                cout << "\n";
	                cout << long_space << "Nhan phim bat ki de tiep tuc... ";
	                _getch();
	                break;
	            }
	            default: {
	                cout << long_space << "Lua chon khong hop le. Vui long nhap lai." << "\n";
	                break;
	            }
	        }
	    } while (choice != 0);

	    reset(flight_code); 

	    cout << "\n"; 
	    cout << long_space << "Ban co muon tiep tuc nhap cac chuyen bay khac? (Y/N): ";
	    string out; 
	    getline(cin, out); 
	    if (!out.empty() && (out[0] == 'y' || out[0] == 'Y')) 
	    	continue; 
	    else {
	    	if (admin_Logout(username)) 
	    		break; 
	    	else 
	    		continue; 
	    }
	} while(true);
}

void end() {
    system("cls");

    cout << "\n";
    cout << short_space << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << short_space << "|                                      Chao tam biet va hen gap lai                                      |" << endl;
    cout << short_space << "|                                               ITF-AIRWAYS                                              |" << endl;
    cout << short_space << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n";
    Sleep(800);
}

void reset_ticket_info(const string& flight_code) {
    fs::path directory = flight_code;

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        cout << long_space << "Chuyen bay khong ton tai!" << endl;
        return;
    }
    fs::path ticket_info_path = directory / TICKET_INFO;
    ofstream ticket_info_files(ticket_info_path);
    ticket_info_files.close();
    cout << long_space << "DU LIEU VE DA DUOC RESET" << endl;
}

void reset(const string& flight_code) {
    cout << long_space << "Reset so do ghe? (Y/N): ";
    string choice;
    getline(cin, choice);
    if (choice[0] == 'y' || choice[0] == 'Y') {
        reset_seating_chart(flight_code);
        cout << long_space << "Reset du lieu ve da dat? (Y/N) ";
        getline(cin, choice);
        if (choice[0] == 'y' || choice[0] == 'Y') {
            reset_ticket_info(flight_code);
        }
    }
}