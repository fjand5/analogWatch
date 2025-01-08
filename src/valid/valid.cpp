#include "valid.h"
#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

void writeToken(String token)
{
  LittleFS.begin();
  File validTokenFile = LittleFS.open("/validToken.data", "w");
  validTokenFile.print(token);
  validTokenFile.close();
}
String getToken()
{

  String token;
  LittleFS.begin();
  File validTokenFile = LittleFS.open("/validToken.data", "r");
  token = validTokenFile.readString();
  validTokenFile.close();
  return token;
}
bool valid()
{
  String token = getToken();
  bool isValid = false;

  String secretStr = String("") + ESP.getSketchMD5() + WiFi.macAddress();
  char *secret = new char[secretStr.length() + 1];
  secretStr.toCharArray(secret, secretStr.length() + 1);
  CustomJWT jwt(secret, 256);
  jwt.allocateJWTMemory();

  String jwtDataStr = token;
  char *jwtData = new char[jwtDataStr.length() + 1];
  jwtDataStr.toCharArray(jwtData, jwtDataStr.length() + 1);
  int res = jwt.decodeJWT(jwtData);

  if (res == 0)
  {
    // Nếu giải mã thành công
    JsonDocument doc;
    deserializeJson(doc, jwt.payload);
    JsonObject obj = doc.as<JsonObject>();
    uint32_t size = obj["size"];
    //     Serial.print("size: ");
    //     Serial.println(size);
    if (size == ESP.getSketchSize())
      isValid = true;
  }
  jwt.clear();
  delete[] secret;
  delete[] jwtData;
  return isValid;
}
void validProcess()
{
  if (valid())
  {
    // Nếu đã valid thì chạy tiếp, không làm gì cả
    return;
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin("ed9d2f2fbd4ac1e9122", "11df1ae29d6893e69b5eb99e224d4a21");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(11);
    // Nếu chạy quá 3 phút thì thoát
    if (millis() > 3 * 60 * 1000)
      return;
  }
  while (1)
  {
    /* code */
    WiFiClient client;

    HTTPClient http;
    String sketchMD5 = ESP.getSketchMD5();
    String sketchSize = String(ESP.getSketchSize());
    String macAddress = WiFi.macAddress();
    String uri = "/2b1969d1bbe7a5b15779e7fef29b94cb9be1f478";
    uri += "?a4975c86441bcb8f2b99c2de0b9ba62c5977acda7c32f267854bac48b4526139=";
    uri += sketchMD5;
    uri += "&2ca04afe5f763512bf7f9e11f27da7df5da0ba1f987d8ebb71daaeb6e1ec9936=";
    uri += sketchSize;
    uri += "&0d520e852e9550510df3d48cbcb8421b5713715c1fbd5c26f0de786ba29c0723=";
    uri += macAddress;
    if (http.begin(client, String("192.168.4.1"), 2929, uri))
    { // HTTP

      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = http.getString();
        writeToken(payload);
        if (valid())
        {
          http.end();
          delay(111);

          WiFi.disconnect();
          delay(111);
          ESP.restart();
        }
      }
      http.end();
    }
    delay(3333);
  }
};
