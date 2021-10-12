#include <stdio.h>
#include <wiringPi.h>
#define TP 20
#define EP 21
float getDistance(void)
{
	float fDistance;
	int nStartTime, nEndTime;
	digitalWrite(TP, LOW);
	delayMicroseconds(2);
	// pull the Trig pin to high level for more than 10us impulse
	digitalWrite(TP, HIGH);
	delayMicroseconds(10);
	digitalWrite(TP, LOW);
	while (digitalRead(EP) == LOW);
	nStartTime = micros();
	while (digitalRead(EP) == HIGH);
	nEndTime = micros();
	fDistance = (nEndTime - nStartTime) / 29. / 2.;
	return fDistance;
}
int main(void)
{
	if (wiringPiSetupGpio() == -1) {
		return 1;
	}
	pinMode(TP, OUTPUT);
	pinMode(EP, INPUT);
	while (1)
	{
		float fDistance = getDistance();
		printf("Distance:%.2fcm\n", fDistance);
		delay(1000);
	}
	return 0;
}