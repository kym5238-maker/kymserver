#include "AccountDBHelper.h"
#include "Error.h"
#include <iostream>
#include "Logger.h"


int main()
{
    Error result = AccountDBHelper::Register("test02", "1234", "moalpapa2");
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
    }

    return 0;
}