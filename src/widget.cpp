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
        render.clearArea(d.x, d.y, d.width, d.height, 7, 0);
        widget->clearPrevDimension();
    }

    // Re-render the widget
    for (auto widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        widget->refresh(render);
        widget->dirty(false);
    }
}

void Widget::focus(bool focus) {
    m_hasFocus = focus;
    if (m_hasFocus && gainFocus != 0) {
        gainFocus();
    }
    if (!m_hasFocus && loseFocus != 0) {
        loseFocus();
    }
}

bool Widget::moveFocusForward() {
    // There are no child widgets to consider
    if (m_widgets.empty()) {
        if (canTakeFocus()) {
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

} // namespace SwearJar
