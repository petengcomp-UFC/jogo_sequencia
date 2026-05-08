// C++ code
#include <LiquidCrystal.h>
#define LR 4  //Red
#define LG 3 //Green
#define LB 2 //Blue
int ledPins[]={LR, LG, LB};
int numLeds=3;

// Sensor Ultrassônico 1 led vermelho
#define TRIG_R 9
#define ECHO_R 8
// Sensor Ultrassônico 2 led azul
#define TRIG_B 7  
#define ECHO_B 5
#define PINO_BOTAO 10 // Pino para o botão do led verde

// --- CONFIGURAÇÕES DO SENSOR DE SOM ---
#define PINO_SENSOR_SOM A0
#define LIMITE_SOM     250 // limite de amplitude
#define TEMPO_RESETE   500 
#define INTERVALO_MEDICAO   20 // tempo entre um som e outro

// --- FIM CONFIGURAÇÕES DE SOM ---

#define DISTANCIA 25 // Distância máxima em cm para acionar (proximidade)

#define TAMANHO_MAX_SEQUENCIA 10  
LiquidCrystal lcd_1(12, 13, A3, 11, A1, A2);
int sequencia[TAMANHO_MAX_SEQUENCIA];

int rodadaAtual = 0;

unsigned long tempoUltimoSom = 0;

int tempoAceso = 450; // Tempo que o led fica aceso
int tempoPausa = 350; // Tempo entre os leds da sequência


void gameOver() {
  Serial.println("\n FIM DE JOGO: SEQUENCIA INCORRETA!");
  Serial.println("Reinicie a simulação para tentar novamente.");
  lcd_1.clear();
  efeitoDigitando("  FIM DE JOGO! ", 0, 150);
  efeitoDigitando("Tente novamente!", 1, 100);
  
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < numLeds; i++) digitalWrite(ledPins[i], HIGH);
    delay(2000);

    for (int i = 0; i < numLeds; i++) digitalWrite(ledPins[i], LOW);
    delay(2000);
  }

  while(true){
    delay(1000);
  }
}

long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH); 
  long distanciaCm = duracao * 0.0343 / 2;
  
  return distanciaCm;
}
bool somDetectado() {
    if (millis() - tempoUltimoSom < TEMPO_RESETE) {
      return false;
    }
    
    unsigned long inicioIntervalo = millis();
    int sinalMaximo = 0;
    int sinalMinimo = 1024;

    // Fica lendo o sensor durante o INTERVALO_MEDICAO
    while (millis() - inicioIntervalo < INTERVALO_MEDICAO) {
        int leitura = analogRead(PINO_SENSOR_SOM);
        
        if (leitura < 1024) {
            if (leitura > sinalMaximo) {
                sinalMaximo = leitura; // Atualiza o pico mais alto
            }
            if (leitura < sinalMinimo) {
                sinalMinimo = leitura; // Atualiza o pico mais baixo
            }
        }
    }

    // calcula a amplitude da variação do som
    int amplitudePicoAPico = sinalMaximo - sinalMinimo;

    // se a variação for maior que o limite, é uma palma
    if (amplitudePicoAPico > LIMITE_SOM) {
        Serial.print(" (Palma detectada! Amplitude: ");
        Serial.print(amplitudePicoAPico);
        Serial.println(")");
        
        tempoUltimoSom = millis();
        return true;
    }
    
    return false;
}

void setup()
{
  lcd_1.begin(16, 2);
  lcd_1.print("Iniciando...");
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);
  }
  delay(300);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  
  pinMode(TRIG_R, OUTPUT);
  pinMode(ECHO_R, INPUT);
  
  pinMode(TRIG_B, OUTPUT);
  pinMode(ECHO_B, INPUT);
  
  pinMode(PINO_BOTAO, INPUT_PULLUP); 

  Serial.begin(9600); 
  
  randomSeed(analogRead(A5)); 
  
  Serial.println("Iniciando jogo de sequência");
  delay(1000); 
}

void efeitoDigitando(String texto, int linha, int delayMs){
  lcd_1.setCursor(0, linha);
  for(int i = 0; i < texto.length(); i++){
    lcd_1.print(texto[i]);
    delay(delayMs);
  }}

