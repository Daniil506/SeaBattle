#include "game.h"

#include <stdexcept>

namespace seabattle {

    Game::Game(Player& p1, Player& p2)
        : players_{ &p1, &p2 }, turn_(0) {
        if (&p1 == &p2) {
            throw std::invalid_argument("Players must be different");
        }
    }

    Player& Game::current() noexcept {
        return *players_[turn_];
    }

    Player& Game::opponent() noexcept {
        return *players_[1 - turn_];
    }

    ShotResult Game::step(const Position& pos) {
        ShotResult result = current().make_shot(opponent(), pos);
        if (result == ShotResult::Miss) {
            turn_ = 1 - turn_;
        }
        return result;
    }

    bool Game::is_over() const noexcept {
        return players_[0]->lost() || players_[1]->lost();
    }

    Player* Game::winner() noexcept {
        if (!is_over()) return nullptr;
        return players_[0]->lost() ? players_[1] : players_[0];
    }

} 