#pragma once
#include "widget.h"
#include <string>

namespace SwearJar {

class Label : public Widget {
public:
    explicit Label(const std::string& name);
    virtual void text(const std::string& text);
    virtual const std::string& text() { return m_text; }

    virtual void centred(bool centred);
    virtual bool centred() { return m_centred; }

protected:
    void render(const RenderContext& context) override;

private:
    std::string m_text;
    bool m_centred = false;
};

} // namespace SwearJar
