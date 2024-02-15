#pragma once

#include "Core/Application.h"


extern Tiler::Application* Tiler::CreateApplication();

int main() {

	auto app = Tiler::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
