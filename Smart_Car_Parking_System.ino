#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  
#include <Servo.h> 

Servo myservo1;

int ir1 = 1;
int ir2 = 2;

int slots = 5;          

int flag1 = 0;
int flag2 = 0;

void setup()
{
  lcd.begin();
  lcd.backlight();
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  
  myservo1.attach(3);
  myservo1.write(100);

  lcd.setCursor (0,0);
  lcd.print("     SMART    ");
  lcd.setCursor (0,1);
  lcd.print(" PARKING SYSTEM ");
  delay (2000);
  lcd.clear();  
}

void loop()
{ 

  if(digitalRead (ir1) == LOW && flag1==0)
  {
     if(Slot>0)
     {flag1=1;
      if(flag2==0)
        {myservo1.write(0); 
         slots = slots-1;
        }
     } 
  else{
    lcd.setCursor (0,0);
    lcd.print("    SORRY :(    ");  
    lcd.setCursor (0,1);
    lcd.print("  Parking Full  "); 
    delay (3000);
    lcd.clear(); 
    }
  }

  if(digitalRead (ir2) == LOW && flag2==0)
  { flag2=1;
    if(flag1==0)
    {
      myservo1.write(0); 
      slots = slots+1;
    }
  }

  if(flag1==1 && flag2==1)
  {
    delay (1000);
    myservo1.write(100);
    flag1=0, flag2=0;
  }

lcd.setCursor (0,0);
lcd.print("    WELCOME!    ");
lcd.setCursor (0,1);
lcd.print("Slots Left: ");
lcd.print(slots);
}
