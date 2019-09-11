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

unsigned int calculateNewSize(unsigned int minSize, unsigned int growthFactor,
                              unsigned int totalGrowthFactor,
                              unsigned int widthToAllocate) {
    double extraSize = 0.0f;
    if (growthFactor > 0) {
        extraSize = growthFactor;
        extraSize /= totalGrowthFactor;
        extraSize *= widthToAllocate;
    }
    return minSize + extraSize;
}

void LayoutWidget::realignHorizontally() {
    unsigned int widthToAllocate = width() - minWidth();
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedWidth = 0;
    for (auto& w : children()) {
        unsigned int newWidth = calculateNewSize(w->minWidth(),
                                    w->growthFactor(), totalGrowthFactor,
                                    widthToAllocate);
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
        unsigned int newHeight = calculateNewSize(w->minHeight(),
                                    w->growthFactor(), totalGrowthFactor,
                                    heightToAllocate);
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

void LayoutWidget::refresh(const RenderContext& render) {
    realign();
    CollectionWidget::refresh(render);
}

} // namespace SwearJar
