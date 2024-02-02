#include "Tiler/Tiler.h"


class Launcher : public Tiler::Application {
public:
	Launcher() {

	}
	~Launcher() {

	}
};

Tiler::Application* Tiler::CreateApplication() {

	return new Launcher();
}

