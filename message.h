#include <Arduino.h>
#define alarm 18 

extern boolean status_warn ;
void IRAM_ATTR message (){
    if(status_warn == true){
    //gưi tin nhắn báo động được 
    digitalWrite(alarm,HIGH);
    Serial.println("bao dong");
    }
    else if ( status_warn == false){
    // gui tin nhan báo động được tắt 
    Serial.println("tat bao dong");
    digitalWrite(alarm,LOW);
    }
    }