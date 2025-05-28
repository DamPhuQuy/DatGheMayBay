#pragma once 

#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
#include <filesystem> 
#include <set>
#include "import_data.h"
#include "global.h"

using namespace std;

void display_seating_chart(const string& first_class, const string& economy_class);
bool is_valid_seat(const string& seat_code);
string seat_replacement(const string& seat_choice);
bool confirm(const string& choice, map<string, string>& seat_status);
string select_seat(int index, 
				   const vector<ticket>& passengers, 
				   vector<vector<string>>& first_class, 
				   vector<vector<string>>& economy_class, 
				   set<string>& seat_status);
int find_passenger(const string& code, const vector<ticket>& passengers);
int valid_number_of_tickets(int booked_tickets);
void update_seating_chart(const string& flight_code, const vector<vector<string>>& first_class, const vector<vector<string>>& economy_class);
void take_seat_code(const string& flight_code,
					set<string>& seat_status,
					set<string>& store_booked_tickets,
					set<string>& booked_tickets_tracking,
					vector<vector<string>>& first_class,
					vector<vector<string>>& economy_class,
                    vector<ticket>& passengers);
void reset_seating_chart(const string& flight_code);
void statistics();

