#include "player.h"
#include <stdexcept>
#include <utility>

namespace seabattle {

    Player::Player(std::string name)
        : name_(std::move(name)) {
        if (name_.empty()) {
            throw std::invalid_argument("Player name cannot be empty");
        }
    }

    ShotResult Player::make_shot(Player& opponent, const Position& pos) {
        return opponent.field_.receive_shot(pos);
    }

    bool Player::lost() const noexcept {
        return field_.all_ships_dead();
    }

} 