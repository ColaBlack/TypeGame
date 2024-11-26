#pragma once
#include<graphics.h>

//水平翻转图片
inline void flipImage(IMAGE* src,IMAGE* dst) {
	int width = src->getwidth();
	int height = src->getheight();

	Resize(dst, width, height);

	DWORD* srcBuffer=GetImageBuffer(src);
	DWORD* dstBuffer=GetImageBuffer(dst);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstBuffer[y * width + (width - 1 - x)] = srcBuffer[y * width + x];
		}
	}
}