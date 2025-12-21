#include "AccountDBHelper.h"
#include "Error.h"
#include <iostream>

int main()
{
    Error result = AccountDBHelper::Register("test02", "1234", "moalpapa2");
    if (result.IsFail())
    {
        std::cerr << "[Error] AccountDBHelper::Register() error=" << result << "\n";
        return 1;
    }

    std::vector<AccountRow> accounts;
    result = AccountDBHelper::GetAllAccounts(accounts);
    if (result.IsFail())
    {
        std::cerr << "[Error] AccountDBHelper::GetAllAccounts() error=" << result << "\n";
        return 1;
    }
   
    if (accounts.empty() == false)
    {
        const int lastAccountID = accounts.back().accountId;

        result = AccountDBHelper::UpdateLoginTimestamp(lastAccountID);
        if (result.IsFail())
        {
            std::cerr << "[Error] AccountDBHelper::UpdateLoginTimestamp() error=" << result << "\n";
            return 1;
        }
    }

    return 0;
}