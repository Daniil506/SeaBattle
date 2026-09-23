#pragma once

#include <array>
#include "player.h"
#include "position.h"
#include "ship.h"

namespace seabattle {

    class Game {
    public:
        Game(Player& p1, Player& p2);

        Player& current() noexcept;
        Player& opponent() noexcept;

        ShotResult step(const Position& pos);

        bool is_over() const noexcept;
        Player* winner() noexcept;

    private:
        std::array<Player*, 2> players_;
        int turn_;
    };

} 