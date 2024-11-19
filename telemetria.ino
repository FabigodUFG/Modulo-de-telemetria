#include <SoftwareSerial.h>          // Include SoftwareSerial library for communication
 
SoftwareSerial XBee(10, 11);         // Define SoftwareSerial pins: RX = 10, TX = 11
int pushbutton = 2;                  // declara o push button na porta 2
bool marcha = 0;
 
void setup() {
  Serial.begin(9600);                // Start communication with the PC for debugging
  XBee.begin(9600);                  // Start communication with the XBee module
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada
}
 
void loop() {
  // Lê o valor no pino analógico A0 e escala para a faixa de temperatura (0 a 200)
  int temperatura_analog = analogRead(A0);
  float temperatura = temperatura_analog * (200.0 / 1023.0);
  
  // Lê o valor no pino analógico A2 e escala para a faixa de velocidade (0 a 160)
  int velocidade_analog = analogRead(A2);
  float velocidade = velocidade_analog * (160.0 / 1023.0);

  // Lê o valor no pino analógico A4 e escala para a faixa de combustível (0 a 3000)
  int combustivel_analog = analogRead(A4);
  float combustivel = combustivel_analog * (3000.0 / 1023.0);

  marcha = (digitalRead(pushbutton) == HIGH); // Atualiza marcha para 1 se o botão estiver pressionado, 0 caso contrário  
  
// Envia os dados pelo XBee, separados por '#'
  XBee.print('<');                      // Marcador de início de transmissão
  XBee.print(velocidade);
  XBee.print('#');
  XBee.print(combustivel);
  XBee.print('#');
  XBee.print(temperatura);
  XBee.print('#');
  XBee.print(marcha);
  XBee.println('>');                    // Marcador de fim de transmissão
  
  // Exibe os dados enviados no monitor serial para depuração
  Serial.print("Sent voltage: ");
  Serial.println(velocidade);
  Serial.print("Sent random values: ");
  Serial.print(combustivel);
  Serial.print(", ");
  Serial.print(temperatura);
  Serial.print(", ");
  Serial.println(marcha);
  
  delay(500);                          // Intervalo entre envios para evitar sobrecarga
}
