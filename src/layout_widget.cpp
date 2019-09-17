#include "layout_widget.h"

namespace SwearJar {

void LayoutWidget::addSpacer(unsigned int factor) {
    auto widget = std::make_shared<SpacerWidget>();
    widget->growthFactor(factor);
    addWidget(widget);
}

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
    unsigned int widthToAllocate = width() - minWidth() - (m_margin * 2);
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedWidth = m_margin;
    for (auto& w : children()) {
        unsigned int newWidth =
            calculateNewSize(w->minWidth(), w->growthFactor(),
                             totalGrowthFactor, widthToAllocate);
        w->width(newWidth);
        w->x(allocatedWidth);
        allocatedWidth += newWidth;

        w->height(height() - (m_margin * 2));
        w->y(m_margin);
    }

    if (allocatedWidth < widthToAllocate && children().size()) {
        auto& first = children()[0];
        first->width(first->width() + widthToAllocate);
    }
}

void LayoutWidget::realignVertically() {
    unsigned int heightToAllocate = height() - minHeight() - (m_margin * 2);
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedHeight = m_margin;
    for (auto& w : children()) {
        unsigned int newHeight =
            calculateNewSize(w->minHeight(), w->growthFactor(),
                             totalGrowthFactor, heightToAllocate);
        w->height(newHeight);
        w->y(allocatedHeight);
        allocatedHeight += newHeight;

        w->width(width() - (m_margin * 2));
        w->x(m_margin);
    }

    if (allocatedHeight < heightToAllocate && children().size()) {
        auto& first = children()[0];
        first->height(first->height() + heightToAllocate);
    }
}

void LayoutWidget::render(const RenderContext* context) {
    if (dirty()) {
        realign();
    }
    CollectionWidget::render(context);
}

} // namespace SwearJar
