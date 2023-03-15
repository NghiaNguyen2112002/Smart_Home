#include "MQTT_server.h"


void on_message(const char* topic, byte* payload, unsigned int length);

void SV_Init(void){
  client.setServer(SERVER_DOMAIN, 1883);
  client.setCallback(on_message);
}

void SV_CheckConnection(void){
    if ( !client.connected() ) {
      Serial.print("Connecting to Server ...");
      if ( client.connect(CLIENT_ID, SERVER_USER, SERVER_PASS) ) {
        Serial.println( "[DONE]" );

        // Subscribing channel
        client.subscribe("channels/2064615");

        // client.subscribe(CHANNEL_STORE_DATA);
      } 
      else {
        Serial.print( "[FAILED] [ rc = " );
        Serial.print( client.state() );
        Serial.println( " : retrying in 5 seconds]" );
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
}

void SV_SendData(char* channel, char* json_string){
  Serial.println(json_string);

  client.publish(channel, json_string);
}

// The callback for when a PUBLISH message is received from the server.
void on_message(const char* topic, byte* payload, unsigned int length) {
  Serial.println("On message");
  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(json);

}
