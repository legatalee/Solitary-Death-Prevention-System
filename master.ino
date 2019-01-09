#include <SoftwareSerial.h>
SoftwareSerial HC12(9, 10);

String data;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);

  Serial.println("CLEARSHEET");//시작시 엑셀 시트를 초기화
  Serial.println("LABEL,Time,Place");//제목 설정

  pinMode(LED_BUILTIN, OUTPUT);
}

bool check = false;
bool Wcheck = false;

void loop() {
  String input = "";
  while (HC12.available() > 0) {//HC12모듈로 수신하는동안
    input += (char) HC12.read();//input에 받은 데이터 입력
    delay(1);
  }
  if (input == "emg") {
    check = true;
    Wcheck = true;
    data = "";
    while (data == "") {
      while (HC12.available() > 0) {//HC12모듈로 수신하는동안
        data += (char) HC12.read();//input에 받은 데이터 입력
        delay(1);
      }
    }
  }
  if (input == "done") {
    Wcheck = false;
  }
  
  if (check == true) {
    if (Wcheck == true)
      DATAwrite(data);

//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(600);//millis()로 바꾸기
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(400);
  }
}

void DATAwrite(String data) {
  Serial.print((String) "DATA,TIME," );//엑셀 매크로 데이타 선언 후 현재시간 출력(나노로 값 보내기)
  Serial.print(data);
  Serial.println((String) ",AUTOSCROLL_20" );//엑셀 매크로 자동스크롤
  Wcheck = false;
  return;
}
