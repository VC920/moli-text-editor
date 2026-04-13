#pragma once
#include "WindowFlag.h"
#include "DisplayManager.h"

#include <imgui.h>

void RenderInfo()
{
    if (!show_info) return;
    
    auto& displayManager = DisplayManager::GetInstance();

    ImGui::Begin("Infomation", &show_info);
    ImGui::Text("moli的信息");
    ImGui::Separator();
    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("window: %d, %d", displayManager.GetWidth(), displayManager.GetHeight());
    if (m_currentDoc != nullptr)
        ImGui::Text("current editor: %s", m_currentDoc->title.c_str());
    
    ImGui::End();
}