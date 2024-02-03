#include "Tiler/Tiler.h"


class EampleLayer : public Tiler::Layer {
public:
	EampleLayer() : Layer("Example") {

	}

	void OnRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(const Tiler::Event& event) override {

	}
};


class Launcher : public Tiler::Application {
public:
	Launcher() {
		PushOverlay(new EampleLayer());
	}
	~Launcher() {

	}
};

Tiler::Application* Tiler::CreateApplication() {

	return new Launcher();
}

