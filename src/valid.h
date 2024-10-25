#include "Arduino.h"
#include "LittleFS.h"

#include <CustomJWT.h>
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