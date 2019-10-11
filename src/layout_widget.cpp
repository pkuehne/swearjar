#include "layout_widget.h"

namespace SwearJar {

void LayoutWidget::addSpacer(unsigned int factor) {
    SpacerWidget& widget = createWidget<SpacerWidget>("spacer");
    widget.growthFactor(factor);
}

unsigned int LayoutWidget::requiredWidth() {
    if (m_alignment == Alignment::Vertical) {
        return CollectionWidget::minWidth();
    }
    return CollectionWidget::requiredWidth();
} // namespace SwearJar

unsigned int LayoutWidget::requiredHeight() {
    if (m_alignment == Alignment::Horizontal) {
        return CollectionWidget::minHeight();
    }
    return CollectionWidget::requiredHeight();
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
    spdlog::info("cNS: {}/{}/{}/{} -> {}", minSize, growthFactor,
                 totalGrowthFactor, widthToAllocate, extraSize);
    return minSize + extraSize;
}

void LayoutWidget::realignHorizontally() {
    spdlog::info("Realigning {} horizontally (W:{} R:{} M:{})", name(), width(),
                 requiredWidth(), m_margin);
    unsigned int widthToAllocate = width() - requiredWidth() - (m_margin * 2);
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedWidth = m_margin;
    for (auto& w : children()) {
        unsigned int newWidth =
            calculateNewSize(w->requiredWidth(), w->growthFactor(),
                             totalGrowthFactor, widthToAllocate);
        spdlog::info("Setting width for {} to {} from {} GF:{}", w->name(),
                     newWidth, name(), w->growthFactor());
        w->width(newWidth);
        w->x(allocatedWidth);
        allocatedWidth += newWidth;

        spdlog::info("Setting height for {} to {} from {}", w->name(),
                     height() - (m_margin * 2), name());
        w->height(height() - (m_margin * 2));
        w->y(m_margin);
    }

    if (allocatedWidth < widthToAllocate && children().size()) {
        auto& first = children()[0];
        first->width(first->width() + widthToAllocate);
    }
}

void LayoutWidget::realignVertically() {
    spdlog::info("Realigning {} vertically (H:{} R:{} M:{})", name(), height(),
                 requiredHeight(), m_margin);
    unsigned int heightToAllocate =
        height() - requiredHeight() - (m_margin * 2);
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedHeight = m_margin;
    for (auto& w : children()) {
        unsigned int newHeight =
            calculateNewSize(w->requiredHeight(), w->growthFactor(),
                             totalGrowthFactor, heightToAllocate);
        spdlog::info("Setting height for {} to {} from {}", w->name(),
                     newHeight, name());
        w->height(newHeight);
        w->y(allocatedHeight);
        allocatedHeight += newHeight;

        spdlog::info("Setting witdth for {} to {} from {}", w->name(),
                     width() - (m_margin * 2), name());
        w->width(width() - (m_margin * 2));
        w->x(m_margin);
    }

    if (allocatedHeight < heightToAllocate && children().size()) {
        auto& first = children()[0];
        first->height(first->height() + heightToAllocate);
    }
}

void LayoutWidget::render(const RenderContext& context) {
    realign();
    CollectionWidget::render(context);
}

} // namespace SwearJar
