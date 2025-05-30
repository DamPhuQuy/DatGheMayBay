#include "import_data.h"

using namespace std;
namespace fs = std::filesystem; 

int booked_tickets = 0;

bool open_input_files(const string& flight_code, ifstream& personal_info_file, ifstream& flight_info_file) {
	fs::path directory = fs::path("data") / flight_code;  
	if (!fs::exists(directory) || !fs::is_directory(directory)) {
		cout << long_space << "Chuyen bay khong ton tai\n"; 
		return false; 
	}

	fs::path personal_info_path = directory / PERSONAL_INFO; 
	fs::path flight_info_path = directory / FLIGHT_INFO; 

	personal_info_file.open(personal_info_path); 
	if (!personal_info_file.is_open()) {
		cout << long_space << "Khong mo duoc file " << PERSONAL_INFO << "\n"; 
		return false; 
	}

	flight_info_file.open(flight_info_path); 
	if (!flight_info_file.is_open()) {
		cout << long_space << "Khong mo duoc file " << FLIGHT_INFO << "\n"; 
		personal_info_file.close(); 
		return false; 
	}

	return true; 
}

bool read_flight_info(ifstream& flight_info_file, ticket& flight_data) {
	cout << "\n";
	cout << long_space << "Doc thong tin chuyen bay...\n"; 
	Sleep(800); 

	if (!getline(flight_info_file, flight_data.flight_code) 	||
        !getline(flight_info_file, flight_data.departure) 	||
        !getline(flight_info_file, flight_data.destination) 	||
        !getline(flight_info_file, flight_data.date) 		||
        !getline(flight_info_file, flight_data.time)) {
    	cout << long_space << "Loi khi doc thong tin chuyen bay!\n";
    	return false; 
    }

    cout << long_space << "Dang lay thong tin chuyen bay...\n"; 
    Sleep(800); 
    cout << long_space << "Lay thong tin chuyen bay thanh cong!\n"; 
    Sleep(800); 

   	return true; 
}

bool read_passenger_info(ifstream& personal_info_file, ticket& flight_data, vector<ticket>& passengers) {
	cout << "\n";
	cout << long_space << "Doc thong tin hanh khach...\n"; 
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
			cout << long_space << "Loi khi doc thong tin khach hang!\n"; 
			return false;
		}
		passengers.push_back(p); 
	}

	cout << long_space << "Doc thong tin hanh khach thanh cong!\n"; 
	cout << long_space << "Co " << passengers.size() << " hanh khach.\n"; 
	Sleep(800); 

	return true; 
}

void import_passengers_info(const string& flight_code, vector<ticket>& passengers) {
	ifstream personal_info_file, flight_info_file; 
	if (!open_input_files(flight_code, personal_info_file, flight_info_file)) {
		cout << long_space << "Khong mo duoc file\n"; 
		return; 
	}
	ticket flight_data; 
	if (!read_flight_info(flight_info_file, flight_data)) {
		personal_info_file.close(); 
		flight_info_file.close(); 
		cout << long_space << "Khong mo duoc file\n"; 
		return; 
	}

	if (!read_passenger_info(personal_info_file, flight_data, passengers)) {
		personal_info_file.close();
		flight_info_file.close(); 
		cout << long_space << "Khong mo duoc file\n"; 
		return; 
	} 

	personal_info_file.close(); 
	flight_info_file.close(); 
}

void import_booked_ticket(const string& flight_code) {
	fs::path directory = fs::path("data") / flight_code;  
	if (!exists(directory) || !fs::is_directory(directory)) {
		cout << long_space << "Chuyen bay khong ton tai!\n"; 
		return;  
	}
	fs::path booked_ticket_path = directory / TICKET_INFO; 

	ifstream booked_ticket_files(booked_ticket_path); 
	if (!booked_ticket_files.is_open()) {
		cout << long_space << "Khong mo duoc file " << TICKET_INFO << "\n"; 
		return; 
	}

	string line; 
	set<string> store_booked_tickets; 

	int found;
	while (getline(booked_ticket_files, line)) {
		found = line.find("Ma so ve:"); 
		if (found != string::npos) {
			string code = line.substr(found + 10); 
			code.erase(0, code.find_first_not_of(" ")); 
			store_booked_tickets.insert(code); 
		}
	}

	booked_ticket_files.close(); 

	cout << "\n";
	cout << long_space << "Kiem tra thong tin ve da dat...\n"; 
	Sleep(800); 
	cout << long_space << "Kiem tra thanh cong!\n"; 
	Sleep(800); 

	booked_tickets = store_booked_tickets.size(); 
	cout << long_space << "Tong cong: " << booked_tickets << " khach hang da dat ghe\n"; 
}

void import_seating_chart(const string& flight_code, vector<vector<string>>& first_class, vector<vector<string>>& economy_class) {
	fs::path directory = fs::path("data") / flight_code;  
	if (!fs::exists(directory) || !fs::is_directory(directory)) {
		cout << long_space << "Chuyen bay khong ton tai!\n"; 
		return;
	}
	fs::path booked_seating_path = directory / BOOKED_CHART;  

	ifstream booked_seating_files(booked_seating_path);
	if (!booked_seating_files.is_open()) {
		cout << long_space << "Loi khi mo file " << BOOKED_CHART << "\n"; 
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
	string line; 
	while (getline(read_flights, line)) {
		flights.push_back(line); 
	}
	read_flights.close(); 
}