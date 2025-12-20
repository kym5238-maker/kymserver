#include "PreparedQuery.h"

PreparedQuery::PreparedQuery(std::unique_ptr<sql::PreparedStatement> pstmt)
    : m_pstmt(std::move(pstmt))
    , m_paramIndex(1)
{
}

PreparedQuery& PreparedQuery::operator<<(const std::string& value)
{
    m_pstmt->setString(m_paramIndex++, value);
    return *this;
}

PreparedQuery& PreparedQuery::operator<<(const char* value)
{
    m_pstmt->setString(m_paramIndex++, value);
    return *this;
}

PreparedQuery& PreparedQuery::operator<<(int value)
{
    m_pstmt->setInt(m_paramIndex++, value);
    return *this;
}

std::unique_ptr<sql::ResultSet> PreparedQuery::ExecuteQuery()
{
    m_paramIndex = 1;
    return std::unique_ptr<sql::ResultSet>(m_pstmt->executeQuery());
}

int PreparedQuery::ExecuteUpdate()
{
    m_paramIndex = 1; // 재사용 대비
    return m_pstmt->executeUpdate();
}

DbResult PreparedQuery::TryExecuteUpdate(int ignoreErrorCode)
{
    try
    {
        int affected = ExecuteUpdate(); // 내부에서 paramIndex 리셋됨
        return DbResult::Ok(affected);
    }
    catch (sql::SQLException& e)
    {
        const int code = e.getErrorCode();
        if (ignoreErrorCode != 0 && code == ignoreErrorCode)
        {
            // “무시” 정책: 실패로 보지 않고, 영향 0으로 성공 처리
            return DbResult::Ok(0);
        }

        return DbResult::Fail(code, e.getSQLState(), e.what());
    }
}

DbQueryResult PreparedQuery::TryExecuteQuery()
{
    try
    {
        auto rs = ExecuteQuery(); // 기존 함수
        return DbQueryResult{ DbResult::Ok(0), std::move(rs) };
    }
    catch (sql::SQLException& e)
    {
        return DbQueryResult{
            DbResult::Fail(e.getErrorCode(), e.getSQLState(), e.what()),
            nullptr
        };
    }
}