#include "f_File.h"
#include "WindowFlag.h"
#include <iostream>
#include <tinyfiledialogs.h>
#include <fstream>
#include <string>

bool FindDocTitle(const char* title)
{
    for (int i = 0; i < m_docs.size(); i++)
    {
        if (m_docs[i].title == title)
            return true;
    }
    return false;
}

// 新建文件
void NewFile()
{
    static int newFileNum = 0;
    EditorDocument doc;

    doc.active = true;
    doc.editor.SetText("");
    doc.filePath = "";
    doc.title = "Untitled_" + std::to_string(newFileNum);

    m_docs.push_back(doc);
    newFileNum++;
}

// 打开文件
void OpenFile()
{
    const char* filters[] = { "*.txt", "*.cpp", "*.h", "*.hlsl", "*.fx", "*.glsl", "*.lua", "*.*" };
    const char* filePath = tinyfd_openFileDialog(
        "打开文件",           // 标题
        "",                  // 默认路径
        8,                   // 过滤器数量
        filters,             // 过滤器数组
        NULL,                // 单个过滤器描述
        0                    // 是否允许多选 (0=单选)
    );
    
    if (filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (file.is_open())
        {
            // 读取文件内容
            std::string content((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());
            file.close();
            
            EditorDocument doc;
            doc.active = true; // 设置激活状态
            doc.editor.SetText(content); // 设置文本到编辑器
            doc.filePath = filePath; // 保存当前文件路径

            size_t pos = doc.filePath.find_last_of("/\\");
            std::string fileName = doc.filePath.substr(pos + 1);
            doc.title = fileName; // 设置标题

            if (!FindDocTitle(doc.title.c_str()))
                m_docs.push_back(doc);
        }
        else
        {
            tinyfd_messageBox("错误", "无法打开文件", "ok", "error", 1);
        }
    }
}

// 另存为文件
void SaveAsFile()
{
    const char* filters[] = { "*.txt", "*.cpp", "*.h", "*.hlsl", "*.fx", "*.glsl", "*.lua", "*.*" };
    const char* filePath = tinyfd_saveFileDialog(
        "保存文件",          // 标题
        "",                  // 默认路径
        8,                   // 过滤器数量
        filters,             // 过滤器数组
        NULL                 // 单个过滤器描述
    );
    
    if (filePath)
    {
        std::ofstream file(filePath, std::ios::binary);
        if (file.is_open())
        {
            std::string content = m_currentDoc->editor.GetText();
            // 去除末尾的换行符
            while (!content.empty() && (content.back() == '\n' || content.back() == '\r'))
            {
                content.pop_back();
            }
            file.write(content.c_str(), content.size());
            file.close();
            tinyfd_messageBox("成功", "文件已保存", "ok", "info", 1);
            // 直接打开
            m_currentDoc->active = false;

            EditorDocument doc;
            doc.active = true; // 设置激活状态
            doc.editor.SetText(content); // 设置文本到编辑器
            doc.filePath = filePath; // 保存当前文件路径

            size_t pos = doc.filePath.find_last_of("/\\");
            std::string fileName = doc.filePath.substr(pos + 1);
            doc.title = fileName; // 设置标题

            if (!FindDocTitle(doc.title.c_str()))
                m_docs.push_back(doc);
        }
        else
        {
            tinyfd_messageBox("错误", "无法保存文件", "ok", "error", 1);
        }
    }
}

// 保存文件
void SaveFile()
{
    std::string filePath;

    filePath = m_currentDoc->filePath;

    // 如果没有文件路径，则调用另存为
    if (filePath.empty())
    {
        SaveAsFile();
        return;
    }
    
    std::ofstream file(filePath, std::ios::binary);
    if (file.is_open())
    {
        std::string content = m_currentDoc->editor.GetText();
        // 去除末尾的换行符
        while (!content.empty() && (content.back() == '\n' || content.back() == '\r'))
        {
            content.pop_back();
        }
        
        file.write(content.c_str(), content.size());
        file.close();
        tinyfd_messageBox("成功", "文件已保存", "ok", "info", 1);
    }
    else
    {
        tinyfd_messageBox("错误", "无法保存文件", "ok", "error", 1);
    }
}

