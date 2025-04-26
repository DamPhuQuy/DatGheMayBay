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
#include "global.h"
using namespace std;

void importSeatingChartData(); 
void displaySeatingChart();
bool isValidSeat(const string& seat);
string selectSeat(int index);
void resetSeatingChart();
void importSeatCode(); 
int findPassengers(const string& code); 
void statistics(); 