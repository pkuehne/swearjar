#include <swearjar.h>

int main() {
	namespace SJ = SwearJar;
	SJ::Screen screen(new SJ::CursesWrapper());
	screen.initialize();

	auto& window = screen.createWindow<SJ::Window>();
	auto& label = window.baseWidget().createWidget<SJ::Label>("Label");
	label.text(L"Hello World 👋");

	screen.run();
	return 0;
}
