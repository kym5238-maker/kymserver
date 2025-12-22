#include "Logger.h"

#include <filesystem>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <Windows.h>

namespace
{
    bool g_initialized = false;
    std::mutex g_initMutex;
    std::mutex g_writeMutex;

    std::ofstream g_infoFile;
    std::ofstream g_errorFile;

    std::string g_timestamp; // 파일명용 타임스탬프

    std::filesystem::path GetExeDir()
    {
        wchar_t buf[MAX_PATH]{};
        GetModuleFileNameW(nullptr, buf, MAX_PATH);
        return std::filesystem::path(buf).parent_path();
    }

    std::string MakeTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(now);

        std::tm tm{};
        localtime_s(&tm, &tt);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d%H%M%S");
        return oss.str();
    }

    std::string TimestampLine()
    {
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(now);

        std::tm tm{};
        localtime_s(&tm, &tt);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    void InitIfNeeded()
    {
        if (g_initialized)
            return;

        std::lock_guard<std::mutex> lock(g_initMutex);
        if (g_initialized)
            return;

        auto logDir = GetExeDir() / "log";
        std::filesystem::create_directories(logDir);

        g_timestamp = MakeTimestamp();
        g_initialized = true;
    }

    void EnsureInfoFileOpen()
    {
        if (g_infoFile.is_open())
            return;

        auto logDir = GetExeDir() / "log";
        g_infoFile.open(
            logDir / ("INFO_" + g_timestamp + ".log"),
            std::ios::out | std::ios::app
        );
    }

    void EnsureErrorFileOpen()
    {
        if (g_errorFile.is_open())
            return;

        auto logDir = GetExeDir() / "log";
        g_errorFile.open(
            logDir / ("ERROR_" + g_timestamp + ".log"),
            std::ios::out | std::ios::app
        );
    }
}

void Logger::LogImpl(Level level, const std::string& message)
{
    InitIfNeeded();

    const std::string line =
        "[" + TimestampLine() + "] " + message + "\n";

    std::lock_guard<std::mutex> lock(g_writeMutex);

    if (level == Level::INFO)
    {
        EnsureInfoFileOpen();
        g_infoFile << line;
        g_infoFile.flush();
    }
    else
    {
        EnsureErrorFileOpen();
        g_errorFile << line;
        g_errorFile.flush();
    }
}