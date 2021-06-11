#include "main.h"
#include "fakeArduino.h"

int _setup(void)
{
#ifndef REAL_TIME
	TIMESTAMP = 0;
#endif
	LOOPS = 0;
	struct timespec initial_time_spec;
	clock_gettime(CLOCK_MONOTONIC_RAW, &initial_time_spec);
	INITIAL_CLOCK_TIME = initial_time_spec;
	return (0);
}

int main(void)
{
	_setup();
#ifdef REAL_TIME
	printf("REAL TIME\n");
#else
	printf("SIMULATED TIME\nLOOP_TIME=%d\n", LOOP_TIME);
#endif
	printf("TIMEOUT SET TO %i MS\n", TIMEOUT_LIMIT);
	printf("LOOPS LIMIT SET TO %i LOOPS\n", LOOPS_LIMIT);
	printf("\n");
	setup();
	while (TIMESTAMP < TIMEOUT_LIMIT && LOOPS < LOOPS_LIMIT)
	{
		loop();
		LOOPS++;
#ifndef REAL_TIME
		TIMESTAMP += LOOP_TIME;
#endif
	}
	return 0;
}