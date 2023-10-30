#include "Logger.h"

Logger::Logger(bool d)
{
    display = d;
}

Logger::~Logger()
{
    // Cleanup code
}

void Logger::Log(std::string type, const std::string message)
{
    if (display == true)
    {
        std::string log = BuildLog(type, message);

        SaveLog(log);
    }
}

std::string Logger::BuildLog(std::string type, std::string message)
{
    auto it = log_message.find(type);
    std::string log = std::format("[{}] {}", it->second.message, message);

    std::cout << it->second.color << log << RESET << std::endl;

    return (log);
}

bool Logger::SaveLog(std::string log)
{
    std::ofstream logfile(LOG_FILE, std::ios::app);

    if (logfile.is_open() == true)
    {
        logfile << log << std::endl;
        logfile.close();
        return (true);
    }

    std::cerr << LOG_FAIL_OPENNING_LOGILE << std::endl;
    return (false);
}
