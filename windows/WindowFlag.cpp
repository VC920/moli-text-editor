#include "WindowFlag.h"

bool show_demo = false;
bool show_info = true;
bool show_about = false;
bool show_editor = true;
bool show_terminal = true;

std::vector<EditorDocument> m_docs;
EditorDocument* m_currentDoc = nullptr;