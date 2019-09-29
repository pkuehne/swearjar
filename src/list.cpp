#include "list.h"

namespace SwearJar {

List::List(const std::string& name) : Widget(name) {}
void List::addItem(std::string item) { m_items.push_back(item); }

} // namespace SwearJar
