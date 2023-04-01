#include <Keypad_I2C.h> // I2C Keypad library by Joe Young https://github.com/joeyoung/arduino_keypads
#include <LiquidCrystal_I2C.h>  // I2C LCD Library by Francisco Malpartida https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home

#define lcd_addr 0x27     // I2C address of typical I2C LCD Backpack
#define keypad_addr 0x20  // I2C address of I2C Expander module (A0-A1-A2 dip switch to off position)

// LCD Pins to I2C LCD Backpack - These are default for HD44780 LCD's

// Create instance for LCD called: i2c_lcd
LiquidCrystal_I2C i2c_lcd(0x27,16,2);
String userDegree="";
String avbDegree="";
int i;
int longStep=0;
int longStep2=0;
bool userDeci = false;
unsigned long fMilis;
unsigned long sMilis;
char message[5];

// Define the keypad pins
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Keypad pins connected to the I2C-Expander pins P0-P6
byte rowPins[ROWS] = {0, 1, 2, 3}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7};    // connect to the column pinouts of the keypad

// Create instance of the Keypad name I2C_Keypad and using the PCF8574 chip
Keypad_I2C I2C_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, keypad_addr, PCF8574 );

const int STEP = 3;//for step signal
const int DIR = 2;//for direction

int avStep = 0;
int wStep=0;
int wDegreeCon=0;
int difStep=0;
int x = 400;
bool cont1 = false;
bool cont2 = false;

void setup() {
  Serial.begin(9600);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  i2c_lcd.begin (); //  our LCD is a 16x2, change for your LCD if needed     
  i2c_lcd.clear();      
  I2C_Keypad.begin();
  i2c_lcd.setCursor(0, 0);
  i2c_lcd.print("Position: 0" );
  i2c_lcd.setCursor(0, 1);
  i2c_lcd.print("Target: 0");
  i2c_lcd.setCursor(10,1);
  digitalWrite(DIR, 0);
  digitalWrite(STEP, 0);
  
}

void loop() {
  char key = I2C_Keypad.getKey();
  
  if(digitalRead(9)==0){
      if(avStep>0){
        longStep++;
        avStep--;
        cont1 = true;
        if(avStep%300==0){
          i2c_lcd.setCursor(10, 0);
          i2c_lcd.print(String(map(avStep,0,3200,0,360)) + "     ");
        }
        
        digitalWrite(DIR, 1);
        if(longStep<600){
          digitalWrite(STEP, HIGH);delayMicroseconds(600);digitalWrite(STEP, LOW);
        }
        else if(longStep>=600 && longStep<2000){
          digitalWrite(STEP, HIGH);delayMicroseconds(350);digitalWrite(STEP, LOW);
        }
        else{digitalWrite(STEP, HIGH);delayMicroseconds(50);digitalWrite(STEP, LOW);}
      fMilis = millis();
      }
  }
  else{
    longStep=0;
    if((millis()-fMilis)>2500 && cont1){
      cont1=false;
      i2c_lcd.setCursor(10, 0);
      i2c_lcd.print(String(map(avStep,0,3200,0,360))+ "      ");
    }
    }


  if(digitalRead(8)==0){
      longStep2++;
      avStep++;
      cont2 = true;
      if(avStep%300==0){
          i2c_lcd.setCursor(10, 0);
          i2c_lcd.print("       ");
          i2c_lcd.setCursor(10, 0);
          i2c_lcd.print(String(map(avStep,0,3200,0,360)));
        }
      digitalWrite(DIR, 0);
      if(longStep2<600){
        digitalWrite(STEP, HIGH);delayMicroseconds(600);digitalWrite(STEP, LOW);
      }
      else if(longStep2>=600 && longStep2<2000){
        digitalWrite(STEP, HIGH);delayMicroseconds(350);digitalWrite(STEP, LOW);
      }
      else{digitalWrite(STEP, HIGH);delayMicroseconds(50);digitalWrite(STEP, LOW);}
  }
  else{
    longStep2=0;
    if((millis()-fMilis)>2500 && cont2){
      cont2=false;
      i2c_lcd.setCursor(10, 0);
      i2c_lcd.print("       ");
      i2c_lcd.setCursor(10, 0);
      i2c_lcd.print(String(map(avStep,0,3200,0,360)));
    }
    }  

  switch (key) {
    case '1':
      userDegree += "1";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '2':
      userDegree += "2";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '3':
      userDegree += "3";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '4':
      userDegree += "4";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '5':
      userDegree += "5";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '6':
      userDegree += "6";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '7':
      userDegree += "7";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '8':
      userDegree += "8";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '9':
      userDegree += "9";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '0':
      userDegree += "0";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print(userDegree);
      break;

    case '*':
      userDegree="";
      i2c_lcd.setCursor(8,1);
      i2c_lcd.print("      ");
      i2c_lcd.setCursor(8,1);
      break;

    case '#':
      userDeci = true;
      break;

    case 'A':
      break;

    case 'B':
      break;

    case 'C':
      break;

    case 'D':
      break;

    }

    if(userDegree.length()==6){
        userDegree="";
        i2c_lcd.setCursor(8,1);
        i2c_lcd.print("      ");
        i2c_lcd.setCursor(8,1);
    }

    if(userDeci){
      i2c_lcd.clear();
      i2c_lcd.setCursor(0,0);
      i2c_lcd.print("    SENDING");
      i2c_lcd.setCursor(0,1);
      i2c_lcd.print("   ---->>>>");
      wStep = map((userDegree).toInt(),0,360,0,3200);
      difStep = wStep - avStep;

      if(difStep > 0){digitalWrite(DIR, 0);}
      else{digitalWrite(DIR, 1);}

    difStep = abs(difStep);
    //Serial.println(difStep);
    
    if(difStep<901){

      for(int i =0; i<abs(difStep); i++){digitalWrite(STEP, HIGH);delayMicroseconds(150);digitalWrite(STEP, LOW);}
    
    }


    else if(difStep>=901){
      
      for(int i =0; i<150; i++){digitalWrite(STEP, HIGH);delayMicroseconds(600);digitalWrite(STEP, LOW);}

      for(int i =0; i<300; i++){digitalWrite(STEP, HIGH);delayMicroseconds(300);digitalWrite(STEP, LOW);}

      for(int i =0; i<(difStep - 900); i++){digitalWrite(STEP, HIGH);delayMicroseconds(80);digitalWrite(STEP, LOW);}

      for(int i =0; i<300; i++){digitalWrite(STEP, HIGH);delayMicroseconds(300);digitalWrite(STEP, LOW);}

      for(int i =0; i<150; i++){digitalWrite(STEP, HIGH);delayMicroseconds(600);digitalWrite(STEP, LOW);}

    }
      avStep = wStep;
      userDeci=false;
      delay(400);
      i2c_lcd.clear();
      i2c_lcd.setCursor(0, 0);
      i2c_lcd.print("Position: 0" );
      i2c_lcd.setCursor(10, 0);
      i2c_lcd.print(userDegree);
      i2c_lcd.setCursor(0, 1);
      i2c_lcd.print("Target: 0");
      i2c_lcd.setCursor(8,1);
      userDegree="";
    }
    
}
