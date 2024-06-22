#pragma once
namespace Core {
    #ifndef VERIFY
        _ACRTIMP void __cdecl _wassert(
            _In_z_ wchar_t const* _Message,
            _In_z_ wchar_t const* _File,
            _In_   unsigned       _Line
        );

        #define VERIFY(expression) (void)(                                                           \
            (!!(expression)) ||                                                                      \
            (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0)         \
        )
    #endif

    #include <windows.h>
    static inline void Abort(const char* errorMessage, const char* title) {
	    MessageBoxA(nullptr, errorMessage, title, MB_ICONERROR | MB_OK);
	    exit(0);
    }
}