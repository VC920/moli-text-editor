#pragma once
#include <string>

// 将 UTF-8 字符串转换为 UTF-16 宽字符串（用于 Windows 文件路径）
std::wstring Utf8ToWide(const std::string& utf8Str);

std::string GBKToUTF8(const std::string& gbkStr);