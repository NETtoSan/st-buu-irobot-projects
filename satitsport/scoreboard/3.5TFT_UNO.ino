
// Example By arduitronics.com
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>    // Core graphics library


// wiring with UNO or Mega2560:
//--------------POWER Pins--------------------------------
//   5V  connects to DC 5V
//   GND connects to Ground
//   3V3 do not need to connect(NC)
//--------------LCD Display Pins--------------------------
//   LCD_RD   connects to Analog pin A0
//   LCD_WR   connects to Analog pin A1
//   LCD_RS   connects to Analog pin A2
//   LCD_CS   connects to Analog pin A3
//   LCD_RST  connects to Analog pin A7
//   LCD_D0   connects to digital pin 8
//   LCD_D1   connects to digital pin 9
//   LCD_D2   connects to digital pin 2
//   LCD_D3   connects to digital pin 3
//   LCD_D4   connects to digital pin 4
//   LCD_D5   connects to digital pin 5
//   LCD_D6   connects to digital pin 6
//   LCD_D7   connects to digital pin 7
//--------------SD-card fuction Pins ----------------------
//This Connection Only for UNO, Do not support Mega2560
//because they use different Hardware-SPI Pins
//SD_SS    connects to digital pin 10
//SD_DI    connects to digital pin 11
//SD_DO    connects to digital pin 12
//SD_SCK   connects to digital pin 13


#define LCD_RESET 5 // Can alternately just connect to Arduino's reset pin
#define LCD_CS 18   // Chip Select goes to Analog 3
#define LCD_CD 19  // Command/Data goes to Analog 2
#define LCD_WR 21  // LCD Write goes to Analog 1
#define LCD_RD 22 // LCD Read goes to Analog 0

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int teamA =0;
int teamB = 0;
String A;
String B;

MCUFRIEND_kbv tft;


void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  tft.reset();

  uint16_t identifier = tft.readID();
  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9595) {
    Serial.println(F("Found HX8347-I LCD driver"));
  } else if (identifier == 0x4747) {
    Serial.println(F("Found HX8347-D LCD driver"));
  } else if (identifier == 0x8347) {
    Serial.println(F("Found HX8347-A LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  } else if (identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));
  } else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if (identifier == 0x0101) {
    identifier = 0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else if (identifier == 0x7793) {
    Serial.println(F("Found ST7793 LCD driver"));
  } else if (identifier == 0xB509) {
    Serial.println(F("Found R61509 LCD driver"));
  } else if (identifier == 0x9486) {
    Serial.println(F("Found ILI9486 LCD driver"));
  } else if (identifier == 0x9488) {
    Serial.println(F("Found ILI9488 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier = 0x9486;
  }
  tft.begin(identifier);
  tft.setRotation(90+45);

  //I2c Communication
  //Wire.begin(SLAVE_ADDR);
  //Wire.onRequest(requestEvent); 
  //Wire.onReceive(receiveEvent);
}

void loop(void) {
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.drawFastVLine(240,0,320,RED);
  tft.setCursor(30,30);
  tft.setTextColor(RED);
  tft.setTextSize(5);
  tft.println("Team A");
  tft.setCursor(270,30);
  tft.setTextColor(BLUE);
  tft.setTextSize(5);
  tft.println("Team B");
  tft.setCursor(50,160);
  tft.setTextColor(WHITE);
  tft.setTextSize(10);
  tft.println(A);
  tft.setCursor(290,160);
  tft.setTextColor(WHITE);
  tft.setTextSize(10);
  tft.println(B);
  //tft.setTextColor(RED);  tft.setTextSize(1);
  //tft.println("Hello World!");
  //tft.println(01234.56789);
  //tft.println(0xDEADBEEF, HEX);
  //tft.println();
  //tft.println();
  //tft.setTextColor(GREEN); tft.setTextSize(2);
  //tft.println("Hello World!");
  //tft.println(01234.56789);
  //tft.println(0xDEADBEEF, HEX);
  //tft.println();
  //tft.println();
//
  //tft.setTextColor(BLUE);    tft.setTextSize(3);
  //tft.println("arduitronics.com");
  //tft.println();
  //tft.println(01234.56789);
  //tft.println(0xDEADBEEF, HEX);
//
  //tft.setTextColor(WHITE);    tft.setTextSize(4);
  //tft.println("Hello All !");
  //tft.setTextColor(YELLOW);    tft.setTextSize(5);
  //tft.println("Welcome!");
  //tft.setTextColor(RED);    tft.setTextSize(6);
  //tft.println();
  //tft.println("Thank!");
  //tft.println();
  //tft.println();
  /*
    tft.println();
    tft.setTextColor(GREEN);
    tft.setTextSize(5);
    tft.println("Groop");
    tft.setTextSize(2);
    tft.println("I implore thee,");
    tft.setTextSize(1);
    tft.println("my foonting turlingdromes.");
    tft.println("And hooptiously drangle me");
    tft.println("with crinkly bindlewurdles,");
    tft.println("Or I will rend thee");
    tft.println("in the gobberwarts");
    tft.println("with my blurglecruncheon,");
    tft.println("see if I don't!");*/
  delay(1000); delay(1000); delay(1000); delay(1000); delay(10000);
}

//void receiveEvent() {
// 
//  // Read while data received
//  String res = "";
//  while (0 < Wire.available()) {
//    char x = Wire.read();
//    res += x;    
//  }
//  
//  // Print to Serial Monitor
//  Serial.println("Receive event");
//  Serial.println(res);
//  A= res;
//}
// 
//void requestEvent() {
 
  // Setup byte variable in the correct size
//  byte response[ANSWERSIZE];
//  
//  // Format answer as array
//  for (byte i=0;i<ANSWERSIZE;i++) {
//    response[i] = (byte)answer.charAt(i);
//  }
//  
//  // Send response back to Master
//  Wire.write(response,sizeof(response));
//  
//  // Print to Serial Monitor
//  Serial.println("Request event");
//}
