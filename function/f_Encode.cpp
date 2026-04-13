#include <winnls.h>
#include <string>

// 将 UTF-8 字符串转换为 UTF-16 宽字符串（用于 Windows 文件路径）
std::wstring Utf8ToWide(const std::string& utf8Str)
{
    if (utf8Str.empty()) return L"";
    
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), 
                                           (int)utf8Str.size(), NULL, 0);
    std::wstring wideStr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), (int)utf8Str.size(), 
                        &wideStr[0], size_needed);
    return wideStr;
}

// GBK 转 UTF-8
std::string GBKToUTF8(const std::string& gbkStr) {
    if (gbkStr.empty()) return "";
    
    // 计算需要的宽字符缓冲区大小
    int unicodeLen = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
    if (unicodeLen <= 0) return gbkStr;
    
    // 转换为宽字符
    std::wstring wideStr(unicodeLen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, &wideStr[0], unicodeLen);
    
    // 计算 UTF-8 缓冲区大小
    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, NULL, 0, NULL, NULL);
    if (utf8Len <= 0) return gbkStr;
    
    // 转换为 UTF-8
    std::string utf8Str(utf8Len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], utf8Len, NULL, NULL);
    
    // 移除末尾的空字符
    if (!utf8Str.empty() && utf8Str.back() == '\0') {
        utf8Str.pop_back();
    }
    
    return utf8Str;
}