#include "print_menu.h"

using namespace std;

void introduction() {
    system("cls"); 

    cout << "\n"; 
    print_color_short_space("----------------------------------------------------------------------------------------------------------\n", 15);
    print_color_short_space("|                               Truong Dai Hoc Bach Khoa - Dai Hoc Da Nang                               |\n", 15);
    print_color_short_space("+--------------------------------------------------------------------------------------------------------+\n", 15);
    print_color_short_space("|   PBL1: Du an lap trinh tinh toan   | Xay dung ung dung dat ghe may bay cua hang hang khong ITF-Airway |\n", 15);
    print_color_short_space("+--------------------------------------------------------------------------------------------------------+\n", 15);
    print_color_short_space("|         Sinh vien thuc hien         |                                                                  |\n", 15);
    print_color_short_space("|             Dam Phu Quy             |                     GVHD. Tran Ho Thuy Tien                      |\n", 15);
    print_color_short_space("|            Dam Vinh Quang           |                                                                  |\n", 15);
    print_color_short_space("----------------------------------------------------------------------------------------------------------\n", 15);
    
    print_color_long_space("Nhan phim bat ki de bat dau...", 9);                                                    
    _getch(); 
}

int main(void) {
    SetConsoleOutputCP(65001); 
    introduction();
    menu();
    end();
    return 0;
}