#include "selecting_seat.h"

using namespace std;
namespace fs = std::filesystem; 

bool take_seat_code(const string& flight_code,
                    set<string>& seat_status,
                    set<string>& store_booked_tickets,
                    set<string>& booked_tickets_tracking,
                    vector<vector<string>>& first_class,
                    vector<vector<string>>& economy_class,
                    vector<ticket>& passengers) {
	int ticket_count = 1; 
	int number_of_tickets = valid_number_of_tickets();

	if (number_of_tickets == -1) {
		return true; 
	}

	while (number_of_tickets > 0) {
		display_seating_chart(first_class, economy_class);
		
		cout << "\n";
		print_color_long_space("STT ve may bay: " + to_string(ticket_count) + "\n", 14); 
		
		string ticket_code; 
		int index;
		while (true) {
			print_color_long_space("Nhap ma so ve may bay (hoac exit): ", 14);
            getline(cin, ticket_code);

			if (ticket_code == "exit" || ticket_code == "Exit") {
				return true;
			}

            if (store_booked_tickets.find(ticket_code) != store_booked_tickets.end()) {
                print_color_long_space("Ma so nay da dat ghe\n", 12);
                print_color_long_space("Nhap lai!\n", 12);
                continue;
            }
            else {
            	store_booked_tickets.insert(ticket_code);
            	booked_tickets_tracking.insert(ticket_code);
            }

            index = find_passenger(ticket_code, passengers);
            if (index != -1) {
            	break; 
            } 
            else {
            	print_color_long_space("Khong tim thay khach hang!\n", 12); 
            	print_color_long_space("Vui long nhap lai!\n", 12); 
            }
		}

		cout << "\n"; 
		print_color_long_space("Class cua ve " + passengers[index].ticket_code + " : " + passengers[index].class_label + "\n", 14); 

		bool leave = false; 
		string seat = select_seat(index, passengers, first_class, economy_class, seat_status, leave); 
		if (leave) {
			store_booked_tickets.erase(ticket_code); 
			booked_tickets_tracking.erase(ticket_code); 
			return leave; 
		}
		update_seating_chart(flight_code, first_class, economy_class); 

		passengers[index].seat_code = seat; 
		number_of_tickets--; 
		ticket_count++;
		booked_tickets++;
    }
	return false; 
}

int valid_number_of_tickets() {
	int available_seats = MAX_SEAT - booked_tickets; 
	string input; 
	int count; 

	while (true) {
		cout << "\n"; 
		print_color_long_space("So ve may bay can dat (hoac exit): ", 14);
		getline(cin, input); 

		if (input == "exit" || input == "Exit") {
			return -1; 
		}

		if (input.empty()) {
			print_color_long_space("Khong duoc de trong!\n", 12);
			continue; 
		}

		bool is_number = true; 
		for (char c : input) {
			if (!isdigit(c)) {
				is_number = false; 
				break; 
			}
		}

		if (!is_number) {
			print_color_long_space("Gia tri khong hop le!\n", 12); 
			continue; 
		}

		count = stoi(input); 
		if (count <= 0) {
			print_color_long_space("So ve phai lon hon 0.\n", 12); 
			continue; 
		}
		if (count > MAX_SEAT) {
			print_color_long_space("Vuot qua tong so ghe (" + to_string(MAX_SEAT) + "ghe).\n", 12); 
			continue; 
		}
		if (count > available_seats) {
			print_color_long_space("Khong du cho trong!\n", 12); 
			continue; 
		}
		return count; 
	}	
}

int find_passenger(const string& code, const vector<ticket>& passengers) {
	for (int i = 0; i < passengers.size(); i++) {
		if (passengers[i].ticket_code == code) {
			return i; 
		}
	}
	return -1; 
}

