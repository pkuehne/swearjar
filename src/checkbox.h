#pragma once

#include "toggle_widget.h"

namespace SwearJar {

class Checkbox : public ToggleWidget {
public:
    explicit Checkbox(const std::string& name);

    void render(const RenderContext& context) override;

    void enabled(bool enabled) override;
    bool enabled() override;
    bool toggle() override;

private:
    bool m_enabled = false;
};

} // namespace SwearJar
