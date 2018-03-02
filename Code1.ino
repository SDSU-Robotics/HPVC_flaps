const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
volatile int buttonState = 0;         // variable for reading the pushbutton status
volatile unsigned int lasttime = 0, currenttime = 0;
unsigned int timechange = 0;
volatile bool updated = false;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR, RISING);
  Serial.begin(9600);
}

void loop() {
  if (updated) // only update if there is a new value
  {
    timechange = currenttime - lasttime;
    Serial.println(timechange);
    updated = false;
  }
}

void pin_ISR() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
  
  lasttime = currenttime;
  currenttime = millis();
  
  updated = true;
}
