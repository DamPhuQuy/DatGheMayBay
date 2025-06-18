#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

const int MAX_SEAT = 166;
const string PERSONAL_INFO = "PersonalInformation.txt";
const string BOOKED_CHART = "BookedSeatingChart.txt";
const string ORIGINAL_CHART = "SeatingChart.txt";
const string TICKET_INFO = "TicketInformation.txt";
const string FLIGHT_INFO = "FlightInformation.txt";
const string SHORT_SPACE (7, ' ');
const string LONG_SPACE (33, ' '); 

extern int booked_tickets; 

struct person {
    string names, DoB, email, phone_number, gender;
};

struct ticket {
    struct person customer;
    string flight_code, ticket_code, departure, destination;
    string time, date, seat_code, class_label;
};
