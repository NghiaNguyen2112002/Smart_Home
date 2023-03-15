#include "wifi.h"

// the Wifi radio's status
int status = WL_IDLE_STATUS;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus);
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len);

void WF_Init(void){
  WiFi.mode(WIFI_AP_STA);

  Serial.println("Connecting to AP ...");
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }

  WiFi.softAP(WIFI_GATEWAY_NAME, WIFI_GATEWAY_PASS);

  Serial.print("IP sta: "); Serial.println(WiFi.localIP());
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
  esp_now_add_peer(Broadcast_Address_1, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_add_peer(Broadcast_Address_2, ESP_NOW_ROLE_COMBO, 1, NULL, 0);


}


void Reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}

void WF_CheckConnection(){
  if (WiFi.status() != WL_CONNECTED) {
    Reconnect();
  }
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

    if(node_turn_for_lcd_display == _data_node.node_id) {
        memcpy(&_data_lcd_buffer, &_data_node, sizeof(_data_lcd_buffer));
    }

    // SV_SendData(char *channel, char *json_string)
}

