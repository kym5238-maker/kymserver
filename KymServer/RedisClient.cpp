#include "RedisClient.h"
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <sstream>
#include <winsock2.h>
#include "Error.h"
#include "ErrorCode.h"
#include "Logger.h"

RedisClient::RedisClient()
    : ctx_(nullptr)
{
}

RedisClient::~RedisClient()
{
    Disconnect();
}

Error RedisClient::Connect(const char* host, int port, int timeoutSec)
{
    Disconnect();

    if (!host || port <= 0)
        return Error{ ErrorCode::InvalidParameter };

    timeval tv{};
    tv.tv_sec = timeoutSec;
    tv.tv_usec = 0;

    ctx_ = redisConnectWithTimeout(host, port, tv);
    if (!ctx_)
    {
        LOG_ERROR("[Redis] connect failed: ctx == nullptr");
        return Error{ ErrorCode::RedisConnectFailed };
    }

    if (ctx_->err)
    {
        LOG_ERROR("[Redis] connect error: {}", ctx_->errstr ? ctx_->errstr : "(null)");
        Disconnect();
        return Error{ ErrorCode::RedisConnectFailed };
    }

    return Error{ ErrorCode::None };
}

void RedisClient::Disconnect()
{
    if (ctx_)
    {
        redisFree(ctx_);
        ctx_ = nullptr;
    }
}

bool RedisClient::IsConnected() const
{
    return ctx_ != nullptr;
}

Error RedisClient::Exec(const RedisCommand& cmd, redisReply*& outReply)
{
    outReply = nullptr;

    if (!ctx_)
        return Error{ ErrorCode::RedisNotConnected };

    const auto& args = cmd.Args();
    if (args.empty())
        return Error{ ErrorCode::InvalidParameter };

    std::vector<const char*> argv;
    std::vector<size_t> argvlen;
    argv.reserve(args.size());
    argvlen.reserve(args.size());

    for (const auto& s : args)
    {
        argv.push_back(s.c_str());
        argvlen.push_back(s.size());
    }

    void* r = redisCommandArgv(
        ctx_,
        static_cast<int>(argv.size()),
        argv.data(),
        argvlen.data()
    );

    if (!r)
    {
        LOG_ERROR("[Redis] command failed: {}", ctx_->errstr ? ctx_->errstr : "(null)");
        return Error{ ErrorCode::RedisCommandFailed };
    }

    redisReply* reply = static_cast<redisReply*>(r);

    if (reply->type == REDIS_REPLY_ERROR)
    {
        LOG_ERROR("[Redis] reply error: {}", reply->str ? reply->str : "(null)");
        freeReplyObject(reply);
        return Error{ ErrorCode::RedisReplyError };
    }

    outReply = reply;
    return Error{ ErrorCode::None };
}

