#include "GL/glew.h"
#define GLFW_DLL
#include "GLFW/glfw3.h"

#include "stdlib.h"
#include "stdio.h"

int main() {
	if (!glfwInit()) {
		printf("Error: Could not start GLFW3\n");
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Vision", NULL, NULL);
	if (!window) {
		printf("Error: Could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float tPoints[] = {
		0.5f, -0.25f, 0.0f,
		-0.5f, -0.25f, 0.0f,
		0.0f, 0.5f, 0.0f,
	};

	const char* vertex_shader =
	"#version 400\n"
	"in vec3 vp;\n"
	"void main() {\n"
	"  gl_Position = vec4(vp, 1.0);\n"
	"}";

	const char* fragment_shader =
	"#version 400\n"
	"out vec4 frag_colour;\n"
	"void main() {\n"
	"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);\n"
	"}";

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

		unsigned int vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), tPoints, GL_STATIC_DRAW);

		unsigned int vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	glfwTerminate();

	return 0;
}
