#include "layout_widget.h"

namespace SwearJar {

void LayoutWidget::addSpacer() { addWidget(std::make_shared<SpacerWidget>()); }

void LayoutWidget::layoutWidgets() {
    unsigned int minWidth = 0;
    unsigned int minHeight = 0;
    for (auto& widget : children()) {
        minHeight += widget->height();
        minWidth += widget->width();
    }
}
} // namespace SwearJar
