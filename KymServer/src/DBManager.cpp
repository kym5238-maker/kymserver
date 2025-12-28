#include "DBManager.h"

#pragma warning(push)
#pragma warning(disable: 4251 4200 4267 4819 4251 4200) 
#include <hiredis/hiredis.h>
#include <google/protobuf/message.h>
#include <google/protobuf/util/json_util.h>
#pragma warning(pop)

#include <iostream>
#include <fstream>
#include <string>
#include "protobuf/protocol_1.pb.h"
#include "Error.h"
#include "Logger.h"
#include "RedisClient.h"
#include "AccountDBHelper.h"
#include "CharacterDBHelper.h"
//#include "lz4.h"


void DBManager::JsonTest()
{
    std::cout << "=== JsonTest 시작 ===" << std::endl;
    SaveCharacter();
    LoadCharacter();
    std::cout << "=== JsonTest 종료 ===" << std::endl;
}

Error DBManager::SaveCharacter()
{
	const int charKey = 1001;

    protocol::CharacterBase charData;
    charData.set_level(18);
    charData.set_job(protocol::JOB_MAGE);
    charData.set_second_job(protocol::SEC_JOB_ARCHMAGE);

    std::string json_output;
    google::protobuf::util::JsonPrintOptions options;
    options.add_whitespace = true;
    options.always_print_fields_with_no_presence = true;

	// 1. JSON으로 직렬화(Serialization) 및 출력 테스트
    auto status = google::protobuf::util::MessageToJsonString(charData, &json_output, options);
    if (status.ok())
    {
        std::ofstream outFile("CharacterData.json");
        if (outFile.is_open())
        {
            outFile << json_output;
            outFile.close();
            std::cout << "[Save] JSON 파일 저장 완료!" << std::endl;
        }
    }

    //// 2. 바이너리로 직렬화 (Serialization)
    //std::string rawBinary = charData.SerializeAsString();
    //if (rawBinary.empty()) {
    //    LOG_ERROR("Protobuf serialization failed!");
    //    return;
    //}
    //
    // 3. LZ4 압축
    // 압축 후 최대 예상 크기를 계산해서 버퍼 확보
    //int maxCompressedSize = LZ4_compressBound(static_cast<int>(rawBinary.size()));
    //std::vector<char> compressedBuffer(maxCompressedSize);
    //
    //// 실제 압축 수행
    //int compressedSize = LZ4_compress_default(
    //    rawBinary.data(),
    //    compressedBuffer.data(),
    //    static_cast<int>(rawBinary.size()),
    //    maxCompressedSize
    //);
    //
    //if (compressedSize <= 0) {
    //    LOG_ERROR("LZ4 Compression failed!");
    //    return;
    //}
    //
    //// 실제 압축된 크기만큼만 string으로 변환
    //std::string finalBlob(compressedBuffer.data(), compressedSize);
    //
    //// 4. DB에 저장 (우리가 만든 DBHelper 사용)
    //Error result = CharacterDBHelper::CreateCharacter(charKey, finalBlob);
    //
    //if (result.IsFail()) 
    //{
    //    LOG_ERROR("SaveCharacterToDB failed! error={}", result);
    //    return result;
    //}
    //
    //LOG_INFO("SaveCharacterToDB success! Original: {} bytes, Compressed: {} bytes",rawBinary.size(), compressedSize);

    return { ErrorCode::None };
}

void DBManager::LoadCharacter()
{
    std::ifstream inFile("CharacterData.json");
    if (!inFile.is_open())
    {
        std::cerr << "[Load] 파일을 열 수 없어!" << std::endl;
        return;
    }

    std::string json_str((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    protocol::CharacterBase loadedChar;
    auto status = google::protobuf::util::JsonStringToMessage(json_str, &loadedChar);
    if (!status.ok())
    {
        std::cerr << "[Load] 파싱 실패: " << status.message() << std::endl;
        return;
    }

    std::cout << "[Load] 로드 성공!" << std::endl;
    std::cout << "Level: " << loadedChar.level() << std::endl;
    std::cout << "Job: " << (int)loadedChar.job() << std::endl;
    std::cout << "Second Job: " << (int)loadedChar.second_job() << std::endl;
}

Error DBManager::SmokeTest()
{
    JsonTest();

    RedisClient redis;
    Error result = redis.SmokeTest();
    if (result.IsFail())
    {
        LOG_ERROR("[Error] RedisClient::SmokeTest() error={}", result);
        return result;
    }

    return { ErrorCode::None };
}

Error DBManager::AccountDBSmokeTest()
{
    RedisClient redis;
    Error result = redis.Connect("127.0.0.1", 6379, 2);
    if (result.IsFail())
    {
        LOG_ERROR("[Error] RedisClient::Connect() error={}", result);
        return result;
    }

    result = AccountDBHelper::Register("test02", "1234", "moalpapa2");
    if (result.IsFail())
    {
        LOG_ERROR("[Error] AccountDBHelper::Register() error={}", result);
        return result;
    }

    std::vector<AccountRow> accounts;
    result = AccountDBHelper::GetAllAccounts(accounts);
    if (result.IsFail())
    {
        LOG_ERROR("[Error] AccountDBHelper::GetAllAccounts() error={}", result);
        return result;
    }

    if (accounts.empty() == false)
    {
        const int lastAccountID = accounts.back().accountId;

        result = AccountDBHelper::UpdateLoginTimestamp(lastAccountID);
        if (result.IsFail())
        {
            LOG_ERROR("[Error] AccountDBHelper::UpdateLoginTimestamp() error={}", result);
            return result;
        }

        bool created = false;
        result = redis.HSet("online_account", std::to_string(lastAccountID), "1", created);
        if (result.IsFail())
        {
            LOG_ERROR("[Error] RedisClient::Set() error={}", result);
            return result;
        }
    }

    if (accounts.empty() == false)
    {
        const int lastAccountID = accounts.back().accountId;

        result = AccountDBHelper::UpdateLogoutTimestamp(lastAccountID);
        if (result.IsFail())
        {
            LOG_ERROR("[Error] AccountDBHelper::UpdateLogoutTimestamp() error={}", result);
            return result;
        }

        int64_t deleted = false;
        result = redis.HDel("online_account", { std::to_string(lastAccountID) }, deleted);
        if (result.IsFail())
        {
            LOG_ERROR("[Error] RedisClient::Set() error={}", result);
            return result;
        }
    }

    return { ErrorCode::None };
}