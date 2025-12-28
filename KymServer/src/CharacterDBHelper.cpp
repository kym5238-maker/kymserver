#include "CharacterDBHelper.h"
#include "DBExecutor.h"
#include "DBResult.h"
#include "DBResultSet.h"
#include "Logger.h"

Error CharacterDBHelper::CreateCharacter(int32_t characterKey, const std::string& blobData)
{
    DBExecutor dbExecutor;
    auto query = dbExecutor.PrepareQuery(
        "INSERT INTO characters (character_key, C1) VALUES (?, ?)"
    );

    auto dbResult = (query << characterKey << blobData).TryExecuteUpdate(1062);
    if (dbResult.IsFail())
    {
        Error error = TranslateError(dbResult);
        LOG_ERROR("Character Create failed! key={}, error={}", characterKey, error);
        return error;
    }

    LOG_INFO("Character Create success! key={}", characterKey);
    return { ErrorCode::None };
}

Error CharacterDBHelper::GetCharacter(int32_t characterKey, CharacterRow& outCharacter)
{
    DBExecutor dbExecutor;
    auto query = dbExecutor.PrepareQuery(
        "SELECT character_key, C1, created_dt FROM characters WHERE character_key = ?"
    );

    DBResultSet rs((query << characterKey).TryExecuteQuery());
    if (rs.IsFail())
    {
        return { ErrorCode::DatabaseError };
    }

    DBRow row;
    if (rs.Next(row))
    {
        row >> outCharacter.characterKey
            >> outCharacter.c1
            >> outCharacter.createdDt;

        return { ErrorCode::None };
    }

    return { ErrorCode::SelectNotFound };
}

Error CharacterDBHelper::TranslateError(const DBResult& dbResult)
{
    if (dbResult.errorCode == 1062)
    {
        return { ErrorCode::DuplicateKey };
    }
    return { ErrorCode::DatabaseError };
}