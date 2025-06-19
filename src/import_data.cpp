#include "import_data.h"

using namespace std;
namespace fs = std::filesystem; 

int booked_tickets = 0;

bool open_input_files(const string& flight_code, ifstream& personal_info_file, ifstream& flight_info_file) {
	fs::path directory = fs::path("data") / flight_code;  
	if (!fs::exists(directory) || !fs::is_directory(directory)) {
		cout << LONG_SPACE << "Chuyen bay khong ton tai\n"; 
		return false; 
	}

	fs::path personal_info_path = directory / PERSONAL_INFO; 
	fs::path flight_info_path = directory / FLIGHT_INFO; 

	personal_info_file.open(personal_info_path); 
	if (!personal_info_file.is_open()) {
		cout << LONG_SPACE << "Khong mo duoc file " << PERSONAL_INFO << "\n"; 
		return false; 
	}

	flight_info_file.open(flight_info_path); 
	if (!flight_info_file.is_open()) {
		cout << LONG_SPACE << "Khong mo duoc file " << FLIGHT_INFO << "\n"; 
		personal_info_file.close(); 
		return false; 
	}

	return true; 
}

bool read_flight_info(ifstream& flight_info_file, ticket& flight_data) {
	cout << "\n";
	cout << LONG_SPACE << "Doc thong tin chuyen bay...\n"; 
	Sleep(800); 

	if (!getline(flight_info_file, flight_data.flight_code) 	||
        !getline(flight_info_file, flight_data.departure) 	||
        !getline(flight_info_file, flight_data.destination) 	||
        !getline(flight_info_file, flight_data.date) 		||
        !getline(flight_info_file, flight_data.time)) {
    	cout << LONG_SPACE << "Loi khi doc thong tin chuyen bay!\n";
    	return false; 
    }

    cout << LONG_SPACE << "Dang lay thong tin chuyen bay...\n"; 
    Sleep(800); 
    cout << LONG_SPACE << "Lay thong tin chuyen bay thanh cong!\n"; 
    Sleep(800); 

   	return true; 
}

bool read_passenger_info(ifstream& personal_info_file, ticket& flight_data, vector<ticket>& passengers) {
	cout << "\n";
	cout << LONG_SPACE << "Doc thong tin hanh khach...\n"; 
	Sleep(800); 

	string line; 
	while (getline(personal_info_file, line)) {
		if (line.empty()) continue; 

		stringstream ss(line); 

		ticket p = flight_data; 
		p.seat_code = "Chua dat ghe"; 

		if (!getline(ss, p.customer.names, ',') 		|| 
			!getline(ss, p.customer.DoB, ',') 			||
			!getline(ss, p.customer.email, ',') 		||
			!getline(ss, p.customer.phone_number, ',')  ||
			!getline(ss, p.customer.gender, ',') 		||
			!getline(ss, p.ticket_code, ',')   			|| 
			!getline(ss, p.class_label)) {
			cout << LONG_SPACE << "Loi khi doc thong tin khach hang!\n"; 
			return false;
		}
		passengers.push_back(p); 
	}

	cout << LONG_SPACE << "Doc thong tin hanh khach thanh cong!\n"; 
	cout << LONG_SPACE << "Co " << passengers.size() << " hanh khach.\n"; 
	Sleep(800); 

	return true; 
}

void import_passengers_info(const string &flight_code, vector<ticket> &passengers) {
	ifstream personal_info_file, flight_info_file; 
	if (!open_input_files(flight_code, personal_info_file, flight_info_file)) {
		cout << LONG_SPACE << "Khong mo duoc file\n"; 
		return; 
	}
	ticket flight_data; 
	if (!read_flight_info(flight_info_file, flight_data)) {
		personal_info_file.close(); 
		flight_info_file.close(); 
		cout << LONG_SPACE << "Khong mo duoc file\n"; 
		return; 
	}

	if (!read_passenger_info(personal_info_file, flight_data, passengers)) {
		personal_info_file.close();
		flight_info_file.close(); 
		cout << LONG_SPACE << "Khong mo duoc file\n"; 
		return; 
	} 

	personal_info_file.close(); 
	flight_info_file.close();
}

