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

void loginFrame();
void Goto(const int x, const int y);
void load_accounts(std::unordered_map<std::string, std::string>& accounts);
std::string input_hidden_pass();
void input(std::string& username, std::string& password1, std::string& password2);
void admin_Login(string& username);
bool checkLogout();
bool admin_Logout(const std::string& username);