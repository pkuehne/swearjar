#include "widget.h"
#include "spdlog/spdlog.h"

namespace SwearJar {

Widget::Widget() { m_focusWidget = m_widgets.end(); }

void Widget::height(unsigned int height) {
    invalidate();
    m_height = height;
}

void Widget::width(unsigned int width) {
    invalidate();
    m_width = width;
}

void Widget::x(unsigned int x) {
    invalidate();
    m_x = x;
}

void Widget::y(unsigned int y) {
    invalidate();
    m_y = y;
}

void Widget::fgColor(short fg) {
    invalidate();
    m_fg = fg;
}

void Widget::bgColor(short bg) {
    invalidate();
    m_bg = bg;
}

void Widget::invalidate() {
    if (dirty()) {
        return;
    }
    dirty(true);
    m_prevDimension = Dimension{m_x, m_y, m_width, m_height};
}

void Widget::addWidget(WidgetP widget) {
    m_widgets.push_back(widget);
    m_focusWidget = m_widgets.end();
}

void Widget::refresh(const RenderContext& render) {
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

void Widget::focus(bool focus) {
    m_hasFocus = focus;
    if (m_hasFocus && gainFocus != 0) {
        gainFocus(this);
    }
    if (!m_hasFocus && loseFocus != 0) {
        loseFocus(this);
    }
}

bool Widget::moveFocusForward() {
    // There are no child widgets to consider
    if (m_widgets.empty()) {
        if (canTakeFocus()) {
            invalidate();
            focus(!focus());
            return focus();
        }
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

bool Widget::handleKeyPress(int ch) {
    if (m_widgets.empty()) {
        return false;
    }
    if (m_focusWidget != m_widgets.end()) {
        return (*m_focusWidget)->handleKeyPress(ch);
    }
    return false;
}

} // namespace SwearJar
