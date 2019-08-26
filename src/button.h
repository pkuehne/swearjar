#pragma once

#include "widget.h"

namespace SwearJar {
class Button : public Widget {
public:
    Button();
    explicit Button(const std::string& text);
    virtual void text(const std::string& text);
    virtual const std::string& text() { return m_text; }

    std::function<void(Button*)> pressed;

protected:
    void refresh(const RenderContext& render) override;
    bool handleKeyPress(int ch) override;

private:
    std::string m_text;
};
} // namespace SwearJar
