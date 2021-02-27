#pragma once // or your preferred include guard syntax

#include <swearjar.h>

// Create a new window
class FortuneWindow : public SwearJar::Window {
public:
    explicit FortuneWindow(SwearJar::Screen& screen);

private:
    void init_widgets();
    void load_fortunes();
    const std::wstring& get_fortune();

private:
    std::vector<std::wstring> m_fortunes;
};