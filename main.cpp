#include <iostream> 
#include <string> 
#include <vector>
#include <map> 
#include <set> 
#include <windows.h> 
#include "global.h" 
#include "printMenu.cpp"
using namespace std;

int ticketCount = 1; 

vector<ticket> passengers;
set<string> bookedStore;
set<string> store;

vector<vector<string>> firstClass;
vector<vector<string>> economyClass;

map<string, string> seatStatus;


int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    menu();
    end();
    reset();
    return 0;
}