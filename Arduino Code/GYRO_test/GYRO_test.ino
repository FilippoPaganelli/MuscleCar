#include <SPI.h> // Included for SFE_LSM9DS0 library
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

void setup()
{
  Serial.begin(115200); // Start serial at 115200 bps
  uint16_t status = dof.begin();
  Serial.println(status, HEX);
  Serial.println("Should be 0x49D4");
  Serial.println();
}


void loop()
{
  printGyro();  // Print "G: gx, gy, gz"
  //printAccel(); // Print "A: ax, ay, az"
  //printMag();   // Print "M: mx, my, mz"
  
  // Print the heading and orientation for fun!
  //printHeading((float) dof.mx, (float) dof.my);
  //printOrientation(dof.calcAccel(dof.ax), dof.calcAccel(dof.ay), dof.calcAccel(dof.az));
  Serial.println();
  
  delay(PRINT_SPEED);
}

void printGyro()
{
  // first call readGyro() function. When this exits, it'll update the
  // gx, gy, and gz variables with the most current data.
  dof.readGyro();
  
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
  Serial.print("G: ");
#ifdef PRINT_CALCULATED

  // on wrist with pins facing the skin:
  // positive value = turn right
  // negative value = turn left
  x_value = dof.calcGyro(dof.gx); 
  Serial.println(x_value, 2);
  /*Serial.print(", ");
  Serial.print(dof.calcGyro(dof.gy), 2);
  Serial.print(", ");
  Serial.println(dof.calcGyro(dof.gz), 2);*/
#elif defined PRINT_RAW
  x_value = dof.gx;
  Serial.print(x_value);
  Serial.print(", ");
  Serial.print(dof.gy);
  Serial.print(", ");
  Serial.println(dof.gz);
#endif
}
