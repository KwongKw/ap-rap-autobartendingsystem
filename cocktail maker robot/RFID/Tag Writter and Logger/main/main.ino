//Include required libraries
#include "WiFi.h"
#include <HTTPClient.h>
#include "Credentials.h"

// WiFi credentials
const char* ssid = WiFi_SSID;
const char* password = WiFi_PASSWORD;
// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = SCRIPT_ID;

void setup() {
  Serial.begin(115200);
  delay(1000);
  // connect to WiFi
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Recipe: ");
    while (!Serial.available()) {};
      String recipe = Serial.readStringUntil('\n');
      recipe.trim();
      Serial.println();

      String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?recipe=" + recipe;
      Serial.print("POST data to spreadsheet:");
      Serial.println(urlFinal);
      HTTPClient http;
      http.begin(urlFinal.c_str());
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
      int httpCode = http.GET();
      Serial.print("HTTP Status Code: ");
      Serial.println(httpCode);
      //---------------------------------------------------------------------
      //getting response from google sheet
      String payload;
      if (httpCode > 0) {
        payload = http.getString();
        Serial.println("Payload: " + payload);
      }
      //---------------------------------------------------------------------
      http.end();
  }
}