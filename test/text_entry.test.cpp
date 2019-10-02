#include "curses.mock.h"
#include "render_context.mock.h"
#include "text_entry.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;
using namespace ::testing;

class TextEntryWidget : public Test {
public:
    void SetUp() {
    }

protected:
};

TEST_F(TextEntryWidget, fail) {
    TextEntry t("test");
    FAIL() << "Not implemented";
}
