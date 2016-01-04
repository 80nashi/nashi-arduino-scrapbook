// http://forum.arduino.cc/index.php?topic=142113.0
//#include <Time.h>
// https://123d.circuits.io/circuits/1385661

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int baseLedPin = 8;    // 
const int numPins = 3;
const int ledPin =  13;      // the number of the LED pin

const int resetAfter = 300;  // reset the counter after this milli sec duration

int cnt = 0; // the rigo counter
int lastButtonMs = -1; // last time when the button was pressed
int pushed = 0; // 

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(baseLedPin, OUTPUT);
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
  doLed(min(cnt, numPins), HIGH);
}

void unlightLed() {
  logTime();
  Serial.println("LED cleared");
  cnt = 0;
  lastButtonMs = -1;
  doLed(numPins, LOW);
}

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
/* original
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    cnt++;
    Serial.print("time:");
    Serial.println(millis());
    Serial.print("cnt:");
    Serial.println(cnt);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    digitalWrite(redLedPin, LOW);
  }
  */
  
}