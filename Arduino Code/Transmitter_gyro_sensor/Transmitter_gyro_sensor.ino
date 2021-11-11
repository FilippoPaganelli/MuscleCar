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

/************************** gyroscope stuff ***********************************/
#include <Wire.h>
#include <SFE_LSM9DS0.h>

// Example I2C Setup //
// Comment out this section if you're using SPI
// SDO_XM and SDO_G are both grounded, so our addresses are:
#define LSM9DS0_XM  0x1D // Would be 0x1E if SDO_XM is LOW
#define LSM9DS0_G   0x6B // Would be 0x6A if SDO_G is LOW
// Create an instance of the LSM9DS0 library called `dof` the
// params: [SPI or I2C Mode declaration],[gyro I2C address],[xm I2C add.]
LSM9DS0 dof(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

#define PRINT_CALCULATED
//#define PRINT_RAW

#define PRINT_SPEED 500 // 500 ms between prints

float x_value = 0;
/***************************** end gyroscope stuff *****************************/


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
String msgToSend = "";
long lastTime = 0;
long interval = 2000;

void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  ////myIMU.begin();

  // maybe we have to use only 1 Serial.begin()
  /* gyroscope */
  //Serial.begin(115200); // Start serial at 115200 bps
  uint16_t status = dof.begin();
  Serial.println(status, HEX);
  Serial.println("Should be 0x49D4");
  Serial.println();
  /* end gyroscope */
}

void loop() {
  //readData = analogRead(A0);

  muscleSensor();
  gyroscope();  
  
  

  sendMsg();

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
  
  
  ////radio,write(&rotationValue, sizeof(rotationValue));
  
  delay(55);

  /* gyroscope stuff */
  
  //printGyro();  // Print "G: gx, gy, gz"
  //printAccel(); // Print "A: ax, ay, az"
  //printMag();   // Print "M: mx, my, mz"
  
  // Print the heading and orientation for fun!
  //printHeading((float) dof.mx, (float) dof.my);
  //printOrientation(dof.calcAccel(dof.ax), dof.calcAccel(dof.ay), dof.calcAccel(dof.az));
  Serial.println();
  
  //delay(PRINT_SPEED);
  /* end gyroscope stuff */
}

void sendMsg()
{
  msgToSend = String(speedValue,2) + ";" + String(x_value,2);
  char msg[15] = "";
  msgToSend.toCharArray(msg, sizeof(msg));
  Serial.print("MSG: ");
  Serial.println(msg);
  radio.write(&msg, sizeof(msg));
}

void muscleSensor()
{
  speedValue = analogRead(A0)/ 1024.0;
  speedValue = speedValue*255;
  Serial.print("Speed value: ");
  Serial.println(speedValue);  
}

void gyroscope()
{
  
  // on wrist with pins facing the skin, yellow wire on top:
  // positive value = turn right
  // negative value = turn left
  
  dof.readGyro();
  int temp_value = dof.calcGyro(dof.gx);
  if (abs(temp_value) > 100)
  {
    x_value = temp_value;
    lastTime = millis();
  }
  else
  {
    if (millis() - lastTime > interval)
    {
      x_value = temp_value;
      lastTime = millis();
    }
  }
  
  
  Serial.print("G: ");
  Serial.println(x_value, 2);
}


/*void printGyro()
{
  // first call readGyro() function. When this exits, it'll update the
  // gx, gy, and gz variables with the most current data.
  dof.readGyro();
  
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
  Serial.print("G: ");
#ifdef PRINT_CALCULATED
  // on wrist with pins facing the skin, yellow wire on top:
  // positive value = turn right
  // negative value = turn left
  x_value = dof.calcGyro(dof.gx); 
  Serial.println(x_value, 2);
  //Serial.print(", ");
  //Serial.print(dof.calcGyro(dof.gy), 2);
  //Serial.print(", ");
  //Serial.println(dof.calcGyro(dof.gz), 2);
#elif defined PRINT_RAW
  Serial.print(dof.gx);
  Serial.print(", ");
  Serial.print(dof.gy);
  Serial.print(", ");
  Serial.println(dof.gz);
#endif
}*/
