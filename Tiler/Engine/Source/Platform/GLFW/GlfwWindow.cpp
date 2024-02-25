#include "GlfwWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Events/KeyEvent.h"
#include "Tiler/Engine/Core/Events/MouseEvent.h"
#include "Tiler/Engine/Core/Events/ApplicationEvent.h"

#include "Platform/OpenGL/OpenGLRenderContext.h"


namespace Tiler {

	static bool s_GlfwInitialized = false;

	static void GlfwErrorCallback(int error, const char* description) {
		TL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const std::string& title, int width, int height) {
		return new GlfwWindow(title, width, height);
	}

	Window* Window::Create() {
		return new GlfwWindow("Tiler", 1280, 720);
	}

	GlfwWindow::GlfwWindow(const std::string& title, int width, int height) {
		Init(title, width, height);
	}

	GlfwWindow::~GlfwWindow() {
		Shutdown();
	}

	void GlfwWindow::Update() {
		m_Context->SwapBuffers();
		glfwPollEvents();
	}

	void GlfwWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool GlfwWindow::IsVSync() const {
		return m_Data.VSync;
	}

	void GlfwWindow::Init(const std::string& title, int width, int height) {
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;

		TL_CORE_TRACE("Create Window {0} ({1}, {2})", title, width, height);

		if (!s_GlfwInitialized) {
			//TODO: glfwTerminate on system shutdown
			const int success = glfwInit();

			TL_CORE_ASSERT(success, "Failed to initialize GLFW!");
			glfwSetErrorCallback(GlfwErrorCallback);

			s_GlfwInitialized = true;
		}

		TL_CORE_ASSERT((1 <= width && width <= std::numeric_limits<int>::max()), "Window width is outside the valid range (1 <= width <= INT_MAX).");
		TL_CORE_ASSERT((1 <= height && height <= std::numeric_limits<int>::max()), "Window height is outside the valid range (1 <= height <= INT_MAX).");

		m_Window = glfwCreateWindow(width, height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLRenderContext(m_Window);
		m_Context->Initialize();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.Callback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.Callback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.Callback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key, 0);
					data.Callback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.Callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.Callback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.Callback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.Callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xOffset, yOffset);
			data.Callback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(xPos, yPos);
			data.Callback(event);
		});
	}
	void GlfwWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}
}
