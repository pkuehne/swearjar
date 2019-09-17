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
    EXPECT_EQ(factor, layout.children()[0]->growthFactor());
}

TEST(LayoutWidget, spacerGrowsByDefault) {
    // Given
    SpacerWidget w;

    // Then
    EXPECT_NE(0, w.growthFactor());
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
    c2->y(0);
    base.addWidget(c2);

    auto c3 = std::make_shared<Widget>("");
    c3->minWidth(2);
    c3->height(8);
    c3->y(4);
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

TEST(LayoutWidget, renderOnlyRealignsWhenDirty) {
    // Given
    auto context = std::make_unique<MockRenderContext>();
    context->width(80);
    context->height(25);

    LayoutWidget base("");
    base.width(80);
    base.height(25);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(4);
    c1->width(4);
    c1->growthFactor(1);
    c1->dirty(false);
    base.addWidget(c1);

    // When
    base.render(context.get());

    // Then
    EXPECT_EQ(c1->width(), c1->minWidth());
}

TEST(LayoutWidget, realignSetsXvalueWithMargin) {
    // Given
    LayoutWidget base("");
    base.width(20);
    base.margin(1);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(4);
    base.addWidget(c1);

    auto c2 = std::make_shared<Widget>("");
    c2->minWidth(5);
    c2->growthFactor(1);
    base.addWidget(c2);

    // When
    base.realign();

    // Then
    EXPECT_EQ(1, c1->x());
    EXPECT_EQ(4, c1->width());
    EXPECT_EQ(5, c2->x());
    EXPECT_EQ(14, c2->width());
}

TEST(LayoutWidget, realignSetsFullHeightWithMargin) {
    // Given
    unsigned int margin = 2;

    LayoutWidget base("");
    base.width(20);
    base.height(10);
    base.margin(margin);
    base.alignment(LayoutWidget::Alignment::Horizontal);

    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(2);
    c1->height(5);
    c1->y(2);
    base.addWidget(c1);

    auto c2 = std::make_shared<Widget>("");
    c2->minWidth(2);
    c2->height(1);
    c2->y(0);
    base.addWidget(c2);

    auto c3 = std::make_shared<Widget>("");
    c3->minWidth(2);
    c3->height(8);
    c3->y(4);
    base.addWidget(c3);

    // When
    base.realign();

    // Then
    EXPECT_EQ(base.height() - (margin * 2), c1->height());
    EXPECT_EQ(base.height() - (margin * 2), c2->height());
    EXPECT_EQ(base.height() - (margin * 2), c3->height());

    EXPECT_EQ(margin, c1->y());
    EXPECT_EQ(margin, c2->y());
    EXPECT_EQ(margin, c3->y());
}
