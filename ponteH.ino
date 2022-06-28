/*
  Rotina para controlar um motor DC com ponte H.
  A rotina utiliza um potenciômetro para setar a velocidade do motor e um botão para mudar o sentido de rotação
  Quando o botão é pressionado a rotina registra a troca de sentido
  Quando liberado o botão, o motor desalecera gradualmente e acelera até a velocidade ditada pelo potenciômetro
*/

const int PINO_ENA = 6;

const int PINO_IN1 = 4; 
const int PINO_IN2 = 3;

const int BOTAO = 7;
const int POT = A0;

bool horario = true;
int velocidade = 0;

const int TEMPO_RAMPA = 30; 

void setup() {

  pinMode(PINO_ENA, OUTPUT); 
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  
  pinMode(BOTAO,INPUT_PULLUP);
  pinMode(POT,INPUT);

  digitalWrite(PINO_IN1, LOW); 
  digitalWrite(PINO_IN2, LOW);
  digitalWrite(PINO_ENA, LOW);

  Serial.begin(9600);
}

void loop() {

  bool valorBotao = digitalRead(BOTAO);
  bool mudou = false;

  while(!valorBotao) {
    Serial.print("Botao pressionado");
    Serial.println(valorBotao);
    delay(200);  
    mudou = true;
    valorBotao = digitalRead(BOTAO);
  }
  if(mudou) {
    horario = !horario;

      for (int i = velocidade; i >= 0; i=i-10){ 
        analogWrite(PINO_ENA, i); 
        delay(TEMPO_RAMPA); //intervalo para incrementar a variavel i
      }

      for (int i = 0; i < velocidade; i=i+10){ 
        analogWrite(PINO_ENA, i);
        delay(TEMPO_RAMPA); //intervalo para incrementar a variavel i
      }
  }
  
  digitalWrite(PINO_IN1, !horario); 
  digitalWrite(PINO_IN2, horario);

  velocidade = map(analogRead(POT),0,1023,0,255);

  analogWrite(PINO_ENA, velocidade);

  delay(200);

  Serial.println(horario);
}
