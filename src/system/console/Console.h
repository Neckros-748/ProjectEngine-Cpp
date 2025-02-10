#pragma once
#include <string>
#include <vector>



class Console {
private:

public:
    static void info(const std::string& message, const std::vector<std::string>& messages = {});
    static void warn(const std::string& message, const std::vector<std::string>& messages = {});
    static void error(const std::string& message, const std::vector<std::string>& messages = {});

private:
    Console() = delete;
    ~Console() = delete;
};