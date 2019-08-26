#include <gtest/gtest.h>
#include "layout_widget.h"

using namespace ::testing;
using namespace SwearJar;

TEST(LayoutWidget, addingSpacerAddsAnotherWidget) {
    // Given
    LayoutWidget layout("layout");

    // When
    layout.addSpacer();

    // Then
    EXPECT_EQ(1, layout.children().size());
}
