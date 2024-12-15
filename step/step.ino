//스텝모터 사용법

int STEP = 33;
int DIR = 32;
int BTN = 25;
boolean Button = true;

void setup(){
    //시리얼모니터 시작
  Serial.begin(115200);

  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT);
  digitalWrite(DIR,HIGH);
  pinMode(BTN,INPUT);
}
void loop(){
  int Button = digitalRead(BTN);
  Serial.println(Button);
  if(Button == 0){
    digitalWrite(DIR,LOW);
    for(int x=0;x<200;x++){
      digitalWrite(STEP,HIGH);
      delayMicroseconds(700);
      digitalWrite(STEP,LOW);
      delayMicroseconds(700);
    }
    digitalWrite(STEP,LOW);
    digitalWrite(STEP,LOW);
    delay(2000);
    digitalWrite(DIR,HIGH);
    delayMicroseconds(100);
    for(int x=0;x<200;x++){
      digitalWrite(STEP,HIGH);
      delayMicroseconds(700);
      digitalWrite(STEP,LOW);
      delayMicroseconds(700);
    }
    digitalWrite(STEP,LOW);
    digitalWrite(STEP,LOW);
  }
}