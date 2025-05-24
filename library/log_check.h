#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include "global.h"

using namespace std;

const string LOG_INFO = "log.txt";

string getCurrentTime(); 
void logLogin(const string &username);
void logLogout(const string &username);