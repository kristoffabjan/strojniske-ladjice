#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <stdexcept>

enum class Orientation {
    Horizontal,
    Vertical
};

inline Orientation intToOrientation(int value) {
    if (value == 0) {
        return Orientation::Horizontal;
    } else if (value == 1) {
        return Orientation::Vertical;
    } else {
        throw std::invalid_argument("Invalid value for Orientation");
    }
}

#endif // ORIENTATION_H
