#include "Logger.h"

Logger::Logger()
{
    // Initialization code
}

Logger::~Logger()
{
    // Cleanup code
}

void Logger::Log(std::string type, const std::string message)
{
    std::ofstream logfile(LOG_FILE, std::ios::app);
    std::string log = BuildLog(type, message);

    if (logfile.is_open() == true)
    {
        std::cout << log << std::endl;
        logfile << log << std::endl;
        logfile.close();
    } else
    {
        std::cerr << "Error: Unable to open the log file." << std::endl;
    }
}

std::string Logger::BuildLog(std::string type, std::string message)
{
    auto it = log_message.find(type);
    std::string log = std::format("{}[{}] {}{}", it->second.color, it->second.message, message, RESET);

    return (log);
}