void import_booked_ticket(const string& flight_code, set<string>& store_booked_tickets, set<string>& seat_status) {
	fs::path directory = fs::path("data") / flight_code;  
	if (!exists(directory) || !fs::is_directory(directory)) {
		cout << LONG_SPACE << "Chuyen bay khong ton tai!\n"; 
		return;  
	}
	fs::path booked_ticket_path = directory / TICKET_INFO; 

	ifstream booked_ticket_files(booked_ticket_path); 
	if (!booked_ticket_files.is_open()) {
		cout << LONG_SPACE << "Khong mo duoc file " << TICKET_INFO << "\n"; 
		return; 
	}

	string line;
	while (getline(booked_ticket_files, line)){
		size_t found = line.find("Ma so ve");
		if (found != string::npos){
			size_t colon = line.find(":");
			if (colon != string::npos) {
				string code = line.substr(colon + 1);
				code.erase(0, code.find_first_not_of(" \t"));
				code.erase(code.find_last_not_of(" \t|") + 1);
				store_booked_tickets.insert(code);
			}
		}

		size_t found_seat = line.find("Ma so ghe");
		if (found_seat != string::npos) {
			size_t colon = line.find(":");
			if (colon != string::npos) {
				string seat_code = line.substr(colon + 1);
				seat_code.erase(0, seat_code.find_first_not_of(" \t"));
				seat_code.erase(seat_code.find_last_not_of(" \t|") + 1);
				seat_status.insert(seat_code); 
			}
		}
	}

	booked_ticket_files.close(); 

	cout << "\n";
	cout << LONG_SPACE << "Kiem tra thong tin ve da dat...\n"; 
	Sleep(800); 
	cout << LONG_SPACE << "Kiem tra thanh cong!\n"; 
	Sleep(800); 

	booked_tickets = store_booked_tickets.size(); 
	cout << LONG_SPACE << "Tong cong: " << booked_tickets << " khach hang da dat ghe\n"; 
}

void import_seating_chart(const string& flight_code, vector<vector<string>>& first_class, vector<vector<string>>& economy_class) {
	fs::path directory = fs::path("data") / flight_code;  
	if (!fs::exists(directory) || !fs::is_directory(directory)) {
		cout << LONG_SPACE << "Chuyen bay khong ton tai!\n"; 
		return;
	}
	fs::path booked_seating_path = directory / BOOKED_CHART;  

	ifstream booked_seating_files(booked_seating_path);
	if (!booked_seating_files.is_open()) {
		cout << LONG_SPACE << "Loi khi mo file " << BOOKED_CHART << "\n"; 
		return; 
	}

	bool is_first_class = false, is_economy_class = false; 

	string line, token; 
	vector<string> row; 
	while (getline(booked_seating_files, line)) {
		if (line == "First Class:")   { is_first_class = true; is_economy_class = false; continue; }
		if (line == "Economy Class:") { is_first_class = false; is_economy_class = true; continue; }
		if (!line.empty()) {
			stringstream ss(line); 
			row.clear();   

			while (ss >> token) 
				row.push_back(token); 

			if (is_first_class) 
				first_class.push_back(row); 
			else if (is_economy_class) 
				economy_class.push_back(row); 
		}
	}
	booked_seating_files.close(); 
}

void import_flights(vector<string>& flights) {
	ifstream read_flights("flights.txt"); 

	if (!read_flights.is_open()) {
		cout << LONG_SPACE << "Khong the mo file flights.txt\n"; 
		return; 
	}

	string line; 
	while (getline(read_flights, line)) {
		flights.push_back(line); 
	}
	read_flights.close(); 
}