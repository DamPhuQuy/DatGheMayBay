#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <cctype>
#include <unordered_map>
#include "log_check.h"
#include "global.h"

using namespace std;

void admin_Login(string& username);
void load_accounts(unordered_map<string, string>& accounts);
void loginFrame();
void input(string& username, string& password1, string& password2);
string input_hidden_pass();
bool admin_Logout(const string& username);
bool checkLogout();