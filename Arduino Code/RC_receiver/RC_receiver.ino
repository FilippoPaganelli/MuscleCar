#include <printf.h>
#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
boolean button_state = 0;

void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
//  digitalWrite(3,HIGH);
}

void loop() {
  if (radio.available()) {
    //Serial.println("Receiver");
    char text[5] = "";
    
    //Serial.println(sizeof(text));
    //Serial.println(text);
    
    radio.read(&button_state, sizeof(button_state));    //Reading the data
    //Serial.println(button_state);
    if (button_state == HIGH)
    {
      digitalWrite(3, HIGH);
      delay(50);
      radio.read(&text, sizeof(text));
      Serial.println("High");
      Serial.println(text);
    }
    else
    {
      digitalWrite(3, LOW);
      Serial.println("Low");
    }
  }
  //delay(50);
}
