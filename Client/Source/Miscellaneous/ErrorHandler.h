#pragma once

namespace {
	#include <windows.h>
	void Abort(const char* errorMessage, const char* title) {
		MessageBoxA(nullptr, errorMessage, title, MB_ICONERROR | MB_OK);
		exit(0);
	}
}