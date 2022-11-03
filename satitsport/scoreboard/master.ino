/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
/*
 * Thanks to mister Rui Santos, who is really kind as he provides an easy-to-follow
 * tutorials. His kindness will lies in our heart, foever and ever. May God bless him and his love ones.
 */
// THis is the code for the master

#include <esp_now.h>
#include <WiFi.h>
int add1 = 34 ;
int minus1 = 35;
int clear1 = 32;
int teamMode = 33;
int status = 1;
int lightTeamA = 25;
int lightTeamb = 26;
int scoreTeam1 = 0;
int scoreTeam2 = 0;

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30, 0xC6, 0xF7, 0x04, 0xD3, 0x00};
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int scoreA;
  int scoreB;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // pinMode pin that will be use to be inputs
  pinMode(add1,INPUT);
  pinMode(minus1, INPUT);
  pinMode(clear1,INPUT);
  pinMode(successPin,OUTPUT);
  pinMode(failedPin,OUTPUT);
  pinMode(lightTeamA,OUTPUT);
  pinMode(lightTeamB,OUTPUT);
  pinMode(teamMode,INPUT);

}
void loop() {
  Serial.println(digitalRead(add1));

  int add1Status = digitalRead(add1);
  int minus1Status = digitalRead(minus1);
  int clear1Status = digitalRead(clear1);
  // Condition to send the message
  if(add1Status == HIGH){
    if(status == 1){
      scoreTeam1 = scoreTeam1 + 1;
      myData.scoreA = scoreTeam1;
      myData.scoreB = scoreTeam2;
    } else() {
      scoreTeam2 = scoreTeam2 + 1;
      myData.scoreA = scoreTeam1;
      myData.scoreB = scoreTeam2;
    }
   // Send message via ESP-NOW

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
      digitalWrite(successPin,HIGH);
      Serial.println("Sent with success YEHAHHHHHHH");
      Serial.println(myData.scoreA);
    }
    else {
      digitalWrite(failedPin,HIGH);
      Serial.println("Error sending the data");
    }
    delay(200);

    Serial.println("Receive data");

  }

  //minus button
  if(minus1Status == HIGH){
    if(status == 1){
      scoreTeam1 = scoreTeam1 - 1;
      myData.scoreA = scoreTeam1;
      myData.scoreB = scoreTeam2;
    } else() {
      scoreTeam2 = scoreTeam2 - 1;
      myData.scoreA = scoreTeam1;
      myData.scoreB = scoreTeam2;      
    }
    
   // Send message via ESP-NOW

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
      digitalWrite(successPin,HIGH);
      Serial.println("Sent with success YEHAHHHHHHH");
      Serial.println(myData.scoreA);
    }
    else {
      digitalWrite(failedPin,HIGH);
      Serial.println("Error sending the data");
    }
    delay(200);
  }
  if(clear1Status == HIGH){
    if(status == 1){
      scoreTeam1 = 0;
      myData.scoreA = scoreTeam1;
      myData.scoreB = scoreTeam2;
    } else() {
      scoreTeam2 = 0;
      myData.scoreA = scoreTeam1;
      myData.scoreB = scoreTeam2;
    }
   // Send message via ESP-NOW

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
      digitalWrite(successPin,HIGH);
      Serial.println("Sent with success YEHAHHHHHHH");
      Serial.println(myData.scoreA);
    }
    else {
      digitalWrite(failedPin,HIGH);
      Serial.println("Error sending the data");
    }
    delay(200);
  }

  // 
  if(digitalRead(teamMode) == HIGH){
    status = status * (-1);
    if(status == 1){
      digitalWrite(lightTeamA,HIGH);
      digitalWrite(lightTeamB,LOW);
    }else(){
      digitalWrite(lightTeamA,LOW);
      digitalWrite(lightTeamB,HIGH);      
      }
    delay(200);
  }

  //function to send the message, it's in void loop to prevent complicated issues if it's out of the void loop
  
  digitalWrite(successPin,LOW);
  digitalWrite(failedPin,LOW);

 delay(200);
}