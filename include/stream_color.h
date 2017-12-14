#ifndef INCLUDE_STREAM_COLOR_H_
#define INCLUDE_STREAM_COLOR_H_

#include <string>
#include <iostream>

namespace ztest {

enum class TextColor {
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA,
    CYAN,
    BLACK
};

void color(std::ostream* out, TextColor color, const std::string& text);

}  // namespace ztest

#endif  // INCLUDE_STREAM_COLOR_H_
