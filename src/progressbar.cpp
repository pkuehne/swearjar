#include "progressbar.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

void Progressbar::value(unsigned int value) {
    if (value > m_maximum) {
        value = m_maximum;
    }
    m_value = value;
    invalidate();
}

void Progressbar::maximum(unsigned int maximum) {
    m_maximum = maximum;
    invalidate();
}

void Progressbar::decrement() {
    if (value() == 0) {
        return;
    }
    value(value() - 1);
}
void Progressbar::refresh(const RenderContext& context) {
    if (m_value > m_maximum) {
        m_value = m_maximum;
    }

    float percent = static_cast<float>(m_value) / m_maximum;

    for (int ii = 0; ii < width() * percent; ii++) {
        context.drawChar(ii, 0, '=', fgColor(), bgColor());
    }
}

} // namespace SwearJar
