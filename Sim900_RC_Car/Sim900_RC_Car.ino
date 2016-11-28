//Created from GxMarkos
//Questions:gxmarkos93@gmail.com




#include <SoftwareSerial.h>
#include "inetGSM.h"
#include "SIM900.h"
//SoftwareSerial SIM900(2, 3);



int motorPin0 = 10; 
int motorPin1 =11; 
int motorPin2 = 8;
int motorPin3 = 9;


int data;
char msg[2];
int numdata;


void setup() {     
  
  
 
  Serial.begin(9600); 
  Serial.print("power up" );
  if(gsm.begin(2400)){
    Serial.println("READY");
    
  }else
    Serial.println("FAILED");
  
Serial.println("AT+CIPSHUT" );
gsm.SimpleWriteln("AT+CIPSHUT");
delay(2000);

Serial.println("AT+CIPMUX=0" );
gsm.SimpleWriteln("AT+CIPMUX=0");
delay(2000);

Serial.println("AT+CGATT=1" );
gsm.SimpleWriteln("AT+CGATT=1");
delay(2000);

Serial.println("Apn setup" );
gsm.SimpleWriteln("AT+CSTT=\"internet.vodafone.gr\",\"\",\"\"");
ShowSerialData();
delay(2000);


gsm.SimpleWriteln("AT+CIICR");
ShowSerialData();
delay(2000);

gsm.SimpleWriteln("AT+CIFSR");
Serial.println("ip address");
ShowSerialData();
delay(2000);

gsm.SimpleWriteln("AT+CIPSTART=\"TCP\",\"77.49.239.22\",\"2520\"");
Serial.println("executecip");
 ShowSerialData();
 delay(2500);

}

void loop(){
//submitRequest();

data=gsm.read(msg,2);
Serial.print(msg);
delay(500);


              if(msg[0]=='w')
              {
                 //  msg[0]='\0';
                  driveForward();
        	        delay(5000);
        	        stop();
                 // i++;
              }
              if(msg[0]=='s')
              {     //msg[0]='\0';
                   driveBackwards();
	                  delay(5000);
		                stop(); 
                   //i++;
              }
              if(msg[0]=='a')
              {     //msg[0]='\0';
                   turnLeft();
                   delay(6000);
                   stop();
                  // i++;
              }
              
              if (msg[0]=='d')  
              {   // msg[0]='\0';
                  turnRight();
                  delay(6000);
                  stop();
                 // i++;
              }
              
              if (msg[0]=='0')
              {
                  //msg[0]='\0';
                  stop();
                 // i++;
              }   
}




/*
void submitRequest(){
Serial.println("Start Gprs" );
SIM900.println("AT+CIICR");
delay(2000);

Serial.println("CIPSTART" );
SIM900.println("AT+CIPSTART=\"TCP\",\"188.4.197.20\",\"2520\"");
}
*/
void ShowSerialData()
{
  while(gsm.available()!=0)
    Serial.write(char (gsm.read()));
}
void driveForward(){
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, LOW);
}

void driveBackwards(){
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, HIGH);
}

void turnLeft(){
digitalWrite(motorPin0, LOW);
digitalWrite(motorPin1, HIGH);
}

void turnRight(){
digitalWrite(motorPin0, HIGH);
digitalWrite(motorPin1, LOW);
}

void stop(){
digitalWrite(motorPin0, LOW);
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW);		
}



