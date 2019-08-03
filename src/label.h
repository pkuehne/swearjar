#pragma once
#include "widget.h"
#include <string>

namespace SwearJar {

class Label : public Widget {
public:
    explicit Label(const std::string& text);
    virtual void text(const std::string& text);
    virtual const std::string& text() { return m_text; }

    virtual void centered(bool centered);
    virtual bool centred() { return m_centred; }

protected:
    void refresh(CIptr& curses);

private:
    std::string m_text;
    bool m_centred;
};

} // namespace SwearJar