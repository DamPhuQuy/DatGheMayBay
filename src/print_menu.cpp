#include "print_menu.h"

using namespace std;
namespace fs = std::filesystem;

void menu() {
    string username;
    admin_Login(username);

    string input_flight;
    vector<string> flights;
    vector<vector<string>> first_class;
    vector<vector<string>> economy_class;
    set<string> seat_status;
    set<string> store_booked_tickets;
    set<string> booked_tickets_tracking;
    vector<ticket> passengers;

    do {
        initialize_new_data(input_flight, flights, first_class, economy_class,
                               seat_status, store_booked_tickets, booked_tickets_tracking, passengers);

        input_flight_code(input_flight, first_class, economy_class, passengers, flights, store_booked_tickets, seat_status);

        if (passengers.empty()) {
            print_color_long_space("Khong co thong tin hanh khach!\n", 12);
            return;
        }

        print_color_long_space("Dang hien thi menu...\n", 15);
        Sleep(2000);

        handle_menu_loop(input_flight, first_class, economy_class,
                         seat_status, store_booked_tickets,
                         booked_tickets_tracking, passengers);

        reset(input_flight);

    } while (ask_to_continue_and_logout(username));
}

void initialize_new_data(string &flight_code,
                            vector<string> &flights,
                            vector<vector<string>> &first_class,
                            vector<vector<string>> &economy_class,
                            set<string> &seat_status,
                            set<string> &store_booked_tickets,
                            set<string> &booked_tickets_tracking,
                            vector<ticket> &passengers) {
    flight_code.clear();
    first_class.clear();
    economy_class.clear();
    seat_status.clear();
    store_booked_tickets.clear();
    booked_tickets_tracking.clear();
    passengers.clear();

    import_flights(flights);
}

void input_flight_code(string& flight_code, 
                       vector<vector<string>>& first_class, 
                       vector<vector<string>>& economy_class, 
                       vector<ticket>& passengers,
                       vector<string>& flights,
                       set<string>& store_booked_tickets,
                       set<string>& seat_status) {
    while (true) {

        flight_menu(flights); 

        cout << "\n"; 
        cout << LONG_SPACE << "----------------------------------------------------\n";
        cout << LONG_SPACE << "| Nhap ma chuyen bay:                              |\n";
        cout << LONG_SPACE << "----------------------------------------------------\n"; 
        Goto(55, 9 + flights.size()); 
        getline(cin, flight_code);

        fs::path directory = fs::path("data") / flight_code;  
        if (flight_code.empty()) {
            cout << "\n"; 
            print_color_long_space("Thong tin khong duoc de trong!\n", 12); 
            Sleep(800); 
        }
        else if (!fs::exists(directory) || !fs::is_directory(directory)) {
            cout << "\n"; 
            print_color_long_space("Chuyen bay khong ton tai!\n", 12);
            Sleep(800);
        }
        else 
            break; 
    }
    
    import(flight_code, first_class, economy_class, seat_status, store_booked_tickets, passengers);
}

void flight_menu(const vector<string>& flights) {
    system("cls");

    cout << "\n"; 
    print_color_short_space("--------------------------------------------Nhap ma chuyen bay--------------------------------------------\n", 15); 

    int nums_space = 47; 

    cout << "\n"; 
    cout << LONG_SPACE << "----------------------------------------------------\n"; 
    cout << LONG_SPACE << "|           Cac chuyen bay trong he thong          |\n";
    cout << LONG_SPACE << "----------------------------------------------------\n";
    for (const string& s : flights) {
        cout << LONG_SPACE << "|   " << setw(nums_space) << left << s << "|\n"; 
    }
    cout << LONG_SPACE << "----------------------------------------------------\n";
}

void import(const string& flight_code,
                    vector<vector<string>>& first_class,
                    vector<vector<string>>& economy_class,
                    set<string>& seat_status,
                    set<string>& store_booked_tickets,
                    vector<ticket>& passengers) {
    import_passengers_info(flight_code, passengers); 
    import_booked_ticket(flight_code, store_booked_tickets, seat_status);
    import_seating_chart(flight_code, first_class, economy_class);
}

