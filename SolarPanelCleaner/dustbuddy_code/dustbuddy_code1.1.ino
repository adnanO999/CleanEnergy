#include <SoftwareSerial.h>
#include <Wire.h>


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
float x_angle = 0;
float y_angle = 0;
float z_angle = 0;

#define IRF1 33
#define IRF2 32
#define IRB1 31
#define IRB2 30

#define Pin_D1_L1  22
#define Pin_D2_L1  23
#define Pin_E_L1   9
#define Pin_D1_L2  24
#define Pin_D2_L2  25
#define Pin_E_L2   8

int count = 0;
int pump = 0;
int statePump = 0;
unsigned long prevTime = 0;
const long  delayON = 3000;
const long  delayOFF = 4000;

#define brushPin1 27
#define brushPin2 26
#define brushPWM 6

#define pumpPin1 27
#define pumpPin2 26
#define pumpPWM 6

# define TxD 11
# define RxD 10
SoftwareSerial BlueTooth (TxD,RxD);
char BT_input;

float Xval = 0;
float Yval1 = 0;
float Yval2 = 0;

void setup() {
  ////////////ACCELEROMETER GYROSCOPE//////////////
  Serial.begin(115200);
  while (!Serial)
    delay(10); // 

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  
  
  delay(100);

//////////////////////////////////////////////////////////

  BlueTooth.begin(115200);  
  Serial.begin(115200);
  
  pinMode (IRF1, INPUT);
  pinMode (IRF2, INPUT);
  pinMode (IRB1, INPUT);
  pinMode (IRB2, INPUT);
  pinMode (Pin_D1_L1, OUTPUT);
  pinMode (Pin_D2_L1, OUTPUT);
  pinMode (Pin_E_L1, OUTPUT);
  pinMode (Pin_D1_L2, OUTPUT);
  pinMode (Pin_D2_L2, OUTPUT);
  pinMode (Pin_E_L2, OUTPUT);
  motor_stop1();
  motor_stop2();

  
  Serial.begin(9600);  
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets();

  initialize();

}

void loop() {
if (Serial.available())
  {
    String  Command = Serial.readString();
    if (Command == "Forward")
    {
      //Move Forward
      motor_CW1();
      motor_CW2();
    }
    else if (Command == "Backward")
    {
      //Move backward
     motor_CCW1()
     motor_CCW2()
    }
    else if (Command == "Left")
    {
      motor_CW1();
      motor_CCW2()
    }
    else if (Command == "Right")
    {
      motor_CCW1()
      motor_CW2();
    }
    
    if (Command == "Pump")
    {
      motorPump_ON();
    }
    if (Command == "Brush")
    {
      if (brushPin1 == HIGH){
        digitalWrite(brushPin1, LOW);
      }
      else if (brushPin1 == LOW){
        digitalWrite(brushPin1, HIGH);
        analogWrite(brushPWM, 250);
      }
    }
    if (Command = "Stop"){
        motor_stop1();
        motor_stop2();
    }
  }
}
}

void initialize(){
  Serial.begin(9600);
  int SF1 = digitalRead (IRF1);
  int SF2 = digitalRead (IRF2);
  int SB1 = digitalRead (IRB1);
  int SB2 = digitalRead (IRB2);

  motor_CCW1();
  motor_CCW2();
  while(SB1 == 0 || SB2 == 0){
     SB1 = digitalRead (IRB1);
     SB2 = digitalRead (IRB2);
     Serial.println (SB1);
     Serial.println (SB2);
    delay(500);
  }
  
  Serial.println (SB1);
  Serial.println (SB2);
  motor_stop1();
  motor_stop2();
  delay(1000);
  motor_CW1();
  motor_CW2();
  delay(1200);
  motor_stop1();
  motor_stop2();

  Serial.begin(9600);  
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets();


  float y = YaccValue();
  Xval = XaccValue()+ 90;


  if( y > 10){
    Yval1 = y;
    Yval2 = 0-y;
    path1();
  }else {
    Yval2 = y;
    Yval1 = 0-y;
    path2();
  }
  
}


void path1(){

  int SF1 = digitalRead (IRF1);
  int SF2 = digitalRead (IRF2);

  SF1 = digitalRead (IRF1);
  SF2 = digitalRead (IRF2);
  motor_CW1();
  motor_CW2();
  motorBrush_ON();
  pump = 1;
  pumpWater();

  
  while(SF1 == 0 || SF2 == 0 ){
   SF1 = digitalRead (IRF1);
   SF2 = digitalRead (IRF2);  
   delay(150);
  }

  pump = 0;

  motor_stop1();
  motor_stop2();
  motorBrush_OFF();
  delay(800);
  motor_CCW1();
  motor_CCW2();
  delay(6000);
  motor_stop1();
  motor_stop2();
  delay(800);
  float x = XaccValue();
  motor_CW2();
  while(x < Xval){
    x = XaccValue();
    delay(7); 
  }
  motor_stop2();
  motor_stop1();
  delay(800);

  motor_CW1();
  motor_CW2();

  SF1 = digitalRead (IRF1);
  SF2 = digitalRead (IRF2);
  count = 0;
  
  while( (SF1 == 0 || SF2 == 0)  && count < 10){
 
   SF1 = digitalRead (IRF1);
   SF2 = digitalRead (IRF2); 
   count += 1;  
   delay(150);
  
  }  
  
  motor_stop1();
  motor_stop2();
  
 if(SF1 == 1 && SF2 == 1){
    done();
  }else{
    motor_CCW1();
    motor_CCW2();
    delay(1500);
    motor_stop1();
    motor_stop2();
    delay(600);

    float y = YaccValue();
    motor_CW2();
    while (y > Yval2){
      y = YaccValue();
      delay(7);
    }
    
    motor_stop2();
    delay(600);
    motor_CCW1();
    motor_CCW2();
    delay(3000);
    motor_stop1();
    motor_stop2();
    
    path2();
  }

 
}


