#include "progressbar.h"

namespace SwearJar {

void Progressbar::value(unsigned int value) {
    if (value > m_maximum) {
        value = m_maximum;
    }
    m_value = value;
}

unsigned int Progressbar::value() {
    return m_value;
}

void Progressbar::maximum(unsigned int maximum) {
    m_maximum = maximum;
}

unsigned int Progressbar::maximum() {
    return m_maximum;
}

void Progressbar::increment() {
    value(value() + 1);
}

void Progressbar::decrement() {
    if (value() == 0) {
        return;
    }
    value(value() - 1);
}

void Progressbar::render(const RenderContext& context) {
    if (m_value > m_maximum) {
        m_value = m_maximum;
    }

    float percent = static_cast<float>(m_value) / m_maximum;

    for (int ii = 0; ii < width() * percent; ii++) {
        context.drawChar(ii, 0, L'█', fgColor(), bgColor());
    }
}

} // namespace SwearJar
