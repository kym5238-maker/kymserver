#include <mysql/jdbc.h> 
#include "DBExecutor.h"
#include "PreparedQuery.h"
#include "DbRow.h"
#include "DbResultSet.h"

int main()
{
	// INSERT 수행
    {
        DBExecutor dbExecutor;
        auto query = dbExecutor.PrepareQuery(
            "INSERT INTO accounts (login_id, password, nickname) "
            "VALUES (?, ?, ?)"
        );

        auto result = (query << "test02" << "1234" << "moalpapa2").TryExecuteUpdate(1062);
        if (result.IsFail())
        {
            std::cerr << result.ToErrorString() << std::endl;
            return 1;
        }

        std::cout << "INSERT 성공, 영향 받은 row 수: " << result.affectedRows << "\n";
    }

	// SELECT 수행
	int lastAccountID = -1;
    {
        DBExecutor dbExecutor;
        auto query = dbExecutor.PrepareQuery(
            "SELECT account_id, login_id, password, nickname, created_at, logined_at "
            "FROM accounts"
        );

        DbResultSet rs(query.TryExecuteQuery());
        if (rs.IsFail())
        {
            std::cerr << rs.ToErrorString() << std::endl;
            return 1;
        }

        DbRow row;
        while (rs.Next(row))
        {
            int accountId;
            std::string loginId;
            std::string password;
            std::string nickname;
            std::string createdAt;
            std::string loginedAt;

            row >> accountId
                >> loginId
                >> password
                >> nickname
                >> createdAt
                >> loginedAt;

            lastAccountID = accountId;

            std::cout   << "account_id: " << accountId << ", "
                        << "login_id: " << loginId << ", "
                        << "password: " << password << ", "
                        << "nickname: " << nickname << ", "
                        << "created_at: " << createdAt << ", "
                        << "logined_at: " << loginedAt
                        << std::endl;
        }
    }
   
    if (lastAccountID != -1)
    {
        DBExecutor dbExecutor;

        auto query = dbExecutor.PrepareQuery(
            "UPDATE accounts "
            "SET logined_at = NOW() "
            "WHERE account_id = ?"
        );

        auto result = (query << lastAccountID).TryExecuteUpdate();
        if (result.IsFail())
        {
            std::cerr << result.ToErrorString() << std::endl;
            return 1;
        }

        std::cout
            << "logined_at 업데이트 완료 (account_id="
            << lastAccountID
            << "), 영향 받은 row 수: "
            << result.affectedRows
            << std::endl;
    }

    return 0;
}