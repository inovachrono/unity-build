#include "cpp_file_collection.h"
#include <stdio.h>

const s32 SCR_WIDTH = 800;
const s32 SCR_HEIGHT = 600;
const s32 DESIRED_FPS = 60;
const f32 REQUIRED_FRAME_TIME = 1/(f32)DESIRED_FPS;
const char *APPLICATION_NAME = "Unity Build System Demo";

void framebuffer_size_callback(GLFWwindow* window, s32 width, s32 height);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

s32 main()
{
	if (!glfwInit())
	{
		printf("ERROR: Initializing GLFW library\n");
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, APPLICATION_NAME, NULL, NULL);
	if (!window)
	{
		printf("ERROR: Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("ERROR: Getting opengl function pointers");
		glfwTerminate();
		return -1;
	}
	// After initalizing opengl functions, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	
	// Initialize imgui
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	f32 delta_time = 0.0f;
	f32 last_frame = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		f32 currentFrame = static_cast<f32>(glfwGetTime());
		delta_time = currentFrame - last_frame;
		while(delta_time < REQUIRED_FRAME_TIME)
		{
			currentFrame = static_cast<f32>(glfwGetTime());
			delta_time = currentFrame - last_frame;
		}
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;
		f32 frame_rate = 1.0f / delta_time;

		// Application code here
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowSize(ImVec2(100.0f, 40.0f));
		ImGui::Text("FPS: %f", frame_rate);
		ImGui::Button("Click ME");
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, s32 width, s32 height)
{
	glViewport(0, 0, width, height);
}

// opengl error callback
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
	ASSERT(0);
}
