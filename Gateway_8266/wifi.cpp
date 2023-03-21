#include "wifi.h"


// the Wifi radio's status
int status = WL_IDLE_STATUS;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus);
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);

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
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(wifi_name, wifi_pass);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
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

