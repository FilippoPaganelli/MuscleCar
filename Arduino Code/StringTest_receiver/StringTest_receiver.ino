#include <printf.h>
#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 7); // CE, CSN

const int ENpwm1 = 3 ;
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
char charMsg[15] = "";
String stringMsg = "";
int rotationThreshold = 20;
int rightWheel = 0;
int leftWheel = 0;

void setup() {
  Serial.begin(9600);

  pinMode(ENpwm1, OUTPUT) ;  //we have to set PWM pins as output
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
    radio.read(&charMsg, sizeof(charMsg));    //Reading the whole msg
    stringMsg = String(charMsg);

    char* temp = strtok(charMsg, ";");
    speedValue = atof(temp);
    temp = strtok(NULL, ";");
    finalSpeed = (int) (round(speedValue));    // final speed values
    rotationValue = atof(temp);

    Drive();
  }
}

void Drive()
{
  //For Clock wise motion , in_1 = High , in_2 = Low
  digitalWrite(in_1, HIGH) ;
  digitalWrite(in_2, LOW) ;
  digitalWrite(in_3, LOW);
  digitalWrite(in_4, HIGH);

  leftWheel = finalSpeed;
  rightWheel = finalSpeed;
  if (abs(rotationValue) > rotationThreshold)
  {
    if (rotationValue > 0) // turn right --> slow down right wheel
    {
      rightWheel = rightWheel-rotationValue;
      if (rightWheel < 0){
        rightWheel = 0;
      }
    }
    else // turn left --> slow down left wheel
    {
      leftWheel = leftWheel+rotationValue;
      if (leftWheel < 0){
        leftWheel = 0;
      }
    }
  }
  analogWrite(ENpwm1, leftWheel) ; // left wheel
  analogWrite(ENpwm2, rightWheel) ; // right wheel
  Serial.print(leftWheel); Serial.print(" - "); Serial.println(rightWheel);
}

void Brake() {
  digitalWrite(in_1, HIGH) ;
  digitalWrite(in_2, HIGH) ;
  digitalWrite(in_3, HIGH) ;
  digitalWrite(in_4, HIGH) ;
}
