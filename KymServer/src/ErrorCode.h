#pragma once

enum class ErrorCode
{
    None = 0,

    // ===== Common =====
    DatabaseError = 1,
    InvalidParameter = 2,

    // ===== Redis =====
    RedisNotConnected = 10,
    RedisConnectFailed = 11,     
    RedisCommandFailed = 12,     
    RedisReplyError = 13,
    RedisUnexpectedReply = 14,   

    // ===== MYSQL =====
    SelectNotFound = 20,

    // ===== Account / Auth =====
    DuplicateKey = 30,
    AccountNotFound = 31,
};