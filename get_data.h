#include <Arduino.h>
#include <ThingsBoard.h>
#include <PubSubClient.h>

# define alarm   18  

// Hàm xử lý khi nhận dữ liệu từ ThingsBoard
void callback(char* topic, byte* payload, unsigned int length) {
    String data_thingsboard;
    Serial.print("Nhận tin nhắn từ topic: ");
    Serial.println(topic);
    Serial.print("Nội dung: ");
    for (int i = 0; i < length; i++) {
      //Serial.print((char)payload[i]);
      data_thingsboard = data_thingsboard + (char)payload[i];
    }
    Serial.println(data_thingsboard);
    StaticJsonDocument<100> doc;
    DeserializationError error = deserializeJson(doc, data_thingsboard);
    String kt = doc["params"];
    Serial.println(kt);

    extern boolean status_warn ;
      if (kt == "true"){
          status_warn = true;
          Serial.println("thingsboard"+ String(status_warn));
      }
      else if( kt == "false"){
          status_warn = false ;
          Serial.println("thingsboard"+ String(status_warn));
      }
      
  }