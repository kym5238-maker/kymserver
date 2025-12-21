#pragma once
#include <string>
#include "Error.h"
#include <vector>

struct DBResult;
struct AccountRow
{
    int accountId = -1;
    std::string loginId;
    std::string password;
    std::string nickname;
    std::string createdAt;
    std::string loginedAt;
};

class AccountDBHelper
{
public:
    static Error Register(const std::string& loginId, const std::string& password, const std::string& nickname);
    static Error UpdateLoginTimestamp(int accountId);
    static Error GetAllAccounts(std::vector<AccountRow>& outAccounts);

private:
    static Error TranslateInsertError(const DBResult& dbResult);
};