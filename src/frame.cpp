#include "frame.h"

namespace SwearJar {

Frame::Frame(const std::string& name) : LayoutWidget(name) {
    alignment(LayoutWidget::Alignment::Vertical);
    margin(1);
}

void Frame::title(const std::string& title) {
    m_title = title;
}

unsigned int Frame::minWidth() {
    unsigned int min = LayoutWidget::minWidth();
    return 4 + (min > title().size() ? min : title().size());
}

void Frame::render(const RenderContext& context) {
    context.drawBorder(0, 0, width(), height(), fgColor(), bgColor());
    context.drawText(2, 0, m_title, fgColor(), bgColor());

    LayoutWidget::render(context); // render child widgets
}

} // namespace SwearJar
