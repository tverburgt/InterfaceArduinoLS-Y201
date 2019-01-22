/***********************
ChangeCameraSize
Jennifer Case
2/28/2013
***********************/

#include <SoftwareSerial.h> 

SoftwareSerial mySerial = SoftwareSerial(10, 3);

void setup()
{ 
  Serial.begin(19200);
  mySerial.begin(38400);
  
}

int sizeChange = 0;

void loop() {
  SendResetCmd();
  delay(3000); 
     
  if (sizeChange==0) {
    ChangeSizeSmall();
    Serial.println("Size Changed");
    sizeChange++;
  }
     
}

//Send Reset command
void SendResetCmd() {
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x26);
  mySerial.write((byte)0x00);
}

void ChangeSizeSmall() {
    mySerial.write((byte)0x56);
    mySerial.write((byte)0x00);
    mySerial.write((byte)0x31);
    mySerial.write((byte)0x05);
    mySerial.write((byte)0x04);
    mySerial.write((byte)0x01);
    mySerial.write((byte)0x00);
    mySerial.write((byte)0x19);
    mySerial.write((byte)0x22);      
}

void ChangeSizeMedium()
{
    mySerial.write((byte)0x56);
    mySerial.write((byte)0x00);
    mySerial.write((byte)0x31);
    mySerial.write((byte)0x05);
    mySerial.write((byte)0x04);
    mySerial.write((byte)0x01);
    mySerial.write((byte)0x00);
    mySerial.write((byte)0x19);
    mySerial.write((byte)0x11);      
}

void ChangeSizeBig()
{
    mySerial.write((byte)0x56);
    mySerial.write((byte)0x00);
    mySerial.write((byte)0x31);
    mySerial.write((byte)0x05);
    mySerial.write((byte)0x04);
    mySerial.write((byte)0x01);
    mySerial.write((byte)0x00);
    mySerial.write((byte)0x19);
    mySerial.write((byte)0x00);      
}
