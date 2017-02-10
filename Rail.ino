
#include <LiquidCrystal.h>
#include <MD_AButton.h>
#include <multiCameraIrControl.h>

// LCD pin definitions
#define  LCD_KEYS  KEY_ADC_PORT // use default pin

LiquidCrystal	lcd(8, 9, 4, 5, 6, 7);
MD_AButton		lcdButton(LCD_KEYS);	

Canon D5(12); // ir led pin 
int photoCount = 1;
int stepMode=0;
int exposure=1;
char* states[]={"Photo Count     ", "Step Length      ","Exposure        ", "Move Forward    ",
"Move Backward   ","Start Shoot    "};

char* steps[]={"1/8 step  ", "1/4 step  ", "Half Step",
"Full Step"};

int state=0;

  void stepChooser(){
  char  a=stepMode;
  
  switch (a) {
      case 0:
         Serial.println("1/8 step    ");
         digitalWrite(A2, HIGH);
         digitalWrite(A1, HIGH);     
         break;
         
      case 1:
         Serial.println("1/4 step    ");
         digitalWrite(A2,LOW);
         digitalWrite(A1, HIGH);    
         break;
         
      case 2:
         Serial.println("Half step    ");
         digitalWrite(A2,HIGH);
         digitalWrite(A1, LOW);    
         break;
         
      case 3:
         Serial.println("Full step    ");
         digitalWrite(A2,LOW);
         digitalWrite(A1, LOW);    
         break;  }   
    }

/*
void sendInfraredSignal() {
  for(int i=0; i<16; i++) { 
    digitalWrite(irLED, HIGH);
    delayMicroseconds(11);
    digitalWrite(irLED, LOW);
    delayMicroseconds(11);
   } 
   delayMicroseconds(7330); 
   for(int i=0; i<16; i++) { 
     digitalWrite(irLED, HIGH);
     delayMicroseconds(11);
     digitalWrite(irLED, LOW);
     delayMicroseconds(11);
   }   
}

*/
 

void setup() 
{ 
  Serial.begin(9600);
  pinMode(A4, OUTPUT);     // direction
  pinMode(A3, OUTPUT);   // step
  pinMode(A2, OUTPUT);   // MS1
  pinMode(A1, OUTPUT);   // MS2
  //digitalWrite(A4, LOW);
  digitalWrite(A3, LOW);


  
  lcd.begin(16,2);
  lcd.clear();
  lcd.home();
  lcd.print("Macro Rail V 2.0");
  lcd.setCursor(0,1);
  delay(1050);
  lcd.clear();
 
}


void loop() 
{
  char	c = lcdButton.getKey();


  lcd.home();
  lcd.print(states[state]);
 if(state==0){lcd.setCursor(0,1);lcd.print(photoCount);lcd.print("   Photos    ");};
 if(state==1){lcd.setCursor(0,1);lcd.print(steps[stepMode]);lcd.print("         ");};
 if(state==2){lcd.setCursor(0,1);lcd.print(exposure);lcd.print("  second       ");;};
 if(state==3){lcd.setCursor(0,1);lcd.print(steps[stepMode]);lcd.print("         ");};
 if(state==4){lcd.setCursor(0,1);lcd.print(steps[stepMode]);lcd.print("         ");};
 if(state==5){lcd.setCursor(0,1);lcd.print(photoCount);lcd.print("p ");lcd.print(exposure);lcd.print("e ");lcd.print(steps[stepMode]); };

 
 
  if(c=='D'&&state<=4){
      state+=1;      
    };
  if(c=='U'&&state>=1){
      state-=1;      
    };
    
    
   if(c=='R'&&state==0){
      photoCount+=1; 
      lcd.setCursor(0,1);lcd.print(photoCount);
    };
   if(c=='L'&&state==0&&photoCount>1){
      photoCount-=1; 
      lcd.setCursor(0,1);lcd.print(photoCount);
    };

    

  if(c=='R'&&state==1&&stepMode<=2){
      stepMode+=1; 
      lcd.setCursor(0,1);lcd.print(steps[stepMode]);
    };
   if(c=='L'&&state==1&&stepMode>0){
      stepMode-=1; 
      lcd.setCursor(0,1);lcd.print(steps[stepMode]);
    };

   if(c=='R'&&state==2){
      exposure+=1; 
      lcd.setCursor(0,1);lcd.print(exposure);lcd.print("  second");
    };
   if(c=='L'&&state==2&&exposure>1){
      exposure-=1; 
      lcd.setCursor(0,1);lcd.print(exposure);lcd.print("  second");
    };


    if(c=='S'&&state==4){

      digitalWrite(A4,LOW);
      stepChooser();
      // for (int i=0; i <= 10; i++){
      
        digitalWrite(A3, HIGH);
       delay(5);          
       digitalWrite(A3, LOW); 
       delay(5);
     //   }
      
      };

 if(c=='S'&&state==3){
      
      stepChooser();
        digitalWrite(A4,HIGH);
      // for (int i=0; i <= 10; i++){      
       digitalWrite(A3, HIGH);
       delay(5);          
       digitalWrite(A3, LOW); 
       delay(5);
      //  }
      
      };  
    
  if(c=='S'&&state==5){
    lcd.clear();
    lcd.home();
    lcd.print("Shooting...");    
    stepChooser();
    digitalWrite(A4,HIGH);
    for (int i=0; i <=photoCount; i++){
    D5.shutterNow();      
    digitalWrite(A3, HIGH);
    delay(5);          
    digitalWrite(A3, LOW); 
    delay(1000*exposure);
        }    
    };
  
    delay(100);
  
 
 
}
