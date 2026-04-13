#pragma once
#include "WindowFlag.h"
#include "f_File.h"
#include "f_Font.h"
#include <imgui.h>
#include <TextEditor.h>

void RenderEditor()
{
    if (!show_editor) return;

    for (int i = 0; i < m_docs.size(); i++)
    {
        auto& doc = m_docs[i];

        if (!doc.active)
        {
            continue;
        }

        ImGui::Begin(doc.title.c_str(), &doc.active);

        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows))
        {
            m_currentDoc = &doc;
        }

        // 更改文本大小
        // 临时改变全局字体缩放
        ChangeFontScale(m_currentFontScale);
        doc.editor.Render(doc.title.c_str());
        ChangeFontScale(m_defaultFontScale);

        ImGui::End();
    }

    // 统一删除所有 inactive 的文档
    for (int i = (int)m_docs.size() - 1; i >= 0; i--)
    {
        if (!m_docs[i].active)
        {
             // 如果删除的是当前文档，清空指针
            if (m_currentDoc == &m_docs[i])
            {
                m_currentDoc = nullptr;
            }
            m_docs.erase(m_docs.begin() + i);
        }
    }
}

void SetDarkStyle()
{
    for (int i = 0; i < m_docs.size(); i++)
    {
        m_docs[i].editor.SetPalette(TextEditor::GetDarkPalette());
    }
}

void SetLightStyle()
{
    for (int i = 0; i < m_docs.size(); i++)
    {
        m_docs[i].editor.SetPalette(TextEditor::GetLightPalette());
    }
}

void SetBlueStyle()
{
    for (int i = 0; i < m_docs.size(); i++)
    {
        m_docs[i].editor.SetPalette(TextEditor::GetRetroBluePalette());
    }
}