#pragma once

#include "widget.h"

namespace SwearJar {
class Button : public Widget {
public:
    explicit Button(const std::string& name);
    virtual void text(const std::string& text);
    virtual const std::string& text() { return m_text; }

    std::function<void(Button*)> pressed;

    void render(const RenderContextP& context) override;
    bool handleKeyPress(int ch) override;

private:
    std::string m_text;
};
} // namespace SwearJar
