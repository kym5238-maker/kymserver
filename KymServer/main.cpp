#include <mysql/jdbc.h> 

int main()
{
    // UPDATE 수행
    try
    {
        // 1. Driver 가져오기
        sql::Driver* driver = get_driver_instance();

        // 2. DB 연결
        std::unique_ptr<sql::Connection> conn(
            driver->connect(
                "tcp://127.0.0.1:3306",
                "root",
                "dudahr5"   // 네 root 비밀번호
            )
        );

        // 3. 사용할 DB 선택
        conn->setSchema("kymdb");

        // 4. PreparedStatement 생성
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(
                "INSERT INTO accounts (login_id, password, nickname) "
                "VALUES (?, ?, ?)"
            )
        );

        // 5. 파라미터 바인딩
        pstmt->setString(1, "test02");
        pstmt->setString(2, "1234");
        pstmt->setString(3, "moalpapa2");

        // 6. 실행
        int affected = pstmt->executeUpdate();

        std::cout << "INSERT 성공, 영향 받은 row 수: "
            << affected << std::endl;


    }
    catch (sql::SQLException& e)
    {
		const auto errorCode = e.getErrorCode();
        if (errorCode != 1062)
        {
            std::cerr << "[MySQL Error]\n";
            std::cerr << "Error Code: " << errorCode << "\n";
            std::cerr << "SQLState: " << e.getSQLState() << "\n";
            std::cerr << "Message: " << e.what() << std::endl;
        }
    }

	// SELECT 수행
    try
    {
        // 1. 드라이버
        sql::mysql::MySQL_Driver* driver =
            sql::mysql::get_mysql_driver_instance();

        // 2. 연결
        std::unique_ptr<sql::Connection> conn(
            driver->connect(
                "tcp://127.0.0.1:3306",
                "root",
                "dudahr5"
            )
        );

        // 3. DB 선택 + 문자셋
        {
            std::unique_ptr<sql::Statement> stmt(conn->createStatement());
            stmt->execute("USE kymdb");
            stmt->execute("SET NAMES utf8mb4");
        }

        // 4. SELECT
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(
            stmt->executeQuery(
                "SELECT account_id, login_id, password, nickname, created_at, logined_at "
                "FROM accounts"
            )
        );

        // 5. 결과 출력
        while (res->next())
        {
            std::cout
                << "account_id: " << res->getInt("account_id") << ", "
                << "login_id: " << res->getString("login_id") << ", "
                << "password: " << res->getString("password") << ", "
                << "nickname: " << res->getString("nickname") << ", "
                << "created_at: " << res->getString("created_at") << ", "
                << "logined_at: " << res->getString("logined_at")
                << std::endl;
        }
    }
    catch (sql::SQLException& e)
    {
        std::cerr << "[SQL ERROR]\n";
        std::cerr << "Error Code: " << e.getErrorCode() << "\n";
        std::cerr << "SQL State: " << e.getSQLState() << "\n";
        std::cerr << "Message: " << e.what() << std::endl;
    }

    return 0;
}