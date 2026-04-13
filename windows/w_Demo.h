#pragma once
#include "WindowFlag.h"

#include <imgui.h>

void RenderDemo()
{
    if (!show_demo) return;
    ImGui::ShowDemoWindow(&show_demo);
}