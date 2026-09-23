#include "position.h"
#include <stdexcept>

namespace seabattle {

    Position::Position(int x, int y) : x_(x), y_(y) {
        if (x < 0 || x >= 10 || y < 0 || y >= 10) {
            throw std::out_of_range("Position out of field (0..9)");
        }
    }

    bool Position::operator==(const Position& other) const noexcept {
        return x_ == other.x_ && y_ == other.y_;
    }

    bool Position::operator!=(const Position& other) const noexcept {
        return !(*this == other);
    }

    std::string Position::to_string() const {
        return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
    }

} // namespace seabattle