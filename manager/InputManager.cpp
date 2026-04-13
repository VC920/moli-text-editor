#include "InputManager.h"

#include "f_File.h"
#include "f_Font.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>

void HandleInputEvent(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        Uint16 mod = event.key.keysym.mod;
        
        // Ctrl+O
        if ((mod & KMOD_CTRL) && key == SDLK_o) {
            OpenFile();
        }
        // Ctrl+S
        else if ((mod & KMOD_CTRL) && key == SDLK_s) {
            SaveFile();
        }
        // Ctrl+N
        else if ((mod & KMOD_CTRL) && key == SDLK_n) {
            NewFile();
        }
    }

    if (event.type == SDL_MOUSEWHEEL) { 
        SDL_Keymod currentMod = SDL_GetModState();
        int scrollY = event.wheel.y;
        int scrollX = event.wheel.x;
        if (currentMod & KMOD_CTRL)
        {
            if (scrollY > 0) {
                // 处理向上滚动，例如：放大或向上移动列表
                m_currentFontScale += 0.1f;
            } else if (scrollY < 0) {
                // 处理向下滚动，例如：缩小或向下移动列表
                m_currentFontScale -= 0.1f;
            }
        }
        
    }
}