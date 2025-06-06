#include "log_check.h"

string getCurrentTime() {
    chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&now_c), "%d-%m-%Y %H:%M:%S");
    return ss.str();
}

void logLogin(const string &username) {
    ofstream logFile(LOG_INFO, ios::app);
    if (logFile.is_open()) {
        logFile << "[" << getCurrentTime() << "] Nguoi dung \"" << username << "\" da dang nhap.\n";
        logFile.close();
        cout << "\n"; 
        cout << long_space << "Du lieu dang nhap duoc ghi!" << endl;
    }
}

void logLogout(const string &username) {
    ofstream logFile(LOG_INFO, ios::app);
    if (logFile.is_open()) {
        logFile << "[" << getCurrentTime() << "] Nguoi dung \"" << username << "\" da dang xuat.\n";
        logFile.close();
        cout << "\n\n"; 
        cout << long_space << "Du lieu dang xuat duoc ghi!" << endl;
    }
}