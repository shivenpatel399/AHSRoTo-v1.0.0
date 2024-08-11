const int E1 = 3; ///<Motor1 Speed
const int E2 = 11;///<Motor2 Speed
const int E3 = 5; ///<Motor3 Speed
const int E4 = 6; ///<Motor4 Speed

const int M1 = 4; ///<Motor1 Direction
const int M2 = 12;///<Motor2 Direction
const int M3 = 8; ///<Motor3 Direction
const int M4 = 7; ///<Motor4 Direction


void M1_advance(char Speed) { ///<Motor1 Advance 
  digitalWrite(M1,LOW);
  analogWrite(E1,Speed);
}

void M2_advance(char Speed) { ///<Motor2 Advance 
  digitalWrite(M2,HIGH);
  analogWrite(E2,Speed);
}

void M3_advance(char Speed) { ///<Motor3 Advance
  digitalWrite(M3,LOW);
  analogWrite(E3,Speed);
}

void M4_advance(char Speed) { ///<Motor4 Advance
  digitalWrite(M4,HIGH);
  analogWrite(E4,Speed);
} 


void M1_back(char Speed) {///<Motor1 Back off
  digitalWrite(M1,HIGH);
  analogWrite(E1,Speed);
}

void M2_back(char Speed) { ///<Motor2 Back off
  digitalWrite(M2,LOW);
  analogWrite(E2,Speed);
}

void M3_back(char Speed) { ///<Motor3 Back off
  digitalWrite(M3,HIGH);
  analogWrite(E3,Speed);
}

void M4_back(char Speed) { ///<Motor4 Back off
  digitalWrite(M4,LOW);
  analogWrite(E4,Speed);
} 

void ForwardPlus() {
  M1_advance(100);
  M3_back(100);
  delay(2000); ///<Delay 2S
  M1_advance(0);
  M3_advance(0);
  delay(2000); ///<Delay 2S
}
 
void RightPlus() {
  M2_advance(100);
  M4_back(100);
  delay(2000); ///<Delay 2S
  M2_advance(0);
  M4_advance(0);
  delay(2000); ///<Delay 2S
}

void stopWait() {
  M1_advance(0);
  M2_advance(0);
  M3_advance(0);
  M4_advance(0);
  delay(5000); ///<Delay 2S
}

void forwardX() {
  M1_advance(100);
  M2_back(100);
  M3_back(100);
  M4_advance(100);
  delay(2000);
  M1_advance(0);
  M2_back(0);
  M3_back(0);
  M4_advance(0);
  delay(2000);
}
void setup() {
  for(int i=3;i<9;i++)
    pinMode(i,OUTPUT);
  for(int i=11;i<13;i++)
    pinMode(i,OUTPUT);
  stopWait();
  RightPlus();
  ForwardPlus();
} 

void loop() {
  // put code here
} 