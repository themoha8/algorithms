#include <time.h> /* struct timespec */
#include "benchmark.h"

enum { microsec_as_nanosec = 1000,
	   sec_as_nanosec = 1000000000,
	   sec_as_microsec = 1000000
};

double diff_timestamps(const struct timespec *start,
							  const struct timespec *end)
{
	struct timespec temp;

	if (end->tv_nsec - start->tv_nsec < 0) {
		temp.tv_sec = end->tv_sec - start->tv_sec - 1;
		temp.tv_nsec = end->tv_nsec - start->tv_nsec + sec_as_nanosec;
	} else {
		temp.tv_sec = end->tv_sec - start->tv_sec;
		temp.tv_nsec = end->tv_nsec - start->tv_nsec;
	}

	double microsec = temp.tv_sec * sec_as_microsec + temp.tv_nsec / microsec_as_nanosec;

	/* result in seconds */
	return microsec / sec_as_microsec;
}
