#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

struct redisContext;
struct redisReply;
struct Error;

class RedisCommand
{
public:
    RedisCommand() = default;
    explicit RedisCommand(const char* cmd) { args_.emplace_back(cmd); }

    RedisCommand& operator<<(const std::string& v) { args_.push_back(v); return *this; }
    RedisCommand& operator<<(const char* v) { args_.emplace_back(v); return *this; }
    RedisCommand& operator<<(int v) { args_.push_back(std::to_string(v)); return *this; }
    RedisCommand& operator<<(int64_t v) { args_.push_back(std::to_string(v)); return *this; }
    RedisCommand& operator<<(double v) { args_.push_back(std::to_string(v)); return *this; }

    const std::vector<std::string>& Args() const { return args_; }

private:
    std::vector<std::string> args_;
};

class RedisClient
{
public:
    RedisClient();
    ~RedisClient();

    RedisClient(const RedisClient&) = delete;
    RedisClient& operator=(const RedisClient&) = delete;

public:
    Error Connect(const char* host, int port, int timeoutSec = 2);
    void Disconnect();
    bool IsConnected() const;

    // low-level (CommandBuilder + redisCommandArgv)
    Error Exec(const RedisCommand& cmd, redisReply*& outReply);

    // ===== String 包访 贸府 =====
    Error Ping();
    Error Set(const std::string& key, const std::string& value, int ttlSec = -1);
    Error Get(const std::string& key, std::string& outValue, bool& outFound);
    Error Del(const std::string& key, int64_t& outDeleted);

    // ===== Hash 包访 贸府 =====
    Error HSet(const std::string& key, const std::string& field, const std::string& value, bool& outCreated);
    Error HGet(const std::string& key, const std::string& field, std::string& outValue, bool& outFound);
    Error HDel(const std::string& key, const std::vector<std::string>& fields, int64_t& outDeleted);
    Error HDel(const std::string& key, const std::string& field, int64_t& outDeleted);

    // ===== ZSet 包访 贸府 =====
    Error ZAdd(const std::string& key, double score, const std::string& member, bool& outAdded);
    Error ZRem(const std::string& key, const std::vector<std::string>& members, int64_t& outRemoved);
    Error ZScore(const std::string& key, const std::string& member, double& outScore, bool& outFound);
    Error ZCard(const std::string& key, int64_t& outCount);
    Error ZRange(const std::string& key, int64_t start, int64_t stop, std::vector<std::string>& outMembers);
    Error ZRangeWithScores(const std::string& key, int64_t start, int64_t stop, std::vector<std::pair<std::string, double>>& outItems);
    Error ZRevRangeWithScores(const std::string& key, int64_t start, int64_t stop, std::vector<std::pair<std::string, double>>& outItems);
    Error ZRevRank(const std::string& key, const std::string& member, int64_t& outRank, bool& outFound);

public:
    Error SmokeTest();

private:
    redisContext* ctx_;
};