int inputJogador(int pinoCorreto){
  Serial.print("Sua vez! ");
  lcd_1.setCursor(0,0);
  lcd_1.print("    Sua vez!    ");

  while(true){
    long distR = medirDistancia(TRIG_R, ECHO_R); 
    long distB = medirDistancia(TRIG_B, ECHO_B);
    
    // Testa o Vermelho (Ultrassônico)
    if(distR <= DISTANCIA && distR > 1){ 
      Serial.print("\n -> Vermelho");
      digitalWrite(LR,HIGH);
      delay(200);
      digitalWrite(LR,LOW);
      while(medirDistancia(TRIG_R, ECHO_R) < DISTANCIA) { delay(100); } 
      return LR;
    }
    
    // Testa o Azul (Ultrassônico)
    if(distB <= DISTANCIA && distB > 1){
      Serial.print("\n -> Azul");
      digitalWrite(LB,HIGH);
      delay(200);
      digitalWrite(LB,LOW);
      while(medirDistancia(TRIG_B, ECHO_B) < DISTANCIA) { delay(100); } 
      return LB;
    }
    
    // Testa o Verde (Botão ou Palma/Som)
    bool ouvirSom = false;
    if (pinoCorreto == LG) {
        ouvirSom = somDetectado();
    }
    
    // Testa o Verde (Botão ou o Som)
    if(digitalRead(PINO_BOTAO) == LOW || ouvirSom){
      Serial.print("\n -> Verde (Botão ou Som)");
      digitalWrite(LG, HIGH);
      delay(200);
      digitalWrite(LG,LOW);
      
      return LG; 
    }


    delay(100);
  }
}

void loop()
{
  int indiceAleatorio = random(numLeds);  
  
  int pinoSorteado = ledPins[indiceAleatorio];

  sequencia[rodadaAtual] = pinoSorteado;

  //só pra gente acompanhar:
  Serial.print("Rodada ");
  Serial.print(rodadaAtual + 1);
  Serial.print(": Novo LED adicionado =  ");
  if(pinoSorteado == 2) Serial.println(" Azul");
  else if(pinoSorteado == 3) Serial.println(" Verde");
  else if(pinoSorteado == 4) Serial.println(" Vermelho");
  
  Serial.println("Mostrando sequencia...");
  
  lcd_1.setCursor(0,0);
  lcd_1.print("Rodada ");
  lcd_1.print(rodadaAtual + 1);
  lcd_1.print("     ");
  delay(1000);
  lcd_1.setCursor(0,0);
  lcd_1.print("   Mostrando      ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("   sequencia");
  
  for (int i = 0; i <= rodadaAtual; i++) {
    int pino = sequencia[i];
    digitalWrite(pino, HIGH); // acende o led
    delay(tempoAceso);
    
    digitalWrite(pino, LOW); // apaga o led
    delay(tempoPausa); // pausa entre um led e outro
  }
    lcd_1.clear();
    efeitoDigitando("    Rodada " + String(rodadaAtual + 1), 1, 150);
  
  for(int i=0; i<=rodadaAtual;i++){
    int pinoCorreto = sequencia[i];
    int pinoEscolhido = inputJogador(pinoCorreto);
    
    if(pinoEscolhido != pinoCorreto){
      Serial.print("\n Ops... pino errado! ");
      lcd_1.setCursor(0,0);
      lcd_1.print("Ops pino errado!");
      lcd_1.setCursor(0,1);
      lcd_1.print("     T-T     ");
      delay(2000);
      gameOver();}
  }
  Serial.print("\n Sequencia correta");
  lcd_1.clear();
  lcd_1.setCursor(0,0);
  lcd_1.print("Sequencia");
  lcd_1.setCursor(0,1);
  lcd_1.print("correta!  :)");
  delay(3000);
  lcd_1.clear();
  rodadaAtual++;
  if (rodadaAtual >= TAMANHO_MAX_SEQUENCIA) {
    Serial.println("Parabéns, você concluiu o desafio!");
    delay(2000); 
    while (true) {
      delay(1000); 
    }
  }

}
