#pragma once

#include <map>
#include <ctime>
#include <string>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>

#include "Logs.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define LOG_FILE "logs.txt"

#define INFO "INFO"
#define WARN "WARN"
#define FAIL "FAIL"
#define DONE "DONE"
#define WAIT "WAIT"
#define MEMORY "===>"

class Logger
{
    public:
        struct Log
        {
            std::string message;
            std::string color;
        };

        const std::map<std::string, Log> log_message = {
            { "info", { INFO, WHITE } },
            { "warn", { WARN, YELLOW } },
            { "error", { FAIL, RED } },
            { "done", { DONE, GREEN } },
            { "wait", { WAIT, WHITE } },
            { "memory", { MEMORY, YELLOW }}
        };

        Logger();
        ~Logger();

        void Log(std::string, const std::string);

    private:
        std::string BuildLog(std::string type, std::string message);
        bool SaveLog(std::string);
};