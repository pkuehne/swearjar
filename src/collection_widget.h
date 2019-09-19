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

    const std::vector<std::unique_ptr<Widget>>& children() const {
        return m_widgets;
    }

    template <class T> T& createWidget(const std::string& name);
    template <class T>
    T& createWidget(const std::string& name, unsigned int x, unsigned int y);

    void render(const RenderContext& context) override;
    bool moveFocusForward() override;
    bool handleKeyPress(int ch) override;

private:
    std::vector<std::unique_ptr<Widget>> m_widgets;
    std::vector<std::unique_ptr<Widget>>::iterator m_focusWidget;
};

template <class T> T& CollectionWidget::createWidget(const std::string& name) {
    return createWidget<T>(name, 0, 0);
}

template <class T>
T& CollectionWidget::createWidget(const std::string& name, unsigned int x,
                                  unsigned int y) {
    auto widget = std::make_unique<T>(name);
    widget->x(x);
    widget->y(y);
    widget->bgColor(bgColor());

    T& retval = *widget;
    m_widgets.push_back(std::move(widget));

    m_focusWidget = m_widgets.end();
    return retval;
}

} // namespace SwearJar
