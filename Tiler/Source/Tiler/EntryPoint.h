#pragma once

#include "Application.h"
#include <iostream>

extern Tiler::Application* Tiler::CreateApplication();

int main(int argc, char** argv) {
	std::cout << "Hello Tiler Engine" << std::endl;
	auto app = Tiler::CreateApplication();
	app->Run();
	delete app;
}