void handle_menu_loop(const string &flight_code,
                      vector<vector<string>> &first_class,
                      vector<vector<string>> &economy_class,
                      set<string> &seat_status,
                      set<string> &store_booked_tickets,
                      set<string> &booked_tickets_tracking,
                      vector<ticket> &passengers) {
    int choice;
    do {
        display_menu();
        while (true) {
            print_color_long_space("Vui long nhap lua chon: ", 14);
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                print_color_long_space("Nhap sai!\n", 12);
            } 
            else if (choice < 0 || choice > 3) {
                print_color_long_space("Lua chon khong hop le. Vui long nhap lai.\n", 12);
                continue;
            }
            else {
                break;
            }
        }
        cin.ignore();

        switch (choice) {
            case 0: {
                print_color_long_space("Ban da chon thoat chuong trinh.\n", 10);
                break;
            }
            case 1: {
                if (!passengers.empty()) {
                    display_flight(passengers[0]);
                    print_color_long_space("Nhan phim bat ki de tiep tuc... ", 15); 
                    _getch();
                } else {
                    print_color_long_space("Khong co thong tin chuyen bay de hien thi.\n", 12);
                }
                break;
            }
            case 2: {
                statistics();
                print_color_long_space("Nhan phim bat ki de tiep tuc... ", 15);
                _getch();
                break;
            }
            case 3: {
                vector<vector<string>> temp_first_class = first_class; 
                vector<vector<string>> temp_economy_class = economy_class; 
                set<string> temp_seat_status = seat_status; 

                bool exit = take_seat_code(flight_code, seat_status, store_booked_tickets, booked_tickets_tracking, first_class, economy_class, passengers);

                if (exit) {
                    print_color_long_space("Ban da chon thoat dat ghe.\n", 10);
                    print_color_long_space("Nhan phim bat ki de tiep tuc... ", 15);
                    _getch();
                    break;
                }
                else {
                    display_info(booked_tickets_tracking, passengers);
                    string check;
                    while (true) {
                        print_color_long_space("Ban co muon xuat ve (Y/N): ", 14); 
                        getline(cin, check);
                        if (check.empty()) {
                            print_color_long_space("Khong duoc de trong.\n", 12);
                            continue;
                        }
                        const char first = check[0];
                        if (first == 'Y' || first == 'y') {
                            print_ticket(flight_code, passengers, booked_tickets_tracking);
                            break;
                        }
                        else {
                            for (const string &code : booked_tickets_tracking) {
                                store_booked_tickets.erase(code);
                            }

                            first_class = temp_first_class; 
                            economy_class = temp_economy_class;
                            seat_status = temp_seat_status;

                            break;
                        }
                    }
                    booked_tickets_tracking.clear();
                    cout << "\n";
                    print_color_long_space("Nhan phim bat ki de tiep tuc... ", 15);
                    _getch();
                }
                break;
            }
            default: {
                print_color_long_space("Lua chon khong hop le. Vui long nhap lai.\n", 12);
                break;
            }
        }
    } while (choice != 0);
}

void display_menu() {
    system("cls");

    cout << "\n";
    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
    print_color_short_space("|                         CHAO MUNG DEN VOI HE THONG DAT GHE MAY BAY - ITF_AIRWAY                        |\n", 15);
    cout << SHORT_SPACE << "+--------------------------------------------------------------------------------------------------------+\n";
    cout << SHORT_SPACE << "|   1. Hien thi thong tin chuyen bay                                                                     |\n";
    cout << SHORT_SPACE << "|                                                                                                        |\n";
    cout << SHORT_SPACE << "|   2. Thong ke so luong ghe                                                                             |\n";
    cout << SHORT_SPACE << "|                                                                                                        |\n";
    cout << SHORT_SPACE << "|   3. Dat ghe cho khach hang                                                                            |\n";
    cout << SHORT_SPACE << "|                                                                                                        |\n";
    cout << SHORT_SPACE << "|   0. Thoat chuong trinh                                                                                |\n";
    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
}

void display_flight(const ticket &flight_info) {
    system("cls");

    int nums_space = 82;

    cout << "\n"; 
    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
	cout << SHORT_SPACE << "|                                        THONG TIN CHUYEN BAY " << setw(43) << left << flight_info.flight_code <<          "|\n";
	cout << SHORT_SPACE << "+--------------------------------------------------------------------------------------------------------+\n";
	cout << SHORT_SPACE << "|   Ma so chuyen bay : " << setw(nums_space) << left << flight_info.flight_code << "|\n"; 
	cout << SHORT_SPACE << "|                                                                                                        |\n";
	cout << SHORT_SPACE << "|   Noi xuat phat    : " << setw(nums_space) << left << flight_info.departure << "|\n"; 
	cout << SHORT_SPACE << "|                                                                                                        |\n";
	cout << SHORT_SPACE << "|   Noi den          : " << setw(nums_space) << left << flight_info.destination << "|\n"; 
	cout << SHORT_SPACE << "|                                                                                                        |\n";
	cout << SHORT_SPACE << "|   Ngay xuat phat   : " << setw(nums_space) << left << flight_info.date << "|\n"; 
	cout << SHORT_SPACE << "|                                                                                                        |\n";
	cout << SHORT_SPACE << "|   Thoi gian        : " << setw(nums_space) << left << flight_info.time << "|\n"; 
	cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
}

