#include "collection_widget.h"
#include <spdlog/spdlog.h>

namespace SwearJar {
CollectionWidget::CollectionWidget(const std::string& name) : Widget(name) {
    m_focusWidget = m_widgets.end();
}

unsigned int CollectionWidget::minHeight() {
    unsigned int min = 0;
    for (auto w : m_widgets) {
        min += w->minHeight();
    }
    return min;
}

unsigned int CollectionWidget::minWidth() {
    unsigned int min = 0;
    for (auto w : m_widgets) {
        min += w->minWidth();
    }
    return min;
}

bool CollectionWidget::dirty() {
    bool dirty = false;
    for (auto w : m_widgets) {
        dirty |= w->dirty();
    }
    return dirty;
}

void CollectionWidget::addWidget(WidgetP widget) {
    m_widgets.push_back(widget);
    m_focusWidget = m_widgets.end();
}

void CollectionWidget::refresh(const RenderContext& render) {
    spdlog::info("WI: refresh called");

    // Clear previous position for the widget
    for (auto widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        render.addOffsets(widget->x(), widget->y());
        Dimension d = widget->prevDimension();
        spdlog::info("WI: clearing {}", widget->name());
        render.clearArea(d.x, d.y, d.width, d.height, 7, 0);
        widget->clearPrevDimension();
        render.clearOffsets(widget->x(), widget->y());
    }

    // Re-render the widget
    for (auto widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        render.addOffsets(widget->x(), widget->y());
        render.reverse(widget->focus());
        widget->refresh(render);
        widget->dirty(false);
        render.reverse(false);
        render.clearOffsets(widget->x(), widget->y());
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