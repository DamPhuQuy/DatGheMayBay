#pragma once
#include <fstream>
#include "global.h"

using namespace std;

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