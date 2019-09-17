#pragma once

#include "collection_widget.h"

namespace SwearJar {

class SpacerWidget : public Widget {
public:
    SpacerWidget(const std::string& name) : Widget(name) { growthFactor(1); }
};

class LayoutWidget : public CollectionWidget {
public:
    enum class Alignment { Fixed, Horizontal, Vertical };

public:
    LayoutWidget(const std::string& name) : CollectionWidget(name) {}

    virtual void addSpacer(unsigned int factor = 1);
    virtual void realign();
    virtual void realignHorizontally();
    virtual void realignVertically();

    void alignment(Alignment align) { m_alignment = align; }
    Alignment alignment() { return m_alignment; }

    void margin(unsigned int margin) { m_margin = margin; }
    unsigned int margin() { return m_margin; }

    void render(const RenderContext* context) override;

private:
    Alignment m_alignment = Alignment::Fixed;
    unsigned int m_margin = 0;
};

} // namespace SwearJar
