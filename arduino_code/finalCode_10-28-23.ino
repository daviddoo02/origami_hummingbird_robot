int motor1pin1 = 2;
int motor1pin2 = 3;

const int trigPin = 7;
const int echoPin = 8;

#include <Servo.h>
Servo myservo;

int pos = 0;
int angle_start = 100;
int angle_end = 45;

int angle_range = angle_start - angle_end;

float angle;

// Defining threshold values
int cm_thres = 55;  //cm   (change it as needed)



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, cm, cm_new;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);

    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  cm_new = microsecondsToCentimeters(duration);


/*
  Serial.print(cm);
  Serial.print("cm,");
  Serial.println();
*/
  
  if(cm <= cm_thres){
    if(abs(cm - cm_new) < 3){
      Move_bird(cm); 
      print_stuff(cm); 
    }
    //Serial.println("1");
    
  }

  else {Original();}



  delay(550);  //500 is cursed!!

}

void Original(){
  myservo.write(angle_start);
}

void print_stuff(float cm){
  angle = angle_end + (angle_range/cm_thres)*cm;

  Serial.print("At cm = ");
  Serial.print(cm);
  Serial.print(", Angle is: ");
  Serial.print(angle);
  Serial.println(".");

}

void Move_bird(float cm){
  angle = angle_end + (angle_range/cm_thres)*cm;
  myservo.write(angle);
  }

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;

  exit(0);
}







