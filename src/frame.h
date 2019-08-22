#pragma once

#include "widget.h"

namespace SwearJar {

class Frame : public Widget {
public:
    void refresh(const RenderContext& render);
};

} // namespace SwearJar
