// CONSTANTS
const int MIN_POS = 250;     // minimum flap position
const int MAX_POS = 500;     // maximum flap position
const double EXP = 2;        // exponent
const double K = (MAX_POS - MIN_POS) / pow(2.895, EXP); // coeffecient for speed^EXP

// INTERNAL USE BELOW

const int hallPin = 2;       // hall effect pin
const int breakpin = 3;      // break button pin
const int DIR = 4;           // DIR stepper driver pin
const int PUL = 5;           // PUL stepper driver pin
const int activate_pin = 6;  // switch to enable/disable speed dependent flap control

int currentPos = 0;          // current position. Updated by stepUp and stepDown
int newPos = 0;              // new position move to

volatile unsigned int lasttime = 0, currenttime = 0;
unsigned int duration = 0;
volatile bool updated = false;
double speed = 0;            // speed in rev/sec

const int numReadings = 10;               // number of readings to average
int readings[numReadings] = { MIN_POS };  // the readings from the analog input
int readIndex = 0;                        // the index of the current reading
int total = MIN_POS * numReadings;        // the running total
int average = MIN_POS;                    // the average


void setup()
{
  // stepper driver outputs
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);

  // sensors and switches
  pinMode(hallPin, INPUT_PULLUP);
  pinMode(breakpin, INPUT_PULLUP);
  pinMode(activate_pin, INPUT_PULLUP);
  
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt (2), pin_ISR, RISING);
  Serial.begin(115200);

  // initialize location to MIN_POS
  setPosition(MIN_POS);
}

void loop()
{
  if (!digitalRead(breakpin))
  {
    setPosition(0);
  }
  else if (!digitalRead(activate_pin))
  {
    setPosition(MAX_POS);
  }
  else if (updated) // only update if there is a new value
  {
    // calculated speed
    duration = currenttime - lasttime;
    speed = 1000.0 / duration;

    // calculate new position
    newPos = K * pow(speed, EXP) + MIN_POS;

    // constrain position
    if (newPos > MAX_POS)
      newPos = MAX_POS;
    else if (newPos < MIN_POS)
      newPos = MIN_POS;

    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = newPos;
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }

    // calculate the average:
    average = total / numReadings;

    // constrain position
    if (average > MAX_POS)
      average = MAX_POS;
    else if (average < MIN_POS)
      average = MIN_POS;

    // move flaps
    setPosition(average);

    updated = false;
  }
}

void stepUp()
{
  // set direction
  digitalWrite(DIR, HIGH);

  // pulse driver
  digitalWrite(PUL, LOW);
  digitalWrite(PUL, HIGH);
  digitalWrite(PUL, LOW);

  delayMicroseconds(500);
  currentPos++;
}

void stepDown()
{
  // set direction
  digitalWrite(DIR, LOW);

  // pulse driver
  digitalWrite(PUL, LOW);
  digitalWrite(PUL, HIGH);
  digitalWrite(PUL, LOW);

  delayMicroseconds(500);
  currentPos--;
}

void setPosition(int pos)
{
  if (pos > currentPos)
  {
    int count = pos - currentPos;
    for (int i = 0; i < count; i++)
      stepUp();
  }
  else if (pos < currentPos)
  {
    int count = currentPos - pos;
    for (int i = 0; i < count; i++)
      stepDown();
  }
}

void pin_ISR() {
  lasttime = currenttime;
  currenttime = millis();
  updated = true;
}
