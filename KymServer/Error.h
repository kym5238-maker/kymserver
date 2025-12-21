#pragma once
#include "ErrorCode.h"
#include <ostream>

struct Error
{
    bool IsFail() const { return code != ErrorCode::None; }
    operator ErrorCode() const { return code; }

    ErrorCode code = ErrorCode::None;
};

// Error 자체를 스트림에 출력 가능하게
inline std::ostream& operator<<(std::ostream& os, ErrorCode code)
{
    return os << static_cast<int>(code);
}