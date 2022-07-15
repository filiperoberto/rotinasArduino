// Código BlueBox 20 - Porta Escova de Dente com Despertador
// Autor: FilipeFlop
 
// Bibliotecas utilizadas no código
#include <TM1637Display.h>      // https://github.com/avishorp/TM1637
#include <NTPClient.h>          // https://github.com/arduino-libraries/NTPClient
#include <Adafruit_NeoPixel.h>  // https://github.com/adafruit/Adafruit_NeoPixel
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
// Informações da rede WiFi
const char *ssid     = "ssid";  // Insira o nome da rede WiFi dentro das aspas
const char *password = "senha"; // Insira a senha da rede WiFi dentro das aspas
 
// Define em quais pinos os componentes estão ligados no ESP8266
#define CLK_DISPLAY   D1
#define DIO_DISPLAY   D2
 
#define CLK_ENCODER   D5
#define DT_ENCODER    D6
#define SW_ENCODER    D7
 
#define LED_GROVE     D0
#define BOTAO_GROVE   D3
 
#define BUZZER_GROVE  D8
 
#define SENSOR_IR     A0
 
#define RGB_GROVE     D4
 
// Define o horário para o GTM-3
const long utcOffsetInSeconds = -3*3600;
 
// Define as variáveis utilizados no código
int despertadorHora = 0;                // Armazena a hora definida para o despertador
int contadorHora = 0;                   // Contador de posições da hora do despertador
int despertadorMinuto = 0;              // Armazena o minuto definido para o despertador
int contadorMinuto = 0;                 // Contador de posições do minuto do despertador
int ultPosicao;                         // Registra a última posição do encoder
int leituraCLK;                         // Armazena a leitura do pino CLK
int mode = 0;                           //
boolean escolhendoHoras = false;        // Flag utilizada para selecionar a hora do despertador
boolean escolhendoMinutos = false;      // Flag utilizada para selecionar o minuto do despertador
boolean despertadorAtivo = false;       // Flag utilizada para verificar se o despertador está ativo

boolean temObjeto = false;
uint32_t corAtual;
 
// Melodia do tema Super Mario
int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
  
// Duração de cada nota
int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};
 
// Definições iniciais para o módulo TM1637 (Display 7 segmentos 4 dígitos)
TM1637Display display(CLK_DISPLAY, DIO_DISPLAY);
 
// Define o cliente NTP para obter o horário atual
WiFiUDP ntpUDP;
 
// Definições iniciais para obter o horário local. A atualização é feita a cada 10 minutos
NTPClient timeClient(ntpUDP, "85.21.78.23", utcOffsetInSeconds, 600000);
 
// Definições iniciais para a linha de LED RGB Grove
#define NUMERO_LEDS   10
Adafruit_NeoPixel strip(NUMERO_LEDS, RGB_GROVE, NEO_GRB + NEO_KHZ800);
 
//----------SETUP----------
void setup() { 
 
  // Define a velocidade da comunicação serial 
  Serial.begin(9600);
  delay(100);
 
  // Define os pinos como entradas ou saídas
  pinMode(CLK_ENCODER,INPUT);
  pinMode(DT_ENCODER,INPUT);
  pinMode(SW_ENCODER,INPUT_PULLUP);
  pinMode(BOTAO_GROVE, INPUT_PULLUP);
  pinMode(LED_GROVE, OUTPUT);
  pinMode(SENSOR_IR, INPUT);
 
  // Define o brilho do display 7 segmentos (0xff é o brilho máximo)
  display.setBrightness(0x1a);
   
  // Armazena a leitura do pino CLK_ENCODER na variável ultPosicao
  ultPosicao = digitalRead(CLK_ENCODER);
 
  // Inicia a linha de LED RGB
  strip.begin();
  strip.show();
  corAtual = strip.Color(0, 0, 0);
  colorWipe(corAtual, 50); // Apagado
  
   
  // Inicia a conexão WiFi
  WiFi.begin(ssid, password);
 
  // Verifica se a conexão com a rede WiFi foi bem sucedida
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
 
  // Faz o LED piscar 5 vezes
  for (int i=0; i<5; i++){
    digitalWrite(LED_GROVE, HIGH);
    delay(500);
    digitalWrite(LED_GROVE, LOW);
    delay(500);
  }
 
  // Inicia a comunicação como cliente NTP
  timeClient.begin();
}
 
