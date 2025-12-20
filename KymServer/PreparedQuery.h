#pragma once

#include <memory>
#include <string>
#include <mysql/jdbc.h>
#include "DbResult.h"
#include "DbQueryResult.h"

class PreparedQuery
{
public:
    PreparedQuery& operator<<(const std::string& value);
    PreparedQuery& operator<<(const char* value);
    PreparedQuery& operator<<(int value);

    explicit PreparedQuery(std::unique_ptr<sql::PreparedStatement> pstmt);
    std::unique_ptr<sql::ResultSet> ExecuteQuery();

    int ExecuteUpdate();
    DbResult TryExecuteUpdate(int ignoreErrorCode = 0);
    DbQueryResult TryExecuteQuery();

private:
    std::unique_ptr<sql::PreparedStatement> m_pstmt;
    int m_paramIndex;
};