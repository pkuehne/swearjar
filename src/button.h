#pragma once

#include "widget.h"

namespace SwearJar {
class Button : public Widget {
public:
    explicit Button(const std::string& text);
    virtual void text(const std::string& text);
    virtual const std::string& text() { return m_text; }

    std::function<void(Button*)> pressed;

protected:
    void refresh(const RenderContext& render);
    bool handleKeyPress(int ch);

private:
    std::string m_text;
};
} // namespace SwearJar
