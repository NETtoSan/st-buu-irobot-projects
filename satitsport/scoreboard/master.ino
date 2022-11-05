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
#include <Wire.h>
#include <WireSlave.h>
int add1 = 34;
int minus1 = 35;
int clear1 = 32;
int successPin = 33;
int failedPin = 25;
int scoreTeam1 = 0;
int scoreTeam2 = 0;
#define SLAVE_ADDR 9
#define ANSWERSIZE 5

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30, 0xC6, 0xF7, 0x04, 0xD3, 0x00};
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
  int scoreA;
  int scoreB;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
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
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
  // pinMode pin that will be use to be inputs
  pinMode(add1, INPUT);
  pinMode(minus1, INPUT);
  pinMode(clear1, INPUT);
  pinMode(successPin, OUTPUT);
  pinMode(failedPin, OUTPUT);

  // Initialize I2C communications as Master
  WireSlave.begin()
  {
  }

  void loop()
  {
    Serial.println(digitalRead(add1));

    int add1Status = digitalRead(add1);
    int minus1Status = digitalRead(minus1);
    int clear1Status = digitalRead(clear1);
    // Condition to send the message
    if (add1Status == HIGH)
    {
      scoreTeam1 = scoreTeam1 + 1;
      myData.scoreA = scoreTeam1;
      myData.scoreB = 69;
      // Send message via ESP-NOW

      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

      if (result == ESP_OK)
      {
        digitalWrite(successPin, HIGH);
        Serial.println("Sent with success YEHAHHHHHHH");
        Serial.println(myData.scoreA);
      }
      else
      {
        digitalWrite(failedPin, HIGH);
        Serial.println("Error sending the data");
      }
      delay(200);

      // Write a charatre to the Slave
      WireSlave.beginTransmission(SLAVE_ADDR);
      char teamAStr[5];
      sprintf(teamAStr, '%d', scoreTeam1);
      WireSlave.write("");
      WireSlave.endTransmission();

      Serial.println("Receive data");

      // Read response from Slave
      // Read back 5 characters
      WireSlave.requestFrom(SLAVE_ADDR, ANSWERSIZE);

      // Add characters to string
      String response = "";
      while (WireSlave.available())
      {
        char b = WireSlave.read();
        response += b;
      }

      // Print to Serial Monitor
      Serial.println(response);
    }

    // minus button
    if (minus1Status == HIGH)
    {
      scoreTeam1 = scoreTeam1 - 1;
      myData.scoreA = scoreTeam1;
      myData.scoreB = 69;
      // Send message via ESP-NOW

      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

      if (result == ESP_OK)
      {
        digitalWrite(successPin, HIGH);
        Serial.println("Sent with success YEHAHHHHHHH");
        Serial.println(myData.scoreA);
      }
      else
      {
        digitalWrite(failedPin, HIGH);
        Serial.println("Error sending the data");
      }
      delay(200);
    }
    if (clear1Status == HIGH)
    {
      scoreTeam1 = 0;
      myData.scoreA = scoreTeam1;
      myData.scoreB = 69;
      // Send message via ESP-NOW

      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

      if (result == ESP_OK)
      {
        digitalWrite(successPin, HIGH);
        Serial.println("Sent with success YEHAHHHHHHH");
        Serial.println(myData.scoreA);
      }
      else
      {
        digitalWrite(failedPin, HIGH);
        Serial.println("Error sending the data");
      }
      delay(200);
    }

    // function to send the message, it's in void loop to prevent complicated issues if it's out of the void loop

    digitalWrite(successPin, LOW);
    digitalWrite(failedPin, LOW);

    delay(200);
  }
