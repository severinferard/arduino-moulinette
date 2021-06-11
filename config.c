#include "fakeArduino.h"

int	fakeDigitalRead(int pin, unsigned long timestamp, unsigned int loops)
{
	switch (pin)
	{
	case 2:
		if (loops >= 5 && loops <= 8)
			return (HIGH);
		if (timestamp >= 5000 && timestamp <= 8000)
			return (HIGH);
		break;
	
	default:
		break;
	}
	return (LOW);
}