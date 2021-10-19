#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#define SPEAKER 1 // wPi GPIO 1
#define BASIC_TIME 187 // 박자 기본 시간 16분음표의 출력 시간으로 지정
void tone(int scale, int timing);
int main()
{
	char tone_scale[] = { 'g', 'e', 'e', 'g', 'e', 'c', 'd', 'e',
		'd', 'c', 'e', 'g', 'C', 'g', 'C', 'g',
		'C', 'g', 'e', 'g', 'd', 'f', 'e', 'd', 'c' }; // 계이름
	int time_scale[] = { 4, 2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 4, 3, 1,
		2, 2, 2, 2, 4, 4, 2, 2, 2, 2, 4 };
	// 4 : ♩ 3:♪ 2: ♪ 1: ♬	int counter = 0;
	if (wiringPiSetup() == -1)
		return 1;
	softToneCreate(SPEAKER); // 스피커 소리를 출력할 핀 번호 설정
	for (counter = 0; counter < 25; counter++)
	{
		tone(tone_scale[counter], time_scale[counter]); // 함수로 해당 음과 박자
														//길이를 전달
	}
}
void tone(int scale, int timing){
	int scale_sound; // 주파수 저장할 변수
	switch (scale) // 음에 해당하는 주파수를 찾는다.
	{
	case 'c':
		scale_sound = 261;
		break;
	case 'd':
		scale_sound = 293;
		break;	case 'e':
		scale_sound = 329;
		break;
	case 'f':
		scale_sound = 349;
		break;
	case 'g':
		scale_sound = 391;
		break;
	case 'a':
		scale_sound = 440;
		break;
	case 'b':
		scale_sound = 493;
		break;
	case 'C':
		scale_sound = 523;
		break;
	default:
		scale_sound = 0;
		break;
	}
	}
