#pragma once

enum class ErrorCode
{
    None = 0,

    // Account / Auth
    DuplicateKey,        // 중복 키 (login_id 등)
    AccountNotFound,

    // Common
    DatabaseError,
    InvalidParameter,
};