#pragma once

#include "layout_widget.h"

namespace SwearJar {

class Frame : public LayoutWidget {
public:
    explicit Frame(const std::string& name);
    void title(const std::string& title) { m_title = title; }
    std::string title() { return m_title; }

    // Overriden Widget functions
    void addWidget(WidgetP widget, unsigned int x, unsigned int y);
    void render(const RenderContextP& context) override;

private:
    std::string m_title;
};

} // namespace SwearJar