//----------LOOP----------
void loop() {
 
  // Obtém o horário atual
  timeClient.update();
 
  // Mostra no display 7 segmentos o horário atual
  display.showNumberDecEx(timeClient.getHours(), 0b11100000, true, 2, 0);
  display.showNumberDecEx(timeClient.getMinutes(), 0b11100000, true, 2, 2);
 
  // Verifica se o botão grove foi pressionado para trocar a cor da linha de LED RGB
  if (digitalRead(BOTAO_GROVE) == LOW){
    mudaCorRGB();
    delay(200);
  }
    
  // Verifica se a o horário atual é igual ao horário do despertador. Se for, chama a função despertadorInicia
  if (timeClient.getHours() == despertadorHora && timeClient.getMinutes() == despertadorMinuto && despertadorAtivo == true){
    despertadorInicia();
  }

  if (analogRead(SENSOR_IR) < 700 && !temObjeto) {
    colorWipe(strip.Color(random(256), random(256), 256), 50);
    colorWipe(corAtual,50);
  }
  temObjeto = analogRead(SENSOR_IR) < 700;
 
  // Verifica se o botão do encoder foi pressionado
  if(digitalRead(SW_ENCODER) == LOW){
    delay(1000);
     
    // Se o botão do encoder é pressionado por 1 segundo, mostra no display 7 segmentos o horário definido para o despertador
    display.showNumberDecEx(despertadorHora, 0b11100000, true, 2, 0);
    display.showNumberDecEx(despertadorMinuto, 0b11100000, true, 2, 2);
    delay(2000);
 
    // Se o botão do encoder é pressionado por mais 2 segundos, o programa para ajuste da hora do despertador é iniciado
    if(digitalRead(SW_ENCODER) == LOW){
      delay(1000);   
      selecaoHora();
      delay(1000);
    }
  }  
}
 
//----------FUNÇÃO PARA AJUSTAR HORA DO DESPERTADOR----------
void selecaoHora(){
 
  // Faz o LED piscar 5 vezes
  for (int i=0; i<5; i++){
    digitalWrite(LED_GROVE, HIGH);
    delay(500);
    digitalWrite(LED_GROVE, LOW);
    delay(500);
  }
 
  // Mantem o LED acesso durante o ajuste
  digitalWrite(LED_GROVE, HIGH);
   
  // Flag é definida para TRUE, mostrando que o ajuste de hora está sendo feito
  escolhendoHoras = true;
 
  // Altera o valor das horas conforme o encoder é ajustado
  while(escolhendoHoras){
    leituraCLK = digitalRead(CLK_ENCODER);
    if(leituraCLK != ultPosicao){
      if(digitalRead(DT_ENCODER) != leituraCLK){
        contadorHora++;
        if (contadorHora == 24){
          contadorHora = 0;
        }
      }
      else{
        contadorHora--;
        if (contadorHora == -1){
          contadorHora = 23;
        }
      }  
      // Mostra no display 7 segmentos a hora do despertador sendo ajustada
      display.showNumberDecEx(contadorHora, 0b11100000, true, 2, 0);
      delay(100);
    }
    ultPosicao = leituraCLK;
     
    // Se o botão do encoder é pressionado por 1 segundo, o programa para ajuste da hora do despertador é finalizado
    if(digitalRead(SW_ENCODER) == LOW){
      despertadorHora = contadorHora;
      escolhendoHoras = false; // Flag é definida para FALSE, mostrando que o ajuste de hora foi realizado
      delay(1000);
      digitalWrite(LED_GROVE, LOW); // Apaga o LED após o ajuste
      selecaoMinuto(); // Chama a função para ajuste do minuto do despertador
    }
    
  }
}
 
