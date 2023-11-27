#include <check.h>
#include <stdint.h>
#include <setjmp.h>
#include "buf.h"

static jmp_buf escape;

void
test_abort(void)
{
    longjmp(escape, 1);
}

static uint32_t
pcg32(uint64_t *s)
{
    uint64_t m = 0x5851f42d4c957f2d;
    uint64_t a = 0x8b260b70b8e98891;
    uint64_t p = *s;
    uint32_t x = ((p >> 18) ^ p) >> 27;
    uint32_t r = p >> 59;
    *s = p * m + a;
    return (x >> r) | (x << (-r & 31u));
}

static unsigned long
bench(uint64_t *rng)
{
    unsigned long r = 0;
    uint32_t n = 1000000 + pcg32(rng) % 4000000;
    float *buf = 0;

    for (uint32_t i = 0; i < n; i++)
        buf_push(buf, pcg32(rng) / (double)UINT32_MAX);

    float threshold = pcg32(rng) / (double)UINT32_MAX;
    for (uint32_t i = 0; i < n; i++)
        r += buf[i] > threshold;

    buf_free(buf);
    return r;
}

#ifdef _WIN32
#include <windows.h>
uint64_t
uepoch(void)
{
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64_t tt = ft.dwHighDateTime;
    tt <<= 32;
    tt |= ft.dwLowDateTime;
    tt /=10;
    tt -= UINT64_C(11644473600000000);
    return tt;
}
#else
#include <sys/time.h>
uint64_t
uepoch(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000000LL * tv.tv_sec + tv.tv_usec;
}
#endif

volatile int count_pass = 0;
volatile int count_fail = 0;
if (setjmp(escape))
    abort();
float *a = 0;

#suite Inits
#tcase Capacity_init
#test capacity_init
	ck_assert_int_eq(buf_capacity(a), 0);

#tcase Size_init
#test size_init
	ck_assert_int_eq(buf_size(a), 0);

#suite Tools
#tcase Size_1
#test size_1
	buf_push(a, 1.3f);
	ck_assert_int_eq(buf_size(a), 1);

#tcase Size_1
#test size_1
	ck_assert_int_ne(a[0] == (float)1.3f, 0);

#tcase Clear
#test clear
    	buf_clear(a);
	ck_assert_int_eq(buf_size(a), 0);

#test clear_not_free
	ck_assert_int_ne(a, 0);

#tcase Free
#test free
    	buf_free(a);
	ck_assert_int_eq(a, 0);

#tcase Clear_empty
#test clear_empty
    	buf_clear(a);
	ck_assert_int_eq(buf_size(a), 0);

#test clear_no_op
	ck_assert_int_eq(a, 0);

/*
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    TEST("size 10000", buf_size(ai) == 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    TEST("match 10000", match == 10000);
    buf_free(ai);

    buf_grow(ai, 1000);
    TEST("grow 1000", buf_capacity(ai) == 1000);
    TEST("size 0 (grow)", buf_size(ai) == 0);
    buf_trunc(ai, 100);
    TEST("trunc 100", buf_capacity(ai) == 100);
    buf_free(ai);

    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    TEST("size 4", buf_size(a) == 4);
    TEST("pop 3", buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    TEST("size 3", buf_size(a) == 3);
    TEST("pop 2", buf_pop(a) == (float)1.3f);
    TEST("pop 1", buf_pop(a) == (float)1.2f);
    TEST("pop 0", buf_pop(a) == (float)1.1f);
    TEST("size 0 (pop)", buf_size(a) == 0);
    buf_free(a);

    return count_fail != 0;
}*/
