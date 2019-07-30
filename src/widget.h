#pragma once

namespace SwearJar {

class Widget {
public:
    bool dirty() { return m_dirty; }
    void dirty(bool value) { m_dirty = value; }

private:
    bool m_dirty = true;
};

} // namespace SwearJar