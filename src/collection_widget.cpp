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
    spdlog::debug("WI: refresh called");

    // Clear previous position for the widget
    for (auto widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        Dimension d = widget->prevDimension();
        render.setOffsets(x() + widget->x(), y() + widget->y());
        render.clearArea(d.x, d.y, d.width, d.height, 7, 0);
        widget->clearPrevDimension();
    }
    render.clearOffsets();

    // Re-render the widget
    for (auto widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        render.setOffsets(x() + widget->x(), y() + widget->y());
        render.reverse(widget->focus());
        widget->refresh(render);
        widget->dirty(false);
        render.reverse(false);
    }
    render.clearOffsets();
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

void CollectionWidget::realign() {
    unsigned int widthToAllocate = width() - minWidth();
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedWidth = 0;
    for (auto& w : children()) {
        double extraWidth = 0.0f;
        if (w->growthFactor() > 0) {
            extraWidth = w->growthFactor();
            extraWidth /= totalGrowthFactor;
            extraWidth *= widthToAllocate;
        }

        unsigned int width = w->minWidth() + extraWidth;
        w->width(width);
        w->x(allocatedWidth);
        allocatedWidth += width;

        w->height(height());
        w->y(0);
    }

    if (allocatedWidth < widthToAllocate && children().size()) {
        auto& first = children()[0];
        first->width(first->width() + widthToAllocate);
    }
}

} // namespace SwearJar
