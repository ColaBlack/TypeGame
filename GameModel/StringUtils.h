#pragma once
#include <Windows.h>
#include <string>

std::wstring string2wstring(const char* utf8_string)
{
	// 获取UTF-8字符串的长度
	int len = strlen(utf8_string);

	// 计算所需缓冲区大小
	int w_size = MultiByteToWideChar(CP_UTF8, 0, utf8_string, len, NULL, 0);

	// 分配宽字符串缓冲区
	wchar_t* w_string = (wchar_t*)malloc((w_size + 1) * sizeof(wchar_t));

	// 将UTF-8多字节转换为宽字符串
	MultiByteToWideChar(CP_UTF8, 0, utf8_string, len, w_string, w_size);
	w_string[w_size] = L'\0';  // 添加NULL终止字符
	return w_string;
}