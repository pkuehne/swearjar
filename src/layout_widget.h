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

    // Creates the specified widget like createWidget(), but adds a SpacerWidget
    // before and after automatically.
    template <class T> T& createCentralWidget(const std::string& name);
    void render(const RenderContext& context) override;

private:
    Alignment m_alignment = Alignment::Fixed;
    unsigned int m_margin = 0;
};

template <class T>
T& LayoutWidget::createCentralWidget(const std::string& name) {
    addSpacer();
    T& w = createWidget<T>(name);
    addSpacer();

    return w;
}

class CenterWrapper {
public:
    CenterWrapper(LayoutWidget& base);
    ~CenterWrapper();

private:
    LayoutWidget& m_base;
};

} // namespace SwearJar
