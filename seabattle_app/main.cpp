#include <windows.h>
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
            } catch (const std::exception&) {
            }
        }
    }
}

void print_shot_result(ShotResult r) {
    switch (r) {
        case ShotResult::Miss: std::cout << "Мимо!\n"; break;
        case ShotResult::Hit:  std::cout << "Попал!\n"; break;
        case ShotResult::Kill: std::cout << "Убил!\n"; break;
    }
}

} 

int main() {
    SetConsoleOutputCP(65001);

    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

    Player human("Игрок");
    Player computer("Компьютер");

    place_ships_randomly(human, rng);
    place_ships_randomly(computer, rng);

    Game game(human, computer);

    std::cout << "=== Морской бой ===\n";
    std::cout << "Поле 10x10, координаты 0..9.\n";
    std::cout << "Введите координаты выстрела: x y\n\n";

    std::uniform_int_distribution<int> dist(0, GameField::SIZE - 1);

    while (!game.is_over()) {
        if (&game.current() == &human) {
            std::cout << "\n[Ваш ход]\n";

            int x, y;
            if (!(std::cin >> x >> y)) {
                std::cout << "Некорректный ввод. Попробуйте снова.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            try {
                Position pos(x, y);
                ShotResult r = game.step(pos);
                print_shot_result(r);
            } catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
        } else {
            std::cout << "\n[Ход компьютера]\n";

            for (int attempt = 0; attempt < 500; ++attempt) {
                try {
                    Position pos(dist(rng), dist(rng));
                    ShotResult r = game.step(pos);
                    print_shot_result(r);
                    break;
                } catch (const std::exception&) {
                }
            }
        }
    }

    std::cout << "\n=== Игра окончена ===\n";
    std::cout << "Победитель: " << game.winner()->name() << "\n";

    return 0;
}
