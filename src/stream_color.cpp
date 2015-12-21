/* Copyright 2015 ZhaoHG */
#include <string>
#include <iostream>
#include "../include/stream_color.h"

using std::ostream;
using std::string;

namespace ztest {

#if defined(_U_S_TEST)

void color(ostream*, TextColor color, const string& text) {
    (*out) << text;
}

#elif defined(_WIN32) || defined(_WIN64)
// Windows

#include <windows.h>

void color(ostream* out, TextColor color, const string& text) {
    switch (color) {
    case TextColor::WHITE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_RED |
                                FOREGROUND_GREEN |
                                FOREGROUND_BLUE);
        break;
    case TextColor::RED:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_RED);
        break;
    case TextColor::GREEN:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        break;
    case TextColor::BLUE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        break;
    case TextColor::YELLOW:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY |
                                FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case TextColor::MAGENTA:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY |
                                FOREGROUND_RED | FOREGROUND_BLUE);
        break;
    case TextColor::CYAN:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY |
                                FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case TextColor::BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_INTENSITY);
        break;
    }
    (*out) << text;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED |
                            FOREGROUND_GREEN |
                            FOREGROUND_BLUE);
}

#else
// Try ANSI escape code

void color(ostream* out, TextColor color, const string& text) {
    switch (color) {
    case TextColor::WHITE:
        (*out) << "\033[0m";
        break;
    case TextColor::RED:
        (*out) << "\033[1;31m";
        break;
    case TextColor::GREEN:
        (*out) << "\033[1;32m";
        break;
    case TextColor::BLUE:
        (*out) << "\033[1;34m";
        break;
    case TextColor::YELLOW:
        (*out) << "\033[1;33m";
        break;
    case TextColor::MAGENTA:
        (*out) << "\033[1;35m";
        break;
    case TextColor::CYAN:
        (*out) << "\033[1;36m";
        break;
    case TextColor::BLACK:
        (*out) << "\033[1;30m";
        break;
    }
    (*out) << text;
    (*out) << "\033[0m";
}

#endif

}  // namespace ztest
