#include "AccountDBHelper.h"
#include "Error.h"
#include <iostream>
#include "Logger.h"
#include <hiredis/hiredis.h>
//#include <iostream>
#include <string>
#include "RedisClient.h"


int main()
{
    Error result{ ErrorCode::None };

    RedisClient redis;
    result = redis.Connect("127.0.0.1", 6379, 2);
    if (result.IsFail())
    {
        LOG_ERROR("[Error] RedisClient::Connect() error={}", result);
        return 1;
    }

    result = redis.SmokeTest();
    if (result.IsFail())
    {
        LOG_ERROR("[Error] RedisClient::SmokeTest() error={}", result);
        return 1;
    }

    result = AccountDBHelper::Register("test02", "1234", "moalpapa2");
    if (result.IsFail())
    {
        LOG_ERROR("[Error] AccountDBHelper::Register() error={}", result);
        return 1;
    }

    std::vector<AccountRow> accounts;
    result = AccountDBHelper::GetAllAccounts(accounts);
    if (result.IsFail())
    {
        LOG_ERROR("[Error] AccountDBHelper::GetAllAccounts() error={}", result);
        return 1;
    }
   
    if (accounts.empty() == false)
    {
        const int lastAccountID = accounts.back().accountId;

        result = AccountDBHelper::UpdateLoginTimestamp(lastAccountID);
        if (result.IsFail())
        {
            LOG_ERROR("[Error] AccountDBHelper::UpdateLoginTimestamp() error={}", result);
            return 1;
        }

        bool created = false;
		result = redis.HSet("online_account", std::to_string(lastAccountID), "1", created);
        if (result.IsFail())
        {
			LOG_ERROR("[Error] RedisClient::Set() error={}", result);
            return 1;
        }
    }

    if (accounts.empty() == false)
    {
        const int lastAccountID = accounts.back().accountId;

        result = AccountDBHelper::UpdateLogoutTimestamp(lastAccountID);
        if (result.IsFail())
        {
            LOG_ERROR("[Error] AccountDBHelper::UpdateLogoutTimestamp() error={}", result);
            return 1;
        }

        int64_t deleted = false;
        result = redis.HDel("online_account", { std::to_string(lastAccountID) }, deleted);
        if (result.IsFail())
        {
            LOG_ERROR("[Error] RedisClient::Set() error={}", result);
            return 1;
        }
    }

    return 0;
}