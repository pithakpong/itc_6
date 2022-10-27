#include <Wire.h>
#define Master 1 
#define Slave_1 2 
#define Slave_2 3  
char Token[20] = "Token#0#"; 
char messagereceive[100];
int check = 0,contin = 0,slot = 0;
int k =0;
char message[100];
void setup() 
{ 
  Wire.begin(Slave_1); 
  Serial.begin(9600); 
  Wire.onReceive(re); 
  Wire.onRequest(qs);
}   
void qs() 
{ 
    Wire.write('2');
 
}
void re(int x) 
{ 
  int i = 0;
  while(Wire.available()) 
  {  
    char c = Wire.read();
    messagereceive[i] = c;
    i++;
  } 
  messagereceive[6] = '1'; 
  messagereceive[8] = '1'; 
  Serial.print(messagereceive);
  memset(messagereceive,0,100);
  Serial.println(); 
  check = 1;
}
void loop() 
{  
   while(Serial.available()>0) 
  { 
    char Byte = (char) Serial.read(); 
      message[k] = Byte;
      k++; 
     if( Byte == 1)
       contin = 1;
  } 
    if(contin == 1 ) 
   {  
      Serial.println(message);
      k = 0; 
      slot = 1; 
      contin  = 0;
   }  

  if(slot == 1) 
  { 
    Wire.beginTransmission(Master);  
    for(int i =0;i<strlen(message);i++)
      Wire.write(message[i]);  
  Wire.endTransmission();
    memset(message,0,100);
    slot = 0;
    check = 1;
  }
  
  if(check ==1) 
  { 
     Wire.requestFrom(Master,1);  
       while( Wire.available()> 0)
     { 
     char x = Wire.read(); 
     Token[8] = x;
     } 
     Serial.println(Token); 
     check = 0;
  }
 
}
