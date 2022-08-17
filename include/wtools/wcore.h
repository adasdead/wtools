#ifndef WTOOLS_WCORE_H
#define WTOOLS_WCORE_H

#define W_OK                            0
#define W_ERR                           -1

typedef char *w_astr_t;
typedef const w_astr_t w_castr_t;
typedef short w_result_t;

#if _MSC_VER

#pragma warning(disable:4996)

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#endif // _MSC_VER

#if _WIN32

#include <wchar.h>
#include <windows.h>

#define W_WIN32_MAIN_VOID(main_func)                     \
    int WINAPI wWinMain(HINSTANCE hInstance,             \
                        HINSTANCE hPrevInstance,         \
                        PWSTR pCmdLine, int nCmdShow)    \
    {                                                    \
        main_func();                                     \
        return 0;                                        \
    }

// https://habr.com/ru/sandbox/43899/

#define W_WIN32_MAIN_ARGS(main_func)                     \
    int WINAPI wWinMain(HINSTANCE hInstance,             \
                        HINSTANCE hPrevInstance,         \
                        PWSTR pCmdLine, int nCmdShow)    \
    {                                                    \
        int argc;                                        \
        char **argv;                                     \
                                                         \
        LPWSTR *largv = CommandLineToArgvW(pCmdLine,     \
                                            &argc);      \
                                                         \
        argv = (char**) malloc(argc * sizeof(char*));    \
                                                         \
        size_t size = 0;                                 \
        for(int i = 0; i < argc; i++)                    \
        {                                                \
            size = wcslen(largv[i]) + 1;                 \
            argv[i] = malloc(size);                      \
            wcstombs(argv[i], largv[i], size);           \
        }                                                \
                                                         \
        LocalFree(largv);                                \
                                                         \
        main_func(argc, argv);                           \
                                                         \
        for(int i = 0; i < argc; i++)                    \
        {                                                \
            free(argv[i]);                               \
            free(argv);                                  \
        }                                                \
    }

typedef wchar_t *w_wstr_t;

static void w_ascii_to_utf16le(w_wstr_t dest,
                               w_castr_t src,
                               size_t size)
{
    if (!src || !dest || !size) return;

    MultiByteToWideChar(CP_UTF8, 0, src, -1,
                        dest, (int) size);
}

static void w_utf16le_to_ascii(w_castr_t dest,
                               w_wstr_t src,
                               size_t size)
{
    if (!src || !dest || !size) return;

    WideCharToMultiByte(CP_UTF8, 0, src, -1,
                        dest, (int) size,
                        NULL, NULL);
}

#elif
#   define W_WIN32_MAIN_VOID(main_func)
#   define W_WIN32_MAIN_ARGS(main_func)
#endif // _WIN32

#endif // WTOOLS_WCORE_H