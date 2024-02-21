#include "GLFWindow.h"

#include "Tiler/Engine/Base.h"


namespace Tiler {

    GLFWindow::GLFWindow(const std::string& title, int width, int height)
        : m_Title(title), m_Width(width), m_Height(height), m_ClockFrequency(0.0) {
        Initialize();
    }

    GLFWindow::~GLFWindow() {
        Shutdown();
    }

    void GLFWindow::OnUpdate() {
        glfwPollEvents();
    }

    double GLFWindow::GetAbsoluteTime() const {
        const uint64_t ticks = glfwGetTimerValue();
        return static_cast<double>(ticks) / glfwGetTimerFrequency();
    }

    void GLFWindow::Initialize() {

        if (!glfwInit()) {
            TL_CORE_ASSERT(false, "Failed to initialize GLFW");
        }

        TL_CORE_TRACE("Creating GLFW Window (title=\"{0}\", width={1}, height={2})", m_Title, m_Width, m_Height);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            glfwTerminate();
            TL_CORE_ASSERT(false, "Failed to create GLFW window");
        }
        // Later, initialization of GLEW or GLAD is done here

        // Initialize clock frequency for high-resolution timer
        m_ClockFrequency = static_cast<double>(glfwGetTimerFrequency());
    }

    void GLFWindow::Shutdown() {

        if (m_Window) {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
        }
        glfwTerminate();
    }

}
