#include "Tiler/Engine/Core/ImGui/ImGuiLayer.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Input.h"

namespace tiler {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
	}

	ImGuiLayer::~ImGuiLayer() {
	}

	void ImGuiLayer::onAttach() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		GLFWwindow* window = glfwGetCurrentContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::onRenderBegin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::onRender(float timestep) {
		static bool show = true;
		// ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::onRenderEnd() {
		ImGuiIO& io    = ImGui::GetIO();
		io.DisplaySize = ImVec2(Input::getWindowWidth(), Input::getWindowHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

}  // namespace tiler