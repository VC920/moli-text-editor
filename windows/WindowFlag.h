#pragma once
#include <string>
#include <vector>
#include <TextEditor.h>

extern bool show_demo;
extern bool show_info;
extern bool show_about;
extern bool show_editor;
extern bool show_terminal;

// 编辑器窗口结构
struct EditorDocument {
    bool active;
    TextEditor editor;
    std::string filePath;
    std::string title;
};

extern std::vector<EditorDocument> m_docs;
extern EditorDocument* m_currentDoc;
