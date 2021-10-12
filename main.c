#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#define CDS 10
int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return 1;

	pinMode(CDS, INPUT);
	while (1)
	{
		if (digitalRead(CDS) == 0)
			printf("Dark....\n");
		if (digitalRead(CDS) == 1)
			printf("Bright!!!\n");
		delay(200);
	}
	return 0;
}