#include <gtest/gtest.h>
#include "position.h"

using namespace seabattle;

TEST(Position, Creation) {
    Position p(3, 4);
    EXPECT_EQ(p.x(), 3);
    EXPECT_EQ(p.y(), 4);
}

TEST(Position, OutOfBounds) {
    EXPECT_THROW(Position(-1, 0), std::out_of_range);
    EXPECT_THROW(Position(10, 0), std::out_of_range);
    EXPECT_THROW(Position(0, 10), std::out_of_range);
}

TEST(Position, Equality) {
    EXPECT_EQ(Position(1, 2), Position(1, 2));
    EXPECT_NE(Position(1, 2), Position(2, 1));
}

TEST(Position, ToString) {
    EXPECT_EQ(Position(1, 2).to_string(), "(1, 2)");
}