#pragma once
#include <string>
#include <string_view>
#include <sstream>

class Logger
{
public:
    enum class Level { Info, Error };

    // 템플릿은 헤더에 정의(중요!)
    template<typename... Args>
    static void Info(std::string_view fmt, Args&&... args)
    {
        LogImpl(Level::Info, BuildMessage(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void Error(std::string_view fmt, Args&&... args)
    {
        LogImpl(Level::Error, BuildMessage(fmt, std::forward<Args>(args)...));
    }

private:
    // 실제 파일 출력은 cpp에 구현(템플릿 아님)
    static void LogImpl(Level level, const std::string& message);

    // "{}" 아주 단순 치환: fmt 안의 {}를 args 순서대로 스트리밍해서 넣음
    static void ReplaceOne(std::ostringstream& out, std::string_view fmt)
    {
        out << fmt;
    }

    template<typename T, typename... Rest>
    static void ReplaceOne(std::ostringstream& out, std::string_view fmt, T&& v, Rest&&... rest)
    {
        const size_t pos = fmt.find("{}");
        if (pos == std::string_view::npos)
        {
            out << fmt;
            return;
        }

        out << fmt.substr(0, pos);
        out << std::forward<T>(v);
        ReplaceOne(out, fmt.substr(pos + 2), std::forward<Rest>(rest)...);
    }

    template<typename... Args>
    static std::string BuildMessage(std::string_view fmt, Args&&... args)
    {
        std::ostringstream oss;
        ReplaceOne(oss, fmt, std::forward<Args>(args)...);
        return oss.str();
    }
};

// 매크로
#define LOG_INFO(fmt, ...)  ::Logger::Info((fmt), ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) ::Logger::Error((fmt), ##__VA_ARGS__)
