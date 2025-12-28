#include "DBExecutor.h"

DBExecutor::DBExecutor()
{
    const char* HOST = "tcp://127.0.0.1:3306";
    const char* USER = "root";
    const char* PASS = "dudahr5";
    const char* DB = "kymdb";

    m_driver = sql::mysql::get_mysql_driver_instance();
    m_conn.reset(m_driver->connect(HOST, USER, PASS));
    m_conn->setSchema(DB);

    std::unique_ptr<sql::Statement> stmt(m_conn->createStatement());
    stmt->execute("SET NAMES utf8mb4");
}

void DBExecutor::Execute(const std::string& query)
{
    std::unique_ptr<sql::Statement> stmt(m_conn->createStatement());
    stmt->execute(query);
}

std::unique_ptr<sql::ResultSet> DBExecutor::ExecuteQuery(const std::string& query)
{
    std::unique_ptr<sql::Statement> stmt(m_conn->createStatement());
    return std::unique_ptr<sql::ResultSet>(stmt->executeQuery(query));
}

std::unique_ptr<sql::PreparedStatement> DBExecutor::Prepare(const std::string& query)
{
    return std::unique_ptr<sql::PreparedStatement>(
        m_conn->prepareStatement(query)
    );
}

PreparedQuery DBExecutor::PrepareQuery(const std::string& query)
{
    return PreparedQuery(
        std::unique_ptr<sql::PreparedStatement>(
            m_conn->prepareStatement(query)
        )
    );
}