#include "layout_widget.h"

namespace SwearJar {

void LayoutWidget::addSpacer() { addWidget(std::make_shared<SpacerWidget>()); }

void LayoutWidget::realign() {
    switch (m_alignment) {
        case Alignment::Fixed:
            // Nothing to be done
            break;
        case Alignment::Horizontal:
            realignHorizontally();
            break;
        case Alignment::Vertical:
            realignVertically();
            break;
    }
}

void LayoutWidget::realignHorizontally() {
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

        unsigned int newWidth = w->minWidth() + extraWidth;
        w->width(newWidth);
        w->x(allocatedWidth);
        allocatedWidth += newWidth;

        w->height(height());
        w->y(0);
    }

    if (allocatedWidth < widthToAllocate && children().size()) {
        auto& first = children()[0];
        first->width(first->width() + widthToAllocate);
    }
}

void LayoutWidget::realignVertically() {
    unsigned int heightToAllocate = height() - minHeight();
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedHeight = 0;
    for (auto& w : children()) {
        double extraHeight = 0.0f;
        if (w->growthFactor() > 0) {
            extraHeight = w->growthFactor();
            extraHeight /= totalGrowthFactor;
            extraHeight *= heightToAllocate;
        }

        unsigned int newHeight = w->minHeight() + extraHeight;
        w->height(newHeight);
        w->y(allocatedHeight);
        allocatedHeight += newHeight;

        w->width(width());
        w->x(0);
    }

    if (allocatedHeight < heightToAllocate && children().size()) {
        auto& first = children()[0];
        first->height(first->height() + heightToAllocate);
    }
}

} // namespace SwearJar
