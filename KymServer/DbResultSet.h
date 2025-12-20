#pragma once
#include <memory>
#include "DbQueryResult.h"
#include "DbRow.h"

class DbResultSet
{
public:
    explicit DbResultSet(DbQueryResult qr)
        : m_result(std::move(qr.result))
        , m_rs(std::move(qr.rs))
    {
    }

    bool IsFail() const { return m_result.IsFail(); }
    std::string ToErrorString() const { return m_result.ToErrorString(); }

    bool Next(DbRow& outRow)
    {
        if (!m_rs) return false;
        if (!m_rs->next()) return false;
        outRow.Bind(m_rs.get());
        return true;
    }

private:
    DbResult m_result;
    std::unique_ptr<sql::ResultSet> m_rs;
};
