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
const char text2[] = " :) ";

void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  Serial.println("Transmitter");
  button_state = digitalRead(button_pin);
  radio.write(&button_state, sizeof(button_state));

  //radio.write(&text, sizeof(text));
  //radio.write(&text2, sizeof(text2));

  if (button_state == HIGH) {
    radio.write(&text, sizeof(text));
    //radio.write(&text2, sizeof(text2));
    Serial.println("sending...");
    //Serial.println(sizeof(text));
    delay(5);
  }
  else {
    delay(5);
  }
}
