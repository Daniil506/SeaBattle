#pragma once

#include <vector>
#include "position.h"
#include "ship.h"

namespace seabattle {

    class GameField {
    public:
        static constexpr int SIZE = 10;

        GameField() = default;

        void add_ship(Ship ship);

        ShotResult receive_shot(const Position& pos);

        const std::vector<Ship>& ships() const noexcept { return ships_; }
        const std::vector<Position>& shots() const noexcept { return shots_; }

        bool all_ships_dead() const noexcept;
        bool already_shot(const Position& pos) const noexcept;

    private:
        std::vector<Ship> ships_;
        std::vector<Position> shots_;
    };

} 