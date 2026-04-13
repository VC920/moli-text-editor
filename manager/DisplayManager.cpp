#include "DisplayManager.h"
#include "InputManager.h"
#include <iostream>
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

bool DisplayManager::Create(const char* title, int width, int height)
{
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
    m_window = SDL_CreateWindow("moli", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, window_flags);
    if (m_window == nullptr)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void DisplayManager::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        HandleInputEvent(event);
        ImGui_ImplSDL2_ProcessEvent(&event);
        
        if (event.type == SDL_QUIT)
            m_quit = true;
    }

    SDL_GetRendererOutputSize(m_renderer, &m_width, &m_height);
}

void DisplayManager::SwapBuffers()
{
    SDL_RenderPresent(m_renderer);
}

void DisplayManager::Clear()
{
    SDL_SetRenderDrawColor(m_renderer, 64, 64, 64, 1);
    SDL_RenderClear(m_renderer);
}

void DisplayManager::Destroy()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void DisplayManager::Close()
{
    m_quit = true;
}