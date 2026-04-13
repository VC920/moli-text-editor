#include "f_Font.h"

#include <imgui.h>

float m_defaultFontScale = 1.0f;
float m_currentFontScale = 1.5f;
// 字体文件的路径常量
std::unordered_map<std::string, std::string> m_fonts = {
    // 中文字体
    { "MsYh",            "C:\\Windows\\Fonts\\msyh.ttc"             },  // 雅黑
    { "SimSun",          "C:\\Windows\\Fonts\\simsun.ttc"           },  // 宋体
    { "SimKai",          "C:\\Windows\\Fonts\\simkai.ttf"           },  // 楷体
    { "SimHei",          "C:\\Windows\\Fonts\\simhei.ttf"           },  // 黑体

    // 英文字体
    { "Segoeui",         "C:\\Windows\\Fonts\\segoeui.ttf"          },  // Segoeui
    { "Arial",           "C:\\Windows\\Fonts\\arial.ttf"            },  // Arial
    { "Calibri",         "C:\\Windows\\Fonts\\calibri.ttf"          },  // Calibri
    { "Verdana",         "C:\\Windows\\Fonts\\verdana.ttf"          },  // Verdana
    { "NotoSansSC-VF",   "C:\\Windows\\Fonts\\NotoSansSC-VF.ttf"    },  // Noto

    // 风格字体
    { "InkFree",         "C:\\Windows\\Fonts\\InkFree.ttf"          },  // 墨水
    { "Gabriola",        "C:\\Windows\\Fonts\\Gabriola.ttf"         },  // Gabriola

};

// 这个只是缩放，并不改变字体
void ChangeFontScale(float size)
{
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = size;
}

void ChangeFont(const char* path, float size)
{
    ImGuiIO& io = ImGui::GetIO();
    m_defaultFontScale = io.FontGlobalScale;

    // 清空所有已加载的字体
    io.Fonts->Clear();

    ImFont* CurrentFont = io.Fonts->AddFontFromFileTTF(
        path,
        size,
        nullptr,
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon()
    );

    io.Fonts->Build();
}