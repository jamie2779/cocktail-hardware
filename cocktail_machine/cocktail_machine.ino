
#include <ctype.h>
#include <WiFi.h>
#include <WebSocketsClient.h>

const char* ssid = "cocktail";
const char* password = "87654321";
const char* websocket_server = "cocktailmaker.kro.kr"; // 서버의 IP 주소 또는 도메인
const int websocket_port = 80; // 웹소켓 서버의 포트 (기본값 80)
const char* websocket_path = "/api/socket"; // 웹소켓 엔드포인트 경로

WebSocketsClient webSocket;

//좌우
int STEP1 = 14;
int DIR1 = 27;

int BTN1 = 26; //좌우
int BTN2 = 25; //상하

//상하
int STEP2 = 33;
int DIR2 = 32;

int now = 0;

void initHorizontalAxis() {
  // 방향 설정: 버튼이 눌리는 방향으로 이동
  digitalWrite(DIR1, LOW);
  
  // 버튼이 눌릴 때까지 무한루프
  while(digitalRead(BTN1) == 1) { 
    // 한 스텝 이동
    digitalWrite(STEP1, HIGH); 
    delayMicroseconds(700); 
    digitalWrite(STEP1, LOW); 
    delayMicroseconds(700); 
  }
  now = 0;
  // 버튼이 눌려서 루프를 탈출하면, 스텝 출력 LOW 유지
  digitalWrite(STEP1, LOW);
}

void initVerticalAxis() {
  // 방향 설정: 버튼이 눌리는 방향으로 이동
  digitalWrite(DIR2, HIGH);
  
  // 버튼이 눌릴 때까지 무한루프
  while(digitalRead(BTN2) == 1) { 
    // 한 스텝 이동
    digitalWrite(STEP2, HIGH); 
    delayMicroseconds(700); 
    digitalWrite(STEP2, LOW); 
    delayMicroseconds(700); 
  }

  // 버튼이 눌려서 루프를 탈출하면, 스텝 출력 LOW 유지
  digitalWrite(STEP2, LOW);
}

void forward(int spin){
  Serial.println("forward" + String(spin));
  digitalWrite(DIR1, HIGH);
  for(int i=0;i<spin;i++) { 
    digitalWrite(STEP1, HIGH); 
    delayMicroseconds(700); 
    digitalWrite(STEP1, LOW); 
    delayMicroseconds(700); 
  }
  // 정지
  digitalWrite(STEP1, LOW);
}

void backward(int spin){
  Serial.println("backward" + String(spin));
  digitalWrite(DIR1, LOW);
  for(int i=0;i<spin;i++) { 
    digitalWrite(STEP1, HIGH); 
    delayMicroseconds(700); 
    digitalWrite(STEP1, LOW); 
    delayMicroseconds(700); 
  }
  // 정지
  digitalWrite(STEP1, LOW);
}

void goLiquor(int num){
  delay(500);
  initVerticalAxis();
  if(num == 0){
    initHorizontalAxis();
    now = 0;
    return;
  }
  if(now == num || num<0 || num > 6) return;
  if(now == 0){
    forward(num * 500 + 110);
  }
  else if(num>now){
    forward((num - now) * 500);
  }
  else if(num<now){
    backward((now - num) * 500);
  }
  now = num;
  return;
}

void press(){
  // 방향 설정: 버튼이 눌리는 방향으로 이동
  digitalWrite(DIR2, LOW);
  for(int i=0;i<3000;i++){
    digitalWrite(STEP2, HIGH); 
    delayMicroseconds(700); 
    digitalWrite(STEP2, LOW); 
    delayMicroseconds(700); 
  }
  //정지
  digitalWrite(STEP2, LOW);

  delay(3000);
  initVerticalAxis();
  delay(1000);
}


void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("❌ 소켓 연결 해제");
      break;
    case WStype_CONNECTED:
      Serial.println("🔗 소켓 연결됨");
      webSocket.sendTXT("connect");
      break;
    case WStype_TEXT:
      webSocket.sendTXT("working");
      Serial.printf("📥 서버 메시지: %s\n", payload);
      for(int i =0; i<strlen((char *) payload);i++){
        if(isdigit(payload[i])){
            int command = payload[i]-'0';
            if(command>=0 && command <= 6){
              goLiquor(command);
          }else if(command == 7){
            press();
          }
        }
      }
      webSocket.sendTXT("idle");
      break;
    case WStype_ERROR:
      Serial.println("⚠️ 에러 발생");
      break;
  }
}

void setup() {
  //버튼 핀모드 설정
  pinMode(BTN1,INPUT);
  pinMode(BTN2,INPUT);

  pinMode(STEP1,OUTPUT);
  pinMode(DIR1,OUTPUT);
  
  pinMode(STEP2,  OUTPUT);
  pinMode(DIR2,OUTPUT);



  initVerticalAxis();
  initHorizontalAxis();
  Serial.println("Horizontal axis initialized.");

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("📡 Wi-Fi 연결 중...");
  }
  Serial.println("✅ Wi-Fi 연결 완료!");

  webSocket.begin(websocket_server, websocket_port, websocket_path);
  webSocket.onEvent(webSocketEvent);

}



void loop() {
    webSocket.loop();
  // 시리얼에 데이터가 들어왔는지 확인
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int command = input.toInt();

    if(command>=0 && command <= 6){
      goLiquor(command);
    }else if(command == 7){
      press();
    }
  }

}

