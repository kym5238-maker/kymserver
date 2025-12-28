#pragma once
#include "ErrorCode.h"
#include <ostream>

struct Error
{
    bool IsFail() const { return code != ErrorCode::None; }
    operator ErrorCode() const { return code; }

    ErrorCode code = ErrorCode::None;
};

std::ostream& operator<<(std::ostream& os, ErrorCode code);
