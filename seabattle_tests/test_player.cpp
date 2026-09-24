#include <gtest/gtest.h>
#include "player.h"

using namespace seabattle;

namespace {

    Ship make_ship(std::initializer_list<Position> cells) {
        return Ship(std::vector<Position>(cells));
    }

} // namespace

TEST(Player, Creation) {
    Player p("Alice");
    EXPECT_EQ(p.name(), "Alice");
    EXPECT_FALSE(p.lost());
}

TEST(Player, EmptyNameThrows) {
    EXPECT_THROW(Player(""), std::invalid_argument);
}

TEST(Player, MakeShotMiss) {
    Player a("A");
    Player b("B");
    b.field().add_ship(make_ship({ Position(0, 0) }));

    EXPECT_EQ(a.make_shot(b, Position(5, 5)), ShotResult::Miss);
    EXPECT_FALSE(b.lost());
}

TEST(Player, MakeShotHit) {
    Player a("A");
    Player b("B");
    b.field().add_ship(make_ship({ Position(0, 0), Position(1, 0) }));

    EXPECT_EQ(a.make_shot(b, Position(0, 0)), ShotResult::Hit);
    EXPECT_FALSE(b.lost());
}

TEST(Player, MakeShotKill) {
    Player a("A");
    Player b("B");
    b.field().add_ship(make_ship({ Position(0, 0) }));

    EXPECT_EQ(a.make_shot(b, Position(0, 0)), ShotResult::Kill);
    EXPECT_TRUE(b.lost());
}

TEST(Player, LostAfterAllShipsDead) {
    Player a("A");
    Player b("B");
    b.field().add_ship(make_ship({ Position(0, 0) }));
    b.field().add_ship(make_ship({ Position(5, 5), Position(5, 6) }));

    EXPECT_FALSE(b.lost());
    a.make_shot(b, Position(0, 0));
    EXPECT_FALSE(b.lost());
    a.make_shot(b, Position(5, 5));
    EXPECT_FALSE(b.lost());
    a.make_shot(b, Position(5, 6));
    EXPECT_TRUE(b.lost());
}