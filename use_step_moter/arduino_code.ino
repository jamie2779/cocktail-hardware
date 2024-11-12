//스텝모터 사용법

int STEP = 8;
int DIR = 7;
boolean Button = true;

void setup(){
  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT);
  digitalWrite(DIR,HIGH);
  pinMode(2,INPUT);
}
void loop(){
  int Button = digitalRead(2);
  if(Button == 1){
    for(int x=0;x<200;x++){
      digitalWrite(STEP,HIGH);
      delayMicroseconds(700);
      digitalWrite(STEP,LOW);
      delayMicroseconds(700);
    }
    Button !=Button;
  }
  else{
    digitalWrite(STEP,LOW);
    digitalWrite(STEP,LOW);
  }
}