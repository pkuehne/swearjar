#pragma once

#include "collection_widget.h"

namespace SwearJar {

class Frame : public CollectionWidget {
    public:
        explicit Frame() :m_title("") {}
        explicit Frame(const std::string& title) :m_title(title) {}
        void title(const std::string& title) { m_title = title; }
        std::string title() { return m_title; }

        // Overriden Widget functions
        void addWidget(WidgetP widget, unsigned int x, unsigned int y);
        void refresh(const RenderContext& render) override;

    private:
        std::string m_title;
};

} // namespace SwearJar
