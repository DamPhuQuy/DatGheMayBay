#pragma once
#include <fstream>
#include "global.h"
using namespace std;

bool openInputFile(ifstream &readFile1, ifstream &readFile2);
bool readFlightInformation(ifstream &readFile2, ticket &data);
void readPassengerInformation(ifstream &readFile1, const ticket &flightData);
void importPassengersInformation();
void importBookedTicket();