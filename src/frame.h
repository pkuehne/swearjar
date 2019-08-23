#pragma once

#include "widget.h"

namespace SwearJar {

class Frame : public Widget {
    public:
        explicit Frame(const std::string& title) :m_title(title) {}
        void title(const std::string& title) { m_title = title; }
        std::string title() { return m_title; }

        // Overriden Widget functions
        void refresh(const RenderContext& render);

    private:
        std::string m_title;
};

} // namespace SwearJar
