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

#include <printf.h>
#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int button_pin = 3;
boolean button_state = 0;
const char text[] = " :D ";
int readData = 0;
int threshold = 600;

void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  readData = analogRead(A0);
  Serial.println(readData);
  if(readData > threshold)
  {
    button_state = HIGH;
    Serial.println("Analog is HIGH");
  }
  else
  {
    button_state = LOW;
    Serial.println("Analog is LOW");
  }
  
  //button_state = digitalRead(button_pin);
  radio.write(&button_state, sizeof(button_state));
  delay(50);

  if (button_state == HIGH) {
    //radio.write(&text, sizeof(text));
    //Serial.println("sending..." + fuck);
    delay(5);
  }
  else {
    delay(5);
  }
}
