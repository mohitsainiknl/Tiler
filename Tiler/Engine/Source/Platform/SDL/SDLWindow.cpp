#include "SDLWindow.h"

#include "SDL.h"

#include "Tiler/Engine/Base.h"


namespace Tiler {

    SDLWindow::SDLWindow(const std::string& title, int width, int height)
        : m_Title(title), m_Width(width), m_Height(height), m_ClockFrequency(0.0) {
        Initialize();
    }

    SDLWindow::~SDLWindow() {
        Shutdown();
    }

    void SDLWindow::OnUpdate() {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Do Nothing
        }
    }

    double SDLWindow::GetAbsoluteTime() const {
        const uint64_t ticks = SDL_GetPerformanceCounter();
        return static_cast<double>(ticks) / m_ClockFrequency;
    }

    void SDLWindow::Initialize() {

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            TL_CORE_ASSERT(false, "Failed to initialize SDL: " + std::string(SDL_GetError()));
        }

        TL_CORE_TRACE("Creating SDL Window (title=\"{0}\", width={1}, height={2})", m_Title, m_Width, m_Height);

        Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

        m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, flags);
        if (!m_Window) {
            SDL_Quit();
            TL_CORE_ASSERT(false, "Failed to create SDL window: " + std::string(SDL_GetError()));
        }

        // Initialize clock frequency for high-resolution timer
        m_ClockFrequency = static_cast<double>(SDL_GetPerformanceFrequency());
    }

    void SDLWindow::Shutdown() {

        if (m_Window) {
            SDL_DestroyWindow(m_Window);
            m_Window = nullptr;
        }
        SDL_Quit();
    }

}
