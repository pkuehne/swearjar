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

TEST(LayoutWidget, spacerGrowsByDefault) {
    // Given
    SpacerWidget w;

    // Then
    EXPECT_EQ(1, w.growthFactor());
}

TEST(LayoutWidget, realignAllocatesWidthOnlyToGrowingWidgets) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(4);
    base.addWidget(c1);

    auto c2 = std::make_shared<Widget>("");
    c2->minWidth(5);
    c2->growthFactor(1);
    base.addWidget(c2);

    auto c3 = std::make_shared<Widget>("");
    c3->minWidth(5);
    c3->growthFactor(1);
    base.addWidget(c3);

    // When
    base.realign();

    // Then
    EXPECT_EQ(4, c1->width());
    EXPECT_EQ(8, c2->width());
    EXPECT_EQ(8, c3->width());
}

TEST(LayoutWidget, realignAllocatesGrowingWidgetsProportionally) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(4);
    base.addWidget(c1);

    auto c2 = std::make_shared<Widget>("");
    c2->minWidth(2);
    c2->growthFactor(1);
    base.addWidget(c2);

    auto c3 = std::make_shared<Widget>("");
    c3->minWidth(2);
    c3->growthFactor(2);
    base.addWidget(c3);

    // When
    base.realign();


    // Then
    EXPECT_EQ(4, c1->width());
    EXPECT_EQ(6, c2->width());
    EXPECT_EQ(10, c3->width());
}

TEST(LayoutWidget, realignAllocatesWidthToFirstWidgetIfNoneExpand) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(2);
    base.addWidget(c1);

    auto c2 = std::make_shared<Widget>("");
    c2->minWidth(2);
    base.addWidget(c2);

    auto c3 = std::make_shared<Widget>("");
    c3->minWidth(2);
    base.addWidget(c3);

    // When
    base.realign();


    // Then
    EXPECT_EQ(16, c1->width());
    EXPECT_EQ(2, c2->width());
    EXPECT_EQ(2, c3->width());
}

TEST(LayoutWidget, realignSetsFullHeightForAllWidgets) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.height(10);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(2);
    c1->height(5);
    c1->y(2);
    base.addWidget(c1);

    auto c2 = std::make_shared<Widget>("");
    c2->minWidth(2);
    c2->height(1);
    c1->y(0);
    base.addWidget(c2);

    auto c3 = std::make_shared<Widget>("");
    c3->minWidth(2);
    c3->height(8);
    c1->y(4);
    base.addWidget(c3);

    // When
    base.realign();

    // Then
    EXPECT_EQ(base.height(), c1->height());
    EXPECT_EQ(base.height(), c2->height());
    EXPECT_EQ(base.height(), c3->height());

    EXPECT_EQ(0, c1->y());
    EXPECT_EQ(0, c2->y());
    EXPECT_EQ(0, c3->y());
}

TEST(LayoutWidget, realignSetsXvalueOnWidgets) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(4);
    base.addWidget(c1);

    auto c2 = std::make_shared<Widget>("");
    c2->minWidth(5);
    c2->growthFactor(1);
    base.addWidget(c2);

    auto c3 = std::make_shared<Widget>("");
    c3->minWidth(5);
    c3->growthFactor(1);
    base.addWidget(c3);

    // When
    base.realign();

    // Then
    EXPECT_EQ(0, c1->x());
    EXPECT_EQ(4, c2->x());
    EXPECT_EQ(12, c3->x());
}

