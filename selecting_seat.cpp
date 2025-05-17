#include "selecting_seat.h"
#include "import_data.h"

using namespace std;
namespace fs = std::filesystem; 

void display_seating_chart(const vector<vector<string>>& first_class, const vector<vector<string>>& economy_class) {
	system("cls");

	cout << "\n";
	cout << short_space << "---------------------------------------------Chon Ghe May Bay---------------------------------------------\n";

	cout << "\n";
    cout << short_space << "----------------------------------------------------------------------------------------------------------\n";
    cout << short_space << "|    First Class     |                                     Economy Class                                 |\n";
    cout << short_space << "+--------------------------------------------------------------------------------------------------------+\n";

    cout << short_space << "|                    | ";
    for (const auto &seat : economy_class[0]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << short_space << "| " << first_class[0][0] << " " << first_class[1][0] << " " << first_class[2][0] << " " << first_class[3][0] << "        | ";
    for (const auto &seat : economy_class[1]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << short_space << "| " << first_class[0][1] << " " << first_class[1][1] << " " << first_class[2][1] << " " << first_class[3][1] << "        | ";
    for (const auto &seat : economy_class[2]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << short_space << "+--------------------------------------------------------------------------------------------------------+\n";
    cout << short_space << "|                                               Loi di                                                   |\n";
    cout << short_space << "+--------------------------------------------------------------------------------------------------------+\n";

    cout << short_space << "| " << first_class[0][2] << " " << first_class[1][2] << " " << first_class[2][2] << " " << first_class[3][2] << "        | ";
    for (const auto &seat : economy_class[3]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << short_space << "| " << first_class[0][3] << " " << first_class[1][3] << " " << first_class[2][3] << " " << first_class[3][3] << "        | ";
    for (const auto &seat : economy_class[4]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << short_space << "|                    | ";
    for (const auto &seat : economy_class[5]) {
        cout << seat << " ";
    }
    cout << "   |\n";

    cout << short_space << "----------------------------------------------------------------------------------------------------------\n";

    cout << "\n"
         << "                         [--] hay [---]: Ghe dat dat                 1A: Ghe chua dat \n";
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

string seat_replacement(const string& seat_choice) {
	return seat_choice.length() == 2 ? "--" : "---"; 
}

bool update_seat(vector<vector<string>>& seatClass, const string& choice, string& error_message) {
    for (int i = 0; i < seatClass.size(); i++) {
        for (int j = 0; j < seatClass[i].size(); j++) {
            if (seatClass[i][j] == choice) {
                seatClass[i][j] = seat_replacement(choice);
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
        cout << long_space << "Xac nhan ghe " << choice << " (Y/N): ";
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
            cout << long_space << "Khong duoc de trong.\n"; 
            continue;
        }
        
        char response = toupper(input[0]);
        if (response == 'Y') {
            seat_status.insert(choice);
            return true;
        } else if (response == 'N') {
            return false; 
        } else {
            cout << long_space << "Khong hop le. Vui long nhap 'Y' or 'N'." << "\n";
        }
    }
}

string select_seat(int index, 
				   const vector<ticket>& passengers, 
				   vector<vector<string>>& first_class, 
				   vector<vector<string>>& economy_class, 
				   set<string>& seat_status) {

	string seat_choice; 
	while (true) {
		cout << long_space<< "Hay chon ghe: ";
        getline(cin, seat_choice);



        auto it = seat_status.find(seat_choice); 
        if (!is_valid_seat(seat_choice) || it != seat_status.end()) {
        	cout << "\n"; 
        	cout << long_space << "Lua chon khong phu hop hoac ghe da dat!\n"; 
        	continue; 
        }

        string error_message;
	    bool seat_found = false;

	    if (passengers[index].class_label == "First Class") {
	        seat_found = update_seat(first_class, seat_choice, error_message);
	    } 
	    else if (passengers[index].class_label == "Economy Class") {
	        seat_found = update_seat(economy_class, seat_choice, error_message);
	    } 
	    else {
	        error_message = "Class khong hop le!";
	    }

	    if (!seat_found) {
	        cout << long_space << error_message << "\n";
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
			for (int i = 0; i < first_class.size(); i++) {
				for (int j = 0; j < first_class[i].size(); j++) {
					if (first_class[i][j] == seat_replacement(seat_choice)) {
						first_class[i][j] = seat_choice; 
						break; 
					}
				}
			}
		}
		else if (passengers[index].class_label == "Economy Class") {
			for (int i = 0; i < economy_class.size(); i++) {
				for (int j = 0; j < economy_class[i].size(); j++) {
					if (economy_class[i][j] == seat_replacement(seat_choice)) {
						economy_class[i][j] = seat_choice;
						break; 
					}
				}
			}
		}
		cout << long_space << "Lua chon ghe da bi huy.\n"; 
		return "Chua dat ghe"; 
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

int valid_number_of_tickets() {
	int available_seats = MaxSeat - booked_tickets; 
	string input; 
	int count; 

	while (true) {
		cout << "\n"; 
		cout << long_space << "So ve may bay can dat: ";
		getline(cin, input); 
		if (input.empty()) {
			cout << long_space << "Khong duoc de trong!\n";
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
			cout << long_space << "Gia tri khong hop le!\n"; 
			continue; 
		}

		count = stoi(input); 
		if (count <= 0) {
			cout << long_space << "So ve phai lon hon 0.\n"; 
			continue; 
		}
		if (count > MaxSeat) {
			cout << long_space << "Vuot qua tong so ghe (" << MaxSeat << "ghe ).\n"; 
			continue; 
		}
		if (count > available_seats) {
			cout << long_space << "Khong du cho trong!\n"; 
			return -1; 
		}
		return count; 
	}	
}

void update_seating_chart(const string& flight_code, const vector<vector<string>>& first_class, const vector<vector<string>>& economy_class) {
	fs::path directory = flight_code; 
	if (!fs::exists(directory) || !fs::is_directory(directory)) {
		cout << long_space << "Chuyen bay khong ton tai!\n"; 
		exit(0); 
	}
	
	fs::path booked_seating_path = directory / BOOKED_CHART; 
	ofstream booked_seating_files(booked_seating_path); 
	if (!booked_seating_files.is_open()) {
		cout << long_space << "Loi khi mo file " << BOOKED_CHART << "\n"; 
		exit(0); 
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

void take_seat_code(const string& flight_code,
                    set<string>& seat_status,
                    set<string>& store_booked_tickets,
                    set<string>& store_booked_tickets_add_only,
                    vector<vector<string>>& first_class,
                    vector<vector<string>>& economy_class,
                    vector<ticket>& passengers) {
	int ticket_count = 1; 
	int number_of_tickets = valid_number_of_tickets();

	while (number_of_tickets > 0) {
		display_seating_chart(first_class, economy_class);
		
		cout << "\n";
		cout << long_space << "STT ve may bay: " << ticket_count << "\n"; 
		
		string ticket_code; 
		int index;
		while (true) {
			cout << long_space << "Nhap ma so ve may bay: ";
            getline(cin, ticket_code);

            if (store_booked_tickets.find(ticket_code) != store_booked_tickets.end()) {
                cout << long_space << "Ma so nay da dat ghe\n";
                cout << long_space << "Nhap lai!\n";
                continue;
            }
            else {
            	store_booked_tickets.insert(ticket_code);
            	store_booked_tickets_add_only.insert(ticket_code);
            }

            index = find_passenger(ticket_code, passengers);
            if (index != -1) {
            	break; 
            } 
            else {
            	cout << long_space << "Khong tim thay khach hang!\n"; 
            	cout << long_space << "Vui long nhap lai!\n"; 
            }
		}

	cout << "\n"; 
	cout << long_space << "Class cua ve " << passengers[index].ticket_code << " : " << passengers[index].class_label << "\n"; 

	string seat = select_seat(index, passengers, first_class, economy_class, seat_status); 
	update_seating_chart(flight_code, first_class, economy_class); 

	passengers[index].seat_code = seat; 
	number_of_tickets--; 
	ticket_count++;
	booked_tickets++;
    }
}

void reset_seating_chart(const string& flight_code) {
    fs::path directory = flight_code;
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        cout << long_space << "Chuyen bay khong ton tai\n";
        exit(0);
    }
    fs::path original_seating_path = directory / ORIGINAL_CHART;
    fs::path booked_seating_path = directory / BOOKED_CHART;

    ifstream read_original_files(original_seating_path);
    if (!read_original_files.is_open()) {
        cout << long_space << "Khong the mo file SeatingChart.txt\n";
        exit(0); 
    }

    ofstream write_booked_chart_files(booked_seating_path, ios::trunc);
    if (!write_booked_chart_files.is_open()) {
        cout << long_space << "Khong the mo file " << BOOKED_CHART<< "\n";
        exit(0);
    }

    string line;
    while (getline(read_original_files, line)) {
        write_booked_chart_files << line << "\n";
    }
    read_original_files.close();
    write_booked_chart_files.close();
    cout << long_space << "So do ghe da duoc reset\n";
}

void statistics() {
    system("cls");

   	int nums_space = 30; 

    cout << "\n"; 
    cout << short_space << "-------------------------------------------------Thong ke-------------------------------------------------\n"; 
    
    cout << "\n"; 
    cout << long_space << "----------------------------------------------------\n";
    cout << long_space << "|                   THONG KE SO GHE                |\n";
    cout << long_space << "+--------------------------------------------------+\n";
    cout << long_space << "| Tong so ghe      : " << setw(nums_space) << left << MaxSeat << "|\n";
    cout << long_space << "|                                                  |\n";
    cout << long_space << "| So ghe da dat    : " << setw(nums_space) << left << booked_tickets << "|\n"; 
    cout << long_space << "|                                                  |\n";
    cout << long_space << "| So ghe con trong : " << setw(nums_space) << left << MaxSeat - booked_tickets << "|\n"; 
    cout << long_space << "----------------------------------------------------\n";
}