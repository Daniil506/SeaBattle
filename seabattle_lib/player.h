#pragma once

#include <string>
#include "game_field.h"
#include "position.h"
#include "ship.h"

namespace seabattle {

    class Player {
    public:
        explicit Player(std::string name);

        const std::string& name() const noexcept { return name_; }

        GameField& field() noexcept { return field_; }
        const GameField& field() const noexcept { return field_; }

        ShotResult make_shot(Player& opponent, const Position& pos);
        bool lost() const noexcept;

    private:
        std::string name_;
        GameField field_;
    };

} 