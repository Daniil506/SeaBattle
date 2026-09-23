#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "game.h"
#include "player.h"
#include "position.h"
#include "ship.h"

using namespace seabattle;

namespace {

    void place_ships_randomly(Player& player, std::mt19937& rng) {
        const int fleet[4][2] = {
            {4, 1},
            {3, 2},
            {2, 3},
            {1, 4}
        };

        std::uniform_int_distribution<int> dist(0, GameField::SIZE - 1);
        std::uniform_int_distribution<int> dir(0, 1);

        for (const auto& entry : fleet) {
            const int size = entry[0];
            const int count = entry[1];

            for (int placed = 0; placed < count; ) {
                const bool horizontal = (dir(rng) == 0);
                const int x = dist(rng);
                const int y = dist(rng);

                std::vector<Position> cells;
                bool ok = true;
                for (int i = 0; i < size; ++i) {
                    const int cx = x + (horizontal ? i : 0);
                    const int cy = y + (horizontal ? 0 : i);
                    if (cx < 0 || cx >= GameField::SIZE ||
                        cy < 0 || cy >= GameField::SIZE) {
                        ok = false;
                        break;
                    }
                    cells.emplace_back(cx, cy);
                }
                if (!ok) continue;

                try {
                    player.field().add_ship(Ship(cells));
                    ++placed;
                }
                catch (const std::exception&) {
                }
            }
        }
    }

    void print_shot_result(ShotResult r) {
        switch (r) {
        case ShotResult::Miss: std::cout << "§®§Ú§Þ§à!\n";  break;
        case ShotResult::Hit:  std::cout << "§±§à§á§Ñ§Ý!\n"; break;
        case ShotResult::Kill: std::cout << "§µ§Ò§Ú§Ý!\n";  break;
        }
    }

} // namespace

int main() {
    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

    Player human("§ª§Ô§â§à§Ü");
    Player computer("§¬§à§Þ§á§î§ð§ä§Ö§â");

    place_ships_randomly(human, rng);
    place_ships_randomly(computer, rng);

    Game game(human, computer);

    std::cout << "=== §®§à§â§ã§Ü§à§Û §Ò§à§Û ===\n";
    std::cout << "§±§à§Ý§Ö 10x10, §Ü§à§à§â§Õ§Ú§ß§Ñ§ä§í 0..9.\n";
    std::cout << "§£§Ó§Ö§Õ§Ú§ä§Ö §Ü§à§à§â§Õ§Ú§ß§Ñ§ä§í §Ó§í§ã§ä§â§Ö§Ý§Ñ: x y\n\n";

    std::uniform_int_distribution<int> dist(0, GameField::SIZE - 1);

    while (!game.is_over()) {
        if (&game.current() == &human) {
            std::cout << "\n[§£§Ñ§ê §ç§à§Õ]\n";

            int x, y;
            if (!(std::cin >> x >> y)) {
                std::cout << "§¯§Ö§Ü§à§â§â§Ö§Ü§ä§ß§í§Û §Ó§Ó§à§Õ. §±§à§á§â§à§Ò§å§Û§ä§Ö §ã§ß§à§Ó§Ñ.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            try {
                Position pos(x, y);
                ShotResult r = game.step(pos);
                print_shot_result(r);
            }
            catch (const std::exception& e) {
                std::cout << "§°§ê§Ú§Ò§Ü§Ñ: " << e.what() << "\n";
            }
        }
        else {
            std::cout << "\n[§·§à§Õ §Ü§à§Þ§á§î§ð§ä§Ö§â§Ñ]\n";

            for (int attempt = 0; attempt < 500; ++attempt) {
                try {
                    Position pos(dist(rng), dist(rng));
                    ShotResult r = game.step(pos);
                    print_shot_result(r);
                    break;
                }
                catch (const std::exception&) {
                }
            }
        }
    }

    std::cout << "\n=== §ª§Ô§â§Ñ §à§Ü§à§ß§é§Ö§ß§Ñ ===\n";
    std::cout << "§±§à§Ò§Ö§Õ§Ú§ä§Ö§Ý§î: " << game.winner()->name() << "\n";

    return 0;
}