#include <Arduino.h>
#include <ThingsBoard.h>
#include <PubSubClient.h>


// Khai báo đối tượng
WiFiClient espClient;
PubSubClient client(espClient);

//#define pump 27
//# define alarm  18
boolean led_state;


void send_control(boolean led_state);

  // Gửi dữ liệu lên ThingsBoard
  void sendTelemetry() {
    extern float temperature ;
   
    String payload = "{\"tem\":" + String(temperature) + "}";
    //String payload = "{'tem':"+String(temperature)+" , 'led_state':"+true+"}";
    char data[30];
    payload.toCharArray(data, 30);
    client.publish("v1/devices/me/telemetry", data);  // gửi dữ liệu lên thingsboard 
    Serial.println("Sent: " + payload);
    Serial.println (strlen(data));
    
  }

  void send_control(boolean led_state){
    StaticJsonDocument<200> doc;
    doc["led_state"] = led_state;
    char buffer[200];
    serializeJson(doc, buffer);
    client.publish("v1/devices/me/attributes", buffer);
    Serial.printf("check");
    Serial.println("yyyyy"+String (led_state));
  }