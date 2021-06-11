
#ifndef test
#define test
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "config.h"
// #define REAL_TIME
// #define TIMEOUT_LIMIT 10000
// #define LOOPS_LIMIT 10
// #define LOOP_TIME 1

#ifdef REAL_TIME
# define TIMESTAMP millis()
#else
long TIMESTAMP;
#endif
long LOOPS;
#define LED_BUILTIN 1
#define OUTPUT 1
#define INPUT 2
#define HIGH 1
#define LOW 0

typedef struct s_pin {
 int set;
} t_pin;

t_pin GPIO_PINS[100];
#define digitalRead(pin) fakeDigitalRead(pin, TIMESTAMP, LOOPS)
struct timespec INITIAL_CLOCK_TIME;

int	fakeDigitalRead(int pin, unsigned long timestamp, unsigned int loops);
unsigned long millis(void);
void digitalWrite(int pin, int state);
void delay(unsigned int time);
void pinMode(int pin, int state);
#endif
