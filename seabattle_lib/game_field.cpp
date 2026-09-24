#include "game_field.h"

#include <algorithm>
#include <cstdlib>
#include <stdexcept>

namespace seabattle {

    void GameField::add_ship(Ship ship) {
        for (const auto& existing : ships_) {
            for (const auto& ep : existing.positions()) {
                for (const auto& np : ship.positions()) {
                    if (std::abs(ep.x() - np.x()) <= 1 &&
                        std::abs(ep.y() - np.y()) <= 1) {
                        throw std::invalid_argument("Ships cannot touch each other");
                    }
                }
            }
        }
        ships_.push_back(std::move(ship));
    }

    bool GameField::already_shot(const Position& pos) const noexcept {
        return std::find(shots_.begin(), shots_.end(), pos) != shots_.end();
    }

    ShotResult GameField::receive_shot(const Position& pos) {
        if (already_shot(pos)) {
            throw std::invalid_argument("Already shot at this position");
        }
        shots_.push_back(pos);

        for (auto& ship : ships_) {
            if (ship.occupies(pos)) {
                return ship.take_hit(pos);
            }
        }
        return ShotResult::Miss;
    }

    bool GameField::all_ships_dead() const noexcept {
        if (ships_.empty()) return false;
        return std::all_of(ships_.begin(), ships_.end(),
            [](const Ship& s) { return !s.is_alive(); });
    }

} 