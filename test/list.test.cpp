#include "list.h"
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

TEST(List, addItemIncreasesItemList) {
    // Given
    List list("lstTest");

    // When
    list.addItem("item1");

    // Then
    EXPECT_EQ(1, list.items().size());
}
