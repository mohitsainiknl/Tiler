#pragma once

#include "Tiler/Editor/Core/Application.h"


extern Editor::Application* Editor::CreateApplication();

// This main function is temporary, later handled by the Tiler Engine.
int main() {

	auto app = Editor::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

