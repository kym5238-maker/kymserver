#pragma once
#include <string>
#include <mysql/jdbc.h>

class DbRow
{
public:
    DbRow() = default;

    void Bind(sql::ResultSet* rs)
    {
        m_rs = rs;
        m_colIndex = 1; // ResultSet은 1-based
    }

    // >> 연산자 오버로딩
    DbRow& operator>>(int& out)
    {
        out = m_rs->getInt(m_colIndex++);
        return *this;
    }

    DbRow& operator>>(std::string& out)
    {
        out = m_rs->getString(m_colIndex++);
        return *this;
    }

private:
    sql::ResultSet* m_rs = nullptr;
    int m_colIndex = 1;
};
