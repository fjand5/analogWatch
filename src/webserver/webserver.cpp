#include "webserver.h"
ESP8266WebServer *server;
ESP8266HTTPUpdateServer httpUpdater;

void addHttpApi(String url, Response response)
{
  // Tạo mới server nếu chưa tạo, bởi vì addHttpApi có thể gọi bất cứ lúc nào
  if (server == nullptr)
  {
    server = new ESP8266WebServer(80);
    server->addHook([](const String &method, const String &url, WiFiClient *client, ESP8266WebServer::ContentTypeFunction contentType)
                    {
    server->sendHeader("Access-Control-Allow-Origin", "*");
    server->sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
    server->sendHeader("Access-Control-Allow-Headers", "*");
    server->sendHeader("Access-Control-Expose-Headers", "*");
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE; });
  }
  server->on(url,
             [=]()
             {
               response(server);
               //  server->send(200, "application/javascript", "WiFi.localIP().toString()");
             });
}

void handleIndex()
{
  server->sendHeader("Content-Encoding", "gzip");
  server->send(200, "text/html", index_html, index_html_length);
}
void setupWebserver()
{
  if (server == nullptr)
  {
    server = new ESP8266WebServer(80);
    server->addHook([](const String &method, const String &url, WiFiClient *client, ESP8266WebServer::ContentTypeFunction contentType)
                    {
    server->sendHeader("Access-Control-Allow-Origin", "*");
    server->sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
    server->sendHeader("Access-Control-Allow-Headers", "*");
    server->sendHeader("Access-Control-Expose-Headers", "*");
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE; });
  }
  server->on("/", handleIndex);
  server->on("/js/app.js", []()
             {
              server->sendHeader("Content-Encoding", "gzip");
              server->send(200, "application/javascript", app_js, app_js_length); });
  server->on("/css/index.css", []()
             {
              server->sendHeader("Content-Encoding", "gzip");
              server->send(200, "text/css", index_css, index_css_length); });
  // server->on("/fonts/element-icons.woff", []()
  //            {
  //             server->sendHeader("Content-Encoding", "gzip");
  //             server->send(200, "application/javascript", font_woff, font_woff_length); });
  server->on("/static/favicon.ico", []()
             {
              server->sendHeader("Content-Encoding", "gzip");
              server->send(200, "application/javascript", favicon_ico, favicon_ico_length); });

  httpUpdater.setup(server);
  server->begin();
}
void loopWebserver()
{
  server->handleClient();
}