#include "Console.h"

#include <iostream>
#include <windows.h>



////////////////////////////////////////////////////////////////////////////////
/////   CONSOLE                                                            /////
////////////////////////////////////////////////////////////////////////////////

void Console::info(const std::string& message, const std::vector<std::string>& messages)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 3);
    std::cout << "Info:\t";
    SetConsoleTextAttribute(handle, 7);
    std::cout << message << std::endl;

    for (const auto& msg : messages) {
        std::cout << "\t" << msg << std::endl;
    }
}

void Console::warn(const std::string& message, const std::vector<std::string>& messages)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 6);
    std::cout << "Warn:\t";
    SetConsoleTextAttribute(handle, 7);
    std::cout << message << std::endl;

    for (const auto& msg : messages) {
        std::cout << "\t" << msg << std::endl;
    }
}

void Console::error(const std::string& message, const std::vector<std::string>& messages)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 4);
    std::cout << "Error:\t";
    SetConsoleTextAttribute(handle, 7);
    std::cout << message << std::endl;

    for (const auto& msg : messages) {
        std::cout << "\t" << msg << std::endl;
    }
}