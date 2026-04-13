#pragma once

#include <string>
#include <unordered_map>

extern float m_defaultFontScale;
extern float m_currentFontScale;

// 字体文件的路径常量
extern std::unordered_map<std::string, std::string> m_fonts;

// 这个只是缩放，并不改变字体
void ChangeFontScale(float size);

void ChangeFont(const char* path, float size);