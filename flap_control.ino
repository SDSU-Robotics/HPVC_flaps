const int DIR = 8;
const int PUL = 13;

int currentPos = 0;
int newPos = 0;

const int MAX_POS = 200;

const int hallPin = 2;     // the number of the hall effect pin
const int breakpin = 3;

volatile unsigned int lasttime = 0, currenttime = 0;
unsigned int duration = 0;
volatile bool updated = false;
double speed = 0;

const double K = 4.0; // coeffecient for speed^2

const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


void setup()
{
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(hallPin, INPUT_PULLUP);
  
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt (2), pin_ISR, RISING);
  Serial.begin(115200);
}

void loop()
{
  if (digitalRead(breakpin) == HIGH)
  {
    setPosition(0);
  }
  else if (updated) // only update if there is a new value
  {
    duration = currenttime - lasttime;
    speed = 1000.0 / duration;
    newPos = K * speed * speed;

    // constrain position
    if (newPos > MAX_POS)
      newPos = MAX_POS;
    else if (newPos < 0)
      newPos = 0;

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
    
    Serial.print("newPos: ");
    Serial.println(average);

    setPosition(average);

    updated = false;
  }
}

void stepUp()
{
  digitalWrite(DIR, HIGH);
  
  digitalWrite(PUL, LOW);
  digitalWrite(PUL, HIGH);
  digitalWrite(PUL, LOW);

  delayMicroseconds(500);
  currentPos++;
}

void stepDown()
{
  digitalWrite(DIR, LOW);
  
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
  /*int tempTime = millis();
  if (tempTime - lasttime > 30) // valid data
  {
    lasttime = currenttime;
    currenttime = tempTime;
    updated = true;
  }*/
  lasttime = currenttime;
  currenttime = millis();
  updated = true;
}
