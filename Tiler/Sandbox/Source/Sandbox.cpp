#include "Tiler/Engine.h"


class Sandbox : public Tiler::Application {

};


Tiler::Application* Tiler::CreateApplication() {

	return new Sandbox();
}
