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

void loginFrame();
void Goto(const int x, const int y);
void load_accounts(unordered_map<string, string>& accounts);
string input_hidden_pass();
void input(string& username, string& password1, string& password2);
void admin_Login(string& username);
bool checkLogout();
bool admin_Logout(const string& username);