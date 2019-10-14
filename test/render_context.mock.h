#include "render_context.h"
#include <gmock/gmock.h>

class MockRenderContext : public SwearJar::RenderContext {
public:
    MockRenderContext(SwearJar::CursesInterface& curses)
        : RenderContext(curses, 0) {
    }
    MOCK_METHOD0(beginRender, void());
    MOCK_METHOD0(endRender, void());
    MOCK_CONST_METHOD1(reverse, void(bool));
    MOCK_CONST_METHOD1(blink, void(bool));
    MOCK_CONST_METHOD6(clearArea, void(unsigned int, unsigned int, unsigned int,
                                       unsigned int, short, short));
    MOCK_CONST_METHOD5(drawText, void(unsigned int, unsigned int,
                                      const std::string&, short, short));
    MOCK_CONST_METHOD5(drawText, void(unsigned int, unsigned int,
                                      const std::wstring&, short, short));
    MOCK_CONST_METHOD3(drawChar, void(unsigned int, unsigned int, char));
    MOCK_CONST_METHOD3(drawChar, void(unsigned int, unsigned int, wchar_t));
    MOCK_CONST_METHOD5(drawChar,
                       void(unsigned int, unsigned int, char, short, short));
    MOCK_CONST_METHOD5(drawChar,
                       void(unsigned int, unsigned int, wchar_t, short, short));
    MOCK_CONST_METHOD6(drawBorder,
                       void(unsigned int, unsigned int, unsigned int,
                            unsigned int, short, short));
    MOCK_METHOD(void, addOffsets, (unsigned int x, unsigned int y),
                (const, override));
    MOCK_METHOD(void, clearOffsets, (unsigned int x, unsigned int y),
                (const, override));
};
