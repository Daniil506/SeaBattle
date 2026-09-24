#include <gtest/gtest.h>
#include "ship.h"

using namespace seabattle;

TEST(Ship, ValidHorizontal) {
    Ship s({ Position(0, 0), Position(1, 0), Position(2, 0) });
    EXPECT_EQ(s.size(), 3u);
    EXPECT_TRUE(s.is_alive());
}

TEST(Ship, ValidVertical) {
    Ship s({ Position(0, 0), Position(0, 1) });
    EXPECT_EQ(s.size(), 2u);
}

TEST(Ship, EmptyThrows) {
    EXPECT_THROW(Ship({}), std::invalid_argument);
}

TEST(Ship, DuplicateThrows) {
    EXPECT_THROW(
        Ship({ Position(0, 0), Position(0, 0) }),
        std::invalid_argument);
}

TEST(Ship, NotStraightThrows) {
    EXPECT_THROW(
        Ship({ Position(0, 0), Position(1, 1) }),
        std::invalid_argument);
}

TEST(Ship, Occupies) {
    Ship s({ Position(1, 1), Position(2, 1) });
    EXPECT_TRUE(s.occupies(Position(1, 1)));
    EXPECT_FALSE(s.occupies(Position(3, 1)));
}

TEST(Ship, Miss) {
    Ship s({ Position(0, 0) });
    EXPECT_EQ(s.take_hit(Position(5, 5)), ShotResult::Miss);
    EXPECT_TRUE(s.is_alive());
}

TEST(Ship, HitAndKill) {
    Ship s({ Position(0, 0), Position(1, 0) });
    EXPECT_EQ(s.take_hit(Position(0, 0)), ShotResult::Hit);
    EXPECT_TRUE(s.is_alive());
    EXPECT_EQ(s.take_hit(Position(1, 0)), ShotResult::Kill);
    EXPECT_FALSE(s.is_alive());
}