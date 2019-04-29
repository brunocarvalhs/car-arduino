/**
* 
*   Esamc - Engenharia da computação 6 semestre 
*   Projeto Robotico Educacional - Trabalho de Sistema Embarcados
*  
*  
*   Integrantes:
*   Bruno Silva Carvalho
*   Bruno Da Silva Lara
*   Sergio Tadeu
*   Kaique 
*
*
*   Objetivo do Projeto:
* 
*   Com intuito de estimular e interesar dos jovens na área de robotica e computacional 
*   o robo desenvolvido tem como funcionalidade, controle de entradas e saidas digitais 
*   e analogicas. Com (3) sensores ultrasonicos para verificar obstaculos em seu caminho, 
*   e analise logica possiveis decições de caminhos a serem redirecionadas
*   
*/

//Biblioteca
#include<Ultrasonic.h>// Biblioteca do sensor Ultrasonico
#include <Wire.h> // Biblioteca do Módulo I2C
#include <LiquidCrystal_I2C.h>// Bilioteca do LCD

/*############################# Classes #########################################################*/

/* ------------------------------ Classe dos sensor ultrasonic ----------------------------------*/
class Ultrasonico{
  
  public:
  
    /*___________________________________ Atributos ______________________________________________*/
    
    long Emitir; // Emitir(trig)
    long Escutar; // Escutar (echo) 
    
    /*___________________________________ Metodos ________________________________________________*/
    
    // metodo de medir em centimetros
    long DistanciaCM(){
      Ultrasonic Sonar(Emitir, Escutar);//Acionando o sensor do pino emitir e escutar
      long dados = Sonar.timing();// Coleta dos dados do sensor
      return (Sonar.convert(dados, Ultrasonic::CM));
    }
    // metodo de medir em polegadas
    long DistanciaPOL(){
      Ultrasonic Sonar(Emitir, Escutar);// Acionando o sensor com os pinos emitir e escutar
      long dados = Sonar.timing();// Coleta dos dados do sensor
      return (Sonar.convert(dados, Ultrasonic::IN));
    }
};
/* ------------------------------ Classe dos motor ----------------------------------------------*/
class Motor{
  public:
   int Pino_motor;
   /*___________________________________ Atributos ______________________________________________*/
  void Ligar(){
    digitalWrite(Pino_motor, HIGH);
  }
  void Desligar(){
    digitalWrite(Pino_motor, LOW);
  }
};

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
byte Olhando_esquerda[8] = {
  B01110,
  B10011,
  B10111,
  B10111,
  B10111,
  B10111,
  B10011,
  B01110
};
byte Olhando_direita[8] = {
  B01110,
  B11001,
  B11101,
  B11101,
  B11101,
  B11101,
  B11001,
  B01110
};
byte Boca[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000
};

byte Acordado[8] = {
  B01110,
  B11001,
  B11101,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110
};


// Variaveis Globais

float DISTANCIA = 20.00;

/*################################# Código principal do arduino ###################################*/
void setup() {
  Serial.begin(9600);// Ativando o Leitor em serial
  pinMode(7, OUTPUT);// Saida de energia 


  
  lcd.begin (16,2);
  
  lcd.createChar(0, Acordado);// Definindo numero do byte
  lcd.createChar (1, Boca);
  lcd.createChar(2, Olhando_esquerda);
  lcd.createChar(3, Olhando_direita);
  lcd.clear();  //Limpa o LCD

  
  lcd.setCursor(5, 1); //Imprime parte da boca na posição 5 linha 1 do LCD
  lcd.write((byte)1);  //Objeto boca
  lcd.setCursor(6, 1); //Imprime parte da boca na posição 6 linha 1 do LCD
  lcd.write((byte)1);  //Objeto boca
  lcd.setCursor(7, 1); //Imprime parte da boca na posição 7 linha 1 do LCD
  lcd.write((byte)1);   //Objeto boca
  lcd.setCursor(8, 1); //Imprime parte da boca na posição 8 linha 1 do LCD
  lcd.write((byte)1);   //Objeto boca
  lcd.setCursor(9, 1);  //Imprime parte da boca na posição 9 linha 1 do LCD
  lcd.write((byte)1);   //Objeto boca
  lcd.setCursor(10, 1);  //Imprime parte da boca na posição 10 linha 1 do LCD
  lcd.write((byte)1);   //Objeto boca
}

void loop() {
  Ultrasonico sensor1; // Criando uma instancia
  Motor Led;
  Led.Pino_motor = 7;
  sensor1.Emitir = 4; // Definindo pino que liga na entrada TRIG
  sensor1.Escutar = 5; // Definindo pino que liga na entrada ECHO
  Serial.print("Distancia em CM: ");// Texto no serial
  Serial.print(sensor1.DistanciaCM());// Mostrando os dados em centimetros no serial
  Serial.print("  Distancia em POL: ");// Texto no serial
  Serial.println(sensor1.DistanciaPOL());//Mostrando dados em polegadas no serial
  if(sensor1.DistanciaCM()<DISTANCIA){
    Led.Desligar();
    delay(500);
    lcd.setCursor(3, 0); //Imprime o olho na posição 12 linha 0 do LCD
    lcd.write((byte)2);   //Objeto olho
    lcd.setCursor(12, 0);  //Imprime o olho na posição 3 linha 0 do LCD
    lcd.write((byte)2);   //Objeto olho
    delay(1000);
    lcd.setCursor(3, 0); //Imprime o olho na posição 12 linha 0 do LCD
    lcd.write((byte)3);   //Objeto olho
    lcd.setCursor(12, 0);  //Imprime o olho na posição 3 linha 0 do LCD
    lcd.write((byte)3);   //Objeto olho
  }
  else{
   Led.Ligar();
   lcd.setCursor(3, 0);  //Imprime o olho na posição 3 linha 0 do LCD
   lcd.write((byte)0);   //Objeto olho
   lcd.setCursor(12, 0); //Imprime o olho na posição 12 linha 0 do LCD
   lcd.write((byte)0);   //Objeto olho
  }
}
