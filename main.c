#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <stdio.h>
#define MQTT_HOSTNAME "localhost"
#define MQTT_PORT 1883
#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"
#define MQTT_TOPIC "hello/world"
int main(int argc, char **argv) {
	struct mosquitto *mosq = NULL;
	// �ʱ�ȭ
	mosquitto_lib_init();
	// ��Ű�� ��Ÿ�� ��ü�� Ŭ���̾�Ʈ ���� ID ����
	mosq = mosquitto_new(NULL, true, NULL);
	if (!mosq) {
		printf("Cant initiallize mosquitto library\n");
		exit(-1);
	}
	21 Publisher �ڵ�
		mosquitto_username_pw_set(mosq, MQTT_USERNAME, MQTT_PASSWORD);
	// MQTT ���� ���� ����, keep-alive �޽��� ��� ����
	int ret = mosquitto_connect(mosq, MQTT_HOSTNAME, MQTT_PORT, 10);
	if (ret) {
		printf("Cant connect to mosquitto server\n");
		exit(-1);
	}
	char text[20] = ��I��m CppCode";
		ret = mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(text), text, 0, false);
	if (ret) {
		printf("Cant connect to mosquitto server\n");
		exit(-1);
	}
	// ��Ʈ��ũ ������ ������ ���� ��Ű�� ������ �������� ����� �����̰� �ʿ���
	//sleep(1);
	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
}