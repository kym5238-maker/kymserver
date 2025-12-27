#pragma warning(push)
#pragma warning(disable: 4251 4200 4267 4819 4251 4200) 
#include <hiredis/hiredis.h>
#include <google/protobuf/message.h>
#include <google/protobuf/util/json_util.h>
#pragma warning(pop)
#include <iostream>
#include <string>
#include <fstream>
#include "AccountDBHelper.h"
#include "Error.h"
#include "Logger.h"
#include "RedisClient.h"
#include "src/protobuf/protocol_1.pb.h"


void SaveCharacter() 
{
    protocol::CharacterBase charData;
    charData.set_level(18);
    charData.set_job(protocol::JOB_MAGE);
    charData.set_second_job(protocol::SEC_JOB_ARCHMAGE);

    std::string json_output;
    google::protobuf::util::JsonPrintOptions options;
    options.add_whitespace = true;
    options.always_print_fields_with_no_presence = true;

    auto status = google::protobuf::util::MessageToJsonString(charData, &json_output, options);
    if (status.ok()) 
    {
        std::ofstream outFile("CharacterData.json");
        outFile << json_output;
        outFile.close();

        std::cout << "JSON 파일 저장 완료!" << std::endl;
    }
}

void LoadCharacter()
{
    std::ifstream inFile("CharacterData.json");
    if (inFile.is_open() == false)
    {
        std::cerr << "파일을 열 수 없어!" << std::endl;
        return;
    }

    std::string json_str((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    protocol::CharacterBase loadedChar;
    auto status = google::protobuf::util::JsonStringToMessage(json_str, &loadedChar);
    if (status.ok() == false)
    {
        std::cerr << "파싱 실패: " << status.message() << std::endl;
        return;
    }

    std::cout << "--- 로드 성공! ---" << std::endl;
    std::cout << "Level: " << loadedChar.level() << std::endl;
    std::cout << "Job: " << loadedChar.job() << std::endl;
    std::cout << "Second Job: " << loadedChar.second_job() << std::endl;
}

int main()
{
    SaveCharacter();
	LoadCharacter();

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