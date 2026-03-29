#include "frame.h"

namespace SwearJar {

Frame::Frame(const std::string& name) : LayoutWidget(name) {
    alignment(LayoutWidget::Alignment::Vertical);
    margin(1);
}

void Frame::title(const std::wstring& title) {
    m_title = title;
}

std::wstring Frame::title() {
    return m_title;
}

void Frame::titleCentred(bool centred) {
    m_titleCentred = centred;
}

bool Frame::titleCentred() {
    return m_titleCentred;
}

unsigned int Frame::requiredWidth() {
    unsigned int childWidth = LayoutWidget::requiredWidth() + 2;
    unsigned int frameWidth = title().size() + 4;
    return (childWidth > frameWidth ? childWidth : frameWidth);
}

void Frame::render(const RenderContext& context) {
    context.drawBorder(0, 0, width(), height(), fgColor(), bgColor());
    unsigned int xStart = 2;
    if (m_titleCentred && width() > m_title.size() + 2) {
        xStart = (width() - m_title.size()) / 2;
    }
    context.drawText(xStart, 0, m_title, fgColor(), bgColor());

    LayoutWidget::render(context); // render child widgets
}

} // namespace SwearJar
