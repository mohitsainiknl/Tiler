#include "Launcher.h"


Launcher::Launcher() {
}

Launcher::~Launcher() {
}

Tiler::Application* Tiler::CreateApplication() {

	return new Launcher();
}

