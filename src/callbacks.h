// For copyright/license information, see LICENSE
#ifndef __VISION_CALLBACKS_H
#define __VISION_CALLBACKS_H

#define SCROLL_RATE 16.0f
// fifth root of 2
#define ZOOM_FACT_FACT 1.148698354997035

void CallbackWindowSize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void CallbackKey(GLFWwindow* window, int key, int scanCode, int action, int mods) { }

void CallbackChar(GLFWwindow* window, unsigned int code) {
	static char pressed[0x100];
	static unsigned pressedCnt = 0;

	switch (code) {
		case 'h': case 'H': case 'l': case 'L': {
			// h: scroll left (H: x2 speed)
			// l: scroll right (L: x2 speed)
			if (!pressedCnt) {
				ctx.centerX += 
					((-1 * (code == 'h')) + (-2 * (code == 'H')) + 
						(1 * (code == 'l')) + (2 * (code == 'L'))) *
					SCROLL_RATE / ctx.zoomFact;
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case 'j': case 'J': case 'k': case 'K': {
			// j: scroll down (J: x2 speed)
			// k: scroll up (K: x2 speed)
			if (!pressedCnt) {
				ctx.centerY += 
					((-1 * (code == 'k')) + (-2 * (code == 'K')) + 
						(1 * (code == 'j')) + (2 * (code == 'J'))) *
					SCROLL_RATE / ctx.zoomFact;
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case '{': case '+': {
			// zoom in
			if (!pressedCnt) {
				ctx.zoomFact *= ZOOM_FACT_FACT;
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case '}': case '-': {
			// zoom out
			if (!pressedCnt) {
				ctx.zoomFact /= ZOOM_FACT_FACT;
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case 'z': {
			if (!pressedCnt) {
				++pressedCnt;
				pressed[0] = 'z';
			}
			// zz: center and reset zoom
			else if (pressedCnt == 1 && pressed[0] == 'z') {
				ctx.centerX = ctx.canvasMaxX / 2;
				ctx.centerY = ctx.canvasMaxY / 2;
				ctx.zoomFact = 1.0f;
				pressedCnt = 0;
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case 'Z': {
			if (!pressedCnt) {
				++pressedCnt;
				pressed[0] = 'Z';
			}
			// ZZ: exit and save
			else if (pressedCnt == 1 && pressed[0] == 'Z') {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		case 'Q': {
			// ZQ: exit and don't save
			if (pressedCnt == 1 && pressed[0] == 'Z') {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			else {
				pressedCnt = 0;
			}
		}
		break;

		pressedCnt = 0;
	}
}

#endif
