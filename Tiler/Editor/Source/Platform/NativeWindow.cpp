#include "NativeWindow.h"

#include "Tiler/Editor/Base.h"



namespace Tiler {

    NativeWindow::NativeWindow(const std::string& title, int width, int height)
        : m_Title(title), m_Width(width), m_Height(height), m_ClockFrequency(0.0) {
        Initialize();
    }

    NativeWindow::~NativeWindow() {
        Shutdown();
    }

    void NativeWindow::OnUpdate() {
        glfwPollEvents();
    }

    double NativeWindow::GetAbsoluteTime() const {
        const uint64_t ticks = glfwGetTimerValue();
        return static_cast<double>(ticks) / glfwGetTimerFrequency();
    }

    void NativeWindow::Initialize() {

        if (!glfwInit()) {
            TL_EDIT_ASSERT(false, "Failed to initialize GLFW");
        }

        TL_EDIT_TRACE("Creating GLFW Window (title=\"{0}\", width={1}, height={2})", m_Title, m_Width, m_Height);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            glfwTerminate();
            TL_EDIT_ASSERT(false, "Failed to create GLFW window");
        }
        // Later, initialization of GLEW or GLAD is done here

        // Initialize clock frequency for high-resolution timer
        m_ClockFrequency = static_cast<double>(glfwGetTimerFrequency());
    }

    void NativeWindow::Shutdown() {

        if (m_Window) {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
        }
        glfwTerminate();
    }

}
