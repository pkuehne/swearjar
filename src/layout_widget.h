#pragma once

#include "collection_widget.h"


namespace SwearJar {

class SpacerWidget : public Widget {
public:
    SpacerWidget() : Widget("spacer") { growthFactor(1); }
};

class LayoutWidget : public CollectionWidget {
public:
    enum class Alignment {
        Fixed,
        Horizontal,
        Vertical
    };

public:
    LayoutWidget(const std::string& name) : CollectionWidget(name) {}

    virtual void addSpacer();
    virtual void realign();
    virtual void realignHorizontally();
    virtual void realignVertically();

    void alignment(Alignment align) { m_alignment = align; }
    Alignment alignment() { return m_alignment; }

    void refresh(const RenderContext& render) override;
private:
    Alignment m_alignment = Alignment::Fixed;
};

} // namespace SwearJar
