// For copyright/license information, see LICENSE
#ifndef __VISION_CALLBACKS_H
#define __VISION_CALLBACKS_H

void CallbackWindowSize(GLFWwindow*, int width, int height) {
	glViewport(0, 0, width, height);
}

#endif
