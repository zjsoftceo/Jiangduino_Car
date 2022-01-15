/*==========================================================================
  // Author : Zhang Jiang Open Source Technology
  // Project : Intelligent obstacle avoidance for cars
  // Description : L298P Motor Shield and HC-SR04 For Arduino UNO R3 Demo
  // Source-Code : Jiangduino_Car.ino
  //==========================================================================
*/

int Buzz = 4;     //
int TrigPin = 5;      // trig pin of HC-SR04
int EchoPin = 6;     // Echo pin of HC-SR04
int Fsensor = 7;
int Esensor = 8;
int E1 = 10;
int M1 = 12;
int E2 = 11;
int M2 = 13;
int Fval, Eval;
float duration, distance;

void setup()
{
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(Buzz, OUTPUT);
  pinMode(TrigPin, OUTPUT);         // set trig pin as output
  pinMode(EchoPin, INPUT);
  pinMode(Fsensor, INPUT);
  pinMode(Esensor, INPUT);
}

void buzz0()
{
  digitalWrite(Buzz, LOW);
}

void buzz1()
{
  digitalWrite(Buzz, HIGH);
  delay(135);
  digitalWrite(Buzz, LOW);
  delay(135);
}

void measdist()
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(TrigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(EchoPin, HIGH); // receive reflected waves
  distance = duration / 58;   // convert to distance
}

void car_stop()
{
  digitalWrite(M1, LOW);
  analogWrite(E1, 0);
  buzz1();
}

void car_back()
{

  { int value;
    for (value = 0 ; value <= 255; value += 1)
    {
      digitalWrite(M1, LOW);
      analogWrite(E1, value);
    }
    buzz1();
  }
}

void car_up()
{
  { int value;
    for (value = 0 ; value <= 255; value += 1)
    {
      digitalWrite(M1, HIGH);
      analogWrite(E1, value);
    }
    buzz0();
  }
}


void Scr()
{
  measdist();
  Fval = digitalRead(Fsensor);
  Eval = digitalRead(Esensor);
  if (distance < 30 || Fval == 0 || Eval == 0)
  {
    car_stop();
    delay(500);
    measdist();
    car_up();
    car_stop();
    delay(500);
  }
  else
  {
    car_stop();
    delay(500);
    measdist();
    car_back();
    delay(500);

  }

}


void loop()
{


  Scr();


}


/*
  { int value;
  for(value = 0 ; value <= 255; value+=5)
  {
  digitalWrite(M1,HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, value);
  analogWrite(E2, value);
  delay(30);
  }

  delay(1000);}

  { int value;
  for(value = 0 ; value <= 255; value+=5)
  {
  digitalWrite(M1,LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, value);
  analogWrite(E2, value);
  delay(30);
  }
  delay(1000);}
  }
*/
