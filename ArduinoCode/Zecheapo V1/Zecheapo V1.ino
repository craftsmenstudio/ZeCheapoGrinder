

// SPI-Oled related headers
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//SPI oled related variables
#define OLED_WIDTH 128 // OLED display width, in pixels
#define OLED_HEIGHT 32 // OLED display height, in pixels
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
int switchPrevious=-1, rpmPrevious=-1;



void setup() {

  // put your setup code here, to run once:
  pinMode(4, INPUT_PULLUP);

  //Begin Serial
  Serial.begin(115200);
  Serial.println("ZeCheapo Initialising");

  
  //initialise Display 
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("Zecheapo");
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("V .1a");


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
    display.print("Motor OFF");
    display.display();
    switchPrevious=0;
    rpmPrevious=-1;

    }
    
  }

 // Detect and display ON state
  while(digitalRead(4)==1){

    //Read Potentiometer value and put inrange 25 to 200
    int sensorValue = map(analogRead(0),0,1023,25,200);
    if((rpmPrevious==-1)||(rpmPrevious!=sensorValue))
    {
    Serial.println("Motor on");
    Serial.println(sensorValue); // serial output RPM value
    //Display RPM on Oled
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("RPM: ");
    display.print(sensorValue);
    display.display();
    switchPrevious=1;
    rpmPrevious=sensorValue;
    delay(1);
    }
  }    
}
