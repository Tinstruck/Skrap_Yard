cmake_minimum_required(VERSION 3.20)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Skrap_Yard" VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# GLFW
add_subdirectory(Resources/glfw)

# imgui 
add_library(imgui STATIC 
    Resources/imgui/imgui.cpp
    Resources/imgui/imgui_draw.cpp
    Resources/imgui/imgui_tables.cpp
    Resources/imgui/imgui_widgets.cpp
    Resources/imgui/backends/imgui_impl_glfw.cpp
    Resources/imgui/backends/imgui_impl_opengl3.cpp
    Resources/imgui/imgui_demo.cpp
)

# Tell ImGui where to find its own headers AND GLFW headers
target_include_directories(imgui PUBLIC 
    Resources/imgui 
    Resources/imgui/backends
    Resources/glfw/include
    Resources/OpenGL-Registry/api
)

# Link GLFW to imgui so backend functions build properly
target_link_libraries(imgui PUBLIC glfw)

add_executable(Skrap_Engine 
    Skrap_Engine/main.cpp
    Skrap_Engine/Skrap_Engine.h
    Skrap_Engine/icon.h
    Resources/glad/src/glad.c
)

target_include_directories(Skrap_Engine PRIVATE 
    Skrap_Engine
    Resources/glad/include
    Resources/OpenGL-Registry/api
    Resources/glfw/include
    Resources/imgui
    Resources/imgui/backends
)

target_link_libraries(Skrap_Engine PRIVATE 
    glfw 
    imgui 
    opengl32
)