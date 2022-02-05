// For copyright/license information, see LICENSE
#ifndef __VISION_CALLBACKS_H
#define __VISION_CALLBACKS_H

void CallbackWindowSize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void CallbackKey(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	static char pressed[0x100];
	static unsigned pressedCnt = 0;

	if (action == GLFW_RELEASE) {
		return;
	}

	switch (key) {
		case GLFW_KEY_Z: {
			if (!pressedCnt) {
				++pressedCnt;
				pressed[0] = 'Z';
			}
			// ZZ: exit and save
			else if (pressed[0] == 'Z') {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case GLFW_KEY_Q: {
			// ZQ: exit and don't save
			if (pressed[0] == 'Z') {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}
		break;
	}
}

#endif
