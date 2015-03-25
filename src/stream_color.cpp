#include <iostream>
#include "stream_color.h"
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
// Windows

#include <windows.h>

ostream& white(ostream& out) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return out;
}

ostream& red(ostream& out) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED);
    return out;
}

ostream& green(ostream& out) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    return out;
}

ostream& blue(ostream& out) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    return out;
}

ostream& yellow(ostream& out) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    return out;
}

ostream& magenta(ostream& out) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
    return out;
}

ostream& cyan(ostream& out) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return out;
}

ostream& black(ostream& out) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    return out;
}

#else
// Try ANSI escape code

ostream& white(ostream& out) {
    out << "\033[0m";
    return out;
}

ostream& red(ostream& out) {
    out << "\033[1;31m";
    return out;
}

ostream& green(ostream& out) {
    out << "\033[1;32m";
    return out;
}

ostream& blue(ostream& out) {
    out << "\033[1;34m";
    return out;
}

ostream& yellow(ostream& out) {
    out << "\033[1;33m";
    return out;
}

ostream& magenta(ostream& out) {
    out << "\033[1;35m";
    return out;
}

ostream& cyan(ostream& out) {
    out << "\033[1;36m";
    return out;
}

ostream& black(ostream& out) {
    out << "\033[1;30m";
    return out;
}

#endif
