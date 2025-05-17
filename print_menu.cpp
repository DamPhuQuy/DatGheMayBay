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

    int nums_space = 82;

    cout << "\n"; 
    cout << short_space << "----------------------------------------------------------------------------------------------------------\n";
	cout << short_space << "|                                          THONG TIN CHUYEN BAY                                          |\n";
	cout << short_space << "+--------------------------------------------------------------------------------------------------------+\n";
	cout << short_space << "|   Ma so chuyen bay : " << setw(nums_space) << left << flight_info.flight_code << "|\n"; 
	cout << short_space << "|                                                                                                        |\n";
	cout << short_space << "|   Noi xuat phat    : " << setw(nums_space) << left << flight_info.departure << "|\n"; 
	cout << short_space << "|                                                                                                        |\n";
	cout << short_space << "|   Noi den          : " << setw(nums_space) << left << flight_info.destination << "|\n"; 
	cout << short_space << "|                                                                                                        |\n";
	cout << short_space << "|   Ngay xuat phat   : " << setw(nums_space) << left << flight_info.date << "|\n"; 
	cout << short_space << "|                                                                                                        |\n";
	cout << short_space << "|   Thoi gian        : " << setw(nums_space) << left << flight_info.time << "|\n"; 
	cout << short_space << "----------------------------------------------------------------------------------------------------------\n";
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
	ostream &os,
	const vector<ticket> &passengers,
	int index,
	bool delete_space)
{
	string print_space = delete_space
							 ? ""
							 : long_space;

	int nums_space = 24;

	os << "\n";
	os << print_space << "----------------------------------------------------\n";
	os << print_space << "|              THONG TIN VE " << passengers[index].ticket_code << setw(18) << right << "|" << "\n";
	os << print_space << "+--------------------------------------------------+\n";

	os << print_space << "|  Ma so chuyen bay      : " << setw(nums_space) << left << passengers[index].flight_code << "|\n";
	os << print_space << "|  Ma so ve              : " << setw(nums_space) << left << passengers[index].ticket_code << "|\n";
	os << print_space << "|  Khach hang            : " << setw(nums_space) << left << passengers[index].customer.names << "|\n";

	string dob_gender = passengers[index].customer.DoB + " - " + passengers[index].customer.gender;
	os << print_space << "|  Ngay sinh - Gioi tinh : " << setw(nums_space) << left << dob_gender << "|\n";

	os << print_space << "|  Email                 : " << setw(nums_space) << left << passengers[index].customer.email << "|\n";
	os << print_space << "|  So dien thoai         : " << setw(nums_space) << left << passengers[index].customer.phone_number << "|\n";

	string route = passengers[index].departure + " -> " + passengers[index].destination;
	os << print_space << "|  Chuyen bay            : " << setw(nums_space) << left << route << "|\n";

	string datetime = passengers[index].date + " - " + passengers[index].time;
	os << print_space << "|  Ngay - Gio            : " << setw(nums_space) << left << datetime << "|\n";

	os << print_space << "|  Ma so ghe             : " << setw(nums_space) << left << passengers[index].seat_code << "|\n";
	os << print_space << "|  Class                 : " << setw(nums_space) << left << passengers[index].class_label	<< "|\n"; 
	os << print_space << "----------------------------------------------------\n";
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


	                string check;

	                while (true) {
	                	cout << long_space << "Ban co muon xuat ve (Y/N): ";
	                	getline(cin, check); 
	                	if (check.empty()) {
	                		cout << long_space << "Khong duoc de trong.\n"; 
	                		continue; 
	                	}

	                	const char first = check[0]; 

	                	if (first == 'Y' || first == 'y') {
	                		print_ticket(flight_code, passengers, store_booked_tickets_add_only); 
	                		break; 
	                	}
	                	else {
	                		// xoa phan tu da them vao truoc do neu huy xuat ve
	                		// de tiep tuc dat ve khac
	                		for (const string& code : store_booked_tickets_add_only) {
	                			store_booked_tickets.erase(code); 
	                		}
	                		break; 
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
	    
	    while (true) {
		    getline(cin, out); 
		    if (out.empty()) {
		    	cout << long_space << "Khong duoc de trong.\n"; 
		    	continue; 
		    }
		    else 
		    	break; 
	    }

	    const char first = out[0]; 
		if (first == 'Y' || first == 'y')  
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
    string choice;
    
    while (true) {
    	cout << long_space << "Reset so do ghe? (Y/N): ";
    	getline(cin, choice);
    	if (choice.empty()) {
    		cout << long_space << "Khong duoc de trong.\n";
    		continue;
    	}
    	else 
    		break; 
    }

    if (choice[0] == 'y' || choice[0] == 'Y') {
        reset_seating_chart(flight_code);
        while (true) {
        	choice.clear(); 
        	cout << long_space << "Reset du lieu ve da dat? (Y/N) ";
        	getline(cin, choice);
        	if (choice.empty()) {
        		cout << long_space << "Khong duoc de trong.\n"; 
        		continue; 
        	}
        	else 
        		break;
        }
        if (choice[0] == 'y' || choice[0] == 'Y') {
            reset_ticket_info(flight_code);
        }
    }
}