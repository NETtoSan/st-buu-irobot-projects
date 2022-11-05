/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
/*
 *  Thanks again to our saint, mister Rui Santos.
 *  Whoever, where ever, whenever you are, we love you. May God bless your life.
 */
// This is the reciever(slave)!!!
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 16

#include <esp_now.h>
#include <WiFi.h>

int TeamA = 0;
int TeamB = 0;
char A[5];
char B[5];

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message
{
  int scoreA;
  int scoreB;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Score team A : ");
  Serial.println(myData.scoreA);
  Serial.print("Score Team B : ");
  Serial.println(myData.scoreB);
  TeamA = myData.scoreA;
  TeamB = myData.scoreB;
}

// setup for matrix things
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(64, 8, PIN,
                                               NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
                                                   NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG +
                                                   NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
    matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)};

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  // initialize matrix led
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(150);
  matrix.setTextColor(colors[0]);
}

int x = matrix.width();
int pass = 0;

void loop()
{
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);
  sprintf(A, "%d", TeamA);
  sprintf(B, "%d", TeamB);
  matrix.print(F(A));
  matrix.setCursor(32, 0);
  matrix.print(F(B));
  // if(--x < -36) {
  //   x = matrix.width();
  //  if(++pass >= 3) pass = 0;
  //  matrix.setTextColor(colors[pass]);
  // }
  matrix.show();
  delay(100);
}