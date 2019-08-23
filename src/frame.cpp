#include "frame.h"

namespace SwearJar {

void Frame::refresh(const RenderContext& render) {
    render.drawBorder(0, 0, width(), height(), fgColor(), bgColor());
    render.drawText(2, 0, m_title, fgColor(), bgColor());
    //Widget::refresh(render); // render child widgets
}

} // namespace SwearJar
