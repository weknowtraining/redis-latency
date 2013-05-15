#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "hiredis.h"
#include "dbg.h"

static long long mstime(void) {
    struct timeval tv;
    long long mst;

    gettimeofday(&tv, NULL);
    mst = ((long long)tv.tv_sec)*1000;
    mst += tv.tv_usec/1000;
    return mst;
}

int main(int argc, char **argv) {
    long long start, latency;

    char * host = "192.168.2.181";
    if (argc > 1) {
        host = argv[1];
    }

    redisReply *reply = NULL;
    redisContext *c = redisConnect(host, 6379);
    check(c, "Failed to connect");

    while(1) {
        start = mstime();
        reply = redisCommand(c, "PING");
        check(reply, "I/O Error");
        freeReplyObject(reply);
        latency = mstime() - start;
        printf("%lld\n", latency);
        fflush(stdout);
        usleep(500000); // 500 ms
    }

    return 0;

error:
    if (c) { redisFree(c); }
    if (reply) { freeReplyObject(reply); }
    return 1;
}
