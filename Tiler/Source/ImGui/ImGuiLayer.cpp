#include "Tiler/ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Tiler/Core.h"
#include "Tiler/Window.h"
#include "Tiler/Application.h"
#include "Tiler/Platform/Independent/OpenGL/imgui_impl_opengl3.h"

#include "Tiler/Events/Event.h"
#include "Tiler/Events/ApplicationEvent.h"
#include "Tiler/Events/KeyEvent.h"
#include "Tiler/Events/MouseEvent.h"

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

		io.KeyMap[ImGuiKey_Tab]         = TL_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow]   = TL_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow]  = TL_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow]     = TL_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow]   = TL_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp]      = TL_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown]    = TL_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home]        = TL_KEY_HOME;
		io.KeyMap[ImGuiKey_End]         = TL_KEY_END;
		io.KeyMap[ImGuiKey_Insert]      = TL_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete]      = TL_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace]   = TL_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space]       = TL_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter]       = TL_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape]      = TL_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = TL_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A]           = TL_KEY_A;
		io.KeyMap[ImGuiKey_C]           = TL_KEY_C;
		io.KeyMap[ImGuiKey_V]           = TL_KEY_V;
		io.KeyMap[ImGuiKey_X]           = TL_KEY_X;
		io.KeyMap[ImGuiKey_Y]           = TL_KEY_Y;
		io.KeyMap[ImGuiKey_Z]           = TL_KEY_Z;

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
		if (false);
		else if (event.GetEventType() == EventType::MOUSE_BUTTON_PRESSED  ) OnMouseButtonPressedEvent ((MouseButtonPressedEvent &)event);
		else if (event.GetEventType() == EventType::MOUSE_BUTTON_RELEASED ) OnMouseButtonReleasedEvent((MouseButtonReleasedEvent&)event);
		else if (event.GetEventType() == EventType::MOUSE_MOVED           ) OnMouseMovedEvent         ((MouseMovedEvent         &)event);
		else if (event.GetEventType() == EventType::MOUSE_SCROLLED        ) OnMouseScrolledEvent      ((MouseScrolledEvent      &)event);
		else if (event.GetEventType() == EventType::KEY_PRESSED           ) OnKeyPressedEvent         ((KeyPressedEvent         &)event);
		else if (event.GetEventType() == EventType::KEY_RELEASED          ) OnKeyReleasedEvent        ((KeyReleasedEvent        &)event);
		else if (event.GetEventType() == EventType::KEY_TYPED             ) OnKeyTypedEvent           ((KeyTypedEvent           &)event);
		else if (event.GetEventType() == EventType::WINDOW_RESIZE         ) OnWindowResizeEvent       ((WindowResizeEvent       &)event);
	}


	void ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		const int b = event.GetMouseButton();
		io.MouseDown[b] = true;
	}


	void ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = false;
	}


	void ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());
	}


	void ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.GetOffsetX();
		io.MouseWheel  += event.GetOffsetY();
	}


	void ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;

		io.KeyCtrl  = io.KeysDown[TL_KEY_LEFT_CONTROL] || io.KeysDown[TL_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[TL_KEY_LEFT_SHIFT]   || io.KeysDown[TL_KEY_RIGHT_SHIFT];
		io.KeyAlt   = io.KeysDown[TL_KEY_LEFT_ALT]     || io.KeysDown[TL_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[TL_KEY_LEFT_SUPER]   || io.KeysDown[TL_KEY_RIGHT_SUPER];
	}


	void ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;
	}


	void ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		const int keycode = event.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned int)keycode);
	}


	void ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetHeight(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
	}

}