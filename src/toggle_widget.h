#pragma once

#include "widget.h"
#include <functional>

namespace SwearJar {

class ToggleWidget : public Widget {
public:
    explicit ToggleWidget(const std::string& name);

    void text(const std::wstring& text);
    void text(const std::string& text);
    std::wstring text();

    virtual void enabled(bool enabled) = 0;
    virtual bool enabled() = 0;
    // Returns true if state actually changed.
    virtual bool toggle() = 0;

    bool handleKeyPress(const KeyEvent& event) override;
    bool handleMouseClick(const MouseEvent& event) override;

    std::function<void(ToggleWidget&)> onToggle;

protected:
    std::wstring m_text;
};

} // namespace SwearJar
