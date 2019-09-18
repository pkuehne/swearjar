#pragma once

#include "layout_widget.h"

namespace SwearJar {

class Frame : public LayoutWidget {
public:
    explicit Frame(const std::string& name);
    void title(const std::string& title);
    std::string title() { return m_title; }

    // Overriden Widget functions
    void render(const RenderContext& context) override;

private:
    std::string m_title;
};

} // namespace SwearJar
