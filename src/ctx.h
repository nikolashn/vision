// For copyright/license information, see LICENSE
#ifndef __VISION_CTX_H
#define __VISION_CTX_H

struct Ctx {
	int width, height;
	int canvasMaxX, canvasMaxY;
	float centerX, centerY;
	float zoomFact;
	int mode;
	int tool; // TODO: tool settings (thickness, etc)
	int* pixels;
};

#endif
