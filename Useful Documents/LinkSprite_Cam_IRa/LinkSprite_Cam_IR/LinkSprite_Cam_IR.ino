/****************************************************************************** 
LinkSprite_Cam
Ryan Owens @ SparkFun Electronics>
Revised by Joel Bartlett on 03/25/15 for compilation on Arduino 1.6+

This code allows you to control the LinkSprite IR Camera (SEN-11610) with an Arduino microcontroller

Development environment specifics:
Arduino 1.6.0

This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given. 
*********************************************************************************/
#include <SoftwareSerial.h>

/* Linksprite */
byte incomingbyte;
SoftwareSerial mySerial(4, 5); // RX, TX         //Configure pin 4 and 5 as soft serial port

int a=0x0000,j=0,k=0,count=0;                    //Read Starting address       
uint8_t MH,ML;
boolean EndFlag=0;
                               
void SendResetCmd();
void SendTakePhotoCmd();
void SendReadDataCmd();
void StopTakePhotoCmd();

void setup()
{ 
  Serial.begin(19200);
  mySerial.begin(38400);
}

void loop() 
{
     SendResetCmd();
     delay(4000);                               //After reset, wait 2-3 second to send take picture command
      
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

         delay(25);
          while(mySerial.available()>0)
          {
               incomingbyte=mySerial.read();
               k++;
               if((k>5)&&(j<32)&&(!EndFlag))
               {
               a[j]=incomingbyte;
               if((a[j-1]==0xFF)&&(a[j]==0xD9))      //Check if the picture is over
               EndFlag=1;                           
               j++;
	       count++;
               }
          }
         
          for(j=0;j<count;j++)
          {   if(a[j]<0x10)
              Serial.print("0");
              Serial.print(a[j],HEX);
              Serial.print(" ");
          }                                       //Send jpeg picture over the serial port
          Serial.println();
      }      
     while(1);
}

//Send Reset command
void SendResetCmd()
{
      mySerial.write(0x56);
      mySerial.write((byte)0);
      mySerial.write(0x26);
      mySerial.write((byte)0);
}

//Send take picture command
void SendTakePhotoCmd()
{
      mySerial.write(0x56);
      mySerial.write((byte)0);
      mySerial.write(0x36);
      mySerial.write(0x01);
      mySerial.write((byte)0);  
}

//Read data
void SendReadDataCmd()
{
      MH=a/0x100;
      ML=a%0x100;
      mySerial.write(0x56);
      mySerial.write((byte)0);
      mySerial.write(0x32);
      mySerial.write(0x0c);
      mySerial.write((byte)0); 
      mySerial.write(0x0a);
      mySerial.write((byte)0);
      mySerial.write((byte)0);
      mySerial.write(MH);
      mySerial.write(ML);   
      mySerial.write((byte)0);
      mySerial.write((byte)0);
      mySerial.write((byte)0);
      mySerial.write(0x20);
      mySerial.write((byte)0);  
      mySerial.write(0x0a);
      a+=0x20;                            //address increases 32£¬set according to buffer size
}

void StopTakePhotoCmd()
{
      mySerial.write(0x56);
      mySerial.write((byte)0);
      mySerial.write(0x36);
      mySerial.write(0x01);
      mySerial.write(0x03);        
}










