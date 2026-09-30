#include "ship.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace seabattle {

    Ship::Ship(std::vector<Position> positions)
        : positions_(std::move(positions)),
        hits_(positions_.size(), false) {
        if (positions_.empty()) {
            throw std::invalid_argument("Ship must have at least one position");
        }

        for (std::size_t i = 0; i < positions_.size(); ++i) {
            for (std::size_t j = i + 1; j < positions_.size(); ++j) {
                if (positions_[i] == positions_[j]) {
                    throw std::invalid_argument("Ship has duplicate positions");
                }
            }
        }

        bool same_x = true;
        bool same_y = true;
        for (const auto& p : positions_) {
            if (p.x() != positions_[0].x()) same_x = false;
            if (p.y() != positions_[0].y()) same_y = false;
        }
        if (!same_x && !same_y) {
            throw std::invalid_argument("Ship must be straight");
        }
    }

    bool Ship::is_alive() const noexcept {
        return std::find(hits_.begin(), hits_.end(), false) != hits_.end();
    }

    bool Ship::occupies(const Position& pos) const noexcept {
        return std::find(positions_.begin(), positions_.end(), pos) != positions_.end();
    }

    ShotResult Ship::take_hit(const Position& pos) {
        for (std::size_t i = 0; i < positions_.size(); ++i) {
            if (positions_[i] == pos) {
                hits_[i] = true;
                return is_alive() ? ShotResult::Hit : ShotResult::Kill;
            }
        }
        return ShotResult::Miss;
    }

} 