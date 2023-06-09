#include "wifi.h"

// the Wifi radio's status
int status = WL_IDLE_STATUS;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus);
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);

void WF_Init(void){
  WiFi.mode(WIFI_AP_STA);

  Serial.println("Connecting to AP ...");
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print("*");
  // }

  Serial.print("IP sta: "); Serial.println(WiFi.localIP());

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Register for a callback function that will be called when data is sent or received
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  esp_now_add_peer(Broadcast_Address, ESP_NOW_ROLE_COMBO, 1, NULL, 0);


}


void WF_Reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    // while (WiFi.status() != WL_CONNECTED) {
    //   delay(500);
    //   Serial.print(".");
    // }
    // Serial.println("Connected to AP");
  }
}

void WF_CheckConnection(){
  if (WiFi.status() != WL_CONNECTED) {
    WF_Reconnect();
  }
}

bool WF_IsConnected(void){
  return (WiFi.status() == WL_CONNECTED);
}

void WF_SendDataEspnow(char* address, char* data){
  // esp_now_send(address, (char*) &data, sizeof(data));
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
    memcpy(&_command, incomingData, sizeof(_command));
    _flag_receive_command = true;
}

