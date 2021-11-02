#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <mosquitto.h>
#define mqtt_host "localhost"
#define mqtt_port 1883
#define MQTT_TOPIC "hello/world"
static int run = 1;
void handle_signal(int s)
{
	run = 0;
}
void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
	printf("connect callback, rc=%d\n", result);
}
void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	bool match = 0;
	printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*)message->payload, message->topic);
	//printf("receive message(%s) : %s",message->topic, message->payload);
	//mosquitto_topic_matches_sub("/devices/wb-adc/controls/+", message->topic, &match);
	if (match) {
		printf("got message for ADC topic\n");
	}
}

int main(int argc, char *argv[])
{
	uint8_t reconnect = true;
	//char clientid[24];//id�� ����ϴ� ���
	struct mosquitto *mosq;
	int rc = 0;
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
	mosquitto_lib_init();
	mosq = mosquitto_new(NULL, true, 0);//mosquitto ����ü ����
	if (mosq) {
		mosquitto_connect_callback_set(mosq, connect_callback);
		mosquitto_message_callback_set(mosq, message_callback);
		rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 60);//mosqutiio ������ ����
		mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 0);//subscribe
		while (run) {
			rc = mosquitto_loop(mosq, -1, 1);
			if (run && rc) {
				printf("connection error!\n");
				sleep(10);
				mosquitto_reconnect(mosq);
			}
		}
		mosquitto_destroy(mosq);
	}
	mosquitto_lib_cleanup();
	return rc;
}