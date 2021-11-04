// Muscle sensor transmitter

// #include "SparkFunLSM6DS3.h" for gyroscope
// LSM6DS3 myIMU; //Default constructor is I2C, addr 0x6B
// myIMU.begin();
// Serial.print("\nGyroscope:\n");
// Serial.print(" X = ");
// Serial.println(myIMU.readFloatGyroX(), 4);
// Serial.print(" Y = ");
// Serial.println(myIMU.readFloatGyroY(), 4);
// Serial.print(" Z = ");
// Serial.println(myIMU.readFloatGyroZ(), 4);
// (?) suppose it goes from 0 to 180 (clockwise) and 0 to -180 (counterclockwise)
// we could read it and use to normalise the speed value for the motors

#include <printf.h>
#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
////#include "SparkFunLSM6DS3.h"

RF24 radio(7, 8); // CE, CSN
////LSM6DS3 myIMU;

const byte address[6] = "00001";
int button_pin = 3;
boolean button_state = 0;
//const char text[] = " :D ";
//int readData = 0;
//int threshold = 600;

////float rotationValue = 0;
float speedValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  ////myIMU.begin();
}

void loop() {
  //readData = analogRead(A0);

  speedValue = analogRead(A0)/ 1024.0;
  speedValue = speedValue*255;
  
  Serial.println(speedValue);
  ////rotation = myIMU.readFloatGyroX() / 180.0;
  
  //Serial.println(readData);
  /*if(readData > threshold)
  {
    button_state = HIGH;
    Serial.println("Analog is HIGH");
  }
  else
  {
    button_state = LOW;
    Serial.println("Analog is LOW");
  }*/
  
  //radio.write(&button_state, sizeof(button_state));
  
  radio.write(&speedValue, sizeof(speedValue));
  ////radio,write(&rotationValue, sizeof(rotationValue));
  
  delay(55);
}
