#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <assert.h>

namespace Core {
    #define VERIFY(expression) assert(expression)
    #define VERIFYF(expression, errorMessage)                           \
        if (!(expression)) std::cout << errorMessage << std::endl;        \
        assert(expression);

    static inline void Abort(const char* errorMessage, const char* title) {
	    MessageBoxA(nullptr, errorMessage, title, MB_ICONERROR | MB_OK);
	    exit(0);
    }
}