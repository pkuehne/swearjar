#pragma once

#include "collection_widget.h"

namespace SwearJar {

class SpacerWidget : public Widget {
public:
    explicit SpacerWidget(const std::string& name);
};

class LayoutWidget : public CollectionWidget {
public:
    enum class Alignment { Fixed, Horizontal, Vertical };

public:
    explicit LayoutWidget(const std::string& name);

    unsigned int requiredWidth() override;
    unsigned int requiredHeight() override;
    void addSpacer(unsigned int factor = 1);
    virtual void realign();
    virtual void realignHorizontally();
    virtual void realignVertically();

    void alignment(Alignment align);
    Alignment alignment();

    void margin(unsigned int margin);
    unsigned int margin();

    void render(const RenderContext& context) override;

private:
    Alignment m_alignment = Alignment::Fixed;
    unsigned int m_margin = 0;
};

} // namespace SwearJar
