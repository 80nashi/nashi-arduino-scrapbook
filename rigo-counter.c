// http://forum.arduino.cc/index.php?topic=142113.0
//#include <Time.h>
// https://123d.circuits.io/circuits/1385661

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int baseLedPin = 8;    // 
const int numLeds = 3;
const int speakerOut = basedLedPin + numLeds;
const int resetAfter = 300;  // reset the counter after this milli sec duration


int buttonState = 0;         // variable for reading the pushbutton status
int cnt = 0; // the rigo counter
int lastButtonMs = -1; // last time when the button was pressed
int pushed = 0; // 

void setup() {
  int i;
  Serial.begin(9600);
  // initialize the LED pins as output:
  for (i = 0; i < numLeds; i++) {
    pinMode(baseLedPin + i, OUTPUT);
  }
  pinMode(speakerOut, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}
void logTime() {
  Serial.print("time:");
  Serial.print(millis());
}

void doLed(int n, int lowhigh) {
  int i;
  for (i = 0; i < n; i++) {
    digitalWrite(baseLedPin + i, lowhigh);
  }
}

void lightLed() {
  int i;
  logTime();
  Serial.println("button pressed");
  Serial.println(cnt);
  doLed(min(cnt, numLeds), HIGH);
}

void unlightLed() {
  logTime();
  Serial.println("LED cleared");
  cnt = 0;
  lastButtonMs = -1;
  doLed(numLeds, LOW);
}

// https://www.arduino.cc/en/Tutorial/PlayMelody
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1/ditch-the-delay
void buzz() {
}

void loop() {
    
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // if expired, reset everything
  if (lastButtonMs > 0 && (millis() - lastButtonMs > resetAfter)) {
    unlightLed();
    return;
  }

  if (buttonState == HIGH) {
    if (!pushed) {
      // only increment cnt when pushed for the first time
      lastButtonMs = millis();
      cnt++;
      lightLed();
      buzz();
    }
    pushed = 1;
  } else {
    pushed = 0;
  }  
}