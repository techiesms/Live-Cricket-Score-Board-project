#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>

// set up pins we are going to use to talk to the screen
#define TFT_DC     D2       // register select (stands for Data Control perhaps!)
#define TFT_RST   D3         // Display reset pin, you can also connect this to the ESP8266 reset
// in which case, set this #define pin to -1!
#define TFT_CS   D4       // Display enable (Chip select), if not enabled will not talk on SPI bus
// initialise the routine to talk to this display with these pin connections (as we've missed off
// TFT_SCLK and TFT_MOSI the routine presumes we are using hardware SPI and internally uses 13 and 11
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

/***************************************************************************/
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;

String result;
String result_1;
String result_2;
String details_2;
String Country_2;
String score_2;
String Country_1;
String details_1;
String score_1;
/***************************************************************************/

void setup(void) {
  tft.init();   // initialize a ST7735S chip,

  /***************************************************************************/
  Serial.begin(115200);

  tft.setRotation(2);
  // tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  delay(1000);
  tft.setRotation(4);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(5, 5);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(2);
  tft.println("LIVE SCORE");
  tft.println("   BOARD  ");
  tft.setTextSize(1);
  tft.setCursor(60, 45);
  tft.println("by");
  tft.setCursor(1, 60);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.println(" techiesms");
  delay(2500);


  tft.setRotation(4);
  // tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(5, 35);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("Connecting");
  tft.println("    to");
  tft.println(" Internet..");
  delay(1500);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("SSID", "PASS");
  /***************************************************************************/

}



void Demo()
{
  tft.setRotation(4);
  tft.fillScreen(ST7735_BLACK);
  tftPrintTest();
}


void loop() {

  while ((WiFiMulti.run() != WL_CONNECTED))
  {
    Serial.println("...");
    delay(1);
  }

  /***************************************************************************/
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(5, 45);
    tft.setTextColor(ST7735_YELLOW);
    tft.setTextSize(2);
    tft.println("Connected!");
    delay(1500);
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(5, 35);
    tft.setTextColor(ST7735_YELLOW);
    tft.setTextSize(2);
    tft.println(" Fetching ");
    tft.println("   Live   ");
    tft.println("  Score...");
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=Your_API_KEY"); //HTTP
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        /***************************************************************************/
        char* temp = &payload[0];
        int i = 0;
        while (temp[i] != 'c' || temp[i + 1] != 'o' || temp[i + 2] != 'u' || temp[i + 3] != 'n' || temp[i + 4] != 't' || temp[i + 5] != 'r' || temp[i + 6] != 'y' )
          i++;
        Country_1 = payload.substring(i + 39);
        int j = 0;
        while (Country_1.charAt(j) != '<')
          j++;
        Country_1 = Country_1.substring(0, j);
        Serial.println(Country_1);
        /***************************************************************************/
        int subject = i + 7 + j;
        payload = payload.substring(subject);
        temp = &payload[0];
        i = 0;
        while (temp[i] != 's' || temp[i + 1] != 'c' || temp[i + 2] != 'o' || temp[i + 3] != 'r' || temp[i + 4] != 'e' )
          i++;
        score_1 = payload.substring(i + 7);
        j = 0;
        while (score_1.charAt(j) != '<')
          j++;
        score_1 = score_1.substring(0, j);
        Serial.println(score_1);
        /***************************************************************************/
        subject = i + 9 + j;
        payload = payload.substring(subject);
        temp = &payload[0];
        i = 0;
        while (temp[i] != 'd' || temp[i + 1] != 'e' || temp[i + 2] != 't' || temp[i + 3] != 'a' || temp[i + 4] != 'i' || temp[i + 5] != 'l' || temp[i + 6] != 's' )
          i++;
        details_1 = payload.substring(i + 9);
        j = 0;
        while (details_1.charAt(j) != '<')
          j++;
        details_1 = details_1.substring(0, j);
        Serial.println(details_1);
        /***************************************************************************/
        /***************************************************************************/
        subject = i + 39 + j;
        payload = payload.substring(subject);
        temp = &payload[0];
        i = 0;
        while (temp[i] != 'c' || temp[i + 1] != 'o' || temp[i + 2] != 'u' || temp[i + 3] != 'n' || temp[i + 4] != 't' || temp[i + 5] != 'r' || temp[i + 6] != 'y' )
          i++;
        Country_2 = payload.substring(i + 39);
        j = 0;
        while (Country_2.charAt(j) != '<')
          j++;
        Country_2 = Country_2.substring(0, j);
        Serial.println(Country_2);
        /***************************************************************************/
        subject = i + 7 + j;
        payload = payload.substring(subject);
        temp = &payload[0];
        i = 0;
        while (temp[i] != 's' || temp[i + 1] != 'c' || temp[i + 2] != 'o' || temp[i + 3] != 'r' || temp[i + 4] != 'e' )
          i++;
        score_2 = payload.substring(i + 7);
        j = 0;
        while (score_2.charAt(j) != '<')
          j++;
        score_2 = score_2.substring(0, j);
        Serial.println(score_2);
        /***************************************************************************/
        subject = i + 9 + j;
        payload = payload.substring(subject);
        temp = &payload[0];
        i = 0;
        while (temp[i] != 'd' || temp[i + 1] != 'e' || temp[i + 2] != 't' || temp[i + 3] != 'a' || temp[i + 4] != 'i' || temp[i + 5] != 'l' || temp[i + 6] != 's' )
          i++;
        details_2 = payload.substring(i + 9);
        j = 0;
        while (details_2.charAt(j) != '<')
          j++;
        details_2 = details_2.substring(0, j);
        Serial.println(details_2);
        /***************************************************************************/
        /***************************************************************************/
        subject = i + 14 + j;
        payload = payload.substring(subject);
        temp = &payload[0];
        i = 0;
        while (temp[i] != 'r' || temp[i + 1] != 'e' || temp[i + 2] != 's' || temp[i + 3] != 'u' || temp[i + 4] != 'l' || temp[i + 5] != 't' || temp[i + 6] != 's' )
          i++;
        result = payload.substring(i + 14);
        j = 0;
        while (result.charAt(j) != '<')
          j++;
        result = result.substring(0, j);
        Serial.println(result);
        /***************************************************************************/
      }
    } else {
      tft.setTextWrap(false);
      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(5, 55);
      tft.setTextColor(ST7735_YELLOW);
      tft.setTextSize(2);
      tft.println(" Fetching");
      tft.println("  Failed");
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      delay(1000);
      tft.setCursor(5, 95);
      tft.setTextColor(ST7735_YELLOW);
      tft.setTextSize(2);
      tft.println("Auto Reset");
      while (1);
    }
    http.end();
  }
  Demo();
  delay(20000);

  /***************************************************************************/

}




