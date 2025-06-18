#include "print_menu.h"

using namespace std;

void introduction() {
    system("cls"); 

    cout << "\n"; 
    cout << "       ----------------------------------------------------------------------------------------------------------\n";
    cout << "       |                               Truong Dai Hoc Bach Khoa - Dai Hoc Da Nang                               |\n";
    cout << "       +--------------------------------------------------------------------------------------------------------+\n";
    cout << "       |   PBL1: Du an lap trinh tinh toan   | Xay dung ung dung dat ghe may bay cua hang hang khong ITF-Airway |\n";
    cout << "       +--------------------------------------------------------------------------------------------------------+\n";
    cout << "       |         Sinh vien thuc hien         |                                                                  |\n";
    cout << "       |             Dam Phu Quy             |                     GVHD. Tran Ho Thuy Tien                      |\n";
    cout << "       |            Dam Vinh Quang           |                                                                  |\n";
    cout << "       ----------------------------------------------------------------------------------------------------------\n";
    
    cout << LONG_SPACE << "Nhan phim bat ki de bat dau...";                                                    
    _getch(); 
}

int main(void) {
    SetConsoleOutputCP(65001); 
    introduction();
    menu();
    end();
    return 0;
}