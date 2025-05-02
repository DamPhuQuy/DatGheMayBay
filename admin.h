#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "logCheck.h"

using namespace std;

void loginFrame();
void Goto(int x, int y);
bool checkUser(); 
void checkPassword(string& password); 
bool checkLogin();
void adminLogin();
bool checkLogout();
void adminLogout();