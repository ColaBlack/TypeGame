#pragma once
#include<graphics.h>
#pragma comment(lib,"WINMM.lib")


// 加载音频
inline void loadAudio(LPCWSTR path, LPCWSTR alias) {
static TCHAR str_cmd[MAX_PATH];
_stprintf_s(str_cmd, _T("open %s alias %s"), path, alias);
mciSendString(str_cmd, NULL, 0, NULL);
}

// 播放音频
inline void playAudio(LPCWSTR alias, bool loop = false) {
static TCHAR str_cmd[MAX_PATH];
_stprintf_s(str_cmd, _T("play %s %s from 0"), alias,loop? _T("repeat") : _T(""));
mciSendString(str_cmd, NULL, 0, NULL);
}

// 停止播放音频
inline void stopAudio(LPCWSTR alias) {
static TCHAR str_cmd[MAX_PATH];
_stprintf_s(str_cmd, _T("stop %s"), alias);
mciSendString(str_cmd, NULL, 0, NULL);
}