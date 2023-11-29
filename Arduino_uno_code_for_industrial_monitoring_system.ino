#include <LiquidCrystal.h>
#define gasinput A0
#define HTinput A1
#define LDRinput A2
#define fireinput A3
bool a;
int b ;
int c;
int trm ;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  // all this pin we are using for lcd arduino
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  lcd.begin(16, 2);     // set up the LCD's number of columns and rows
  pinMode(A0,INPUT);    // A0 pin as gas sensor analog input  (MQ-5)
  pinMode(A1,INPUT);    // A1 pin as temp. sensor analog input (thermister)
  pinMode(A2,INPUT);    // A2 pin as ldr sensor analog input (LDR)
  pinMode(A3,INPUT);    // A3 pin as fire sensor  digital input (flame sensor)
  pinMode(6 ,OUTPUT);   // D6  digital output pin for fan
  pinMode(7 ,OUTPUT);   // D7 digital output pin for 12 volt exhaust fan 
  pinMode(8 ,OUTPUT);   // D8 digital output for 12 volt night light
  pinMode(9 , OUTPUT);  // D9 digital pin for 12 volt water valve 
  pinMode(10,OUTPUT);   // D10 buzzer for fire and gas output 
  pinMode(13,OUTPUT);   // FOR MAIN SUPPLY RELAY
  b = 0 ;               // int b for time because we are not using delay know
  a = 0;               //  bool a for first 8 seconds for displaying name of the project and created by
  c = 0 ;                    // if fire took time then 13 relay pin to switch of the whole project
  trm = 0;            
  Serial.begin(9600);
  digitalWrite(A5,HIGH);
}




void ldrtemp ()
            {

             int ldr = analogRead(LDRinput);
             int  temp = analogRead(HTinput);
                      if (ldr<=100)
                      {         
                       digitalWrite(8,LOW);
                      }
                      else
                      {                     
                       digitalWrite(8,HIGH);
                      }
                       
                       if (temp<200)
                      {
                        digitalWrite(6,HIGH);
                        digitalWrite(7,HIGH);
                      }
                      else if (temp<=300)
                      {
                        digitalWrite(6,HIGH);
                        digitalWrite(7,LOW);
                      }
                      else
                      {
                        digitalWrite(6,LOW);
                        digitalWrite(7,LOW);
                      }

                      return ;

                  }





