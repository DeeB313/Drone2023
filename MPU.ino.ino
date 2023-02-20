#include <Wire.h>


long temperature;
long gyroX, gyroY, gyroZ, rollrate, pitchrate, yawrate;
float accelX, accelY, accelZ, totalaccel;
float Roll, Pitch, Yaw, accelangleX, accelangleY, accelangleZ, tempPitch;
float deltatime1, lasttime1;

void setup() {
  
  Serial.begin(9600);
//MPU configuration ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Wire.begin();
  TWBR = 12;
  setupMPU();

}

void loop() {
  
  readaccelgyrotemp();
  processMPUdata();
  Serial.println("roll: " + String(Roll) + "  " + " Pitch: " + String(Pitch) + "  " + "yaw: " + String(Yaw) + "  " + " gyroX: " + String(gyroX) + "  " + " gyroY: " + String(gyroY) + "  " + " gyroZ: " + String(gyroZ) );
  //Serial.println("accelX: " + String(accelX) + "  " + " accelY: " + String(accelY) + "  " + " accelZ: " + String(accelZ) + "  " + " taccel: " + String(totalaccel) + "  " + " angleX: " + String(accelangleX) + "  " + " angleY: " + String(accelangleY) );
  
}



void setupMPU(){
  Wire.beginTransmission(0x68);         //start communicating with the MPU using its I²C address
  Wire.write(0x6B);                         //select the power management register 
  Wire.write(B00000000);                    //exit sleep and cycle mode and set the internal clock inside the power management register 
  Wire.endTransmission(0x68);           //end communication with the MPU 

  Wire.beginTransmission(0x68);        //start communicating with the MPU
  Wire.write(0x1B);                         //select the register 1B - Gyroscope Configuration
  Wire.write(B00001000);                    //Set the gyro to full scale +/- 500deg./s 
  Wire.endTransmission(0x68); 

  Wire.beginTransmission(0x68);        //start communicating with the MPU
  Wire.write(0x1C);                         //Accessing the register 1C - Acccelerometer Configuration
  Wire.write(B00001000);                    //Set the accel to full scale +/- 4g
  Wire.endTransmission(0x68);
}

void readaccelgyrotemp(){                                             //Subroutine for reading the raw gyro and accelerometer data
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission(0x68);                                              //End the transmission
  Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  accelX = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_x variable
  accelY = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_y variable
  accelZ = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_z variable
  temperature = Wire.read()<<8|Wire.read();                            //Add the low and high byte to the temperature variable
  gyroX = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_x variable
  gyroY = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_y variable
  gyroZ = Wire.read()<<8|Wire.read();
}

void processMPUdata(){
  deltatime1 = (micros()-lasttime1)/1000000;
  lasttime1 = micros();
  gyroX /= 65.5;
  gyroY /= 65.5;
  gyroZ /= 65.5;

  gyroX += 2;
  gyroY += 0;
  gyroZ += -1;

  rollrate = gyroX - gyroZ*sin(Pitch);
  pitchrate = gyroY*cos(Roll) + gyroZ*cos(Pitch)*sin(Roll);
  yawrate = -gyroY*sin(Roll) + gyroZ*cos(Pitch)*cos(Roll);
 
  Roll += rollrate*deltatime1;
  Pitch += pitchrate*deltatime1;
  Yaw += yawrate*deltatime1;

  //tempPitch = Pitch;
  //Pitch -= Roll * sin(gyroZ*(3.142/180));
  //Roll += tempPitch * sin(gyroZ*(3.142/180));
  
  accelX /= 8192.0;
  accelY /= 8192.0;
  accelZ /= 8192.0;
  
  accelX -= 0;
  accelY -= 0;
  accelZ += 0;
  
  
  totalaccel = sqrt( accelX*accelX + accelY*accelY + accelZ*accelZ );
  accelangleY = 57.296*asin(accelX/totalaccel);
  accelangleX = 57.296*asin(accelY/totalaccel);
  

  
  Pitch = Pitch * 0.8 + accelangleY * 0.2;
  Roll = Roll * 0.8 + accelangleX * 0.2;
  
  
  
  }
