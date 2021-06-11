#include "fakeArduino.h"

unsigned long millis(void)
{
#ifdef REAL_TIME
	struct timespec time_spec;
	clock_gettime(CLOCK_MONOTONIC_RAW, &time_spec);
	return ((time_spec.tv_sec - INITIAL_CLOCK_TIME.tv_sec) * 1000000 + (time_spec.tv_nsec - INITIAL_CLOCK_TIME.tv_nsec) / 1000) / 1000;
#else
	return (TIMESTAMP);
#endif
}

void digitalWrite(int pin, int state)
{
	if (GPIO_PINS[pin].set != OUTPUT)
		printf("ERROR: pin %d was no set as an output", pin);
	printf("%li digitalWrite(%d, %d)\n", millis(), pin, state);
}

void delay(unsigned int time)
{
#ifdef REAL_TIME
	usleep(time * 1000);
#else
	TIMESTAMP += time;
#endif
}

void pinMode(int pin, int state)
{
	GPIO_PINS[pin].set = state;
}
