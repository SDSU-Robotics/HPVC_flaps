const int buttonPin = 2;     // the number of the pushbutton pin

// variables will change:
volatile unsigned int lasttime = 0, currenttime = 0;
unsigned int timechange = 0;
volatile bool updated = false;
unsigned int position = 0; //position of the flap

void setup() {
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
    updated = false;
    position = timechange*timechange;
    Serial.println(position);
  }
}

void pin_ISR() {
  
  lasttime = currenttime;
  currenttime = millis();
  
  updated = true;
}
