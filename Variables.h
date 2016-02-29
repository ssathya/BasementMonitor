//Timers
unsigned long sensorTimer = 0;
unsigned long dataSendTimer = 0;
unsigned long disconnetCheckTimer = 0;
unsigned long ledCheckTimer = 0;

//Dynamic values
bool digitalState = true;
int analogValue = 1023;

//Policemen to check if wi-fi disconnected.
short disconnectedCount = 0;

//JSON object
StaticJsonBuffer<258> jsonBuffer;
JsonObject& jsonObj = jsonBuffer.createObject();
