

#include <ESP8266WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(43333);
int pwmPin = 4;
int pwmFreq = 1000;
int pwmDuty = 512;
int current = 512;
int stepcounter = 0;
int posStepcounter = 0;
int dimTimer = 0;
int lastValue = 512;



void setup() {
	Serial.begin(115200);
	delay(10);

	// prepare GPIO2
	pinMode(2, OUTPUT);
	analogWrite(2, current);

	// Connect to WiFi network
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	IPAddress ip(10, 100, 1, 50);
	IPAddress gw(10, 100, 1, 1);
	IPAddress sn(255, 255, 255, 0);

	WiFi.config(ip, gw, sn);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");

	// Start the server
	server.begin();
	Serial.println("Server started");

	// Print the IP address
	Serial.println(WiFi.localIP());
}

void loop() {
	// Check if a client has connected
	WiFiClient client = server.available();
	if (!client) {
		return;
	}

	// Wait until the client sends some data
	Serial.println("new client");
	while (!client.available()){
		delay(1);
	}

	// Read the first line of the request
	String req = client.readStringUntil('\r');
	Serial.println(req);
	client.flush();

	int target = req.substring(28).toInt();
	int fadetime = req.substring(11, 15).toInt();

	Serial.println("target " + req.substring(28));
	Serial.println("ft " + req.substring(11, 15));

	client.flush();

	if (target == -1){
		lastValue = current;
		target = 0;
	}
	if (target == -2){
		target = lastValue;
	}

	stepcounter = (target)-(current);

	if (stepcounter < 0){
		posStepcounter = (stepcounter)*-1;
	}
	else{
		posStepcounter = (stepcounter);
	}

	if (posStepcounter == 0){
		posStepcounter = (posStepcounter)+1;
	}

	dimTimer = fadetime / posStepcounter;

	if (dimTimer == 0){
		dimTimer = dimTimer + 1;
	}

	Serial.println("DT:" + String(dimTimer));
	Serial.println("Cur:" + String(current));
	Serial.println("Target:" + String(target));

	while (current != target)
	{
		
		if (current < target){
			current++;
		}
		if (current > target){
			current--;
		}
		//as the LED strip flickers below a target of 8 we simply turn it off. This might not
		//be the case for all circuits, so you can try and ommit it
		if (current < 8){ 
			analogWrite(2, 0);
		}
		else{
			analogWrite(2, current);
		}
		Serial.println("Cur:" + String(current));

		delay(dimTimer);
	}

}


