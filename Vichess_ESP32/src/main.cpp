#include <WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>

const char *ssid = "WLAN-W4NZFY";
const char *password = "----";

const char *udpAddress = "192.168.2.103";  // Server IP address
const int udpPort = 11;                  // Server Port
int vt1, vm1, vb1,vt2, vm2, vb2;

WiFiUDP udp;

void sendVibration(int, int,int);
// Define the pin connected to the vibration module's signal pin
int v_topPin = 14;
int v_midPin = 4;
int v_botPin = 19;

void setup() {
  // Start the serial communication
  Serial.begin(115200);

  // Connect to the Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi!");

  // Start UDP communication
  udp.begin(udpPort);
  Serial.println("UDP client started.");
  pinMode(v_topPin, OUTPUT);
  digitalWrite(v_topPin, LOW); // Ensure the vibration module starts off
  pinMode(v_midPin, OUTPUT);
  digitalWrite(v_midPin, LOW); // Ensure the vibration module starts off
  pinMode(v_botPin, OUTPUT);
  digitalWrite(v_botPin, LOW); // Ensure the vibration module starts off
}

void loop() {
  // Wait for a response
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = '\0';  // Null-terminate the string
    }
    sscanf(incomingPacket, "%d,%d,%d %d,%d,%d", &vt1, &vm1, &vb1, &vt2, &vm2, &vb2);
    Serial.printf("Received integers: %d, %d, %d, %d, %d, %d\n", vt1, vm1, vb1, vt2, vm2, vb2);
    sendVibration(vt1, vm1, vb1);
  }

  delay(100);  // Delay between sends
}
void sendVibration(int a, int b, int c)
{
  Serial.printf("Vibration called: %d,%d,%d\n", a,b,c);
  for(int i=0;i<a;i++){
    digitalWrite(v_topPin, HIGH);  
    delay(1000);  // Vibrate for 1 second
    // Turn off the vibration module
    digitalWrite(v_topPin, LOW);   
    delay(1000);  // Pause for 1 second
  }
  
  delay(1000);
  
  for(int i=0;i<b;i++){
    digitalWrite(v_midPin, HIGH);  
    delay(1000);  // Vibrate for 1 second
  
    // Turn off the vibration module
    digitalWrite(v_midPin, LOW);   
    delay(1000);  // Pause for 1 second
  }

  delay(1000);
  
  for(int i=0;i<c;i++){
    digitalWrite(v_botPin, HIGH);  
    delay(1000);  // Vibrate for 1 second
    // Turn off the vibration module
    digitalWrite(v_botPin, LOW);   
    delay(1000);  // Pause for 1 second
  }
}



 