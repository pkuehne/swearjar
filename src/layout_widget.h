#pragma once

#include "collection_widget.h"

namespace SwearJar {

class SpacerWidget : public Widget {
public:
    SpacerWidget() : Widget("spacer") {}
};

class LayoutWidget : public CollectionWidget {
public:
    LayoutWidget(const std::string& name) : CollectionWidget(name) {}
    virtual void addSpacer();

    virtual void layoutWidgets();
};

} // namespace SwearJar
