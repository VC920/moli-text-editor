#include "DisplayManager.h"
#include "UIManager.h"

#include "f_File.h"
#include "f_Font.h"

#include "w_MenuBar.h"
#include "w_Demo.h"
#include "w_Info.h"
#include "w_About.h"
#include "w_Editor.h"
#include "w_Terminal.h"

void UpdateWindows()
{
    // 顶部菜单
    RenderMenuBar();

    // imgui demo 面板
    RenderDemo();

    // 信息面板
    RenderInfo();
    
    // 帮助/关于/致谢面板
    RenderAbout();

    // 终端面板
    RenderTerminal();
    
    // 文本编辑面板
    RenderEditor();
}

int main()
{
    auto& displayManager = DisplayManager::GetInstance();
    auto& uiManager = UIManager::GetInstance();

    if (!displayManager.Create("moli", 1280, 720))
        return -1;
    
    if (!uiManager.Create(displayManager.GetWindow(), displayManager.GetRenderer()))
        return -1;

    ChangeFont(m_fonts.find("MsYh")->second.c_str(), 16.0f);

    NewFile();
    while (!displayManager.ShouldClose())
    {
                                  
        displayManager.PollEvents();
        uiManager.Update();

        UpdateWindows();
    
        displayManager.Clear();
        uiManager.Render(displayManager.GetRenderer());
        displayManager.SwapBuffers();
    }

    uiManager.Destroy();
    displayManager.Destroy();

    return 0;
}