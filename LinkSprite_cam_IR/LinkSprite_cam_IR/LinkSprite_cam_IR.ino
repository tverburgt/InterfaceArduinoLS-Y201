/* Linksprite */
#include <SoftwareSerial.h>

byte incomingbyte;
SoftwareSerial mySerial = SoftwareSerial(10, 3); //SoftwareSerial(rx of arduino, tx of arduino)
int a=0x0000,j=0,k=0,count=0; //Read Starting address       
uint8_t MH,ML;
boolean EndFlag=0;
                               
void SendResetCmd();
void SendTakePhotoCmd();
void SendReadDataCmd();
void StopTakePhotoCmd();

void setup()
{ 
  //This initialises a serial port that will connect the arduino to a computer via USB at Baud rate of 19200
  Serial.begin(19200);
  //This initialises a serial port that will connect the arduino to the camera via the rx and tx pins at Baud rate of 38400
  mySerial.begin(38400);
}

void loop() 
{
     SendResetCmd();
     delay(4000);  //After reset, wait 2-3 second to send take picture command
      
      SendTakePhotoCmd();

     while(mySerial.available()>0)
      {
        incomingbyte=mySerial.read();

      }   
      byte a[32];
      
      while(!EndFlag)
      {  
         j=0;
         k=0;
         count=0;
         SendReadDataCmd();

         delay(400); //Play with this value
          while(mySerial.available()>0)
          {
               incomingbyte=mySerial.read();
               k++;
               if((k>5)&&(j<32)&&(!EndFlag))
               {
               a[j]=incomingbyte;
               if((a[j-1]==0xFF)&&(a[j]==0xD9))      //Check if the picture is over
               {
                 EndFlag=1;
               }
                                          
               j++;
	       count++;
               }
          }
         
          for(j=0;j<count;j++)
          {   if(a[j]<0x10)
              Serial.print("0");
              Serial.print(a[j],HEX);
              //Serial.print(" ");
          }                           //Send jpeg picture over the serial port
          //Serial.println();
      }      
     while(1);
}

//Send Reset command
void SendResetCmd() {
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x26);
  mySerial.write((byte)0x00);   
}

//Send take picture command
void SendTakePhotoCmd() {
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x36);
  mySerial.write((byte)0x01);
  mySerial.write((byte)0x00);
    
  a = 0x0000; //reset so that another picture can taken
}

void FrameSize() {
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x34);
  mySerial.write((byte)0x01);
  mySerial.write((byte)0x00);  
}

//Read data
void SendReadDataCmd() {
  MH=a/0x100;
  ML=a%0x100;
      
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x32);
  mySerial.write((byte)0x0c);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x0a);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)MH);
  mySerial.write((byte)ML);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x20);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x0a);

  a+=0x20; 
}

void StopTakePhotoCmd() {
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x36);
  mySerial.write((byte)0x01);
  mySerial.write((byte)0x03);        
}
