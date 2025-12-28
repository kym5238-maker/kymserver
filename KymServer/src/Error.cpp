#include <ostream>
#include "Error.h"

// Error 자체를 스트림에 출력 가능하게
std::ostream& operator<<(std::ostream& os, ErrorCode code)
{
    return os << static_cast<int>(code);
}