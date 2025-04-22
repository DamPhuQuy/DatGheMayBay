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

bool openInputFile(ifstream& readFile1, ifstream& readFile2); 
bool readFlightInformation(ifstream& readFile2, ticket& data); 
void readPassengerInformation(ifstream& readFile1, const ticket& flightData);
void importPassengersInformation();
void importBookedTicket(); 