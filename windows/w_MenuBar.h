#pragma once
#include "WindowFlag.h"
#include "w_Editor.h"
#include "DisplayManager.h"
#include "f_File.h"
#include "f_Font.h"

#include <imgui.h>

#include <iostream>

void RenderMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        // 文件菜单
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
            {
                NewFile();  // 新建文件逻辑
            }
            if (ImGui::MenuItem("Open", "Ctrl+O"))
            {
                OpenFile(); // 打开文件逻辑
            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                SaveFile(); // 保存文件逻辑
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4"))
            {
                DisplayManager::GetInstance().Close();  // 退出逻辑
            }
            ImGui::EndMenu();
        }
        
        // 编辑菜单
        if (ImGui::BeginMenu("Edit"))
        {
            // 获取当前活动的编辑器
            EditorDocument* currentDoc = m_currentDoc;
            
            if (currentDoc)
            {
                auto& editor = currentDoc->editor;
                
                // Undo/Redo
                if (ImGui::MenuItem("Undo", "Ctrl+Z", false, editor.CanUndo()))
                {
                    editor.Undo();
                }
                
                if (ImGui::MenuItem("Redo", "Ctrl+Y", false, editor.CanRedo()))
                {
                    editor.Redo();
                }
                
                ImGui::Separator();
                
                // 剪切/复制/粘贴
                if (ImGui::MenuItem("Cut", "Ctrl+X", false, editor.HasSelection()))
                {
                    editor.Cut();
                }
                
                if (ImGui::MenuItem("Copy", "Ctrl+C", false, editor.HasSelection()))
                {
                    editor.Copy();
                }
                
                if (ImGui::MenuItem("Paste", "Ctrl+V"))
                {
                    editor.Paste();
                }
                
                ImGui::Separator();
                
                // 全选
                if (ImGui::MenuItem("Select All", "Ctrl+A"))
                {
                    editor.SelectAll();
                }
                
                // 删除
                if (ImGui::MenuItem("Delete", "Del", false, editor.HasSelection()))
                {
                    editor.Delete();
                }
            }
            else
            {
                // 没有活动文档时禁用菜单项
                ImGui::MenuItem("Undo", "Ctrl+Z", false, false);
                ImGui::MenuItem("Redo", "Ctrl+Y", false, false);
                ImGui::Separator();
                ImGui::MenuItem("Cut", "Ctrl+X", false, false);
                ImGui::MenuItem("Copy", "Ctrl+C", false, false);
                ImGui::MenuItem("Paste", "Ctrl+V", false, false);
                ImGui::Separator();
                ImGui::MenuItem("Select All", "Ctrl+A", false, false);
                ImGui::MenuItem("Delete", "Del", false, false);
            }
            
            ImGui::EndMenu();
        }
        
        // 视图菜单
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Demo Window", nullptr, &show_demo);
            ImGui::MenuItem("Info Window", nullptr, &show_info);
            ImGui::MenuItem("Editor Window", nullptr, &show_editor);
            ImGui::MenuItem("Terminal Window", nullptr, &show_terminal);
            ImGui::EndMenu();
        }

        // 主题菜单
        if (ImGui::BeginMenu("Theme"))
        {
            static std::string currentTheme = "Dark";

            // 每个菜单项独立判断
            bool isDarkSelected = (currentTheme == "Dark");
            if (ImGui::MenuItem("Dark", nullptr, isDarkSelected))
            {
                ImGui::StyleColorsDark();
                SetDarkStyle();
                currentTheme = "Dark";
            }
            
            bool isLightSelected = (currentTheme == "Light");
            if (ImGui::MenuItem("Light", nullptr, isLightSelected))
            {
                ImGui::StyleColorsLight();
                SetLightStyle();
                currentTheme = "Light";
            }
            
            bool isClassicSelected = (currentTheme == "Classic");
            if (ImGui::MenuItem("Classic", nullptr, isClassicSelected))
            {
                ImGui::StyleColorsClassic();
                SetBlueStyle();
                currentTheme = "Classic";
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Fonts"))
        {
            static std::string currentFont = "MsYh";

            for (auto it = m_fonts.begin(); it != m_fonts.end(); ++it)
            {
                bool isSelected = (currentFont == it->first);
                if (ImGui::MenuItem(it->first.c_str(), nullptr, isSelected))
                {
                    currentFont = it->first;
                    ChangeFont(it->second.c_str(), 16.0f);
                }
            }
            ImGui::EndMenu();
        }
        
        // 帮助菜单
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", nullptr, &show_about);
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
}