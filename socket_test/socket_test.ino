#include <WiFi.h>
#include <WebSocketsClient.h>

const char* ssid = "cocktail";
const char* password = "87654321";
const char* websocket_server = "211.194.248.245"; // 서버의 IP 주소 또는 도메인
const int websocket_port = 3000; // 웹소켓 서버의 포트 (기본값 3000)
const char* websocket_path = "/api/socket"; // 웹소켓 엔드포인트 경로

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("❌ 소켓 연결 해제");
      break;
    case WStype_CONNECTED:
      Serial.println("🔗 소켓 연결됨");
      webSocket.sendTXT("📡 ESP32 연결됨");
      break;
    case WStype_TEXT:
      Serial.printf("📥 서버 메시지: %s\n", payload);
      if (strcmp((char *)payload, "test") == 0) {
        Serial.println("🚀 모터 시작 명령 수신");
      }
      break;
    case WStype_ERROR:
      Serial.println("⚠️ 에러 발생");
      break;
  }
}

void setup() {
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

  if(Serial.available() > 0){
    String input = Serial.readStringUntil('\n');
    webSocket.sendTXT(input);

  }
  // if (millis() % 5000 == 0) {
  //   webSocket.sendTXT("📡 센서 데이터 전송");
  // }
}
