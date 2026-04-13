#pragma once
#include "WindowFlag.h"

#include <imgui.h>
#include <windows.h>
#include <shellapi.h>

void RenderAbout()
{
    if (!show_about) return;
    ImGui::Begin("About", &show_about);
    ImGui::Text("Hello this is moli editor\n");

    if (ImGui::Button("https://github.com/xuansh/DickProgramLanguage"))  // 按钮样式
    {
        // 使用 ShellExecute 直接打开 URL，不创建命令行窗口
        #ifdef _WIN32
            ShellExecute(NULL, "open", 
                "https://github.com/xuansh/DickProgramLanguage", 
                NULL, NULL, SW_SHOWNORMAL);
        #elif __APPLE__
            system("open https://github.com/xuansh/DickProgramLanguage");
        #elif __linux__
            system("xdg-open https://github.com/xuansh/DickProgramLanguage");
        #endif
    }

    if (ImGui::Button("https://github.com/VC920/moli-text-editor"))  // 按钮样式
    {
        // 使用 ShellExecute 直接打开 URL，不创建命令行窗口
        #ifdef _WIN32
            ShellExecute(NULL, "open", 
                "https://github.com/VC920/moli-text-editor", 
                NULL, NULL, SW_SHOWNORMAL);
        #elif __APPLE__
            system("open https://github.com/VC920/moli-text-editor");
        #elif __linux__
            system("xdg-open https://github.com/VC920/moli-text-editor");
        #endif
    }

    if (ImGui::Button("https://www.deepseek.com/"))  // 按钮样式
    {
        // 使用 ShellExecute 直接打开 URL，不创建命令行窗口
        #ifdef _WIN32
            ShellExecute(NULL, "open", 
                "https://www.deepseek.com/", 
                NULL, NULL, SW_SHOWNORMAL);
        #elif __APPLE__
            system("open https://www.deepseek.com/");
        #elif __linux__
            system("xdg-open https://www.deepseek.com/");
        #endif
    }
    ImGui::End();
}