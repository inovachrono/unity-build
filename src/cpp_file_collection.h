#ifndef CPP_FILE_COLLECTION_H
#define CPP_FILE_COLLECTION_H

// include files ordered are in the increasing order of dependency after including 3rd party includes first

#include "nova_define.h"    // always first
#include "nova_base.h"      // always second

#include <glad/glad.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
// Since we are using glad opengl function we don't want imgui to declare and define macros with it's implementation of opengl. Thus avoiding macro redefinition.
// Make sure to init ImGui_ImplOpenGL3_Init after loading opengl functions
#include <imgui/imgui_draw.cpp>
#include <imgui/imgui_impl_glfw.cpp>
#include <imgui/imgui_impl_opengl3.cpp>
#include <imgui/imgui_tables.cpp>
#include <imgui/imgui_widgets.cpp>
#include <imgui/imgui.cpp>

// Including glad.c after imgui cpp files since they don't do check for APIENTRY macro redefinition but glad does
#include <glad/glad.c>

// including glfw
#include <glfw/glfw3.h>

#endif
