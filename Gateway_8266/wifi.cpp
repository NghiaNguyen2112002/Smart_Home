#include "wifi.h"

String list_wf;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus);
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);
String MakePage(String title, String contents);


void WF_Init(void){
  WiFi.mode(WIFI_AP_STA);

  WiFi.softAP(WIFI_GATEWAY_NAME, WIFI_GATEWAY_PASS);

  // Serial.print("IP sta: "); Serial.println(WiFi.localIP());
  Serial.print("IP ap: "); Serial.println(WiFi.softAPIP());

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Register for a callback function that will be called when data is sent or received
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  for(int i = 0; i < NO_OF_NODE_SENSOR - 1; i++){
    esp_now_add_peer(Broadcast_Address[i], ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  }
  
}

bool WF_IsConnected(void){
  return WiFi.status() == WL_CONNECTED;
}
void WF_Connect(String wifi_name, String wifi_pass){
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(wifi_name, wifi_pass);
  }
}

void WF_Disconnect(void){
  WiFi.disconnect();
}

//=======Webserver for config wifi=========//
void WF_CreateWebserver(void){
  WiFi.disconnect();              //ngat ket noi wifi
  WiFi.softAP(WIFI_GATEWAY_NAME, WIFI_GATEWAY_PASS);
  Serial.println(WiFi.softAPIP());

  int n = WiFi.scanNetworks();
  delay(100);
  list_wf = "";
  
  for (int i = 0; i < n; i++) {    //dua danh sach wifi vao list
    list_wf += "<option value='";
    list_wf += WiFi.SSID(i);
    list_wf += "'>";
    list_wf += WiFi.SSID(i);
    list_wf += "</option>";
  }

  WebServer.on("/", [](){
    String s = "<h1>Wi-Fi Configuration.</h1>";
      s += "<form method='get' action='setap'><label>SSID: </label><select name='wf_name'>";
      s += list_wf;
      s += "Password: <input name='pass' length=64 type='passwod'>";
      s += "<input type='submit'>";
    WebServer.send(200, "text/html", MakePage("Wifi Configuration", s));  
  });

  WebServer.on("/setap", [](){
    _wifi_name = WebServer.arg("wf_name");
    _wifi_pass = WebServer.arg("pass");
    _flag_wf_selected = true;

    Serial.println(_wifi_name);
    Serial.println(_wifi_pass);
    
    String s = "<h1>Wifi configuration's successful !!</h1>";
    WebServer.send(200, "text/html", MakePage("", s));
  });


  WebServer.begin();
}

//==================SUBFUNCTION=============//
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus){
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len){
    memcpy(&_data_node, incomingData, sizeof(_data_node));

    _flag_send_data_sv = true;
}


String MakePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}
