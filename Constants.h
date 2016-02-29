//Display
#define DISPLAY_BAUD 115200

//Network related
const char* host = "api.thingspeak.com";
const char* ssid = "My Data Center";
const char* password = "God give me the password";

//Inputs
#define analogPin  A0
#define digitalIn  4

//Strings for POST request
const char* postHeader1 = "POST /update?key=1234567890ABCDEF HTTP/1.1\r\n";
const char* postHeader2 = "Host: api.thingspeak.com\r\n";
const char* postHeader3 = "Content-Type: application/json\r\n";
const char* postHeader4 = "Cache-Control: no-cache\r\n";
const char* postHeader5 = "Content-Length: $JSONSTRINGLENGTH$";
const char* postHeader6 = "\r\nConnection: close\r\n\r\n";
String postMessageHeader;

//Loop Controllers
#ifdef DEBUG_ON
#define sensorCycleTime 5000U //read the values every 5 seconds
#define dataSendTime  60000U // send the values every 1 minutes
#else
#define sensorCycleTime 300000U //read the values every 5 minutes
#define dataSendTime  600000U // send the values every 10 minutes
#endif // DEBUG_ON

#define disconnectCheck 180000U //check if Wi-if is connected every 3 minutes
#define ledCycleTimer 30U

//LED
#define LED 5
