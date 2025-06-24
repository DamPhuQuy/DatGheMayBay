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

bool take_seat_code(const string& flight_code,
					set<string>& seat_status,
					set<string>& store_booked_tickets,
					set<string>& booked_tickets_tracking,
					vector<vector<string>>& first_class,
					vector<vector<string>>& economy_class,
                    vector<ticket>& passengers);
int valid_number_of_tickets();
int find_passenger(const string& code, const vector<ticket>& passengers);
void display_seating_chart(const vector<vector<string>>& first_class, const vector<vector<string>>& economy_class);
string select_seat(int index, 
				   const vector<ticket>& passengers, 
				   vector<vector<string>>& first_class, 
				   vector<vector<string>>& economy_class, 
				   set<string>& seat_status, 
				   bool& leave);
bool is_valid_seat(const string& seat_code);
bool update_seat(vector<vector<string>>& seatClass, const string& choice, string& error_message, pair<int, int>& pos);
bool confirm(const string& choice, set<string>& seat_status);
string seat_replacement(const string& seat_choice);
void update_seating_chart(const string& flight_code, const vector<vector<string>>& first_class, const vector<vector<string>>& economy_class);
void reset_seating_chart(const string& flight_code);
void statistics();

