//#define DEBUG_ON

#include "ESP8266WiFi.h"
#include "ArduinoJson.h"
#include "Constants.h"
#include "Variables.h"

void setup()
{
#ifdef DEBUG_ON
	Serial.begin(DISPLAY_BAUD);
#endif
	/* add setup code here */
	ConnectToNetwork(ssid, password);

	//Build message header
	BuildPostMessageHeader();

	//define input pin(s).
	pinMode(digitalIn, INPUT);
	pinMode(LED, OUTPUT);
}

void loop()
{
	if (CycleCheck(&sensorTimer, sensorCycleTime))
	{
		digitalState = false;
		analogValue = 0;
		ReadDigitalInput(digitalState);
		ReadAnalogInput(analogValue);
#ifdef DEBUG_ON
		String msg = "Digital Value :";
		msg += digitalState == true ? "High" : "Low";
		msg += " Analog Value :";
		msg += String(analogValue);
		SerialPrintln(msg);
		//delay(5000);
#endif // DEBUG_ON
	}
	if (CycleCheck(&dataSendTimer, dataSendTime))
		SendDataToServer();
	if (CycleCheck(&disconnetCheckTimer, disconnectCheck))
		CheckWiFiHealth(ssid, password);
	if (CycleCheck(&ledCheckTimer, ledCycleTimer))
		BlinkLed();
}
void ReadDigitalInput(bool &state)
{
	state = digitalRead(digitalIn) == 1 ? true : false;
}
void ReadAnalogInput(int &value)
{
	value = analogRead(analogPin);
}
void SendDataToServer()
{
	SerialPrint("Connecting to ");
	SerialPrintln(host);

	WiFiClient client;
	const uint16_t httpPort = 80;
	if (!client.connect(host, httpPort)) {
		SerialPrintln("*** Connection failed ***");
		++disconnectedCount;
		return;
	}
	disconnectedCount = 0;
	client.setTimeout(5000);
	String serverMessage = BuildOutMessage();
	client.print(serverMessage);
	SerialPrint(serverMessage);
	delay(10);
	String ackMsg;
	for (size_t i = 0; i < 1000; i++)
	{
		while (client.available()) {
			char c = client.read();
			ackMsg += c;
		}
		if (ackMsg.length() > 20)
			break;
		delay(50);
	}
	SerialPrintln(ackMsg);
}
String BuildOutMessage()
{
	String outMessage(postMessageHeader);
	jsonObj["field1"] = digitalState == true ? "1" : "0";
	jsonObj["field2"] = analogValue;
	char buffer[128];
	jsonObj.printTo(buffer, 128);
	int stringLen = strlen(buffer);
	outMessage.replace("$JSONSTRINGLENGTH$", String(stringLen));
	outMessage += buffer;
	outMessage += "\r\n";
	return outMessage;
}