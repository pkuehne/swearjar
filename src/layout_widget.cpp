#include "layout_widget.h"
#include "logging.h"

namespace SwearJar {

void LayoutWidget::addSpacer(unsigned int factor) {
    auto& widget = createWidget<SpacerWidget>("spacer");
    widget.growthFactor(factor);
}

unsigned int LayoutWidget::requiredWidth() {
    if (m_alignment == Alignment::Vertical) {
        unsigned int min = 0;
        for (const auto& w : children()) {
            if (w->requiredWidth() > min) {
                min = w->requiredWidth();
            }
        }
        return min;
    }
    return CollectionWidget::requiredWidth();
}

unsigned int LayoutWidget::requiredHeight() {
    if (m_alignment == Alignment::Horizontal) {
        unsigned int min = 0;
        for (const auto& w : children()) {
            if (w->requiredHeight() > min) {
                min = w->requiredHeight();
            }
        }
        return min;
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
    return minSize + extraSize;
}

void LayoutWidget::realignHorizontally() {
    LOG_DEBUG << "Realigning " << name() << " horizontally "
              << "(W:" << width() << " R:" << requiredWidth()
              << " M:" << m_margin << ")" << LOG_END;
    unsigned int widthToAllocate = width() - requiredWidth() - (m_margin * 2);
    if (widthToAllocate > width()) {
        LOG_WARN << "Can't realign " << name() << " horizontally as "
                 << requiredWidth() << " > " << width()
                 << " M:" << (m_margin * 2) << LOG_END;
        return;
    }
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedWidth = m_margin;
    for (auto& w : children()) {
        unsigned int newWidth =
            calculateNewSize(w->requiredWidth(), w->growthFactor(),
                             totalGrowthFactor, widthToAllocate);
        w->width(newWidth);
        w->x(allocatedWidth);
        allocatedWidth += newWidth;

        w->height(height() - (m_margin * 2));
        w->y(m_margin);
    }

    if (allocatedWidth < widthToAllocate && !children().empty()) {
        auto& first = children()[0];
        first->width(first->width() + widthToAllocate);
    }
}

void LayoutWidget::realignVertically() {
    LOG_DEBUG << "Realigning " << name() << " vertically "
              << "(H:" << height() << " R:" << requiredHeight()
              << " M:" << m_margin << ")" << LOG_END;
    unsigned int heightToAllocate =
        height() - requiredHeight() - (m_margin * 2);
    if (heightToAllocate > height()) {
        LOG_WARN << "Can't realign " << name() << " vertically as "
                 << requiredHeight() << " > " << height()
                 << " M:" << (m_margin * 2) << LOG_END;
        return;
    }
    unsigned int totalGrowthFactor = 0;
    for (const auto& w : children()) {
        totalGrowthFactor += w->growthFactor();
    }

    unsigned int allocatedHeight = m_margin;
    for (auto& w : children()) {
        unsigned int newHeight =
            calculateNewSize(w->requiredHeight(), w->growthFactor(),
                             totalGrowthFactor, heightToAllocate);
        w->height(newHeight);
        w->y(allocatedHeight);
        allocatedHeight += newHeight;

        w->width(width() - (m_margin * 2));
        w->x(m_margin);
    }

    if (allocatedHeight < heightToAllocate && !children().empty()) {
        auto& first = children()[0];
        first->height(first->height() + heightToAllocate);
    }
}

void LayoutWidget::render(const RenderContext& context) {
    realign();
    CollectionWidget::render(context);
}

} // namespace SwearJar
