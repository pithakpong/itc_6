#include <string.h>
#include <Wire.h> 
#define Master 1 
#define Slave_1 2 
#define Slave_2 3  
char Token[20] = "Token#0#"; 
char message[100]; 
char messagereceive[100]; 
int i = 0,slot = 0,check = 0,contin = 0;
void setup() 
{  
  Serial.begin(9600);
  Wire.begin(Master);
  Wire.onRequest(RequestFunc); 
  Wire.onReceive(ReceiveFunc);
} 
void RequestFunc() 
{ 

    Wire.write('1');
  
}
void ReceiveFunc(int x) 
{  
  //Serial.println("come");
  int n =0;
  while(Wire.available()) 
  {  
    char c = Wire.read();
    messagereceive[n] = c;
    n++;
  }   
  check = 1;
}
void loop() 
{  
  while(Serial.available()>0) 
  { 
    char Byte = (char) Serial.read(); 
    if(Byte !=  '\n') 
    { 
      message[i] = Byte;
      i++;
     
    }
    //else 
    //{ 
      //message[i] = '\n';
      //Serial.println(message);   
      //i = 0; 
      //slot = 1;
    //} 
    contin = 1;
  }  
  if(contin == 1) 
   {  
      Serial.println(message);
      i = 0; 
      slot = 1; 
      contin  = 0;
   }
  if(slot == 1) 
  { 
    if (message[8] == '1') 
    Wire.beginTransmission(Slave_1);
  else if (message[8] == '2') 
    Wire.beginTransmission(Slave_2);  
    for(int i =0;i<strlen(message);i++)
      Wire.write(message[i]);  
  Wire.endTransmission();
    memset(message,0,100);
    slot = 0; 
    check = 1;
  } 
  if(check == 1) 
  {  
     if (messagereceive[8] == '1') 
  { 
    Wire.beginTransmission(Slave_1); 
      Wire.write(messagereceive); 
    Wire.endTransmission();
  }
    if (messagereceive[8] == '2') 
  { 
    Wire.beginTransmission(Slave_2);  
      Wire.write(messagereceive); 
    Wire.endTransmission();
  }
    if (messagereceive[8] == '3') 
  { 
  
  messagereceive[6] = '1'; 
  messagereceive[8] = '3'; 
  Serial.print(messagereceive);
  memset(messagereceive,0,100);
  Serial.println();  
    }
    Wire.requestFrom(Slave_2,1); 
    while(Wire.available() > 0) 
    { 
      char x = Wire.read(); 
      Token[8] = x;
    } 
    Serial.println(Token); 
    check = 0;
  }
 delay(100);
}
