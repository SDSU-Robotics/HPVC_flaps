const int hallPin = 2;     // the number of the hall effect pin
const int breakpin = 3;

volatile unsigned int lasttime = 0, currenttime = 0;
unsigned int timechange = 0;
volatile bool updated = false;
unsigned int position = 0; //position of the flap
double speed;


const double K = 1.0; // coeffecient for speed^2

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(hallPin, INPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt (2), pin_ISR, RISING);
  Serial.begin(115200);
}

void loop() {

  if (digitalRead(breakpin) == HIGH)
  {
    position = 0;
  }
  else if (updated) // only update if there is a new value
  {
    timechange = currenttime - lasttime;
    updated = false;
    speed = 1000.0 / timechange;
    position = K * speed * speed;
  }
  Serial.println(position);
}

void pin_ISR() {

  lasttime = currenttime;
  currenttime = millis();
  
  updated = true;
}
