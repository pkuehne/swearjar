#pragma once
#include "widget.h"
#include <string>

namespace SwearJar {

class Label : public Widget {
public:
    explicit Label(const std::string& name);
    virtual void text(const std::wstring& text);
    virtual const std::wstring& text() {
        return m_text;
    }

    virtual void centred(bool centred);
    virtual bool centred() {
        return m_centred;
    }

    void render(const RenderContext& context) override;

private:
    std::wstring m_text;
    bool m_centred = false;
};

} // namespace SwearJar
