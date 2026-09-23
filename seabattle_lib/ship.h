#pragma once

#include <cstddef>
#include <vector>
#include "position.h"

namespace seabattle {

    enum class ShotResult {
        Miss,
        Hit,
        Kill
    };

    class Ship {
    public:
        explicit Ship(std::vector<Position> positions);

        const std::vector<Position>& positions() const noexcept { return positions_; }
        std::size_t size() const noexcept { return positions_.size(); }

        bool is_alive() const noexcept;
        bool occupies(const Position& pos) const noexcept;

        ShotResult take_hit(const Position& pos);

    private:
        std::vector<Position> positions_;
        std::vector<bool> hits_;
    };

} 