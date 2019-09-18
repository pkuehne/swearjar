#include "collection_widget.h"
#include <spdlog/spdlog.h>

namespace SwearJar {
CollectionWidget::CollectionWidget(const std::string& name) : Widget(name) {}

unsigned int CollectionWidget::minHeight() {
    unsigned int min = 0;
    for (const auto& w : m_widgets) {
        min += w->minHeight();
    }
    return min;
}

unsigned int CollectionWidget::minWidth() {
    unsigned int min = 0;
    for (const auto& w : m_widgets) {
        min += w->minWidth();
    }
    return min;
}

bool CollectionWidget::dirty() {
    bool dirty = false;
    for (const auto& w : m_widgets) {
        dirty |= w->dirty();
    }
    return dirty;
}

void CollectionWidget::render(const RenderContext* context) {
    spdlog::debug("WI: render called");

    // Clear previous position for the widget
    for (auto& widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        context->addOffsets(widget->x(), widget->y());
        Dimension d = widget->prevDimension();
        context->clearArea(d.x, d.y, d.width, d.height, 7, 0);
        widget->clearPrevDimension();
        context->clearOffsets(widget->x(), widget->y());
    }

    // Re-render the widget
    for (auto& widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        context->addOffsets(widget->x(), widget->y());
        context->reverse(widget->focus());
        widget->render(context);
        widget->dirty(false);
        context->reverse(false);
        context->clearOffsets(widget->x(), widget->y());
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
        m_focusWidget++;
    } while (m_focusWidget != m_widgets.end());

    // No more widgets
    return false;
}

bool CollectionWidget::handleKeyPress(int ch) {
    if (m_widgets.empty()) {
        return false;
    }
    if (m_focusWidget != m_widgets.end()) {
        spdlog::debug("Sending keyPress to {}", (*m_focusWidget)->name());
        return (*m_focusWidget)->handleKeyPress(ch);
    }
    return false;
}

} // namespace SwearJar
