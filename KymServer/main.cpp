#include "AccountDBHelper.h"
#include "Error.h"
#include <iostream>
#include "Logger.h"
#include <hiredis/hiredis.h>
#include <iostream>
#include <string>
#include <winsock2.h>   // timeval 정의

static bool RedisSmokeTest(const char* host, int port)
{
    // 1) Connect (timeout 포함)
    timeval timeout{};
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    redisContext* ctx = redisConnectWithTimeout(host, port, timeout);
    if (ctx == nullptr)
    {
        std::cerr << "[Redis] connect failed: ctx == nullptr\n";
        return false;
    }
    if (ctx->err)
    {
        std::cerr << "[Redis] connect error: " << ctx->errstr << "\n";
        redisFree(ctx);
        return false;
    }

    auto Exec = [&](const char* fmt, auto... args) -> redisReply*
        {
            redisReply* reply = (redisReply*)redisCommand(ctx, fmt, args...);
            if (reply == nullptr)
            {
                std::cerr << "[Redis] command failed: reply == nullptr ("
                    << (ctx->err ? ctx->errstr : "unknown") << ")\n";
                return nullptr;
            }
            if (reply->type == REDIS_REPLY_ERROR)
            {
                std::cerr << "[Redis] command error: " << (reply->str ? reply->str : "(null)") << "\n";
                freeReplyObject(reply);
                return nullptr;
            }
            return reply;
        };

    // 2) PING
    {
        redisReply* r = Exec("PING");
        if (!r) { redisFree(ctx); return false; }

        std::cout << "[Redis] PING => "
            << ((r->type == REDIS_REPLY_STATUS && r->str) ? r->str : "(unexpected)") << "\n";
        freeReplyObject(r);
    }

    // 3) SET / GET
    const std::string key = "kymserver:smoke";
    const std::string val = "what the hell";

    {
        redisReply* r = Exec("SET %s %s", key.c_str(), val.c_str());
        if (!r) { redisFree(ctx); return false; }
        std::cout << "[Redis] SET => " << (r->str ? r->str : "(ok)") << "\n";
        freeReplyObject(r);
    }

    {
        redisReply* r = Exec("GET %s", key.c_str());
        if (!r) { redisFree(ctx); return false; }

        if (r->type == REDIS_REPLY_STRING)
            std::cout << "[Redis] GET => " << r->str << "\n";
        else if (r->type == REDIS_REPLY_NIL)
            std::cout << "[Redis] GET => (nil)\n";
        else
            std::cout << "[Redis] GET => (unexpected type=" << r->type << ")\n";

        freeReplyObject(r);
    }

    // 4) DEL
    //{
    //    redisReply* r = Exec("DEL %s", key.c_str());
    //    if (!r) { redisFree(ctx); return false; }
    //
    //    if (r->type == REDIS_REPLY_INTEGER)
    //        std::cout << "[Redis] DEL => " << r->integer << "\n";
    //    else
    //        std::cout << "[Redis] DEL => (unexpected)\n";
    //
    //    freeReplyObject(r);
    //}

    redisFree(ctx);
    std::cout << "[Redis] smoke test OK\n";
    return true;
}

int main()
{
    const bool ok = RedisSmokeTest("127.0.0.1", 6379);
    //return ok ? 0 : 1;

    Error result = AccountDBHelper::Register("test02", "1234", "moalpapa2");
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
    }

    return 0;
}