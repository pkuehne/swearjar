#include "render_context.h"
#include <gmock/gmock.h>

class MockRenderContext : public SwearJar::RenderContext {
public:
    MockRenderContext(SwearJar::CursesInterface& curses)
        : RenderContext(curses, 0) {
    }
    MOCK_METHOD(void, beginRender, (), (override));
    MOCK_METHOD(void, endRender, (), (override));
    MOCK_METHOD(void, reverse, (bool), (override, const));
    MOCK_METHOD(void, blink, (bool), (override, const));
    MOCK_METHOD(void, clearArea,
                (unsigned int, unsigned int, unsigned int, unsigned int, short,
                 short),
                (override, const));
    MOCK_METHOD(void, drawText,
                (unsigned int, unsigned int, const std::string&, short, short),
                (override, const));
    MOCK_METHOD(void, drawText,
                (unsigned int, unsigned int, const std::wstring&, short, short),
                (override, const));
    MOCK_METHOD(void, drawChar, (unsigned int, unsigned int, char),
                (override, const));
    MOCK_METHOD(void, drawChar, (unsigned int, unsigned int, wchar_t),
                (override, const));
    MOCK_METHOD(void, drawChar,
                (unsigned int, unsigned int, char, short, short),
                (override, const));
    MOCK_METHOD(void, drawChar,
                (unsigned int, unsigned int, wchar_t, short, short),
                (override, const));
    MOCK_METHOD(void, drawBorder,
                (unsigned int, unsigned int, unsigned int, unsigned int, short,
                 short),
                (override, const));
    MOCK_METHOD(void, addOffsets, (unsigned int x, unsigned int y),
                (const, override));
    MOCK_METHOD(void, clearOffsets, (unsigned int x, unsigned int y),
                (const, override));
};