void path2(){

  int SF1 = digitalRead (IRF1);
  int SF2 = digitalRead (IRF2);

  SF1 = digitalRead (IRF1);
  SF2 = digitalRead (IRF2);
  motor_CW1();
  motor_CW2();
  motorBrush_ON();
  pump = 1;
  pumpWater();

  
  while(SF1 == 0 || SF2 == 0 ){
   SF1 = digitalRead (IRF1);
   SF2 = digitalRead (IRF2);  
   delay(150);
  }

  pump = 0;

  motor_stop1();
  motor_stop2();
  motorBrush_OFF();
  delay(800);
  motor_CCW1();
  motor_CCW2();
  delay(6000);
  motor_stop1();
  motor_stop2();
  delay(800);
  float x = XaccValue();
  motor_CW1();
  while(x < Xval){
    x = XaccValue();
    delay(7); 
  }
  motor_stop2();
  motor_stop1();
  delay(800);

  motor_CW1();
  motor_CW2();

  SF1 = digitalRead (IRF1);
  SF2 = digitalRead (IRF2);
  count = 0;
  
  while( (SF1 == 0 || SF2 == 0)  && count < 10){
 
   SF1 = digitalRead (IRF1);
   SF2 = digitalRead (IRF2); 
   count += 1;  
   delay(150);
  
  }  
  
  motor_stop1();
  motor_stop2();
  
 if(SF1 == 1 && SF2 == 1){
    done();
  }else{
    motor_CCW1();
    motor_CCW2();
    delay(1500);
    motor_stop1();
    motor_stop2();
    delay(600);

    float y = YaccValue();
    motor_CW1();
    while (y > Yval1){
      y = YaccValue();
      delay(7);
    }
    
    motor_stop1();
    delay(600);
    motor_CCW1();
    motor_CCW2();
    delay(3000);
    motor_stop1();
    motor_stop2();
    
    path1();
  }

 
}


void done(){

  int SB1 = digitalRead (IRB1);
  int SB2 = digitalRead (IRB2);
  Serial.println("in done");
  motor_CCW1();
  motor_CCW2();
  while(SB1 == 0 || SB2 == 0){
   SB1 = digitalRead (IRB1);
   SB2 = digitalRead (IRB2);
   delay(150);
  }  
  motor_stop1();
  motor_stop2();
}



//////////////////////////////////////////////////////////////
void motorBrush_OFF(){
  digitalWrite(brushPin1, LOW);
  digitalWrite(brushPin2, LOW);
  analogWrite(brushPWM, 0);
}
void motorBrush_ON(){
  digitalWrite(brushPin1, HIGH);
  digitalWrite(brushPin2, LOW);
  analogWrite(brushPWM, 250);
}

void motor_stop1(){
  digitalWrite(Pin_D1_L1, LOW);
  digitalWrite(Pin_D2_L1, LOW);
  analogWrite(Pin_E_L1, 0);
}

void motor_stop2(){
  digitalWrite(Pin_D1_L2, LOW);
  digitalWrite(Pin_D2_L2, LOW);
  analogWrite(Pin_E_L2, 0);
}

void motor_CW1(){
  analogWrite(Pin_E_L1, 200);
  digitalWrite(Pin_D1_L1, HIGH);
  digitalWrite(Pin_D2_L1, LOW);  
}
void motor_CW2(){
  analogWrite(Pin_E_L2, 200);
  digitalWrite(Pin_D1_L2, HIGH);
  digitalWrite(Pin_D2_L2, LOW);  
}
void motor_CCW1(){
  analogWrite(Pin_E_L1, 200);
  digitalWrite(Pin_D1_L1, LOW);
  digitalWrite(Pin_D2_L1, HIGH);  
}
void motor_CCW2(){
  analogWrite(Pin_E_L2, 200);
  digitalWrite(Pin_D1_L2, LOW);
  digitalWrite(Pin_D2_L2, HIGH);  
}

float XaccValue(){
  mpu.update();  
  return mpu.getAngleX();  
}
float YaccValue(){
  mpu.update();  
  return mpu.getAngleY();  
}
float ZaccValue(){
  mpu.update();  
  return mpu.getAngleZ();  
}

void motorPump_OFF(){
  digitalWrite(pumpPin1, LOW);
  digitalWrite(pumpPin2, LOW);
  analogWrite(pumpPWM, 0);
  statePump = 0;
}
void motorPump_ON(){
  digitalWrite(pumpPin1, HIGH);
  digitalWrite(pumpPin2, LOW);
  analogWrite(pumpPWM, 250);
  statePump = 1;
}

void pumpWater(){

  motorPump_ON();

  while(statePump == 1){
    if(millis() - prevTime >= delayON){
       Serial.println("motor will turn off");
       motorPump_OFF();
       prevTime = millis();
    }
   }
 while(statePump == 0) {
    if(millis() - prevTime >= delayOFF){
      Serial.println("motor will turn on");
      prevTime = millis();
      
      
      if(pump == 1)
      pumpWater();
    } 
  }
  Serial.println(millis());
}
