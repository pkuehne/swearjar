#pragma once

#include "layout_widget.h"

namespace SwearJar {

class Frame : public LayoutWidget {
public:
    explicit Frame(const std::string& name);
    void title(const std::wstring& title);
    std::wstring title() {
        return m_title;
    }

    unsigned int minWidth() override;

    void render(const RenderContext& context) override;

private:
    std::wstring m_title;
};

} // namespace SwearJar
