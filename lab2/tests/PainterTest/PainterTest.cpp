#include <gtest/gtest.h>
#include "../../classes/Painter/Painter.h"

TEST(PainterTest, Constructor) {
    Painter painter(1, "Alex Painter", 35000.0, 0.1);
    EXPECT_EQ(painter.getFullName(), "Alex Painter");
}

TEST(PainterTest, PaintingMethods) {
    Painter painter(1, "Alex Painter", 35000.0, 0.1);
    
    EXPECT_NO_THROW(painter.paintSurface());
    EXPECT_NO_THROW(painter.mixColors());
    EXPECT_NO_THROW(painter.calculatePaintRequired(100.0));
}

TEST(PainterTest, PerformWork) {
    Painter painter(1, "Alex Painter", 35000.0, 0.1);
    EXPECT_NO_THROW(painter.performWork());
}
