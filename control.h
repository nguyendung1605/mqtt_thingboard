#include <Arduino.h>


extern boolean status_warn  ;                          //trang thai canh bao                               
extern boolean status_check ; 

# define alarm   18                                 //  chan canh bao 18 

volatile unsigned long lastInterruptTime = 0;            // thoi gian xay ra ngat cuoi cung 
const unsigned long debounceDelay = 200;                // khoang gian tối thiểu để sử dụng nút nhấn 



void IRAM_ATTR status_interrup (){
    
    unsigned long currentTime = millis();

    if(currentTime - lastInterruptTime > debounceDelay){
        status_check = true ;
        Serial.println("nonn");
        status_warn = !status_warn;                         // doi trang thai bao dong 
        Serial.println("interrup"+String(status_warn));                              
        lastInterruptTime = currentTime;                    // lan sư dụng nút nhấn tiếp theo 
    }
}
/* gui tin nhan đen ngươi sử dụng 
void IRAM_ATTR message (){
if(send_mess == 1){
//gưi tin nhắn báo động được bật
Serial.println("bao dong");
send_mess = 0;
}
else if ( send_mess ==2){
// gui tin nhan báo động được tắt 
Serial.println("tat bao dong");
send_mess = 0 ;
}
}

// dieu khien bao động 
void IRAM_ATTR warn(){
if (status_warn == true){
   digitalWrite(alarm,HIGH);
   send_mess = 1;
}
else {
    digitalWrite(alarm,LOW);
    send_mess = 2;
}
}*/