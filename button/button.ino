void setup() {
  pinMode(26,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Button = digitalRead(26);
  Serial.println(Button);

}
