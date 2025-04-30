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
#include "seatingchart.h" 
using namespace std;
using namespace std::filesystem;

void importSeatingChartData(); 
void displaySeatingChart();
bool isValidSeat(const string& seat);
string selectSeat(int index);
void resetSeatingChart();
void importSeatCode(); 
int findPassengers(const string& code); 
void statistics(); 