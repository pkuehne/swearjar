#pragma once

#include "widget.h"

namespace SwearJar {

class CollectionWidget : public Widget {
public:
    CollectionWidget(const std::string& name);

    bool dirty() override;
    void dirty(bool) override{};
    unsigned int minHeight() override;
    unsigned int minWidth() override;

    const WidgetV& children() const { return m_widgets; }

    template <class T> std::shared_ptr<T> createWidget(const std::string& name);
    template <class T>
    std::shared_ptr<T> createWidget(const std::string& name, unsigned int x,
                                    unsigned int y);
    void addWidget(WidgetP widget);

    void render(const RenderContext* context) override;
    bool moveFocusForward() override;
    bool handleKeyPress(int ch) override;

private:
    WidgetV m_widgets;
    WidgetV::iterator m_focusWidget;
};

template <class T>
std::shared_ptr<T> CollectionWidget::createWidget(const std::string& name) {
    return createWidget<T>(name, 0, 0);
}

template <class T>
std::shared_ptr<T> CollectionWidget::createWidget(const std::string& name,
                                                  unsigned int x,
                                                  unsigned int y) {
    auto widget = std::make_shared<T>(name);
    widget->x(x);
    widget->y(y);
    this->addWidget(widget);
    return widget;
}

} // namespace SwearJar
