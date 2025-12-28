#pragma once

#include <string>
#include "Error.h"

namespace protocol 
{
    class CharacterBase;
}

class DBManager
{
public:
    DBManager() = default;
    ~DBManager() = default;

    void JsonTest();

private:
    void SaveCharacter();
    void LoadCharacter();

public:
    Error SmokeTest();
	Error AccountDBSmokeTest();
};