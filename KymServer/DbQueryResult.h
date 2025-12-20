#pragma once
#include <memory>
#include <mysql/jdbc.h>
#include "DbResult.h"

struct DbQueryResult
{
    DbResult result;
    std::unique_ptr<sql::ResultSet> rs;

    bool IsFail() const { return result.IsFail(); }
    std::string ToErrorString() const { return result.ToErrorString(); }
};