#include "widget.h"
#include <gtest/gtest.h>

TEST(Widget, initializesDirtyToTrue) {
    using namespace SwearJar;

    Widget w;
    EXPECT_TRUE(w.dirty());
}