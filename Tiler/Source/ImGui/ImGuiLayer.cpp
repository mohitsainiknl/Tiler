#include "Tiler/ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "GLFW/glfw3.h"

#include "Tiler/Application.h"
#include "Tiler/Window.h"
#include "Tiler/Platform/Independent/OpenGL/imgui_impl_opengl3.h"


namespace Tiler {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {

	}


	ImGuiLayer::~ImGuiLayer() {

	}


	void ImGuiLayer::OnAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui_ImplOpenGL3_Init("#version 410");
	}


	void ImGuiLayer::OnDetach() {

	}


	void ImGuiLayer::OnUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	void ImGuiLayer::OnEvent(const Event& event) {

	}

}