void loop() 
{
 digitalWrite(A5,HIGH);
 int gas = analogRead(gasinput);
 int ldr = analogRead(LDRinput);
 int fire = analogRead(fireinput);
 int temp = analogRead(HTinput);
 c = 0;
 
 lcd.clear();

 if ( a== 0)
   {
    lcd.setCursor(0, 0);
    lcd.print("PROJECT MADE BY ");
    lcd.setCursor(0, 1);
    lcd.print("VINAY AND ANUJ");
    delay (2000);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,HIGH);
    delay (2000);
    lcd.clear();
    for (int i = 0; i <= 8; i++) 
    {
      lcd.setCursor(0, 0);
     lcd.print(" IOT based Industerial");
     lcd.setCursor(0, 1);
     lcd.print(" Monitering system");
     delay (750);
     lcd.scrollDisplayLeft();
    }    
    a=!a;
   }

  else
   {  
      // code for LDR sensor
      ldr = analogRead(LDRinput);
       //Serial.print("ldr");
       //Serial.println(ldr);
        if (ldr<=200)
        {
          if (b <50 && b>0)
          { lcd.setCursor(0,0);
            lcd.print("NIGHT TIME");
            lcd.setCursor(0,1);
            lcd.print("light on");
            
          }
          digitalWrite(8,LOW);         
        }
        else
        {  
          if (b <50  && b>0)
          {
           lcd.setCursor(0,0);
           lcd.print("DAY TIME");
           lcd.setCursor(0,1);
           lcd.print("light off");
           
          }
          digitalWrite(8,HIGH);
          
        }

        // code for temp sensor        
      temp = analogRead(HTinput);
       // Serial.print("temp");
       // Serial.println(temp);

       //int cal = (temp - 0.5) * 100.0 ;
        if (temp<=200)
        {    
          if (b <100 && b>50)
          {  
            lcd.setCursor(0,0);
            lcd.print("TEMP low");
            lcd.setCursor(0,1);
            lcd.print("fan off ");
            
            
          }
         digitalWrite(6,HIGH);
         digitalWrite(7,HIGH);
        }

        else if (temp <=300)
        {  
          if (b <100 && b>50)
          {    
           lcd.setCursor(0,0);
           lcd.print("TEMP moderate");
           lcd.setCursor(0,1);
           lcd.print("fan on ");
           
           
          }
         digitalWrite(6,HIGH);
         digitalWrite(7,LOW);
        }

        else
       {  
         if (b <100 && b>50)
          {
           lcd.setCursor(0,0);
           lcd.print("TEMP high");
           lcd.setCursor(0,1);
           lcd.print("exhaust fan on");
           
          }
         digitalWrite(6,LOW);
         digitalWrite(7,LOW);
        }
     
       // code for fire sensor
      fire = analogRead(fireinput);
       // Serial.print("fire");
       // Serial.println(fire);
        if (fire<200) 
        {  
          lcd.clear();
           while ( fire <200 )   
           { 
              lcd.setCursor(0,0);
              lcd.print("FIRE detected");
              lcd.setCursor(0,1);
              lcd.print("water  on");
              digitalWrite(9,LOW);
              digitalWrite(10,LOW);
              fire = analogRead(fireinput);
              delay(2000);
              while ( fire <200)
             { 
              lcd.clear();
               lcd.setCursor(0,0);
               digitalWrite(10,HIGH);
               lcd.print("Fire Fire Fire");
               String sensorData = String(ldr) + "," + String(temp) + "," + String(gas) + "," + String(0000);
               Serial.println(sensorData);
               delay(300);
               lcd.setCursor(0,1);
               lcd.print("Alert  !!!!");
               digitalWrite(10,LOW);
               delay(300);
               ldrtemp();              
                 c++ ;
                    if (c>=15)
                    {
                      digitalWrite(A5,LOW);
                    }

                fire = analogRead(fireinput);
                gas = analogRead(gasinput);
                if (gas>150)
               {
                 while ( fire<300 && gas>170)
                 {
                   lcd.clear();
                   lcd.setCursor(0,1);
                   lcd.print(" FIRE & GAS");
                   lcd.setCursor(0,0);
                   lcd.print("Alert !!!");
                   String sensorData = String(ldr) + "," + String(temp) + "," + String(1112) + "," + String(0000);
                   Serial.println(sensorData);
                   delay(150);
                   digitalWrite(10,HIGH);
                   fire = analogRead(fireinput);
                   gas = analogRead(gasinput);
                   lcd.clear();
                   delay(150);
                   digitalWrite(10,LOW);
                   ldrtemp();
                   c++ ;
                    if (c>=30)
                    {
                      digitalWrite(A5,LOW);
                    }
                
                  }
               }
             }            // for iot based system we need to serial write here
           }
         
        }

        else  
        {  if (b <150 && b>100)
          {    
           lcd.setCursor(0,0);
           lcd.print("NO FIRE detected");
           lcd.setCursor(0,1);
           lcd.print("water off");
           
          }
         digitalWrite(9,LOW);
        }
      
       // program for gas sensor
       gas = analogRead(gasinput);
     //  Serial.print("gas sensor");
     //  Serial.println(gas);       
        if (gas>270)
        {
          while (gas>270)
         {
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("GAS leaking");
           lcd.setCursor(0,1);
           lcd.print("Alert  ! ! ");
           digitalWrite(10,LOW);
           String sensorData = String(ldr) + "," + String(temp) + "," + String(1111) + "," + String(fire);
           Serial.println(sensorData);
           delay(225);
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print("GAS leaking");
           delay(500);
           lcd.setCursor(0,1);
           lcd.print("Alert   ! !");
           digitalWrite(10,LOW);
           delay(225); 
           ldrtemp();          
           gas = analogRead(gasinput);
           fire = analogRead(fireinput);
           if (fire <300)
            { 
              digitalWrite(9,LOW);
              while ( fire<300 && gas>170)
             {
               lcd.setCursor(0,0);
               lcd.print(" FIRE & GAS");
               lcd.setCursor(0,1);
               lcd.print("Alert !!!");
               digitalWrite(10,HIGH);
               digitalWrite(10,HIGH);
               String sensorData = String(ldr) + "," + String(temp) + "," + String(1111) + "," + String(0000);
               Serial.println(sensorData);
               delay(150);
               fire = analogRead(fireinput);
               gas = analogRead(gasinput);
               lcd.clear();
               digitalWrite(10,LOW);
               delay(150);
               ldrtemp();
                 c++ ;
                    if (c>=30)
                    {
                      digitalWrite(A5,LOW);
                    }
             }                // for iot based we need to write serial write for node mcu here aleart
            }
          }
        }
        else
        { 
          if (b <= 200  && b>150)
          {
            lcd.setCursor(0,0);
            lcd.print("GAS");
            lcd.setCursor(0,1);
            lcd.print("not leaking");
           
          }
          digitalWrite(10,HIGH);        
        }
        b++;
        if (b>200)
         {
           b = 0 ;
         }
         
                                       
  }   
        String sensorData = String(ldr) + "," + String(temp) + "," + String(gas) + "," + String(fire);
        Serial.println(sensorData);
        delay (100);  // a litle delay so that it easily send the data

     

 }
