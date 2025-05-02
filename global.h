#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

const int MaxSeat = 166;
const string PERSONAL_INFO = "PersonalInformation.txt";
const string BOOKED_CHART = "BookedSeatingChart.txt";
const string ORIGINAL_CHART = "SeatingChart.txt";
const string TICKET_INFO = "TicketInformation.txt";
const string FLIGHT_INFO = "FlightInformation.txt";
const string LOG_INFO = "log.txt";

struct person {
    string names, DoB, email, phoneNumber, gender;
};

struct ticket {
    person customer;
    string flightCode, ticketCode, departure, destination;
    string time, date, seatCode, classLabel;
};

extern int ticketCount;
extern string flightCode;

extern vector<ticket> passengers;
extern set<string> bookedStore;
extern set<string> store;
extern int number_of_bookedSeats;

extern vector<vector<string>> firstClass;
extern vector<vector<string>> economyClass;

extern map<string, string> seatStatus;
