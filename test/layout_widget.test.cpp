#include "layout_widget.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

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

TEST(LayoutWidget, addingSpacerCanSetGrowthFactor) {
    // Given
    LayoutWidget layout("layout");
    unsigned int factor = 5;

    // When
    layout.addSpacer(factor);

    // Then
    SpacerWidget* spacer =
        dynamic_cast<SpacerWidget*>(layout.children()[0].get());
    EXPECT_EQ(factor, spacer->growthFactor());
}

TEST(LayoutWidget, spacerGrowsByDefault) {
    // Given
    SpacerWidget w("");

    // Then
    EXPECT_NE(0, w.growthFactor());
}

TEST(LayoutWidget, realignDoesNothingIfRequiredWidthIsBiggerThanWidth) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(14);
    auto defaultWidth = c1.width();

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(15);
    c2.growthFactor(1);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(15);
    c3.growthFactor(1);

    // When
    base.realign();

    // Then
    EXPECT_EQ(defaultWidth, c1.width());
    EXPECT_EQ(defaultWidth, c2.width());
    EXPECT_EQ(defaultWidth, c3.width());
}

TEST(LayoutWidget, realignDoesNothingIfRequiredHeightIsBiggerThanHeight) {
    // Given
    LayoutWidget base("");
    base.height(20);
    base.alignment(LayoutWidget::Alignment::Vertical);

    auto& c1 = base.createWidget<Widget>("");
    c1.minHeight(14);
    auto defaultHeight = c1.width();

    auto& c2 = base.createWidget<Widget>("");
    c2.minHeight(15);
    c2.growthFactor(1);

    auto& c3 = base.createWidget<Widget>("");
    c3.minHeight(15);
    c3.growthFactor(1);

    // When
    base.realign();

    // Then
    EXPECT_EQ(defaultHeight, c1.height());
    EXPECT_EQ(defaultHeight, c2.height());
    EXPECT_EQ(defaultHeight, c3.height());
}

TEST(LayoutWidget, realignAllocatesWidthOnlyToGrowingWidgets) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(4);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(5);
    c2.growthFactor(1);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(5);
    c3.growthFactor(1);

    // When
    base.realign();

    // Then
    EXPECT_EQ(4, c1.width());
    EXPECT_EQ(8, c2.width());
    EXPECT_EQ(8, c3.width());
}

TEST(LayoutWidget, realignAllocatesGrowingWidgetsProportionally) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(4);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(2);
    c2.growthFactor(1);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(2);
    c3.growthFactor(2);

    // When
    base.realign();

    // Then
    EXPECT_EQ(4, c1.width());
    EXPECT_EQ(6, c2.width());
    EXPECT_EQ(10, c3.width());
}

TEST(LayoutWidget, realignAllocatesWidthToFirstWidgetIfNoneExpand) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(2);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(2);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(2);

    // When
    base.realign();

    // Then
    EXPECT_EQ(16, c1.width());
    EXPECT_EQ(2, c2.width());
    EXPECT_EQ(2, c3.width());
}

TEST(LayoutWidget, realignSetsFullHeightForAllWidgets) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.height(10);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(2);
    c1.height(5);
    c1.y(2);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(2);
    c2.height(1);
    c2.y(0);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(2);
    c3.height(8);
    c3.y(4);

    // When
    base.realign();

    // Then
    EXPECT_EQ(base.height(), c1.height());
    EXPECT_EQ(base.height(), c2.height());
    EXPECT_EQ(base.height(), c3.height());

    EXPECT_EQ(0, c1.y());
    EXPECT_EQ(0, c2.y());
    EXPECT_EQ(0, c3.y());
}

TEST(LayoutWidget, realignSetsXvalueOnWidgets) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(4);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(5);
    c2.growthFactor(1);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(5);
    c3.growthFactor(1);

    // When
    base.realign();

    // Then
    EXPECT_EQ(0, c1.x());
    EXPECT_EQ(4, c2.x());
    EXPECT_EQ(12, c3.x());
}

TEST(LayoutWidget, realignSetsXvalueWithMargin) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.margin(1);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(4);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(5);
    c2.growthFactor(1);

    // When
    base.realign();

    // Then
    EXPECT_EQ(1, c1.x());
    EXPECT_EQ(4, c1.width());
    EXPECT_EQ(5, c2.x());
    EXPECT_EQ(14, c2.width());
}

TEST(LayoutWidget, realignSetsFullHeightWithMargin) {
    // Given
    unsigned int margin = 2;

    LayoutWidget base("");
    base.width(20);
    base.height(10);
    base.margin(margin);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(2);
    c1.height(5);
    c1.y(2);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(2);
    c2.height(1);
    c2.y(0);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(2);
    c3.height(8);
    c3.y(4);

    // When
    base.realign();

    // Then
    EXPECT_EQ(base.height() - (margin * 2), c1.height());
    EXPECT_EQ(base.height() - (margin * 2), c2.height());
    EXPECT_EQ(base.height() - (margin * 2), c3.height());

    EXPECT_EQ(margin, c1.y());
    EXPECT_EQ(margin, c2.y());
    EXPECT_EQ(margin, c3.y());
}

TEST(LayoutWidget, requiredHeightUsesParentClassWhenVertical) {
    // Given
    LayoutWidget base("");
    base.alignment(LayoutWidget::Alignment::Vertical);

    auto& c1 = base.createWidget<Widget>("");
    c1.minHeight(2);

    auto& c2 = base.createWidget<Widget>("");
    c2.minHeight(3);

    auto& c3 = base.createWidget<Widget>("");
    c3.minHeight(5);

    // When
    auto height = base.requiredHeight();
    auto superHeight = base.LayoutWidget::requiredHeight();

    EXPECT_EQ(height, superHeight);
    EXPECT_GT(height, 5);
}

TEST(LayoutWidget, requiredHeightCalculatesMaxHeightWhenHorizontal) {
    // Given
    LayoutWidget base("");
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minHeight(2);

    auto& c2 = base.createWidget<Widget>("");
    c2.minHeight(3);

    auto& c3 = base.createWidget<Widget>("");
    c3.minHeight(5);

    // When
    auto height = base.requiredHeight();

    EXPECT_EQ(height, c3.requiredHeight());
}

TEST(LayoutWidget, requiredWidthUsesParentClassWhenHorizontal) {
    // Given
    LayoutWidget base("");
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(2);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(3);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(5);

    // When
    auto width = base.requiredWidth();
    auto superWidth = base.LayoutWidget::requiredWidth();

    EXPECT_EQ(width, superWidth);
    EXPECT_GT(width, 5);
}

TEST(LayoutWidget, requiredWidthCalculatesMaxWidthWhenVertical) {
    // Given
    LayoutWidget base("");
    base.alignment(LayoutWidget::Alignment::Vertical);

    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(2);

    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(3);

    auto& c3 = base.createWidget<Widget>("");
    c3.minWidth(5);

    // When
    auto width = base.requiredWidth();

    EXPECT_EQ(width, c3.requiredWidth());
}
