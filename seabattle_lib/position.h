#pragma once

#include <string>

namespace seabattle {

    class Position {
    public:
        Position(int x, int y);

        int x() const noexcept { return x_; }
        int y() const noexcept { return y_; }

        bool operator==(const Position& other) const noexcept;
        bool operator!=(const Position& other) const noexcept;

        std::string to_string() const;

    private:
        int x_;
        int y_;
    };

} // namespace seabattle