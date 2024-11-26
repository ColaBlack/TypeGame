#pragma once
#include<graphics.h>
#pragma comment(lib,"MSIMG32.LIB")

//水平翻转图片
inline void flipImage(IMAGE* src, IMAGE* dst) {
	int width = src->getwidth();
	int height = src->getheight();

	Resize(dst, width, height);

	DWORD* srcBuffer = GetImageBuffer(src);
	DWORD* dstBuffer = GetImageBuffer(dst);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dstBuffer[y * width + (width - 1 - x)] = srcBuffer[y * width + x];
		}
	}
}

// 放置有透明度的图片
inline void putImageAlpha(IMAGE* img, int x, int y) {
	int width = img->getwidth();
	int height = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, width, height, GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER,0,255,AC_SRC_OVER });
}