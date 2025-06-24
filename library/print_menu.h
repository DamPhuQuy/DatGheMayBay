#pragma once

#include <iostream>
#include <stdio.h> 
#include <string> 
#include <vector> 
#include <set> 
#include <windows.h> 
#include <fstream>
#include <filesystem>
#include "selecting_seat.h"
#include "admin.h"
#include "global.h"

using namespace std;

void menu(); 
void initialize_new_data(string &flight_code,
                            vector<string> &flights,
                            vector<vector<string>> &first_class,
                            vector<vector<string>> &economy_class,
                            set<string> &seat_status,
                            set<string> &store_booked_tickets,
                            set<string> &booked_tickets_tracking,
                            vector<ticket> &passengers);
void input_flight_code(
    string& flight_code,
    vector<vector<string>>& first_class,
    vector<vector<string>>& economy_class,
    vector<ticket>& passengers,
    vector<string>& flights,
    set<string>& store_booked_tickets,
    set<string>& seat_status
);
void flight_menu(const vector<string>& flights);
void import(
    const string& flight_code,
    vector<vector<string>>& first_class,
    vector<vector<string>>& economy_class,
    set<string>& seat_status,
    set<string>& store_booked_tickets,
    vector<ticket>& passengers
);
void handle_menu_loop(const string &flight_code,
                      vector<vector<string>> &first_class,
                      vector<vector<string>> &economy_class,
                      set<string> &seat_status,
                      set<string> &store_booked_tickets,
                      set<string> &booked_tickets_tracking,
                      vector<ticket> &passengers);
void display_menu();
void display_flight(const ticket &flight_info);
void display_info(const set<string>& booked_tickets_tracking, const vector<ticket>& passengers);
void print_ticket(const string& flight_code, const vector<ticket>& passengers, const set<string>& booked_tickets_tracking);
void ticket_output(ostream& write_file, int index, const vector<ticket>& passengers);
void output_ticket_info(
    ostream& os,
    const vector<ticket> &passengers,
    int index,
    bool delete_space = false);
void reset(const string& flight_code);
void reset_ticket_info(const string& flight_code);
bool ask_to_continue_and_logout(const string &username);
void end();
