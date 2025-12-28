#pragma once

#include <memory>
#include <string>
#include <mysql/jdbc.h>
#include "PreparedQuery.h"


class DBExecutor
{
public:
    DBExecutor();

    void Execute(const std::string& query);
    std::unique_ptr<sql::ResultSet> ExecuteQuery(const std::string& query);
    std::unique_ptr<sql::PreparedStatement> Prepare(const std::string& query);
    
    PreparedQuery PrepareQuery(const std::string& query);

private:
    sql::mysql::MySQL_Driver* m_driver;
    std::unique_ptr<sql::Connection> m_conn;
};