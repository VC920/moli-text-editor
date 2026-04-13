#pragma once
#include <imgui.h>

struct SDL_Window;
struct SDL_Renderer;
class UIManager
{
//==== Meyers 单例
public:
    static UIManager& GetInstance()
    {
        static UIManager instance;
        return instance;
    }
    // 禁止拷贝/移动
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;
    UIManager(UIManager&&) = delete;
    UIManager& operator=(UIManager&&) = delete;
private:
    UIManager() = default;
    ~UIManager() = default;
//=====

public:
    bool Create(SDL_Window* window, SDL_Renderer* renderer);
    void Update();
    void Render(SDL_Renderer* renderer);
    void Destroy();
};