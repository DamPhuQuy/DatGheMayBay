#pragma once
#include <string>

using namespace std;

void importSeatingChartData();
void displaySeatingChart();
bool isValidSeat(const string &seat);
string selectSeat(int index);
void resetSeatingChart();
void importSeatCode();
int findPassengers(const string &code);
void statistics();