void display_seating_chart(const vector<vector<string>>& first_class, const vector<vector<string>>& economy_class) {
	system("cls");

	cout << "\n";
	print_color_short_space("---------------------------------------------Chon Ghe May Bay---------------------------------------------\n", 15);

	cout << "\n";
    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";
    print_color_short_space("|    First Class     |                                     Economy Class                                 |\n", 15);
    cout << SHORT_SPACE << "+--------------------------------------------------------------------------------------------------------+\n";

    cout << SHORT_SPACE << "|                    | ";
    for (const auto &seat : economy_class[0]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << SHORT_SPACE << "| " << first_class[0][0] << " " << first_class[1][0] << " " << first_class[2][0] << " " << first_class[3][0] << "        | ";
    for (const auto &seat : economy_class[1]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << SHORT_SPACE << "| " << first_class[0][1] << " " << first_class[1][1] << " " << first_class[2][1] << " " << first_class[3][1] << "        | ";
    for (const auto &seat : economy_class[2]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << SHORT_SPACE << "+--------------------------------------------------------------------------------------------------------+\n";
    print_color_short_space("|                                               Loi di                                                   |\n", 15);
    cout << SHORT_SPACE << "+--------------------------------------------------------------------------------------------------------+\n";

    cout << SHORT_SPACE << "| " << first_class[0][2] << " " << first_class[1][2] << " " << first_class[2][2] << " " << first_class[3][2] << "        | ";
    for (const auto &seat : economy_class[3]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << SHORT_SPACE << "| " << first_class[0][3] << " " << first_class[1][3] << " " << first_class[2][3] << " " << first_class[3][3] << "        | ";
    for (const auto &seat : economy_class[4]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << SHORT_SPACE << "|                    | ";
    for (const auto &seat : economy_class[5]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << SHORT_SPACE << "----------------------------------------------------------------------------------------------------------\n";

    cout << "\n"
         << "                         [--] hay [---]: Ghe dat dat                 1A: Ghe chua dat \n";
}

string select_seat(int index, 
				   const vector<ticket>& passengers, 
				   vector<vector<string>>& first_class, 
				   vector<vector<string>>& economy_class, 
				   set<string>& seat_status, 
				   bool& leave) {

	string seat_choice;
	pair<int, int> pos;   
	while (true) {
		print_color_long_space("Hay chon ghe (hoac exit): ", 14);
        getline(cin, seat_choice);

		if (seat_choice == "exit" || seat_choice == "Exit") {
			leave = true;
			return "Chua dat ghe";
		}

        auto it = seat_status.find(seat_choice); 
        if (!is_valid_seat(seat_choice) || it != seat_status.end()) {
        	cout << "\n"; 
        	print_color_long_space("Lua chon khong phu hop hoac ghe da dat!\n", 12); 
        	continue; 
        }

        string error_message;
	    bool seat_found = false;

	    if (passengers[index].class_label == "First Class") {
	        seat_found = update_seat(first_class, seat_choice, error_message, pos);
	    } 
	    else if (passengers[index].class_label == "Economy Class") {
	        seat_found = update_seat(economy_class, seat_choice, error_message, pos);
	    } 
	    else {
	        error_message = "Class khong hop le!";
	    }

	    if (!seat_found) {
	        print_color_long_space(error_message + "\n", 12);
	    }
	    else {
	    	break;
	    }
	} 

	if (confirm(seat_choice, seat_status)) {
		return seat_choice; 
	}
	else {
		if (passengers[index].class_label == "First Class") {
			if (first_class[pos.first][pos.second] == seat_replacement(seat_choice)) {
				first_class[pos.first][pos.second] = seat_choice; 
			}
		}
		else if (passengers[index].class_label == "Economy Class") {
			if (economy_class[pos.first][pos.second] == seat_replacement(seat_choice)) {
				economy_class[pos.first][pos.second] = seat_choice; 
			}
		}
		print_color_long_space("Lua chon ghe da bi huy.\n", 12); 
		return "Chua dat ghe"; 
	}
}

bool is_valid_seat(const string& seat_code) {
	if (seat_code.length() < 2 || seat_code.length() > 3) 
		return false;
	string num_part = seat_code.substr(0, seat_code.length() - 1); 
	char character_part = seat_code[seat_code.length() - 1]; 

	for (char c : num_part) {
		if (!isdigit(c)) return false; 
	}

	int num = stoi(num_part); 
	if (num < 1 || num > 25) 
		return false; 
	if (character_part < 'A' || character_part > 'F') 
		return false; 

	return true; 
}

bool update_seat(vector<vector<string>>& seatClass, const string& choice, string& error_message, pair<int, int>& pos) {
    for (int i = 0; i < seatClass.size(); i++) {
        for (int j = 0; j < seatClass[i].size(); j++) {
            if (seatClass[i][j] == choice) {
                seatClass[i][j] = seat_replacement(choice);
				pos.first = i; 
				pos.second = j; 
                return true;
            }
        }
    }
    error_message = "Ghe da chon khong phu hop voi Class cua ban!";
    return false;
}

bool confirm(const string& choice, set<string>& seat_status) {
    string input;
    while (true) {
        print_color_long_space("Xac nhan ghe " + choice + " (Y/N): ", 14);
        getline(cin, input);
        
        // trim chuoi, tach khoang trang neu nguoi dung nhap vao
        unsigned int first = input.find_first_not_of(" \t"); 
        unsigned int last = input.find_last_not_of(" \t"); 
        if (first == string::npos) {
        	input.clear(); 
        }
        else {
        	input = input.substr(first, last - first + 1); 
        }


        if (input.empty()) {
            print_color_long_space("Khong duoc de trong.\n", 12); 
            continue;
        }
        
        char response = toupper(input[0]);
        if (response == 'Y') {
            seat_status.insert(choice);
            return true;
        } else if (response == 'N') {
            return false; 
        } else {
            print_color_long_space("Khong hop le. Vui long nhap 'Y' or 'N'.\n", 12);
        }
    }
}

string seat_replacement(const string& seat_choice) {
	return seat_choice.length() == 2 ? "--" : "---"; 
}

void update_seating_chart(const string& flight_code, const vector<vector<string>>& first_class, const vector<vector<string>>& economy_class) {
	fs::path directory = fs::path("data") / flight_code;  
	if (!fs::exists(directory) || !fs::is_directory(directory)) {
		print_color_long_space("Chuyen bay khong ton tai!\n", 12); 
		return; 
	}
	
	fs::path booked_seating_path = directory / BOOKED_CHART; 
	ofstream booked_seating_files(booked_seating_path); 
	if (!booked_seating_files.is_open()) {
		print_color_long_space("Loi khi mo file " + BOOKED_CHART + "\n", 12); 
		return; 
	}

	booked_seating_files << "First Class:" << "\n";
    for (int i = 0; i < first_class.size(); i++) {
        for (int j = 0; j < first_class[i].size(); j++) {
            booked_seating_files << first_class[i][j] << " ";
        }
        booked_seating_files << endl;
    }

    booked_seating_files << "\nEconomy Class:\n";
    for (int i = 0; i < economy_class.size(); i++) {
        for (int j = 0; j < economy_class[i].size(); j++) {
            booked_seating_files << economy_class[i][j] << " ";
        }
        booked_seating_files << "\n";
    }
    booked_seating_files.close();
}

void reset_seating_chart(const string& flight_code) {
    fs::path directory = fs::path("data") / flight_code; 
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        print_color_long_space("Chuyen bay khong ton tai\n", 12); 
        return;
    }
    fs::path original_seating_path = directory / ORIGINAL_CHART;
    fs::path booked_seating_path = directory / BOOKED_CHART;

    ifstream read_original_files(original_seating_path);
    if (!read_original_files.is_open()) {
        print_color_long_space("Khong the mo file SeatingChart.txt\n", 12); 
        return; 
    }

    ofstream write_booked_chart_files(booked_seating_path, ios::trunc);
    if (!write_booked_chart_files.is_open()) {
        print_color_long_space("Khong the mo file " + BOOKED_CHART + "\n", 12); 
        return;
    }

    string line;
    while (getline(read_original_files, line)) {
        write_booked_chart_files << line << "\n";
    }
    read_original_files.close();
    write_booked_chart_files.close();
    print_color_long_space("So do ghe da duoc reset\n", 10);
}

void statistics() {
    system("cls");

   	int nums_space = 30; 

    cout << "\n"; 
    print_color_short_space("-------------------------------------------------Thong ke-------------------------------------------------\n", 15); 
    
    cout << "\n"; 
    cout << LONG_SPACE << "----------------------------------------------------\n";
    print_color_long_space("|                   THONG KE SO GHE                |\n", 15);
    cout << LONG_SPACE << "+--------------------------------------------------+\n";
    cout << LONG_SPACE << "| Tong so ghe      : " << setw(nums_space) << left << MAX_SEAT << "|\n";
    cout << LONG_SPACE << "|                                                  |\n";
    cout << LONG_SPACE << "| So ghe da dat    : " << setw(nums_space) << left << booked_tickets << "|\n"; 
    cout << LONG_SPACE << "|                                                  |\n";
    cout << LONG_SPACE << "| So ghe con trong : " << setw(nums_space) << left << MAX_SEAT - booked_tickets << "|\n"; 
    cout << LONG_SPACE << "----------------------------------------------------\n";
}