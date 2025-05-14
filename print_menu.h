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

void introduction();
void flight_menu();
void display_flight(const ticket &flight_info);
void input_flight_code(string& flight_code, vector<vector<string>>& first_class, vector<vector<string>>& economy_class);
void output_ticket_info(
    std::ostream& os,
    const std::vector<ticket> &passengers,
    int index,
    bool delete_space = false
);
void display_info(const set<string>& booked_ticket, const vector<ticket>& passengers, int index);
void ticket_output(ostream& write_file, int index);
void print_ticket(const string& flight_code, vector<string> passengers);
void display_menu();
void menu();
void end();
void reset_ticket_info(const string& flight_code);
void reset(const string& flight_code);