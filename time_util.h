#ifndef _TIME_UTIL_H_
#define _TIME_UTIL_H_

#include <assert.h>
#include <time.h>


// Get time elapsed between t0 and t1
static inline struct timespec difftimespec(struct timespec t1, struct timespec t0)
{
    assert(t1.tv_nsec < 1000000000);
    assert(t0.tv_nsec < 1000000000);

    return (t1.tv_nsec >= t0.tv_nsec)
        ? (struct timespec){ t1.tv_sec - t0.tv_sec    , t1.tv_nsec - t0.tv_nsec             }
        : (struct timespec){ t1.tv_sec - t0.tv_sec - 1, t1.tv_nsec - t0.tv_nsec + 1000000000};
}


// Convert struct timespec to seconds
static inline double timespec_to_sec(struct timespec t)
{
    return t.tv_sec * 1.0 + t.tv_nsec / 1000000000.0;
}

// Convert struct timespec to milliseconds
static inline double timespec_to_msec(struct timespec t)
{
    return t.tv_sec * 1000.0 + t.tv_nsec / 1000000.0;
}

// Convert struct timespec to microseconds
static inline double timespec_to_usec(struct timespec t)
{
    return t.tv_sec * 1000000.0 + t.tv_nsec / 1000.0;
}

// Convert struct timespec to nanoseconds
static inline double timespec_to_nsec(struct timespec t)
{
    return t.tv_sec * 1000000000.0 + t.tv_nsec / 1.0;
}


#endif// _TIME_UTIL_H_