void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(30, 5);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  tft.println("Today's Match");
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(33, 20);
  tft.setTextSize(1);
  tft.println("Live Updates");

  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(2);
  char space;

  int count = Country_1.length();
  Serial.println(count);
  switch (count) {
    case 5:
      space = 2;
      break;
    case 6:
      space = 2;
      break;
    case 7:
      space = 1;
      break;

    default:
      space = 0;
  }
  tft.setCursor(10, 45);
  for (int i = 0; i < space; i++)
  {
    tft.print(" ");
  }
  tft.println(Country_1);
  for (int i = 0; i < space; i++)
  {
    tft.print(" ");
  }

  tft.setTextSize(1);
  tft.setCursor(60 ,65);
  tft.setTextColor(ST7735_CYAN);
  tft.print("vs");

  tft.setTextSize(2);
  tft.setTextColor(ST7735_RED);


  count = Country_2.length();
  Serial.println(count);
  switch (count) {
    case 5:
      space = 2;
      break;
    case 6:
      space = 2;
      break;
    case 7:
      space = 1;
      break;

    default:
      space = 0;
  }
  tft.setCursor(15, 80);
  for (int i = 0; i < space; i++)
  {
    tft.print(" ");
  }
  tft.println(Country_2);
  for (int i = 0; i < space; i++)
  {
    tft.print(" ");
  }

  delay(5000);

  tft.setCursor(30, 5);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println(Country_1);
  tft.setCursor(40, 15);
  tft.println("score");
  tft.setTextSize(1);
  tft.setCursor(30, 30);
  tft.setTextColor(ST7735_GREEN);
  tft.print(score_1); tft.println(" runs");
  tft.setTextSize(1);
  tft.setCursor(25, 45);
  tft.print(details_1); tft.println();
  tft.setCursor(30, 65);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println(Country_2);
  tft.setCursor(40, 75);
  tft.println("score");
  tft.setTextSize(1);
  tft.setCursor(30, 90);
  tft.setTextColor(ST7735_GREEN);
  tft.print(score_2); tft.println(" runs");
  tft.setTextSize(1);
  tft.setCursor(15, 105);
  tft.print(details_2); tft.println();

  delay(5000);
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(15, 15);
  tft.println(" STATUS");
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.setCursor(10, 40);
  if (result.length() > 20)
  {
    result_1 = result.substring(0, 19);
    result_2 = result.substring(19);
  }
  Serial.println(result_1);
  tft.print(result_1);
  tft.println();
  tft.print(" "); tft.print(result_2);
  //delay(5000);
}
