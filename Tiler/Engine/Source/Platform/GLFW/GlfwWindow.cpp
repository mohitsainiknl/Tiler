#include "GlfwWindow.h"

#include "Tiler/Engine/Base.h"
#include "Tiler/Engine/Core/Events/ApplicationEvent.h"
#include "Tiler/Engine/Core/Events/KeyEvent.h"
#include "Tiler/Engine/Core/Events/MouseEvent.h"

namespace tiler {

	static bool s_glfwInitialized = false;

	static void s_glfwErrorCallback(int error, const char* description) {
		TL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GlfwWindow::GlfwWindow(const std::string& title, int width, int height) {
		init(title, width, height);
	}

	GlfwWindow::~GlfwWindow() {
		shutdown();
	}

	void GlfwWindow::onUpdate() {
		glfwPollEvents();
	}

	void GlfwWindow::init(const std::string& title, int width, int height) {
		m_data.title  = title;
		m_data.width  = width;
		m_data.height = height;

		TL_CORE_TRACE("Create Window {0} ({1}, {2})", title, width, height);

		if (!s_glfwInitialized) {
			// TODO: glfwTerminate on system shutdown
			const int success = glfwInit();

			TL_CORE_ASSERT(success, "Failed to initialize GLFW!");
			glfwSetErrorCallback(s_glfwErrorCallback);

			TL_GLFW_OPENGL_DEBUG_CONTEXT;

			s_glfwInitialized = true;
		}

		TL_CORE_ASSERT((1 <= width && width <= std::numeric_limits<int>::max()),
		    "Window width is outside the valid range (1 <= width <= INT_MAX).");
		TL_CORE_ASSERT((1 <= height && height <= std::numeric_limits<int>::max()),
		    "Window height is outside the valid range (1 <= height <= INT_MAX).");

		m_innerWindow = glfwCreateWindow(width, height, m_data.title.c_str(), nullptr, nullptr);

		glfwSetWindowUserPointer(m_innerWindow, &m_data);

		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_innerWindow, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.width  = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.callback(event);
		});

		glfwSetWindowCloseCallback(m_innerWindow, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.callback(event);
		});

		glfwSetKeyCallback(m_innerWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key, 0);
					data.callback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_innerWindow, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.callback(event);
		});

		glfwSetMouseButtonCallback(m_innerWindow, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_innerWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xOffset, yOffset);
			data.callback(event);
		});

		glfwSetCursorPosCallback(m_innerWindow, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(xPos, yPos);
			data.callback(event);
		});
	}
	void GlfwWindow::shutdown() {
		glfwDestroyWindow(m_innerWindow);
	}
}  // namespace tiler