//----------FUNÇÃO PARA AJUSTAR MINUTO DO DESPERTADOR----------
void selecaoMinuto(){
 
  // Faz o LED piscar 1 vez
  digitalWrite(LED_GROVE, HIGH);
  delay(500);
  digitalWrite(LED_GROVE, LOW);
  delay(500);
 
  // Mantem o LED acesso durante o ajuste
  digitalWrite(LED_GROVE, HIGH);
   
  // Flag é definida para TRUE, mostrando que o ajuste de minuto está sendo feito
  escolhendoMinutos = true;
   
  // Altera o valor dos minutos conforme o encoder é ajustado
  while(escolhendoMinutos){
    leituraCLK = digitalRead(CLK_ENCODER);
    if(leituraCLK != ultPosicao){ 
      if(digitalRead(DT_ENCODER) != leituraCLK){
        contadorMinuto++;
        if (contadorMinuto == 60){
          contadorMinuto = 0;
        }
      }
      else{
        contadorMinuto--;
        if (contadorMinuto == -1){
          contadorMinuto = 59;
        }
      }  
      // Mostra no display 7 segmentos a hora do despertador sendo ajustada
      display.showNumberDecEx(contadorMinuto, 0b11100000, true, 2, 2);
      delay(100);
    }
    ultPosicao = leituraCLK;
 
    // Se o botão do encoder é pressionado por 1 segundo, o programa para ajuste do minuto do despertador é finalizado
    if(digitalRead(SW_ENCODER) == LOW){
      despertadorMinuto = contadorMinuto;
      escolhendoMinutos = false; // Flag é definida para FALSE, mostrando que o ajuste de minuto foi realizado
      despertadorAtivo = true;
      delay(1000); 
    }
  }
  // Faz o LED piscar 5 vezes
  for (int i=0; i<5; i++){
    digitalWrite(LED_GROVE, HIGH);
    delay(500);
    digitalWrite(LED_GROVE, LOW);
    delay(500);
  }
  delay(2000); // Aguarda 2 segundos para voltar a mostar a horário atual
}

void beep() {
  tone(BUZZER_GROVE, 660,100);
  delay(100);
  noTone(BUZZER_GROVE);
}
 
//----------FUNÇÃO PARA LIGAR O DESPERTADOR----------
void despertadorInicia(){
 
  while(despertadorAtivo == true){
 
    // Obtém o horário atual
    timeClient.update();
    display.showNumberDecEx(timeClient.getHours(), 0b11100000, true, 2, 0);
    display.showNumberDecEx(timeClient.getMinutes(), 0b11100000, true, 2, 2);
 
    for (int nota = 0; nota < 156; nota++) {
 
      // Verifica se o despetatador não foi desativado
      if(analogRead(SENSOR_IR) > 700){
      //if(digitalRead(BOTAO_GROVE) == LOW){
        delay(1000);
        despertadorAtivo = false;
        loop();    
      }
       
      if (despertadorAtivo == true){
        int duracaodanota = duracaodasnotas[nota];
        tone(BUZZER_GROVE, melodia[nota],duracaodanota);
     
        // Pausa depois de cada uma das notas
        int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
        delay(pausadepoisdasnotas[nota]);
      }
      else{
        noTone(BUZZER_GROVE); 
      }
    }
  }
}
 
//----------FUNÇÃO PARA TROCAR A COR DA LINHA DE LED RGB----------
void mudaCorRGB(){
 
  // Se o botão grove é pressionado, a cor da linha de LED RGB é alterada
  if(digitalRead(BOTAO_GROVE) == LOW) {
    beep();
    if(++mode > 7) mode = 0;
    switch(mode){
      case 0:
        corAtual = strip.Color(255, 0, 0); // Vermelho
        break;
      case 1:
        corAtual = strip.Color(255, 69, 0); // Laranja
        break;
      case 2:
        corAtual = strip.Color(255, 255, 0); // Amarelo
        break;
      case 3:
        corAtual = strip.Color(0, 255, 0); // Verde
        break;
      case 4:
        corAtual = strip.Color(0, 255, 255); // Ciano 
        break;
      case 5:
        corAtual = strip.Color(0, 0, 255); // Azul
        break;
      case 6:
        corAtual = strip.Color(102, 0, 51); // Roxo
        break;
      case 7:
        corAtual = strip.Color(0, 0, 0); // Apagado
        break;
    }
    colorWipe(corAtual, 50);
  }
}
 
//----------FUNÇÃO GERAR AS CORES NA LINHA DE LED RGB----------
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
