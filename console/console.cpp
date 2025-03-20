#include "console.h"
#include <windows.h>   
#include <iostream>
#include <cstdio>     

using namespace std;   

Console console;  

void Console::printHeader()
{
    SetColor(YELLOW);
    WriteLine(L"  ____    ____    ____   ");
    WriteLine(L" |  _ \\  | __ )  | ___|  ");
    WriteLine(L" | |_) | |  _ \\  |___ \\  ");
    WriteLine(L" |  _ <  | |_) |  ___) | ");
    WriteLine(L" |_| \\_\\ |____/  |____/  ");
    WriteLine(L"\n\n");
}
void Console::CreateConsole(const wchar_t* title, int width, int height)
{
    if (AllocConsole())
    {
        SetConsoleTitleW(title);  

		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);		

        HWND consoleWindow = GetConsoleWindow();
        if (consoleWindow)
        {
            RECT rect;
            GetWindowRect(consoleWindow, &rect);
            MoveWindow(consoleWindow, rect.left, rect.top, width, height, TRUE);
        }
    }
    else
    {
        MessageBoxW(NULL, L"Failed to create console", L"Error", MB_OK | MB_ICONERROR);
    }
}

void Console::SetColor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Console::SetCursorPosition(int x, int y)
{
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console::Clear()
{
    COORD topLeft = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO screen;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacter(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void Console::Write(const wchar_t* text)
{
    wcout << text; 
}
void Console::Write(const char* text)
{
    cout << text;  
}

void Console::WriteLine(const wchar_t* text)
{
    wcout << text << endl;  
}

void Console::WriteLine(const char* text)
{
    cout << text << endl;  
}

void Console::Read(wchar_t* buffer, int length)
{
    wcin.read(buffer, length); 
}

void Console::ReadLine(wchar_t* buffer, int length)
{
    wcin.getline(buffer, length); 
}
