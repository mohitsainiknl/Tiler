#include "GlfwWindow.h"

#include "Log.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"


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

	void GlfwWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
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
		m_Data.Dispatcher = EventDispatcher();

		TL_CORE_TRACE("Create Window {0} ({1}, {2})", title, width, height);

		if (!s_GlfwInitialized) {
			//TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			glfwSetErrorCallback(GlfwErrorCallback);
			s_GlfwInitialized = true;
		}

		m_Window = glfwCreateWindow(width, height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.Dispatcher.Dispatch(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.Dispatcher.Dispatch(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.Dispatcher.Dispatch(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key, 0);
					data.Dispatcher.Dispatch(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.Dispatcher.Dispatch(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.Dispatcher.Dispatch(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.Dispatcher.Dispatch(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xOffset, yOffset);
			data.Dispatcher.Dispatch(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xPos, yPos);
			data.Dispatcher.Dispatch(event);
		});
	}
	void GlfwWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}
}
