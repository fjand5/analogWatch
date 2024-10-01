#include "wifi.h"

IPAddress apIP(4, 3, 2, 1); // 172.217.28.1

String scanWifi()
{
  JsonDocument doc;
  JsonArray array = doc.to<JsonArray>();
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t *bssid;
  int32_t channel;
  bool hidden;
  int scanResult;

  // Serial.println(F("Starting WiFi scan..."));

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0)
  {
    // Serial.println(F("No networks found"));
  }
  else if (scanResult > 0)
  {
    // Serial.printf(PSTR("%d networks found:\n"), scanResult);

    // Print unsorted scan results
    for (int8_t i = 0; i < scanResult; i++)
    {
      JsonObject nestedObj = array.createNestedObject();
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
      nestedObj["ssid"] = ssid;
      nestedObj["rssi"] = rssi;
      nestedObj["hidden"] = hidden;

      // Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
      //               i,
      //               channel,
      //               bssid[0], bssid[1], bssid[2],
      //               bssid[3], bssid[4], bssid[5],
      //               rssi,
      //               (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
      //               hidden ? 'H' : 'V',
      //               ssid.c_str());
      delay(0);
    }
  }
  else
  {
    // Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }
  String ret;
  serializeJson(array, ret);
  return ret;
  // server.send(200, "application/json", ret.c_str());
}

// void setWifi()
// {
//   DynamicJsonDocument doc(256);
//   auto err = deserializeJson(doc, server.arg(0));

//   if (!err)
//   {
//     setValue("_ssid", doc["ssid"], true);
//     setValue("_sspw", doc["sspw"], true);
//   }
//   server.send(200, "application/json", server.arg(0));
// }
// void getWifi()
// {
//   DynamicJsonDocument doc(256);
//   JsonObject obj = doc.to<JsonObject>();
//   obj["wifi"] = getValue("_ssid");
//   obj["ip"] = WiFi.localIP().toString();
//   String ret;
//   serializeJson(obj, ret);
//   server.send(200, "application/json", ret);
// }
void setupWifi(void)
{
  LittleFS.begin();

  File wifiSetupFile;

  // Nếu chưa thiết lập thông tin thì dung thông số mặc định
  if (!LittleFS.exists("/wifiSetup.json"))
  {
    wifiSetupFile = LittleFS.open("/wifiSetup.json", "w");
    wifiSetupFile.print(DEFAULT_AP);
    wifiSetupFile.close();
  }

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  wifiSetupFile = LittleFS.open("/wifiSetup.json", "r");
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, wifiSetupFile);
  JsonObject wifiSetupJson = doc.as<JsonObject>();
  if (err)
  {
    deserializeJson(doc, DEFAULT_AP);
  }

  WiFi.softAP(
      wifiSetupJson["APSSID"].as<String>() + String("-") + String(ESP.getChipId()),
      wifiSetupJson["APPSK"].as<String>());

  if (wifiSetupJson.containsKey("STASSID") && wifiSetupJson.containsKey("STAPSK"))
    WiFi.begin(wifiSetupJson["STASSID"].as<String>(), wifiSetupJson["STAPSK"].as<String>());
  else
    WiFi.begin(DEFAULT_STASSID, DEFAULT_STAPSK);

  wifiSetupFile.close();

  addHttpApi("/ip",
             [](ESP8266WebServer *server)
             {
               server->send(200, "text/html", WiFi.localIP().toString());
             });
  addHttpApi("/scanWifi",
             [](ESP8266WebServer *server)
             {
               server->send(200, "application/json", scanWifi());
             });
}

void loopWifi(void)
{
  // Serial.println(WiFi.status())
}