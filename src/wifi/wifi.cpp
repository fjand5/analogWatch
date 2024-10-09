#include "wifi.h"

IPAddress apIP(4, 3, 2, 1); // 172.217.28.1
String apSSID;
String apPSK;
String staSSID;
String staPSK;
void updateWifi()
{
  LittleFS.begin();

  File wifiSetupFile;
  wifiSetupFile = LittleFS.open("/wifiSetup.json", "w");
  JsonDocument doc;
  JsonObject wifiSetupJson = doc.to<JsonObject>();
  wifiSetupJson["STASSID"] = staSSID;
  wifiSetupJson["STAPSK"] = staPSK;
  wifiSetupJson["APSSID"] = apSSID;
  wifiSetupJson["APPSK"] = apPSK;
  serializeJson(doc, wifiSetupFile);
  wifiSetupFile.close();
}

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
String getWifi()
{
  JsonDocument doc;
  JsonObject wifiSetupJson = doc.to<JsonObject>();
  wifiSetupJson["STASSID"] = staSSID;
  wifiSetupJson["STAPSK"] = staPSK;
  wifiSetupJson["APSSID"] = apSSID;
  wifiSetupJson["APPSK"] = apPSK;
  wifiSetupJson["ip"] = WiFi.localIP().toString();
  String ret;
  serializeJson(wifiSetupJson, ret);
  return ret;
}
void setupWifi(void)
{
  LittleFS.begin();

  File wifiSetupFile;

  // Nếu chưa thiết lập thông tin thì dung thông số mặc định
  if (!LittleFS.exists("/wifiSetup.json"))
  {
    wifiSetupFile = LittleFS.open("/wifiSetup.json", "w");
    wifiSetupFile.print(DEFAULT_SETUP_WIFI);
    wifiSetupFile.close();
  }

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  wifiSetupFile = LittleFS.open("/wifiSetup.json", "r");
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, wifiSetupFile);
  if (err != DeserializationError::Ok)
  {
    deserializeJson(doc, DEFAULT_SETUP_WIFI);
  }
  JsonObject wifiSetupJson = doc.as<JsonObject>();
  apSSID = wifiSetupJson["APSSID"].as<String>();
  apPSK = wifiSetupJson["APPSK"].as<String>();

  WiFi.softAP(apSSID + String("-") + String(ESP.getChipId()), apPSK);
  if (wifiSetupJson["STASSID"].is<String>() && wifiSetupJson["STAPSK"].is<String>())
  {

    staSSID = wifiSetupJson["STASSID"].as<String>();
    staPSK = wifiSetupJson["STAPSK"].as<String>();
    WiFi.begin(staSSID, staPSK);
  }
#ifdef DEVELOPMENT
  else
    WiFi.begin(DEFAULT_STASSID, DEFAULT_STAPSK);
#endif
  wifiSetupFile.close();

  addHttpApi("/scanWifi",
             [](ESP8266WebServer *server)
             {
               server->send(200, "application/json", scanWifi());
             });
  addHttpApi("/getWifi",
             [](ESP8266WebServer *server)
             {
               server->send(200, "application/json", getWifi());
             });
  addHttpApi("/setWifi",
             [](ESP8266WebServer *server)
             {
               JsonDocument doc;
               JsonObject obj = doc.to<JsonObject>();

               obj["oldValue"] = getWifi();
               apSSID = server->hasArg("apSSID") ? server->arg("apSSID") : apSSID;
               apPSK = server->hasArg("apPSK") ? server->arg("apPSK") : apPSK;
               staSSID = server->hasArg("staSSID") ? server->arg("staSSID") : staSSID;
               staPSK = server->hasArg("staPSK") ? server->arg("staPSK") : staPSK;
               updateWifi();
               obj["newValue"] = getWifi();
               String ret;
               serializeJson(obj, ret);
               server->send(200, "application/json", ret.c_str());
             });
}

void loopWifi(void)
{
}