cmake_minimum_required(VERSION 3.10)
project(moli)

set(SDL2_DIR "thirdparty/SDL2/lib/cmake/SDL2")
find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME}
    thirdparty/imgui/src/imgui.cpp
    thirdparty/imgui/src/imgui_demo.cpp
    thirdparty/imgui/src/imgui_draw.cpp
    thirdparty/imgui/src/imgui_tables.cpp
    thirdparty/imgui/src/imgui_widgets.cpp
    thirdparty/imgui/src/imgui_impl_sdl2.cpp
    thirdparty/imgui/src/imgui_impl_sdlrenderer2.cpp
    thirdparty/tinyfiledialogs/tinyfiledialogs.c
    thirdparty/ImGuiColorTextEdit/TextEditor.cpp
    main.cpp
    manager/DisplayManager.cpp
    manager/UIManager.cpp
    manager/InputManager.cpp
    function/f_Encode.cpp
    function/f_File.cpp
    function/f_Font.cpp
    windows/WindowFlag.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    thirdparty/SDL2/include/SDL2
    thirdparty/imgui/include
    thirdparty/tinyfiledialogs
    thirdparty/ImGuiColorTextEdit
    manager
    windows
    function
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2-static
)