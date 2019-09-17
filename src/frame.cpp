#include "frame.h"

namespace SwearJar {

Frame::Frame(const std::string& name) : LayoutWidget(name) {
    alignment(LayoutWidget::Alignment::Vertical);
    margin(1);
}

void Frame::render(const RenderContextP& context) {
    context->drawBorder(0, 0, width(), height(), fgColor(), bgColor());
    context->drawText(2, 0, m_title, fgColor(), bgColor());

    LayoutWidget::render(context); // render child widgets
}

void Frame::addWidget(WidgetP widget, unsigned int x, unsigned int y) {
    widget->x(x);
    widget->y(y);
    CollectionWidget::addWidget(widget);
}
} // namespace SwearJar
