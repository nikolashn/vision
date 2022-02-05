// For copyright/license information, see LICENSE

#include "GL/glew.h"
#define GLFW_DLL
#include "GLFW/glfw3.h"

#include "stdlib.h"
#include "stdio.h"

#include "ctx.h"
struct Ctx ctx;

#include "callbacks.h"

int main() {
	ctx.canvasMaxX = 640;
	ctx.canvasMaxY = 480;
	ctx.centerX = 320;
	ctx.centerY = 240;
	ctx.zoomFact = 1.0f;

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
	glfwSetWindowSizeCallback(window, CallbackWindowSize);
	glfwSetKeyCallback(window, CallbackKey);

	glewInit();

	const char* vertexShaderSrc =
	"#version 400\n"
	"in vec3 vp;\n"
	"void main() {\n"
	"  gl_Position = vec4(vp, 1.0);\n"
	"}";
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	const char* fragmentShaderSrc =
	"#version 400\n"
	"out vec4 frag_colour;\n"
	"void main() {\n"
	"  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);\n"
	"}";
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float canvasPoints[6*3] = {
		1, -1, 0,  -1, -1, 0,   1,  1, 0,
		1,  1, 0,  -1, -1, 0,  -1,  1, 0,
	};

	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6*3*sizeof(float), canvasPoints, 
		GL_STATIC_DRAW);

	unsigned int vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	while (!glfwWindowShouldClose(window)) {
		glfwGetWindowSize(window, &ctx.width, &ctx.height);
		{
			float pixX = 2 * ctx.zoomFact / (float)ctx.width;
			float pixY = 2 * ctx.zoomFact / (float)ctx.height;
			float l = pixX * -ctx.centerX;
			float t = pixY * ctx.centerY;
			float r = l + pixX * ctx.canvasMaxX;
			float b = t + pixY * -ctx.canvasMaxY;
			canvasPoints[0]  = r; canvasPoints[1]  = b;
			canvasPoints[3]  = l; canvasPoints[4]  = b;
			canvasPoints[6]  = r; canvasPoints[7]  = t;
			canvasPoints[9]  = r; canvasPoints[10] = t;
			canvasPoints[12] = l; canvasPoints[13] = b;
			canvasPoints[15] = l; canvasPoints[16] = t;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 6*3*sizeof(float), canvasPoints, 
			GL_STATIC_DRAW);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwTerminate();

	return 0;
}

