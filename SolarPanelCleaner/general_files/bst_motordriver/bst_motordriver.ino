#define Pin1_D1_L  22 //lpwm 1
#define Pin1_D2_L  23 //rpwm 1
#define Pin1_E_L   9 //pwm enable 1

#define Pin2_D1_L  24 //lpwm 2
#define Pin2_D2_L  25 //rpwm 2
#define Pin2_E_L   8 //pwm enable 2

#define backIR1 30
#define backIR2 31
#define frontIR1 32
#define frontIR2 34



void setup()
{
  //attachInterrupt(digitalPinToInterrupt(18),motor1_stop,RISING);
  
  Serial.begin(9600);
  pinMode(Pin1_D1_L, OUTPUT);
  pinMode(Pin1_D2_L, OUTPUT);
  pinMode(Pin1_E_L, OUTPUT);
  motor1_stop();

  pinMode(Pin2_D1_L, OUTPUT);
  pinMode(Pin2_D2_L, OUTPUT);
  pinMode(Pin2_E_L, OUTPUT);
  motor2_stop();

  pinMode(frontIR1,INPUT);
  pinMode(frontIR2,INPUT);
  pinMode(backIR1,INPUT);
  pinMode(backIR2,INPUT);
  
}
////////////////////////MAIN PROGRAM////////////
void loop()
{
 // motor1_stop();   delay(1000);
 // motor1_cw();     
 // motor2_cw();     delay(3000);
 // motor1_stop();   delay(1000);
 // motor1_ccw();     delay(1000);

  boolean onPanelf1 = digitalRead(36);
  Serial.println(onPanelf1);
  delay(500);
  if(!onPanelf1){
    
    motor1_cw();
    motor2_cw();  
  }

  if(onPanelf1){
    motor1_stop();
    motor2_stop();  
  }
  
}
////////////MOTOR SECTION////////////
void motor1_cw()
{
  analogWrite(Pin1_E_L, 245);
  digitalWrite(Pin1_D1_L, HIGH);
  digitalWrite(Pin1_D2_L, LOW);
}

void motor1_ccw()
{
  analogWrite(Pin1_E_L, 255); //0-255
  digitalWrite(Pin1_D1_L, LOW);
  digitalWrite(Pin1_D2_L, HIGH);
}

void motor1_stop()
{
  digitalWrite(Pin1_D1_L, LOW);
  digitalWrite(Pin1_D2_L, LOW);
  analogWrite(Pin1_E_L, 0);
}
void motor2_cw()
{
  analogWrite(Pin2_E_L, 255);
  digitalWrite(Pin2_D1_L, HIGH);
  digitalWrite(Pin2_D2_L, LOW);
}

void motor2_ccw()
{
  analogWrite(Pin2_E_L, 255); //0-255
  digitalWrite(Pin2_D1_L, LOW);
  digitalWrite(Pin2_D2_L, HIGH);
}

void motor2_stop()
{
  digitalWrite(Pin2_D1_L, LOW);
  digitalWrite(Pin2_D2_L, LOW);
  analogWrite(Pin2_E_L, 0);
}

////////SENSOR SECTION/////////
boolean readSensor(int sensorPin){
  boolean onPanel = true;
  int sensorState = digitalRead(sensorPin);
  if(sensorState == 1){
    Serial.println(sensorState);
    onPanel = false;
  }
  return onPanel;
}
