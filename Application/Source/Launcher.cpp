#include "Tiler/Tiler.h"


class Launcher : public Tiler::Application {
public:
	Launcher() {
		PushOverlay(new Tiler::ImGuiLayer());
	}
	~Launcher() {

	}
};

Tiler::Application* Tiler::CreateApplication() {

	return new Launcher();
}

