#pragma once
#include <windows.h>

namespace {
	void Abort(const char* errorMessage, const char* title) {
		MessageBoxA(nullptr, errorMessage, title, MB_ICONERROR | MB_OK);
		exit(0);
	}
}