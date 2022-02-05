// For copyright/license information, see LICENSE
#ifndef __VISION_CALLBACKS_H
#define __VISION_CALLBACKS_H

#define SCROLL_RATE 16.0f
// fifth root of 2
#define ZOOM_FACT_FACT 1.148698354997035

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
		case GLFW_KEY_H: {
			// h: move left
			if (!pressedCnt) {
				ctx.centerX -= SCROLL_RATE / ctx.zoomFact;
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case GLFW_KEY_J: {
			// J: zoom out
			if (mods & GLFW_MOD_SHIFT) {
				ctx.zoomFact /= ZOOM_FACT_FACT;
			}
			else {
				// j: move down
				if (!pressedCnt) {
					ctx.centerY += SCROLL_RATE / ctx.zoomFact;
				}
				else {
					pressedCnt = 0;
				}
			}
		}
		break;

		case GLFW_KEY_K: {
			// K: zoom in
			if (mods & GLFW_MOD_SHIFT) {
				ctx.zoomFact *= ZOOM_FACT_FACT;
			}
			else {
				// k: move up
				if (!pressedCnt) {
					ctx.centerY -= SCROLL_RATE / ctx.zoomFact;
				}
				else {
					pressedCnt = 0;
				}
			}
		}
		break;

		case GLFW_KEY_L: {
			// l: move right
			if (!pressedCnt) {
				ctx.centerX += SCROLL_RATE / ctx.zoomFact;
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case GLFW_KEY_Z: {
			if (mods & GLFW_MOD_SHIFT) {
				if (!pressedCnt) {
					++pressedCnt;
					pressed[0] = 'Z';
				}
				// ZZ: exit and save
				else if (pressed[0] == 'Z') {
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				}
			}
			else {
				if (!pressedCnt) {
					++pressedCnt;
					pressed[0] = 'z';
				}
				// zz: center and reset zoom
				else if (pressed[0] == 'z') {
					ctx.centerX = ctx.canvasMaxX / 2;
					ctx.centerY = ctx.canvasMaxY / 2;
					ctx.zoomFact = 1.0f;
					pressedCnt = 0;
				}
				else {
					pressedCnt = 0;
				}
			}
		}
		break;

		case GLFW_KEY_Q: {
			if (mods & GLFW_MOD_SHIFT) {
				// ZQ: exit and don't save
				if (pressed[0] == 'Z') {
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				}
			}
		}
		break;
	}
}

#endif
