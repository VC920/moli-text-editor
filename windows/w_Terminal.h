/*
    ai 写的，以后会重写，这里先实现这样就可以自举了
*/


#pragma once
#include "WindowFlag.h"
#include "f_Encode.h"

#include <imgui.h>
#include <windows.h>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

static std::vector<std::string> g_terminalLines;
static char g_terminalInput[256] = "";
static HANDLE g_hInputWrite = NULL;
static HANDLE g_hOutputRead = NULL;
static HANDLE g_hProcess = NULL;
static std::string g_pendingOutput;

void RenderTerminal()
{
    if (!show_terminal) return;
    // ========== 初始化（只执行一次） ==========
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        
        // 创建管道
        HANDLE hInputRead, hOutputWrite;
        SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
        
        CreatePipe(&g_hOutputRead, &hOutputWrite, &sa, 0);
        CreatePipe(&hInputRead, &g_hInputWrite, &sa, 0);
        
        // 启动 CMD
        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        si.dwFlags = STARTF_USESTDHANDLES;
        si.hStdInput = hInputRead;
        si.hStdOutput = hOutputWrite;
        si.hStdError = hOutputWrite;
        
        CreateProcessA(NULL, (LPSTR)"cmd.exe", NULL, NULL, TRUE, 
                       CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
        
        CloseHandle(pi.hThread);
        CloseHandle(hInputRead);
        CloseHandle(hOutputWrite);
        g_hProcess = pi.hProcess;

        // 等待 CMD 启动完成
        Sleep(100);
    
        // 发送初始命令（示例：设置编码为UTF-8）
        std::string initCmd;
        DWORD written;

        initCmd = "cd /d C:\\Users\\%USERNAME%\n";
        WriteFile(g_hInputWrite, initCmd.c_str(), initCmd.size(), &written, NULL);

        initCmd = "dir\n";
        WriteFile(g_hInputWrite, initCmd.c_str(), initCmd.size(), &written, NULL);
        
        g_terminalLines.push_back("=== CMD Terminal Ready ===");
    }
    
    // ========== 读取 CMD 输出 ==========
    char buffer[4096];
    DWORD bytesRead;
    while (PeekNamedPipe(g_hOutputRead, NULL, 0, NULL, &bytesRead, NULL) && bytesRead > 0) {
        if (ReadFile(g_hOutputRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            g_pendingOutput += buffer;
            
            // 按行分割
            size_t pos;
            while ((pos = g_pendingOutput.find('\n')) != std::string::npos) {
                std::string line = g_pendingOutput.substr(0, pos);
                if (!line.empty() && line.back() == '\r') line.pop_back();
                if (!line.empty()) {
                    // 转换编码
                    line = GBKToUTF8(line);
                    g_terminalLines.push_back(line);
                }
                g_pendingOutput.erase(0, pos + 1);
            }
        }
    }
    
    // ========== 渲染 ImGui 窗口 ==========
    ImGui::Begin("Terminal", &show_terminal);
    
    // 输出区域
    ImGui::BeginChild("Output", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
    for (const auto& line : g_terminalLines) {
        ImGui::TextUnformatted(line.c_str());
    }
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();
    
    // 输入框
    ImGui::PushItemWidth(-1);
    if (ImGui::InputText("##cmd", g_terminalInput, sizeof(g_terminalInput), 
                         ImGuiInputTextFlags_EnterReturnsTrue)) {
        // 发送命令到 CMD
        if (g_hInputWrite) {
            std::string cmd = std::string(g_terminalInput) + "\n";
            DWORD written;
            WriteFile(g_hInputWrite, cmd.c_str(), cmd.size(), &written, NULL);
        }
        // 清空输入框
        memset(g_terminalInput, 0, sizeof(g_terminalInput));
        ImGui::SetKeyboardFocusHere(-1);
    }
    ImGui::PopItemWidth();
    
    ImGui::End();
}