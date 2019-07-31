#pragma once

#include "curses_interface.h"
#include <memory>

namespace SwearJar {

class Widget {
    friend class Panel;

public:
    virtual ~Widget() {}
    virtual void dirty(bool value) { m_dirty = value; }
    virtual bool dirty() { return m_dirty; }

    void curses(std::shared_ptr<CursesInterface>& curses) { m_curses = curses; }

protected:
    std::shared_ptr<CursesInterface>& curses() { return m_curses; }

    virtual void refresh();

private:
    bool m_dirty = true;
    std::shared_ptr<CursesInterface> m_curses;
};

} // namespace SwearJar