#pragma once 

#include <iostream> 
#include <iomanip> 
#include <filesystem> 
#include <windows.h> 
#include <sstream> 
#include <vector>
#include <fstream> 
#include "global.h" 

using namespace std;

bool open_input_files(const string& flight_code, ifstream& personal_info_file, ifstream& flight_info_file);
bool read_flight_info(ifstream& flight_info_file, ticket& flight_data);
bool read_passenger_info(ifstream& personal_info_file, ticket& flight_data, vector<ticket>& passengers);
void import_passengers_info(const string& flight_code, vector<ticket>& passengers);
void import_booked_ticket(const string& flight_code);
void import_seating_chart(const string& flight_code, vector<vector<string>>& first_class, vector<vector<string>>& economy_class);
void import_flights(vector<string>& flights); 