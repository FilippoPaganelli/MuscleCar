#include <printf.h>
#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7); // CE, CSN

const int pwm = 2 ;  //initializing pin 2 as pwm
const int in_1 = 8 ;
const int in_2 = 9 ;
const int in_3 = 10;
const int in_4 = 4;


//For providing logic to L298 IC to choose the direction of the DC motor

const byte address[6] = "00001";
boolean button_state = 0;

void setup() {
  Serial.begin(9600);

  pinMode(pwm, OUTPUT) ;  //we have to set PWM pin as output
  pinMode(in_1, OUTPUT) ; //Logic pins are also set as output
  pinMode(in_2, OUTPUT) ;
  pinMode(in_3, OUTPUT) ;
  pinMode(in_4, OUTPUT) ;

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    Serial.println("Radio available");

    char text[5] = "";
    radio.read(&button_state, sizeof(button_state));    //Reading the data
    if (button_state == HIGH)
    {
      delay(50);
      radio.read(&text, sizeof(text));
      Serial.println(text);
      Drive();
      Serial.println("Drive");
    }
    else
    {
      Brake();
      Serial.println("Brake");
    }
  }
}

void Drive()
{
  //For Clock wise motion , in_1 = High , in_2 = Low
  digitalWrite(in_1, HIGH) ;
  digitalWrite(in_2, LOW) ;
  digitalWrite(in_3, HIGH);
  digitalWrite(in_4, LOW);
  analogWrite(pwm, 100) ;
}

void Brake() {
  digitalWrite(in_1, HIGH) ;
  digitalWrite(in_2, HIGH) ;
  digitalWrite(in_3, HIGH) ;
  digitalWrite(in_4, HIGH) ;
}
