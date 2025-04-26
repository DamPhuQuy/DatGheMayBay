#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

const int MaxSeat = 166;

typedef struct {
    string names, DoB, email, phoneNumber, gender;
} person;

typedef struct {
    person customer;
    string flightCode, ticketCode, departure, destination;
    string time, date, seatCode, classLabel;
} ticket;

extern int ticketCount;

extern vector<ticket> passengers;
extern set<string> bookedStore;
extern set<string> store;
extern int number_of_bookedSeats; 

extern vector<vector<string>> firstClass;
extern vector<vector<string>> economyClass;

extern map<string, string> seatStatus;
