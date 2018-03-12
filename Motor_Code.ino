#include <Stepper.h>
boolean speedin = A3;
int pin1 = 8;
int pin2 = 9;
int pin3 = 10;
int pin4 = 11;
int low = "0";
int high ="0";

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (speedin < 3){
    closed();
  }
  else if (speedin >= 3){
    forward(); 
  }
  else if (speedin >= 6){
    backward();
  }
}

void closed(){
  digitalWrite(pin1, low);
  digitalWrite(pin2, low);
  digitalWrite(pin3, low);
  digitalWrite(pin4, low);
}
void forward(){
switch(
  case{
  digitalWrite(pin1, high);
  digitalWrite(pin2, low);
  digitalWrite(pin3, low);
  digitalWrite(pin4, low);
   break;
  }
  case{
  digitalWrite(pin1, low);
  digitalWrite(pin2, high);
  digitalWrite(pin3, low);
  digitalWrite(pin4, low);
  break;
  }
  case{
  digitalWrite(pin1, low);
  digitalWrite(pin2, low);
  digitalWrite(pin3, high);
  digitalWrite(pin4, low); 
  break;
  }
  case{
  digitalWrite(pin1, low);
  digitalWrite(pin2, low);
  digitalWrite(pin3, low);
  digitalWrite(pin4, high);
  break;
   }
)
}
void backward(){
  switch(
  case {
  digitalWrite(pin1, low);
  digitalWrite(pin2, low);
  digitalWrite(pin3, low);
  digitalWrite(pin4, high);
   break;
   }
  case {
  digitalWrite(pin1, low);
  digitalWrite(pin2, low);
  digitalWrite(pin3, high);
  digitalWrite(pin4, low);
   break;
  }
  case {
  digitalWrite(pin1, low);
  digitalWrite(pin2, high);
  digitalWrite(pin3, low);
  digitalWrite(pin4, low);
   break;
  }
  case {
  digitalWrite(pin1, high);
  digitalWrite(pin2, low);
  digitalWrite(pin3, low);
  digitalWrite(pin4, low);
   break;
  }
)
}

