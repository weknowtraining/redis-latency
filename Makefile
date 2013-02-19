CC?=gcc

redis-latency: redis-latency.c dbg.h hiredis
	${CC} -pipe -Wall -Werror -Ideps/hiredis -o $@ $< deps/hiredis/libhiredis.a

hiredis:
	cd deps/hiredis && make

clean:
	cd deps/hiredis && make clean
	rm -rf redis-latency
