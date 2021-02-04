/* TCC - GATEWAY MAIN
 * Gateway que faz a comunicação entre o display e a internet - ESP8266
 * Antenas:  LoRa 915MHz
 */ // Pinagem do ESP:
#define D0  16  // Red LED
#define D1  5
#define D2  4
#define D3  0
#define D4  2   // Blue LED - or BUILTIN_LED
#define D5  14
#define D6  12
#define D7  13
#define D8  15
#define D9  3
#define D10 1

// Bibliotecas:
#include <SoftwareSerial.h>       // LORA - ANTENA
#include <ESP8266WiFi.h>          // MQTT
#include <PubSubClient.h>
#include <SoftwareSerial.h>

// Defines: Nenhum por hora

// Inicializando Objetos:
SoftwareSerial loraserial(D1, D2);            // LORA RX, TX
WiFiClient espClient;
PubSubClient client(espClient);               // MQTT

// Variaveis:
// SSID: nome, PASSWORD: senha da tua rede, MQTT_SERVER: link do servidor MQTT
const char* ssid = "Bestweb-ROCHA-33425506";  // MQTT
const char* password = "acesso2020rocha";
const char* mqtt_server = "broker.hivemq.com";

long lastMsg = 0;                             // MQTT
char msg_mqtt[50];
String input;                                 // RX by LORA, TX by MQTT
int i = 0;                                    // LORA
String msg = "";
String linha020;                              // MQTT e LoRa usam estas variaveis
String linha075;

void setup() {  // Configura apenas 1 vez.
  Serial.begin(9600);                   // MONITOR SERIAL - DEBUG
  pinMode(D0, OUTPUT);                  // WIFI/MQTT - Pino BUILTIN_LED como saída
  pinMode(D4, OUTPUT);                  // LoRa - Pino LED
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);  // MQTT
  client.setCallback(callback);
  
  loraserial.begin(9600);               // LORA
  Serial.println("Gateway LoRa - ESP");
  
  digitalWrite(D0, HIGH);               //LED INICIA DESLIGADO
  digitalWrite(D4, HIGH);               //NODEMCU Leds Invertidos
}

void loop() { // CODIGO
  if (!client.connected()) {  // MQTT
    reconnect();
  }
  client.loop();
  recebelora();
}



// ROTINAS:
void recebelora(){                                           //ROTINA - LORA RX
  if(loraserial.available()>0){
    digitalWrite(D4, LOW);
    input = loraserial.readString();
    Serial.print("RX LoRa: ");
    Serial.println(input);
    input.toCharArray(msg_mqtt, 40);
    client.publish("sistema/pontobus", msg_mqtt);  // "outTopic", "message"

    delay(100);
    envialora();
  }
  digitalWrite(D4,HIGH);
}

void envialora(){                                            //ROTINA - LORA TX
  digitalWrite(D0, LOW);
  msg  = linha020;
  msg += linha075;
  
  loraserial.print(msg);
  Serial.print("Sent: ");
  Serial.println(msg + " - " + (String)i);
  delay(500);
  digitalWrite(D0, HIGH);
  i++;
}
void setup_wifi() {                                          //ROTINA - WIFI
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");          // Connect to a WiFi network
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  // If not connected, wait
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {  //ROTINA - MQTT
  digitalWrite(D0, LOW);
  Serial.print("MQTT RX [");
  Serial.print(topic);
  Serial.print("] : ");

  if(strcmp(topic, "sistema/linha/020") == 0){
    linha020 = "";
    for (int i = 0; i < length; i++) {
      linha020 += (char)payload[i];
      Serial.print((char)payload[i]);
    }
  }
  if(strcmp(topic, "sistema/linha/075") == 0){
    linha075 = "";
    for (int i = 0; i < length; i++) {
      linha075 += (char)payload[i];
      Serial.print((char)payload[i]);
    }
  }
  Serial.println();
  delay(50);
  digitalWrite(D0, HIGH);  // Turn the LED off by making the voltage HIGH
}

void reconnect() {                                           //ROTINA - MQTT
  while (!client.connected()) {                              // Loop until reconnect
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";                      // Create a random client ID
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {                  // Attempt to connect
      Serial.println("connected");
      client.publish("sistema/pontobus", "Teste com LoRa");  // Publish Test - OutTopic, Message
      client.subscribe("sistema/linha/020");                 // Resubscribe - InTopic, Message
      client.subscribe("sistema/linha/075");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);                                           // Wait 5 seconds before retrying
    }
  }
}
