#include "global.h"

using namespace std;


// color codes for console text
// 0 = black, 1 = blue, 2 = green, 3 = cyan, 4 = red, 5 = magenta, 6 = yellow, 7 = white
// 8 = gray, 9 = light blue, 10 = light green,

void set_text_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void reset_text_color() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void print_color_short_space(const string& text, int color) {
    set_text_color(color);
    cout << SHORT_SPACE << text;
    reset_text_color();
}

void print_color_long_space(const string& text, int color) {
    set_text_color(color);
    cout << LONG_SPACE << text;
    reset_text_color();
}

void Goto(const int x, const int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}