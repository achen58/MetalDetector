SENSOR CONTROL AND MOVEMENT
# define trigPin1 3 // Front Sensor 
# define echoPin1 8 // Front Sensor
# define trigPin2 4 // Right Sensor
# define echoPin2 7 // Right Sensor
# define leftforward 5
# define leftback 6
# define rightforward 10
# define rightback 11

double FrontSensor;
double RightSensor;
double duration;
double distance;
int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(leftforward, OUTPUT);
  pinMode(leftback, OUTPUT);
  pinMode(rightforward, OUTPUT);
  pinMode(rightback, OUTPUT);
  delay(1000);
} 

void drive_forward() {
  analogWrite(leftforward, 100);
  analogWrite(leftback, 0);

  analogWrite(rightforward, 120);
  analogWrite(rightback, 0);
}

void drive_backward() {
  analogWrite(leftforward, 0);
  analogWrite(leftback, 140);

  analogWrite(rightforward, 0);
  analogWrite(rightback, 140);
}

void turn_left() {
  analogWrite(leftforward, 0);
  analogWrite(leftback, 175);

  analogWrite(rightforward, 175);
  analogWrite(rightback, 0);
}

void turn_right() {
  analogWrite(leftforward, 175);
  analogWrite(leftback, 0);

  analogWrite(rightforward, 0);
  analogWrite(rightback, 175);
}

void drive_stop() {
  analogWrite(leftforward, 0);
  analogWrite(leftback, 0);

  analogWrite(rightforward, 0);
  analogWrite(rightback, 0);
}

void ReadSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/148;
}

void loop() {
  delay(500);
  ReadSensor(trigPin1,echoPin1);
  FrontSensor = distance;
  delay(100);
  ReadSensor(trigPin2,echoPin2);
  RightSensor = distance;
 
  Serial.print("Front: ");
  Serial.println(FrontSensor);
  Serial.print("Side: ");
  Serial.println(RightSensor);

  if ((FrontSensor < 8) && (RightSensor < 10)){ // Front = 1 , Right = 1
    drive_stop(); 
    delay(150);
    turn_left();
    delay(2075);
    drive_forward();
    delay(1050);
    counter = counter + 1;
  }
 /* else if ((FrontSensor < 4) && (RightSensor > 10)) { // Front = 1, Right = 0
   drive_stop();
   delay(100);
  }*/
  
  else if ((FrontSensor > 8) && (RightSensor < 10)) { // Front = 0 , Right = 1
   drive_forward();
  }
  
  else if ((FrontSensor > 8) && (RightSensor > 10)) { // Front = 0 ,  Right = 0
    //drive_forward();
    //delay(200);
    turn_right();
    delay(2075);
    drive_stop();
    delay(300);
    drive_forward();
    delay(2200);
  }
  
  else {
    drive_backward();
    delay(500);
  }

  if (counter == 8) {
    while(1) {
      delay(500);
      ReadSensor(trigPin1,echoPin1);
      FrontSensor = distance;
      if (FrontSensor < 8) {
        turn_left();
        delay(random(500,2075));
      }
      else {
        drive_forward();
        delay(5000);
      }
    }
  }
}
----------------------------------------------------------------------------------------------------------------------------------------
METAL DETECTOR 

# define LED1 9 
# define LED2 12
# define LED3 13
# define METALDETECT 2 

int metaldetectval = 0;
int METALCOUNTER = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  delay(1000);
}


void loop() {
  int metaldetectval = analogRead(A0); // read the input on analog pin 0:
  if (metaldetectval < 200) { // NOISE
    metaldetectval = 1000;
  }
  
  if ((METALCOUNTER == 0) && (metaldetectval < 500)) {
    METALCOUNTER = METALCOUNTER + 1;
    delay(5000);
  }
  
  else if ((METALCOUNTER == 1) && (metaldetectval < 500)) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    METALCOUNTER = METALCOUNTER + 1;
    delay(5000);
  }
  
  else if ((METALCOUNTER == 2) && (metaldetectval < 500)) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    METALCOUNTER = METALCOUNTER + 1;
    delay(5000);
  }

  else if ((METALCOUNTER == 3) && (metaldetectval < 500)) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    METALCOUNTER = METALCOUNTER + 1;
    delay(5000);
  }

  else if ((METALCOUNTER == 4) && (metaldetectval < 500)) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }

  Serial.print("MetalCounter : ");
  Serial.println(METALCOUNTER);
  Serial.print("Value : ");
  Serial.println(metaldetectval);
}

