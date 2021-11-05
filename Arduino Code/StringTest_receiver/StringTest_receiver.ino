#include <printf.h>
#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7); // CE, CSN

const int ENpwm1 = 3 ;  //initializing pin 2 as pwm
const int ENpwm2 = 5 ;
const int in_1 = 8 ;
const int in_2 = 9 ;
const int in_3 = 10;
const int in_4 = 4;


//For providing logic to L298 IC to choose the direction of the DC motor

const byte address[6] = "00001";
boolean button_state = 0;
float speedValue = 0;
float rotationValue = 0;
int finalSpeed =0;
String msg = "";

void setup() {
  Serial.begin(9600);

  pinMode(ENpwm1, OUTPUT) ;  //we have to set PWM pin as output
  pinMode(ENpwm2, OUTPUT);
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
    //Serial.println("Radio available");

    char text[5] = "";
    //radio.read(&speedValue, sizeof(speedValue));    //Reading the speed multiplier
    radio.read(&msg, sizeof(msg));    //Reading the whole msg
    //radio.read(&rotationValue, sizeof(rotationValue));    //Reading the rotation multiplier

    //finalSpeed = (int) (speedValue);    // final speed value
    //Serial.println(finalSpeed);
    Serial.println(msg);

    Drive();
    /*if (finalSpeed > 400)
    {
      Drive();
      Serial.println("Drive");
    }
    else
    {
      Brake();
      Serial.println("Brake");
    }*/
  }
}

void Drive()
{
  //For Clock wise motion , in_1 = High , in_2 = Low
  digitalWrite(in_1, HIGH) ;
  digitalWrite(in_2, LOW) ;
  digitalWrite(in_3, HIGH);
  digitalWrite(in_4, LOW);
  analogWrite(ENpwm1, finalSpeed) ;
  analogWrite(ENpwm2, finalSpeed) ;
}

void Brake() {
  digitalWrite(in_1, HIGH) ;
  digitalWrite(in_2, HIGH) ;
  digitalWrite(in_3, HIGH) ;
  digitalWrite(in_4, HIGH) ;
}
