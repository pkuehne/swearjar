#pragma once

#include "widget.h"

namespace SwearJar {

class CollectionWidget : public Widget {
public:
    explicit CollectionWidget(const std::string& name);

    unsigned int requiredHeight() override;
    unsigned int requiredWidth() override;

    const std::vector<std::unique_ptr<Widget>>& children() const;

    template <class T> T& createWidget(const std::string& name);
    template <class T>
    T& createWidget(const std::string& name, unsigned int x, unsigned int y);
    template <class T> T* getWidget(const std::string& name);
    void render(const RenderContext& context) override;
    bool moveFocusForward() override;
    bool handleKeyPress(const KeyEvent& event) override;
    bool handleMouseClick(const MouseEvent& event) override;

private:
    std::vector<std::unique_ptr<Widget>> m_widgets;
    std::vector<std::unique_ptr<Widget>>::iterator m_focusWidget;
};

template <class T> T* CollectionWidget::getWidget(const std::string& name) {
    for (auto& widget : m_widgets) {
        if (widget->name() == name) {
            return dynamic_cast<T*>(widget.get());
        }
        auto* collection = dynamic_cast<CollectionWidget*>(widget.get());
        if (collection != nullptr) {
            // This is a collection widget, check its children as well
            auto* found = collection->getWidget<T>(name);
            if (found != nullptr) {
                return found;
            }
        }
    }
    return nullptr;
}

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
