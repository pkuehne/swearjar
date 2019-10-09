#include "curses.mock.h"
#include "label.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

class LabelWidget : public Test {
public:
    void SetUp() {
        EXPECT_CALL(*context, clearArea(_, _, _, _, _, _)).Times(AnyNumber());
    }

protected:
    Label label{"testLabel"};
    std::shared_ptr<MockCurses> curses{
        std::make_shared<::testing::NiceMock<MockCurses>>()};
    std::unique_ptr<MockRenderContext> context{
        std::make_unique<MockRenderContext>(*curses)};
};

TEST_F(LabelWidget, settingTextAlsoSetsTheMinWidth) {
    // Given
    EXPECT_EQ(1, label.minWidth());

    // When
    label.text(L"Foo");

    // Then
    EXPECT_EQ(3, label.minWidth());
    EXPECT_EQ(L"Foo", label.text());
}

TEST_F(LabelWidget, uncentredTextRendersAtXZero) {
    // Given
    label.text(L"A");
    label.width(11);

    EXPECT_CALL(
        *context,
        drawText(0, _, TypedEq<const std::wstring&>(label.text()), _, _))
        .Times(1);

    // WHen
    label.render(*context);

    // Then
}

TEST_F(LabelWidget, centredTextRendersInTheMiddleOfWidth) {
    // Given
    label.text(L"A");
    label.width(11);
    label.centred(true);

    EXPECT_CALL(
        *context,
        drawText(5, _, TypedEq<const std::wstring&>(label.text()), _, _))
        .Times(1);

    // WHen
    label.render(*context);

    // Then
}
