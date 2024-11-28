#pragma once
#include<graphics.h>
#include"Camera.h"
#pragma comment(lib,"MSIMG32.LIB")

typedef struct {
	int x, y, w, h;
}Rect;


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

// 放置有透明度的图片，不依赖摄像机
inline void putImageAlpha(IMAGE* img, int x, int y) {
	int width = img->getwidth();
	int height = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, width, height, GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER,0,255,AC_SRC_OVER });
}

// 放置带透明度图片，依赖摄像机，带裁切功能
inline void putImageAlphaCam(const Camera& camera, IMAGE* img, const Rect* dst, const Rect* src = nullptr) {
	const Vector2D pos = camera.getPosition();

	AlphaBlend(
		GetImageHDC(GetWorkingImage()),
		(int)(dst->x - pos.x),
		(int)(dst->y - pos.y),
		dst->w,
		dst->h,
		GetImageHDC(img),
		src ? src->x : 0,
		src ? src->y : 0,
		src ? src->w : img->getwidth(),
		src ? src->h : img->getheight(),
		{ AC_SRC_OVER,0,255,AC_SRC_ALPHA }
	);
}