

// SPI-Oled related headers
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Stepper.h>

//SPI oled related variables
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
#define i2c_Address 0x3c

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 2,3);

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int switchPrevious=-1, rpmPrevious=-1;



void setup() {

  // put your setup code here, to run once:
  pinMode(4, INPUT_PULLUP);

  //Begin Serial
  Serial.begin(115200);
  Serial.println("ZeCheapo Initialising");

  
  //initialise Display 
  display.begin(i2c_Address, true); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  display.println("  Welcome");
 
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.println("");
  display.setTextSize(2);
  display.println("  Zecheapo");
  display.setTextSize(1);
  display.println("");
  //display.println("");
  display.println("   V.1a Initialising");


  display.display();
  delay(2000);


  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
  

}

void loop() {
  // put your main code here, to run repeatedly:
 
 // Detect and display Off state
  while(digitalRead(4)==0){
    if((switchPrevious==-1)||(switchPrevious==1)){
    Serial.println("Motor Off");
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println(" Zecheapo");
    display.println("");
    display.setTextSize(3);    
    display.print("  OFF");
    display.display();
    switchPrevious=0;
    rpmPrevious=-1;

    }
    
  }

 // Detect and display ON state
  while(digitalRead(4)==1){

    //Read Potentiometer value and put inrange 25 to 200
    int sensorValue = map(analogRead(0),0,1023,25,200);
    int motorSpeed = sensorValue;
     if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    // step 1/100 of a revolution:
    myStepper.step(stepsPerRevolution / 100);
  }
    if(((rpmPrevious==-1)||(rpmPrevious!=sensorValue))&&((sensorValue>1.5+rpmPrevious)||(sensorValue<rpmPrevious-1.5)))
    {
    Serial.println("Motor on");
    Serial.println(sensorValue); // serial output RPM value
    //Display RPM on Oled
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println(" Zecheapo");
    display.println("");
    display.setTextSize(3);    
    display.print("RPM:");
    display.display();
    display.print(sensorValue);
    display.display();
    switchPrevious=1;
    rpmPrevious=sensorValue;
    delay(1);
    }
  }    
}
