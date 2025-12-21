#pragma once
#include <string>
#include <sstream>

struct DBResult
{
    bool IsFail() const { return ok == false; }
    static DBResult Ok(int affected) { return { true, affected, 0, "", "" }; }
    static DBResult Fail(int code, std::string state, std::string msg)
    {
        DBResult r;
        r.ok = false;
        r.errorCode = code;
        r.sqlState = std::move(state);
        r.message = std::move(msg);
        return r;
    }

    bool ok = false;
    int affectedRows = 0;

    // 에러 정보(필요할 때만)
    int errorCode = 0;
    std::string sqlState;
    std::string message;

    std::string ToErrorString() const
    {
        std::ostringstream oss;
        oss << "[MySQL Error]\n"
            << "Error Code: " << errorCode << "\n"
            << "SQLState: " << sqlState << "\n"
            << "Message: " << message;
        return oss.str();
    }
};