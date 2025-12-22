#include "AccountDBHelper.h"

#include <iostream>
#include "DBExecutor.h"
#include "Error.h"
#include "ErrorCode.h"
#include "DBResult.h"
#include "DBResultSet.h"
#include "Logger.h"

Error AccountDBHelper::Register(
    const std::string& loginId,
    const std::string& password,
    const std::string& nickname)
{
    DBExecutor dbExecutor;
    auto query = dbExecutor.PrepareQuery(
        "INSERT INTO accounts (login_id, password, nickname) "
        "VALUES (?, ?, ?)"
    );

    auto dbResult = (query << loginId << password << nickname).TryExecuteUpdate(1062);
    if (dbResult.IsFail())
    {
        Error error = TranslateInsertError(dbResult);
		LOG_ERROR("Account Register failed! error={}", error);

        return { error };
    }

    if (dbResult.affectedRows > 0)
        LOG_INFO("Account Register success! affectedRows={}", dbResult.affectedRows);

    return { ErrorCode::None };
}

Error AccountDBHelper::UpdateLoginTimestamp(int accountId)
{
    DBExecutor dbExecutor;
    auto query = dbExecutor.PrepareQuery(
        "UPDATE accounts "
        "SET logined_at = NOW() "
        "WHERE account_id = ?"
    );

    auto dbResult = (query << accountId).TryExecuteUpdate();
    if (dbResult.IsFail())
    {
        return { ErrorCode::DatabaseError };
    }

    return { ErrorCode::None };
}

Error AccountDBHelper::UpdateLogoutTimestamp(int accountId)
{
    DBExecutor dbExecutor;
    auto query = dbExecutor.PrepareQuery(
        "UPDATE accounts "
        "SET logouted_at = NOW() "
        "WHERE account_id = ?"
    );

    auto dbResult = (query << accountId).TryExecuteUpdate();
    if (dbResult.IsFail())
    {
        return { ErrorCode::DatabaseError };
    }

    return { ErrorCode::None };
}

Error AccountDBHelper::TranslateInsertError(const DBResult& dbResult)
{
    if (dbResult.errorCode == 1062)
    {
        return { ErrorCode::DuplicateKey };
    }

    return { ErrorCode::DatabaseError };
}

Error AccountDBHelper::GetAllAccounts(std::vector<AccountRow>& outAccounts)
{
    DBExecutor dbExecutor;
    auto query = dbExecutor.PrepareQuery(
        "SELECT account_id, login_id, password, nickname, created_at, logined_at "
        "FROM accounts"
    );

    DBResultSet rs(query.TryExecuteQuery());
    if (rs.IsFail())
    {
        return { ErrorCode::DatabaseError };
    }

    DBRow row;
    while (rs.Next(row))
    {
        AccountRow account;

        row >> account.accountId
            >> account.loginId
            >> account.password
            >> account.nickname
            >> account.createdAt
            >> account.loginedAt;

        outAccounts.push_back(std::move(account));
    }

    return { ErrorCode::None };
}