void display_info(const set<string>& booked_tickets_tracking, const vector<ticket>& passengers) {
    system("cls"); 

    cout << "\n";
    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
    print_color_short_space("|                                     THONG TIN KHACH HANG VA GHE NGOI                                   |\n", 15);
    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
       
    for (int index = 0; index < passengers.size(); index++) {
        if ((passengers[index].ticket_code != "Chua dat ghe") && (booked_tickets_tracking.find(passengers[index].ticket_code) != booked_tickets_tracking.end())) {
            output_ticket_info(cout, passengers, index);
            cout << "\n"; 
        }
    }
}

void print_ticket(const string& flight_code, const vector<ticket>& passengers, const set<string>& booked_tickets_tracking) {
    fs::path directory = fs::path("data") / flight_code; 
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        print_color_long_space("Chuyen bay khong ton tai!\n", 12);
        return;
    }
    
    fs::path ticket_info_path = directory / TICKET_INFO;
    ofstream write_file(ticket_info_path, ios::app);
    for (int index = 0; index < passengers.size(); index++) {
        if ((passengers[index].ticket_code != "Chua dat ghe") && (booked_tickets_tracking.find(passengers[index].ticket_code) != booked_tickets_tracking.end())) {
            ticket_output(write_file, index, passengers);
        }
    }

    print_color_long_space("Dang luu thong tin...\n", 15);
    Sleep(800);
    print_color_long_space("Thong tin da duoc luu!\n", 10);
    Sleep(800);
}

void ticket_output(ofstream& write_file, int index, const vector<ticket>& passengers) {
    if (index < passengers.size()) {
        output_ticket_info(write_file, passengers, index, true); 
    }
    else {
        write_file << LONG_SPACE << "Da xay ra loi!\n"; 
    }
}

void output_ticket_info(
	ostream &os,
	const vector<ticket> &passengers,
	int index,
	bool delete_space) {
	string print_space = delete_space
							 ? ""
							 : LONG_SPACE;

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

void reset(const string& flight_code) {
    string choice;
    
    while (true) {
        print_color_long_space("Reset so do ghe? (Y/N): ", 14);
        getline(cin, choice);
        if (choice.empty()) {
            print_color_long_space("Khong duoc de trong.\n", 12);
            continue;
        }
        else 
            break; 
    }

    if (choice[0] == 'y' || choice[0] == 'Y') {
        reset_seating_chart(flight_code);
        while (true) {
            choice.clear(); 
            print_color_long_space("Reset du lieu ve da dat? (Y/N) ", 14);
            getline(cin, choice);
            if (choice.empty()) {
                print_color_long_space("Khong duoc de trong.\n", 12); 
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

void reset_ticket_info(const string& flight_code) {
    fs::path directory = fs::path("data") / flight_code; 

    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        print_color_long_space("Chuyen bay khong ton tai!\n", 12);
        return;
    }
    fs::path ticket_info_path = directory / TICKET_INFO;
    ofstream ticket_info_files(ticket_info_path);
    ticket_info_files.close();

    booked_tickets = 0; // reset lai so luong ve da dat

    print_color_long_space("DU LIEU VE DA DUOC RESET\n", 10); 
}

bool ask_to_continue_and_logout(const string &username) {
    cout << "\n";
    print_color_long_space("Tiep tuc nhap cac chuyen bay khac? (Y/N): ", 14);
    string out;

    while (true) {
        getline(cin, out);
        if (out.empty()) {
            print_color_long_space("Khong duoc de trong.\n", 12);
            continue;
        } else {
            break;
        }
    }

    char first = out[0];
    if (first == 'Y' || first == 'y') {
        return true;
    } else {
        return !admin_Logout(username) ? true : false;
    }
}

void end() {
    system("cls");

    cout << "\n";
    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
    print_color_short_space("|                                      Chao tam biet va hen gap lai                                      |\n", 15);
    print_color_short_space("|                                               ITF-AIRWAYS                                              |\n", 15);
    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
    cout << "\n";
    Sleep(800);
}