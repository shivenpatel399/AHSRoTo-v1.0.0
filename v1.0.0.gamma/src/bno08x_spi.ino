/*
  Using the BNO08x IMU

  This example shows how check for a "Reset Complete" message from the sensor,
  which is helpful when used in tandem with requestResetReason() and
  getResetReason(). The sensor will be reset each time 100 readings are received
  to demonstrate.

  It outputs the x/y/z parts of the gyro.

  Hardware Connections:
  IoT RedBoard --> BNO08x
  D5  --> CS
  PICO --> SI
  POCI --> SO
  SCK  --> SCK
  A4  --> INT
  A5  --> RST
  3V3  --> 3V3
  GND  --> GND

  BNO08x "mode" pins set for SPI:
  PSO --> 3V3
  PS1 --> 3V3

*/

#include "SparkFun_BNO08x_Arduino_Library.h"  // CTRL+Click here to get the library: http://librarymanager/All#SparkFun_BNO08x
BNO08x myIMU;

// For SPI, we need some extra pins defined:
// Note, these can be other GPIO if you like.
#define BNO08X_CS   5
#define BNO08X_INT  A4
#define BNO08X_RST  A5

int cyclecount = 0;

#define BNO08X_ADDR 0x4B  // SparkFun BNO08x Breakout (Qwiic) defaults to 0x4B
//#define BNO08X_ADDR 0x4A // Alternate address if ADR jumper is closed

void setup() {
  Serial.begin(115200);
  
  while(!Serial) delay(10); // Wait for Serial to become available.
  // Necessary for boards with native USB (like the SAMD51 Thing+).
  // For a final version of a project that does not need serial debug (or a USB cable plugged in),
  // Comment out this while loop, or it will prevent the remaining code from running.
  
  Serial.println();
  Serial.println("BNO08x Read Example");

  Wire.begin();

  if (myIMU.beginSPI(BNO08X_CS, BNO08X_INT, BNO08X_RST) == false) {
    Serial.println("BNO08x not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1)
      ;
  }
  Serial.println("BNO08x found!");

  Serial.print(F("Reset Reason: "));
  printResetReasonName(myIMU.getResetReason());
  Serial.println();

  setReports();

  Serial.println("Reading events");
  delay(100);
}

// Here is where you define the sensor outputs you want to receive
void setReports(void) {
  Serial.println("Setting desired reports");
  if (myIMU.enableGyro() == true) {
    Serial.println(F("Gyro enabled"));
    Serial.println(F("Output in form x, y, z, in radians per second"));
  } else {
    Serial.println("Could not enable gyro");
  }
  delay(100); // This delay allows enough time for the BNO086 to accept the new 
              // configuration and clear its reset status
}

void loop() {
  delay(1);
  myIMU.serviceBus();

  // One of these will appear at the very start because of the power on reset.
  // Use requestResetReason() and getResetReason() for the difference between
  // different resets.
  if (myIMU.wasReset()) {
    Serial.println(" ------------------ BNO08x has reset. ------------------ ");
    Serial.print(F("Reset Reason: "));
    printResetReasonName(myIMU.getResetReason());
    Serial.println();

    setReports();  // We'll need to re-enable reports after any reset.
  }

  // Has a new event come in on the Sensor Hub Bus?
  if (myIMU.getSensorEvent() == true) {

    // is it the correct sensor data we want?
    if (myIMU.getSensorEventID() == SENSOR_REPORTID_GYROSCOPE_CALIBRATED) {

      cyclecount++;

      Serial.print(F("["));
      if (cyclecount < 10) Serial.print(F("0"));
      Serial.print(cyclecount);
      Serial.print(F("] "));

      float x = myIMU.getGyroX();
      float y = myIMU.getGyroY();
      float z = myIMU.getGyroZ();

      Serial.print(x, 2);
      Serial.print(F(","));
      Serial.print(y, 2);
      Serial.print(F(","));
      Serial.print(z, 2);

      Serial.println();

      if (cyclecount == 100) {
        myIMU.softReset();
        cyclecount = 0;
      }
    }
  }
}


//Given a number between 0 and 5, print the name of the reset reason
//1 = POR, 2 = Internal reset, 3 = Watchdog, 4 = External reset, 5 = Other
void printResetReasonName(byte resetReasonNumber)
{
  if(resetReasonNumber == 1) Serial.print("POR");
  else if(resetReasonNumber == 2) Serial.print("Internal reset");
  else if(resetReasonNumber == 3) Serial.print("Watchdog");
  else if(resetReasonNumber == 4) Serial.print("External reset");
  else if(resetReasonNumber == 5) Serial.print("Other");
}
