/* TCC - ARDUINO MAIN
 * Dispositivo da Parada de Ônibus
 * Sensores: DHT11
 * Telas:    E-Ink
 * Antenas:  LoRa 915MHz
 */

// Bibliotecas:
// DHT11 - SENSOR
#include <dht11.h>                   //Sensor Temp e Umid
// LORA - ANTENA
#include <SoftwareSerial.h>          //Para Antena LoRa CDE Byte use ebytesender/receiver
// E-INK DISPLAY - TELA
#include "DEV_Config.h"
#include "EPD_2in13.h"
#include "GUI_Paint.h"  //Não adicionei imagedata porque ocupa 22KB
// ALGORITMO GPS
#include "CORD_Config.h"

// Defines:
#define DHT11_PIN 4                   // DHT11
#define LATITUDE   -3.738678 
#define LONGITUDE -38.569697
#define b1 200
#define b2 750
#define bt1 "Campus do Pici In "
#define bt2 "CampusPici Unifor "

// Inicializando Objetos:
dht11 DHT;                            // DHT11
SoftwareSerial loraserial(2, 3);      // LORA RX, TX

// Variaveis:
int chk;                              // DHT11

unsigned char BlackImage[((EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8 ) : (EPD_WIDTH / 8 + 1)) * 50]; //50 line

int t1 = 3;  // Campus do Pici Interno - E-INK
int t2 = 4;  // Campus do Pici Unifor

char buff[10];  // TESTE LORA ENVIO. DEPOIS APAGO
String enviar = "";

float dist = 0;


void setup() {  // Configuracao:
  //Serial.begin(9600);
  loraserial.begin(9600);            // LORA
  //Serial.print("Main do TCC - Arduino");
  
  DEV_ModuleInit();                  // E-INK
  if (EPD_Init(FULL_UPDATE) != 0) {  // Refresh total.
      Serial.print("e-Paper init failed\r\n");
  }
  EPD_Clear();
  DEV_Delay_ms(500);

  // Testes:
  Serial.println(DHT11LIB_VERSION);
  //Serial.println();
  //Serial.println("Tipo,\tstatus,\tUmidade (%),\tTemperatura (C)");
}

void loop() {  // CODIGO
  sensor();
  envialora();
  recebelora();
  delay(500);
  display();
  //delay(500);
}



// ROTINAS:
void sensor(){  //ROTINA - DHT11
  //Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);  // Ler Dados
  switch (chk){
    case DHTLIB_OK:  
                //Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                //Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                //Serial.print("Time out error,\t"); 
                break;
    default: 
                //Serial.print("Unknown error,\t"); 
                break;
  }
  //Serial.print(DHT.humidity,1); // Mostrar Dados
  //Serial.print(",\t");
  //Serial.println(DHT.temperature,1);
  delay(500);
}

void recebelora(){
  //Serial.println("Esperando dados");
  if(loraserial.available()>0){
    String input = loraserial.readString();
    //Serial.print("Received: ");
    //Serial.println(input);
    float lat = input.toFloat();
    float lon = input.substring(10,19).toFloat();
    dist = cord_dist_e(LATITUDE, LONGITUDE, lat, lon);
    t1 = dist / 0.5;
    lat = input.substring(21,29).toFloat();
    lon = input.substring(31,40).toFloat();
    dist = cord_dist_e(LATITUDE, LONGITUDE, lat, lon);
    t2 = dist;
    
    //Serial.print("Dist: ");
    //Serial.println(dist * 1000);
    //display();
  }
}

void envialora(){  //ROTINA - LORA ENVIAR
  //enviar = LATITUDE;  enviar += ",";
  //enviar += LONGITUDE; enviar += ",";
  enviar = "";
  dtostrf(LATITUDE, 4, 6, buff);  //4 is mininum width, 6 is precision
  enviar += buff;  enviar += ",";
  dtostrf(LONGITUDE, 4, 6, buff);  //4 is mininum width, 6 is precision
  enviar += buff;  enviar += ",";
  dtostrf(DHT.temperature, 2, 1, buff);  //4 is mininum width, 6 is precision
  enviar += buff;  enviar += ",";
  dtostrf(DHT.humidity, 2, 1, buff);  //4 is mininum width, 6 is precision
  enviar += buff;
  String msg = enviar;
  loraserial.print(msg);
  //Serial.print("Enviado: ");
  //Serial.println(msg);
  delay(500);
  //recebelora();
}

void display(){  //ROTINA - E-INK
  Paint_NewImage(BlackImage, EPD_WIDTH, 50, 0, WHITE);
  Paint_SelectImage(BlackImage);
  Paint_Clear(0xff);
  
  Paint_DrawString_EN(0, 0, "Linhas  Bus", &Font16, WHITE, BLACK);
  Paint_DrawLine(0, 16, 122, 16, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);

  EPD_DisplayWindows(BlackImage, 0, 0, 122, 16); // imagem, xstart, ystart, xend, yend    
  
  Paint_Clear(0xff);

  Paint_DrawNum(0, 0, b1, &Font16, BLACK, WHITE);        // Começa a imprimir info dos onibus.
  Paint_DrawString_EN(40, 0, "T:", &Font16, WHITE, BLACK);
  Paint_DrawNum(62, 0, t1, &Font16, WHITE, BLACK);
  Paint_DrawString_EN(85, 0, "m", &Font16, WHITE, BLACK);
  for(int i = 0; i < sizeof(bt1); i++){
    Paint_DrawChar(i*7, 16, bt1[i], &Font12, WHITE, BLACK);
  }
  
  Paint_DrawLine(0, 28, 122, 28, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1); 
  EPD_DisplayWindows(BlackImage, 0, 17, 122, 45); // imagem, xstart, ystart, xend, yend
  // Adicione 28 sempre que colocar outro busão no painel
  Paint_Clear(0xff);
  Paint_DrawNum(0, 0, b2, &Font16, BLACK, WHITE);
  Paint_DrawString_EN(40, 0, "T:", &Font16, WHITE, BLACK);
  Paint_DrawNum(62, 0, t2, &Font16, WHITE, BLACK);
  Paint_DrawString_EN(85, 0, "m", &Font16, WHITE, BLACK);
  for(int i = 0; i < sizeof(bt2); i++){
    Paint_DrawChar(i*7, 16, bt2[i], &Font12, WHITE, BLACK);
  }
  Paint_DrawLine(0, 28, 122, 28, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
  EPD_DisplayWindows(BlackImage, 0, 45, 122, 73);

  Paint_Clear(0xff);
  // PARTE SENSOR DHT11 
  Paint_DrawString_EN(0, 0, "Temp:", &Font16, WHITE, BLACK);
  Paint_DrawNum(56, 0, DHT.temperature, &Font16, WHITE, BLACK);
  Paint_DrawString_EN(0, 17, "Umid:", &Font16, WHITE, BLACK);
  Paint_DrawNum(56, 17, DHT.humidity, &Font16, WHITE, BLACK);
  EPD_DisplayWindows(BlackImage, 0, 102, 122, 135); 
  // PARTE SENSOR DHT11
  
  //Paint_Clear(0xff);
  EPD_TurnOnDisplay();
  DEV_Delay_ms(500);//Analog clock 1s
}
