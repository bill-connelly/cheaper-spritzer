#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Sensing Dial
const int analogInPin = A0;
int sensorValue, outputValue, skipLength;
String outputString;

//Sensing button press
const int  buttonPin = 8;
int buttonPushCounter = 0;   // counter for the number of button presses for deugging purposes
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

//Output behaviour
const int maxTime = 1000;
const int outputPin = 12;

void setup() {
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Puff Duration");

  pinMode(buttonPin, INPUT);
  pinMode(outputPin, OUTPUT);
  
  Serial.begin(9600); //for debugging purposes
}


void loop() {

  //See if button has been toggled from on to off. If so, trigger pulse

  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      digitalWrite(outputPin, HIGH);
      delay(outputValue); //using delay rather than a millis() counter. Simple. robust. Works.
      digitalWrite(outputPin, LOW);
    } else {

    }
  }
  lastButtonState = buttonState;
   
   
  //Code to display value 
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, maxTime, 0);
  outputString = String(outputValue);
  skipLength = outputString.length() + 5;

  lcd.setCursor(5,1);
  lcd.print(outputValue);
  lcd.setCursor(skipLength, 1);
  lcd.print(" ms   ");
  
  // debugging code
  Serial.print("button state: \t");
  Serial.print(buttonState);
  Serial.print("   lastButtonState: \t");
  Serial.println(lastButtonState);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);

  
}
