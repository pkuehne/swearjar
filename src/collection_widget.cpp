#include "collection_widget.h"
#include "logging.h"

namespace SwearJar {
CollectionWidget::CollectionWidget(const std::string& name) : Widget(name) {
}

unsigned int CollectionWidget::requiredHeight() {
    unsigned int min = 0;
    for (const auto& w : m_widgets) {
        min += w->requiredHeight();
    }
    return min;
}

unsigned int CollectionWidget::requiredWidth() {
    unsigned int min = 0;
    for (const auto& w : m_widgets) {
        min += w->requiredWidth();
    }
    return min;
}

void CollectionWidget::render(const RenderContext& context) {
    LOG_DEBUG << "WI: render called" << LOG_END;

    // Render the widgets
    for (auto& widget : m_widgets) {
        context.addOffsets(widget->x(), widget->y());
        context.reverse(widget->focus());
        widget->render(context);
        context.reverse(false);
        context.clearOffsets(widget->x(), widget->y());
    }
}

bool CollectionWidget::moveFocusForward() {
    if (m_widgets.empty()) {
        return false;
    }

    // Have we got focus on a child widget currently?
    if (m_focusWidget == m_widgets.end()) {
        // Then start from the beginning
        m_focusWidget = m_widgets.begin();
    }

    do {
        bool focusMoved = (*m_focusWidget)->moveFocusForward();
        if (focusMoved) {
            return true;
        }
        ++m_focusWidget;
    } while (m_focusWidget != m_widgets.end());

    // No more widgets
    return false;
}

bool CollectionWidget::handleKeyPress(const KeyEvent& event) {
    if (m_widgets.empty()) {
        return false;
    }
    if (m_focusWidget != m_widgets.end()) {
        LOG_DEBUG << "Sending keyPress to " << (*m_focusWidget)->name()
                  << LOG_END;
        return (*m_focusWidget)->handleKeyPress(event);
    }
    return false;
}

bool CollectionWidget::handleMouseClick(const MouseEvent& event) {
    if (m_widgets.empty()) {
        return false;
    }

    MouseEvent l_event(event);
    l_event.x -= this->x();
    l_event.y -= this->y();
    LOG_DEBUG << "Check against (" << l_event.x << "," << l_event.y << ")"
              << LOG_END;
    for (auto& widget : m_widgets) {
        LOG_DEBUG << "click on " << widget->name() << " @ (" << widget->x()
                  << ", " << widget->y() << ")" << LOG_END;
        if (l_event.x >= widget->x() &&
            l_event.x <= (widget->x() + widget->width())) {
            if (l_event.y >= widget->y() &&
                l_event.y <= (widget->y() + widget->height())) {
                return widget->handleMouseClick(l_event);
            }
        }
    }
    return false;
}
} // namespace SwearJar
