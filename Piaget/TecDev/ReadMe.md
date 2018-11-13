// se pueden definir los pines de entrada/salida de distintas maneras:
#define LED_R 2
#define LED_B 3
#define LED_Y 4

#define BUT_R 10
#define BUT_B 9
#define BUT_Y 8
#define RESET 11

void setup() {
  // put your setup code here, to run once:
  // en el codigo de setup se pone toda la inicializacion/configuracion del sistema
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_Y, OUTPUT);

  pinMode(BUT_R, INPUT);
  pinMode(BUT_B, INPUT);
  pinMode(BUT_Y, INPUT);
  pinMode(RESET, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:

  // leyendo un boton y si devuelve una lectura en HIGH, enciende su foco respectivo
 if(digitalRead(BUT_R)){
  digitalWrite(LED_R, HIGH);
  delay(300);
 }
 if(digitalRead(BUT_B)){
  digitalWrite(LED_B, HIGH);
  delay(300);
 }
 if(digitalRead(BUT_Y)){
  digitalWrite(LED_Y, HIGH);
  delay(300);
 }

 // funcion de reset para apagar todos los leds
 if(digitalRead(RESET)){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_Y, LOW);
  delay(300);
 }  
}
