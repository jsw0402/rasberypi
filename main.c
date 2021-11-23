#include <stdio.h>
#include <wiringPi.h>
#define INPUT_PIN 4
int g_nPirState = LOW;
int g_nVal = 0;
int main(void)
{
	if (wiringPiSetupGpio() == -1)
		return 1;
	pinMode(INPUT_PIN, INPUT);
	while (1)
	{
		g_nVal = digitalRead(INPUT_PIN);
		if (g_nVal == HIGH)
		{
			if (g_nPirState == LOW)
				printf("Motion Detected!!\n");
			g_nPirState = HIGH;
		}
		else
		{
			if (g_nPirState == HIGH)
				printf("Motion ended.\n");
			g_nPirState = LOW;
		}
	}
	return 0;
}