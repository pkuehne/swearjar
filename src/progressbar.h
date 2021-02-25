#pragma once

#include "widget.h"

namespace SwearJar {

class Progressbar : public Widget {
public:
    explicit Progressbar(const std::string& name) : Widget(name) {
    }
    void value(unsigned int value);
    unsigned int value();
    void maximum(unsigned int maximum);
    unsigned int maximum();
    void increment();
    void decrement();

    void render(const RenderContext& context) override;

private:
    unsigned int m_value = 0;
    unsigned int m_maximum = 100;
};

} // namespace SwearJar
