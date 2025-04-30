#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <cctype>
#include <sstream>
#include <set>
#include <windows.h>
#include <iomanip>  
#include <filesystem> 
#include "global.h"
#include "importdata.h"
#include "seatingchart.h"
#include "admin.h"

using namespace std;
using namespace std::filesystem;

void displayFlight(const ticket &flightList);
void displayInformation();
void TicketOutput(ofstream &WriteFile, int index);
void printTicket();
void resetTicketInformation();
void displayMenu();
void inputFlightCode();
void menu();
void end();
void reset();