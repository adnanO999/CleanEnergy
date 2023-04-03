
#define enA 9
#define in1 6
#define in2 7



int state = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
    analogWrite(enA, 255);
    
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

   
