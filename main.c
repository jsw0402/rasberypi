#include <wiringPi.h>         // wiringPi ���̺귯�� ���
#include <stdio.h>            // ǥ������¿� ���̺귯��  
#include <stdlib.h>           // ǥ�� ��ƿ��Ƽ�� ���̺귯��
#include <stdint.h>           // ���� �ڷ��� ���̺귯��

#define MAX_TIMINGS	85        // �ִ� ��ȣ ���� ����
#define DHT_PIN		2	      // GPIO�� ����� �� ��ȣ

int data[5] = { 0, 0, 0, 0, 0 };       // �½��� �� checksum ������ ����� ���� �迭

void read_dht_data()                    // dht������ �б� �Լ�
{
	uint8_t laststate = HIGH;          // DHT���� ���� ����� ����(���� ��ȣ�� HIGH���� LOW���� Ȯ���ϱ� ���� �뵵)
	uint8_t counter = 0;             // ��ȣ�� ���̸� �����ϱ� ���� ī���� ����
	uint8_t j = 0, i;          // 40���� ��ȣ �ε��� �� ����

	data[0] = data[1] = data[2] = data[3] = data[4] = 0;    //�ʱ� ������ ���� 0���� ����

															/* DHT11�������� ����� �����ϱ� ���� DATA���� 18ms���� LOW�� ��� */
	pinMode(DHT_PIN, OUTPUT);
	digitalWrite(DHT_PIN, LOW);
	delay(18);

	/* ���� �Է¸��� �����ؼ� DHT11�� ���� ������ ��ٸ� */
	pinMode(DHT_PIN, INPUT);

	/* DHT11���� ���� ��ȣ ���� �� �����ͺ�Ʈ ���� */
	for (i = 0; i < MAX_TIMINGS; i++)       // �� 85�� ���� ��ȣ�� Ȯ��
	{
		counter = 0;                           // �ʱ� ī���ʹ� 0
		while (digitalRead(DHT_PIN) == laststate) //DHT���� ��ȣ�� �о ���� ������ DATA�� ��ȣ�� ���� ����==�� ��ȣ�� ��ȯ�� ���� ����
		{
			counter++;                              // ī���� ���� 1 ����
			delayMicroseconds(1);                 // 1uS(����ũ����) ���� ���
			if (counter == 255)                  // ī���Ͱ� 255���� �����ϸ�, �� �ʹ� ���� ���� ����ϸ�==������ ����ٴ� �ǹ� ��
			{
				break;                              // ī���� ���� ����
			}
		}
		laststate = digitalRead(DHT_PIN);       // ���� �� ���� ����

		if (counter == 255)                     // ī���Ͱ� 255�̻� �����ߴٸ�, �����ͺ�Ʈ ���� ����== for�� ������ ������ ó������ ���� �ްڴٴ� �ǹ���
			break;

		/* ù��° 3���� ��ȣ�� �����ϰ� ¦����°�� �ش��ϴ� ��ȣ���̸� �о� 0���� 1������ ���� �½��� ������ ����
		ù��° 3���� ��ȣ�� DHT11�� ���� �� ��ȣ�� ���� ������ ���̸� ���� ������ �����ϴ� ���� �ƴϹǷ� ������.
		¦���� �����ϴ� ������ ¦�� ��°�� ��ȣ ���̿� ���� �ش� ��ȣ�� 0�� �ǹ��ϴ��� 1�� �ǹ��ϴ����� ��Ÿ��.
		*/
		if ((i >= 4) && (i % 2 == 0))   // 4��° ������ ��ȣ�̸鼭 ¦����° ��ȣ��� 
		{
			/* ������ ������ ��Ʈ�� �µ� �� ���� ������ �ϳ��� �־��� */
			data[j / 8] <<= 1;                    // �������� �ڸ����� �ϳ��� ������ �̵���Ŵ
			if (counter > 16)                    // ī������ ���� 16���� ũ�ٸ�, �� ��ȣ�� ���̰� �� ��Ʈ 1�� �νĵȴٸ�
				data[j / 8] |= 1;                  // �ش� ��Ʈ�� 1�� �־���
			j++;                                 // ���� �����͸� ���� �ε��� ���� �ϳ� ���� ��Ŵ
		}
	}

	/*
	* 40��Ʈ�� �� Ȯ���ߴٸ� (8��Ʈ x 5 ) üũ�� �����Ϳ� ����üũ�� �ؼ�
	* ������ ������ �����͸� �����.
	*/
	if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
	{        //������ ������ ���� �� �µ� ���
		printf("Humidity = %d.%d %% Temperature = %d.%d C\n", data[0], data[1], data[2], data[3]);
	}
	else {
		printf("Data not good, skip\n");      //���� �߻��� Data not good �޽��� ���
	}
}

int main(void)
{
	printf("Raspberry Pi DHT11 temperature/humidity test\n");

	if (wiringPiSetupGpio() == -1)    //����������� BCM GPIO �ɹ�ȣ�� ����ϰڴٰ� ����
		exit(1);

	while (1)
	{
		read_dht_data();              // �µ� �� ���� ������ ȹ�� �� ���
		delay(2000);                // ���� �б���� 2�� ���
	}

	return(0);
}