#pragma once
#include <windows.h> 

#define RED FOREGROUND_RED | FOREGROUND_INTENSITY
#define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define MAGENTA FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define CYAN FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define GRAY FOREGROUND_INTENSITY
#define DARK_RED FOREGROUND_RED
#define DARK_GREEN FOREGROUND_GREEN
#define DARK_BLUE FOREGROUND_BLUE
#define DARK_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define DARK_MAGENTA FOREGROUND_RED | FOREGROUND_BLUE
#define DARK_CYAN FOREGROUND_GREEN | FOREGROUND_BLUE

class Console
{
public:
    void printHeader();
    void CreateConsole(const wchar_t* title, int width = 800, int height = 600);
    void SetColor(WORD color);
    void SetCursorPosition(int x, int y);
    void Clear();
    void Write(const wchar_t* text);
    void WriteLine(const wchar_t* text);
    void Write(const char* text);
    void WriteLine(const char* text);
    void Read(wchar_t* buffer, int length);
    void ReadLine(wchar_t* buffer, int length);
};

extern Console console;  
