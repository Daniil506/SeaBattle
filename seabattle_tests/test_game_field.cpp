#include <gtest/gtest.h>
#include "game_field.h"

using namespace seabattle;

namespace {

    Ship make_ship(std::initializer_list<Position> cells) {
        return Ship(std::vector<Position>(cells));
    }

} // namespace

TEST(GameField, EmptyInitially) {
    GameField f;
    EXPECT_TRUE(f.ships().empty());
    EXPECT_TRUE(f.shots().empty());
    EXPECT_FALSE(f.all_ships_dead());
}

TEST(GameField, AddShipOk) {
    GameField f;
    f.add_ship(make_ship({ Position(0, 0), Position(1, 0) }));
    EXPECT_EQ(f.ships().size(), 1u);
}

TEST(GameField, ShipsCannotTouch) {
    GameField f;
    f.add_ship(make_ship({ Position(0, 0), Position(1, 0) }));
    // §Ü§Ñ§ã§Ñ§Ö§ä§ã§ñ §å§Ô§Ý§à§Þ §Ü§Ý§Ö§ä§Ü§Ú (2,1)
    EXPECT_THROW(
        f.add_ship(make_ship({ Position(2, 1), Position(3, 1) })),
        std::invalid_argument);
}

TEST(GameField, ShipsCanBeApart) {
    GameField f;
    f.add_ship(make_ship({ Position(0, 0), Position(1, 0) }));
    f.add_ship(make_ship({ Position(5, 5), Position(5, 6) }));
    EXPECT_EQ(f.ships().size(), 2u);
}

TEST(GameField, ShotMiss) {
    GameField f;
    f.add_ship(make_ship({ Position(0, 0) }));
    EXPECT_EQ(f.receive_shot(Position(5, 5)), ShotResult::Miss);
    EXPECT_EQ(f.shots().size(), 1u);
}

TEST(GameField, ShotHitAndKill) {
    GameField f;
    f.add_ship(make_ship({ Position(0, 0), Position(1, 0) }));
    EXPECT_EQ(f.receive_shot(Position(0, 0)), ShotResult::Hit);
    EXPECT_FALSE(f.all_ships_dead());
    EXPECT_EQ(f.receive_shot(Position(1, 0)), ShotResult::Kill);
    EXPECT_TRUE(f.all_ships_dead());
}

TEST(GameField, CannotShootTwice) {
    GameField f;
    f.add_ship(make_ship({ Position(0, 0) }));
    f.receive_shot(Position(5, 5));
    EXPECT_THROW(f.receive_shot(Position(5, 5)), std::invalid_argument);
}

TEST(GameField, AlreadyShot) {
    GameField f;
    EXPECT_FALSE(f.already_shot(Position(3, 3)));
    f.receive_shot(Position(3, 3));
    EXPECT_TRUE(f.already_shot(Position(3, 3)));
}

TEST(GameField, AllShipsDead) {
    GameField f;
    f.add_ship(make_ship({ Position(0, 0) }));
    f.add_ship(make_ship({ Position(5, 5), Position(5, 6) }));
    EXPECT_FALSE(f.all_ships_dead());

    f.receive_shot(Position(0, 0));
    EXPECT_FALSE(f.all_ships_dead());

    f.receive_shot(Position(5, 5));
    f.receive_shot(Position(5, 6));
    EXPECT_TRUE(f.all_ships_dead());
}