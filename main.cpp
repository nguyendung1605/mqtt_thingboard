#include <Arduino.h>
#include <WiFi.h>
#include <ThingsBoard.h>
#include <PubSubClient.h>
#include "send_data.h"
#include "get_data.h"
#include "control.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "message.h"
#include "send_data_node.h"

// Thông tin WiFi
const char *ssid = "333";          // Thay bằng SSID WiFi của bạn
const char *password = "12121212"; // Thay bằng mật khẩu WiFi

// Thông tin ThingsBoard
const char *mqtt_server = "app.coreiot.io"; // Server ThingsBoard
const int mqtt_port = 1883;
const char *access_token = "hd4tWbXpSEMtfTeIRjDf"; // Thay bằng Access Token từ ThingsBoard

// Biến lưu thời gian
unsigned long lastSend;
unsigned long time_reset ;

//
boolean status_warn = false; // trang thai canh bao
boolean status_check;        // dong bo hoa trang thai voi thingsboard và client khi su dung nut nhan
boolean mess = false;
boolean check_node ;
// bien toan cuc
float temperature; // nhiet do

// khai bao chan input output
#define alarm 18        // bao dong
#define switch_alarm 19 // nut nhan dieu khien
//  # define pump  27

// Kết nối WiFi
void setupWiFi()
{
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while ((WiFi.status() != WL_CONNECTED))
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// Kết nối MQTT
void reconnect()
{

  while (!client.connected())
  { // kiểm tra kết nối với thingsboard
    Serial.print("Connecting to ThingsBoard...");
    if (client.connect("Device", access_token, NULL))
    { // kết nối voi thingsboard
      Serial.println("connected");
      // Subscribe để nhận lệnh RPC
      client.subscribe("v1/devices/me/rpc/request/+"); // đăng ký nhận lệnh từ thingsboard
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state()); // trạng thái thất bại của kết nối
      Serial.println(" try again in 5 seconds");
    }
  }
}

void setup()
{
  Serial.begin(9600);
  setupWiFi(); // Kết nối WiFi
  // mqtt
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); // Đăng ký hàm callback để nhận lệnh
  // CHAN DIEU KHIEN
  pinMode(switch_alarm, INPUT_PULLUP);
  pinMode(alarm, OUTPUT);
  // ngat ngoai
  attachInterrupt(digitalPinToInterrupt(switch_alarm), status_interrup, RISING);
  // send_control();
  digitalWrite(alarm, LOW);
  //gui gia tri đầu
  sendTelemetry();
}

void loop()
{
  
  if (!client.connected())
  {
    reconnect(); // Kết nối lại nếu mất kết nối
  }
  client.loop(); // Xử lý các gói tin MQTT

  data_node ();
  // Gửi dữ liệu mỗi 5 giây
  if (millis() - lastSend > 5000)
  {
    sendTelemetry(); // Gửi dữ liệu lên ThingsBoard
    lastSend = millis();
  }
  // dong bo hoa trang thai switch len thingsboard
  /*
   if (status_warn == true && status_check == true)
  {
    status_check = false;
    Serial.println("checkkkk" + String(status_check));
    send_control(status_warn);
    Serial.println("bat ");
  }

  else if (status_warn == false && status_check == true)
  {
    send_control(status_warn);
    Serial.println("thoatttt"+ String(status_warn));
    status_check = false;
  }*/
 
  // canh bao và gửi tin nhắn 

  
  if((status_warn == true && mess == false)|| (status_warn == false && mess == true)){
    mess = status_warn ;
    IRAM_ATTR message ();
    send_control(status_warn);
    //Serial.println("thoat"+ String(mess));
  }
  /*
   if (millis() - time_reset > 60000)
  {
    Serial.println("reset");
    ESP.restart();
  }*/
 
}