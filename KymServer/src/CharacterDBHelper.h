#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "Error.h"

struct CharacterRow
{
    int32_t characterKey = 0; // int32로 변경
    std::string c1;
    std::string createdDt;
};

class CharacterDBHelper
{
public:
    // 캐릭터 생성
    static Error CreateCharacter(int32_t characterKey, const std::string& blobData);

    // 특정 캐릭터 키로 조회
    static Error GetCharacter(int32_t characterKey, CharacterRow& outCharacter);

private:
    static Error TranslateError(const struct DBResult& dbResult);
};