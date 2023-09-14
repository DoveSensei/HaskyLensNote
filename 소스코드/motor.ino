// 모터 드라이버의 핀 정의
const int motorA_1A = 5; // 모터 A_1A의 제어 핀 1
const int motorA_1B = 6; // 모터 A_1B의 제어 핀 2

const int motorB_1A = 10; // 모터 B_1A의 제어 핀 1
const int motorB_1B = 11; // 모터 B_1B의 제어 핀 2

void setup()
{
  // 모터 제어 핀을 출력으로 설정
  pinMode(motorA_1A, OUTPUT);
  pinMode(motorA_1B, OUTPUT);

  pinMode(motorB_1A, OUTPUT);
  pinMode(motorB_1B, OUTPUT);
}

void loop()
{
  // 모터 A 제어
  analogWrite(motorA_1A, 255);
  analogWrite(motorA_1B, 0);

  // 모터 B 제어
  analogWrite(motorB_1A, 0);
  analogWrite(motorB_1B, 255);

  delay(1000); // 1초 대기
}

