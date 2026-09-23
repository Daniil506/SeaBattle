#include <gtest/gtest.h>
#include "game.h"

using namespace seabattle;

namespace {

    Ship make_ship(std::initializer_list<Position> cells) {
        return Ship(std::vector<Position>(cells));
    }

    

} 

TEST(Game, InitialState) {
    Player a("A");
    Player b("B");
    Game g(a, b);
    EXPECT_EQ(&g.current(), &a);
    EXPECT_EQ(&g.opponent(), &b);
    EXPECT_FALSE(g.is_over());
    EXPECT_EQ(g.winner(), nullptr);
}

TEST(Game, SamePlayerThrows) {
    Player a("A");
    EXPECT_THROW(Game(a, a), std::invalid_argument);
}

TEST(Game, TurnSwitchesOnMiss) {
    Player a("A");
    Player b("B");
    b.field().add_ship(make_ship({ Position(0, 0) }));
    Game g(a, b);

    EXPECT_EQ(&g.current(), &a);
    EXPECT_EQ(g.step(Position(5, 5)), ShotResult::Miss);
    EXPECT_EQ(&g.current(), &b);
    EXPECT_EQ(&g.opponent(), &a);
}

TEST(Game, TurnDoesNotSwitchOnHit) {
    Player a("A");
    Player b("B");
    b.field().add_ship(make_ship({ Position(0, 0), Position(1, 0) }));
    Game g(a, b);

    EXPECT_EQ(g.step(Position(0, 0)), ShotResult::Hit);
    EXPECT_EQ(&g.current(), &a);
}

TEST(Game, TurnDoesNotSwitchOnKill) {
    Player a("A");
    Player b("B");
    b.field().add_ship(make_ship({ Position(0, 0) }));
    Game g(a, b);

    EXPECT_EQ(g.step(Position(0, 0)), ShotResult::Kill);
    EXPECT_EQ(&g.current(), &a);
}

TEST(Game, WinnerAfterAllShipsDead) {
    Player a("A");
    Player b("B");
    b.field().add_ship(make_ship({ Position(0, 0), Position(1, 0) }));
    Game g(a, b);

    EXPECT_FALSE(g.is_over());
    g.step(Position(0, 0));
    EXPECT_FALSE(g.is_over());
    g.step(Position(1, 0));
    EXPECT_TRUE(g.is_over());
    EXPECT_EQ(g.winner(), &a);
}

TEST(Game, LoserIsNotWinner) {
    Player a("A");
    Player b("B");
    a.field().add_ship(make_ship({ Position(0, 0) }));
    Game g(a, b);

    g.step(Position(5, 5));

    EXPECT_EQ(g.step(Position(0, 0)), ShotResult::Kill);
    EXPECT_TRUE(g.is_over());
    EXPECT_EQ(g.winner(), &b);
}