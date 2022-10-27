#include <Wire.h>
#define Master 1 
#define Slave_1 2 
#define Slave_2 3  
char Token[20] = "Token#0#"; 
char messagereceive[100]; 
char message[100];
int check = 0,slot = 0,contin = 0;
int k = 0;
void setup() 
{ 
  Wire.begin(Slave_2); 
  Serial.begin(9600); 
  Wire.onReceive(re); 
  Wire.onRequest(qs);
}   
void qs() 
{ 
    Wire.write('3');
 
}
void re(int x) 
{ 
  int i =0;
  while(Wire.available()) 
  {  
    char c = Wire.read();
    messagereceive[i] = c;
    i++;
  } 
  messagereceive[6] = '1'; 
  messagereceive[8] = '2'; 
  Serial.print(messagereceive);
  memset(messagereceive,0,100);
  Serial.println(); 
  check = 1;
}
void loop() 
{  
  //Serial.println(Serial.available());
   while(Serial.available()>0) 
  {  
     //Serial.println(Serial.available());
    char Byte = (char) Serial.read();  
      message[k] = Byte;
      k++; 
     if (Byte == ' ')
        contin = 1;
  }  
  if(contin == 1 && Serial.available()<=0) 
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
    check = 1;
    slot = 0; 
  }
  
  if(check ==1) 
  { 
     Wire.requestFrom(Slave_1,1);  
       while( Wire.available()> 0)
     { 
     char x = Wire.read(); 
     Token[8] = x;
     } 
     Serial.println(Token); 
     check = 0;
  }
 
}
