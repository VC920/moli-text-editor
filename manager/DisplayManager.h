#pragma once

struct SDL_Window;
struct SDL_Renderer;
class DisplayManager
{
//==== Meyers 单例
public:
    static DisplayManager& GetInstance()
    {
        static DisplayManager instance;
        return instance;
    }
    // 禁止拷贝/移动
    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;
    DisplayManager(DisplayManager&&) = delete;
    DisplayManager& operator=(DisplayManager&&) = delete;
private:
    DisplayManager() = default;
    ~DisplayManager() = default;
//=====

private:
    bool m_quit;
    int m_width, m_height;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

public:
    bool Create(const char* title, int width, int height);
    void PollEvents();
    void Clear();
    void SwapBuffers();
    void Destroy();

    void Close();

    inline bool ShouldClose() { return m_quit; }
    inline int GetWidth() { return m_width; }
    inline int GetHeight() { return m_height; }
    inline SDL_Window* GetWindow() { return m_window; }
    inline SDL_Renderer* GetRenderer() { return m_renderer; }
};