Error RedisClient::Ping()
{
    RedisCommand cmd("PING");

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type != REDIS_REPLY_STATUS)
    {
        LOG_ERROR("[Redis] PING unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    freeReplyObject(r);
    return Error{ ErrorCode::None };
}

// ===== String =====
Error RedisClient::Set(const std::string& key, const std::string& value, int ttlSec)
{
    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("SET");
    cmd << key << value;

    if (ttlSec > 0)
        cmd << "EX" << ttlSec;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    freeReplyObject(r);
    return Error{ ErrorCode::None };
}

Error RedisClient::Get(const std::string& key, std::string& outValue, bool& outFound)
{
    outValue.clear();
    outFound = false;

    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("GET");
    cmd << key;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type == REDIS_REPLY_NIL)
    {
        outFound = false;
    }
    else if (r->type == REDIS_REPLY_STRING && r->str)
    {
        outFound = true;
        outValue.assign(r->str, r->len);
    }
    else
    {
        LOG_ERROR("[Redis] GET unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    freeReplyObject(r);
    return Error{ ErrorCode::None };
}

Error RedisClient::Del(const std::string& key, int64_t& outDeleted)
{
    outDeleted = 0;

    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("DEL");
    cmd << key;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type != REDIS_REPLY_INTEGER)
    {
        LOG_ERROR("[Redis] DEL unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    outDeleted = r->integer;
    freeReplyObject(r);
    return Error{ ErrorCode::None };
}

// ===== Hash =====
Error RedisClient::HSet(const std::string& key, const std::string& field, const std::string& value, bool& outCreated)
{
    outCreated = false;

    if (key.empty() || field.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("HSET");
    cmd << key << field << value;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type != REDIS_REPLY_INTEGER)
    {
        LOG_ERROR("[Redis] HSET unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    outCreated = (r->integer == 1);
    freeReplyObject(r);
    return Error{ ErrorCode::None };
}

Error RedisClient::HGet(const std::string& key, const std::string& field, std::string& outValue, bool& outFound)
{
    outValue.clear();
    outFound = false;

    if (key.empty() || field.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("HGET");
    cmd << key << field;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type == REDIS_REPLY_NIL)
    {
        outFound = false;
    }
    else if (r->type == REDIS_REPLY_STRING && r->str)
    {
        outFound = true;
        outValue.assign(r->str, r->len);
    }
    else
    {
        LOG_ERROR("[Redis] HGET unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    freeReplyObject(r);
    return Error{ ErrorCode::None };
}

Error RedisClient::HDel(const std::string& key, const std::vector<std::string>& fields, int64_t& outDeleted)
{
    outDeleted = 0;

    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };

    if (fields.empty())
        return Error{ ErrorCode::None }; // 지울 게 없으면 성공 처리

    RedisCommand cmd("HDEL");
    cmd << key;

    for (const auto& f : fields)
    {
        cmd << f;
    }

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type != REDIS_REPLY_INTEGER)
    {
        LOG_ERROR("[Redis] HDEL unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    outDeleted = r->integer;
    freeReplyObject(r);
    return Error{ ErrorCode::None };
}

// ===== ZSet =====
Error RedisClient::ZAdd(const std::string& key, double score, const std::string& member, bool& outAdded)
{
    outAdded = false;

    if (key.empty() || member.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("ZADD");
    cmd << key << score << member;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type != REDIS_REPLY_INTEGER)
    {
        LOG_ERROR("[Redis] ZADD unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    outAdded = (r->integer == 1);
    freeReplyObject(r);
    return Error{ ErrorCode::None };
}

Error RedisClient::ZRem(const std::string& key, const std::vector<std::string>& members, int64_t& outRemoved)
{
    outRemoved = 0;

    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };
    if (members.empty())
        return Error{ ErrorCode::None };

    RedisCommand cmd("ZREM");
    cmd << key;
    for (const auto& m : members)
        cmd << m;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type != REDIS_REPLY_INTEGER)
    {
        LOG_ERROR("[Redis] ZREM unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    outRemoved = r->integer;
    freeReplyObject(r);

    return Error{ ErrorCode::None };
}

Error RedisClient::ZScore(const std::string& key, const std::string& member, double& outScore, bool& outFound)
{
    outScore = 0.0;
    outFound = false;

    if (key.empty() || member.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("ZSCORE");
    cmd << key << member;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type == REDIS_REPLY_NIL)
    {
        outFound = false;
    }
    else if (r->type == REDIS_REPLY_STRING && r->str)
    {
        outFound = true;
        outScore = std::strtod(r->str, nullptr);
    }
    else
    {
        LOG_ERROR("[Redis] ZSCORE unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    freeReplyObject(r);

    return Error{ ErrorCode::None };
}

Error RedisClient::ZCard(const std::string& key, int64_t& outCount)
{
    outCount = 0;

    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("ZCARD");
    cmd << key;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type != REDIS_REPLY_INTEGER)
    {
        LOG_ERROR("[Redis] ZCARD unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    outCount = r->integer;
    freeReplyObject(r);

    return Error{ ErrorCode::None };
}

Error RedisClient::ZRange(const std::string& key, int64_t start, int64_t stop, std::vector<std::string>& outMembers)
{
    outMembers.clear();

    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("ZRANGE");
    cmd << key << start << stop;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type != REDIS_REPLY_ARRAY)
    {
        LOG_ERROR("[Redis] ZRANGE unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    outMembers.reserve(r->elements);
    for (size_t i = 0; i < r->elements; ++i)
    {
        redisReply* elem = r->element[i];
        if (!elem || elem->type != REDIS_REPLY_STRING || !elem->str)
        {
            LOG_ERROR("[Redis] ZRANGE element unexpected type={}", elem ? elem->type : -1);
            freeReplyObject(r);
            return Error{ ErrorCode::RedisUnexpectedReply };
        }
        outMembers.emplace_back(elem->str, elem->len);
    }

    freeReplyObject(r);

    return Error{ ErrorCode::None };
}

static Error ParseWithScores(redisReply* r, std::vector<std::pair<std::string, double>>& outItems)
{
    outItems.clear();

    if (r->type != REDIS_REPLY_ARRAY)
        return Error{ ErrorCode::RedisUnexpectedReply };

    if ((r->elements % 2) != 0)
        return Error{ ErrorCode::RedisUnexpectedReply };

    outItems.reserve(r->elements / 2);

    for (size_t i = 0; i < r->elements; i += 2)
    {
        redisReply* m = r->element[i];
        redisReply* s = r->element[i + 1];

        if (!m || !s || m->type != REDIS_REPLY_STRING || !m->str || s->type != REDIS_REPLY_STRING || !s->str)
            return Error{ ErrorCode::RedisUnexpectedReply };

        outItems.emplace_back(std::string(m->str, m->len),std::strtod(s->str, nullptr));
    }

    return Error{ ErrorCode::None };
}

Error RedisClient::ZRangeWithScores(const std::string& key, int64_t start, int64_t stop, std::vector<std::pair<std::string, double>>& outItems)
{
    outItems.clear();

    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("ZRANGE");
    cmd << key << start << stop << "WITHSCORES";

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    Error pe = ParseWithScores(r, outItems);
    if (pe.IsFail())
        LOG_ERROR("[Redis] ZRANGE WITHSCORES parse failed");

    freeReplyObject(r);
    return pe;
}

Error RedisClient::ZRevRangeWithScores(const std::string& key, int64_t start, int64_t stop, std::vector<std::pair<std::string, double>>& outItems)
{
    outItems.clear();

    if (key.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("ZREVRANGE");
    cmd << key << start << stop << "WITHSCORES";

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    Error pe = ParseWithScores(r, outItems);
    if (pe.IsFail())
    {
        LOG_ERROR("[Redis] ZREVRANGE WITHSCORES parse failed");
    }

    freeReplyObject(r);

    return pe;
}

Error RedisClient::ZRevRank(const std::string& key, const std::string& member, int64_t& outRank, bool& outFound)
{
    outRank = -1;
    outFound = false;

    if (key.empty() || member.empty())
        return Error{ ErrorCode::InvalidParameter };

    RedisCommand cmd("ZREVRANK");
    cmd << key << member;

    redisReply* r = nullptr;
    Error e = Exec(cmd, r);
    if (e.IsFail())
        return e;

    if (r->type == REDIS_REPLY_NIL)
    {
        outFound = false;
    }
    else if (r->type == REDIS_REPLY_INTEGER)
    {
        outFound = true;
        outRank = r->integer; // 0-based
    }
    else
    {
        LOG_ERROR("[Redis] ZREVRANK unexpected reply type={}", r->type);
        freeReplyObject(r);
        return Error{ ErrorCode::RedisUnexpectedReply };
    }

    freeReplyObject(r);
    return Error{ ErrorCode::None };
}


Error RedisClient::SmokeTest()
{
    if (!IsConnected())
        return Error{ ErrorCode::RedisNotConnected };

    Error e;

    // ---------- PING ----------
    e = Ping();
    if (e.IsFail())
        return e;

    // ---------- String ----------
    {
        const std::string key = "kymserver:smoke:string";
        const std::string val = "what the hell";

        e = Set(key, val, 60);
        if (e.IsFail())
            return e;

        std::string got;
        bool found = false;
        e = Get(key, got, found);
        if (e.IsFail())
            return e;

        if (!found || got != val)
        {
            LOG_ERROR("[Redis] String smoke mismatch found={} got='{}'", found, got);
            return Error{ ErrorCode::RedisUnexpectedReply };
        }

        int64_t deleted = 0;
        e = Del(key, deleted);
        if (e.IsFail())
            return e;
    }

    // ---------- Hash ----------
    {
        const std::string key = "kymserver:smoke:hash";
        const std::string field = "nickname";
        const std::string val = "moalpapa2";

        bool created = false;
        e = HSet(key, field, val, created);
        if (e.IsFail())
            return e;

        std::string got;
        bool found = false;
        e = HGet(key, field, got, found);
        if (e.IsFail())
            return e;

        if (!found || got != val)
        {
            LOG_ERROR("[Redis] Hash smoke mismatch found={} got='{}'", found, got);
            return Error{ ErrorCode::RedisUnexpectedReply };
        }

        int64_t deletedFields = 0;
        e = HDel(key, std::vector<std::string>{ field }, deletedFields);
        if (e.IsFail())
            return e;
    }

    // ---------- ZSet (ranking) ----------
    {
        const std::string key = "kymserver:smoke:zset";

        struct Player
        {
            const char* name;
            double score;
        };

        Player players[] =
        {
            { "alice", 100.0 },
            { "bob",   250.0 },
            { "carol", 180.0 },
            { "dave",  300.0 }, // 1등
            { "user1", 123.0 }, // 우리가 검사할 대상
        };

        // 1) ZADD 여러 명
        for (const auto& p : players)
        {
            bool added = false;
            e = ZAdd(key, p.score, p.name, added);
            if (e.IsFail())
                return e;
        }

        // 2) 전체 인원 수 확인
        int64_t card = 0;
        e = ZCard(key, card);
        if (e.IsFail())
            return e;

        if (card != std::size(players))
        {
            LOG_ERROR("[Redis] ZSet card mismatch expected={} got={}", std::size(players), card);
            return Error{ ErrorCode::RedisUnexpectedReply };
        }

        // 3) user1 점수 확인
        {
            double gotScore = 0.0;
            bool found = false;
            e = ZScore(key, "user1", gotScore, found);
            if (e.IsFail())
                return e;

            if (!found || gotScore != 123.0)
            {
                LOG_ERROR("[Redis] ZScore mismatch found={} gotScore={}", found, gotScore);
                return Error{ ErrorCode::RedisUnexpectedReply };
            }
        }

        // 4) user1 등수 확인 (높을수록 상위, 0-based)
        {
            int64_t rank = -1;
            bool found = false;
            e = ZRevRank(key, "user1", rank, found);
            if (e.IsFail())
                return e;

            // 점수 순 정렬: dave(300)=0, bob(250)=1, carol(180)=2, user1(123)=3, alice(100)=4
            const int64_t expectedRank = 3;

            if (!found || rank != expectedRank)
            {
                LOG_ERROR("[Redis] ZRevRank mismatch found={} rank={} expected={}", found, rank, expectedRank);
                return Error{ ErrorCode::RedisUnexpectedReply };
            }
        }

        // 5) TOP 3 조회 (검증용)
        {
            std::vector<std::pair<std::string, double>> top3;
            e = ZRevRangeWithScores(key, 0, 2, top3);
            if (e.IsFail())
                return e;

            if (top3.size() != 3 || top3[0].first != "dave")
            {
                LOG_ERROR("[Redis] ZRevRangeWithScores TOP3 mismatch");
                return Error{ ErrorCode::RedisUnexpectedReply };
            }
        }

        // 6) 정리
        int64_t removed = 0;
        std::vector<std::string> members;
        for (const auto& p : players)
            members.emplace_back(p.name);

        e = ZRem(key, members, removed);
        if (e.IsFail())
            return e;
    }

    return Error{ ErrorCode::None };
}
