#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// 모터 드라이버의 핀 정의
const int motorA_1A = 5; // 모터 A_1A의 제어 핀 1
const int motorA_1B = 6; // 모터 A_1B의 제어 핀 2

const int motorB_1A = 10; // 모터 B_1A의 제어 핀 1
const int motorB_1B = 11; // 모터 B_1B의 제어 핀 2

int xOrigin = 0;
int xTarget = 0;
int xAverage = 0;

#define MOTOR_POWER 255

HUSKYLENS huskylens;
int ID1 = 1;
void printResult(HUSKYLENSResult result);

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING); //Switch the algorithm to line tracking.

  // 모터 제어 핀을 출력으로 설정
  pinMode(motorA_1A, OUTPUT);
  pinMode(motorA_1B, OUTPUT);

  pinMode(motorB_1A, OUTPUT);
  pinMode(motorB_1B, OUTPUT);
}

void loop()
{  
  if (!huskylens.request(ID1)) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
  else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
  else
  {
    HUSKYLENSResult result = huskylens.read();
    printResult(result);
    xOrigin = result.xOrigin;
    xTarget = result.xTarget;
  
    // 화살표 x좌표 평균값 계산
    xAverage = (xTarget + xOrigin) / 2;
  }

  // x좌표 오차 계산
  float error = 160 - xAverage;
  Serial.println(error);

  // x좌표 오차에 따른 모터 제어
  if(error > 0)
  {
    // 우회전
    // 모터 A 제어
    analogWrite(motorA_1A, MOTOR_POWER);
    analogWrite(motorA_1B, 0);

    // 모터 B 제어
    analogWrite(motorB_1A, 0);
    analogWrite(motorB_1B, 0);
  }
  else if(error < 0)
  {
    // 좌회전
    // 모터 A 제어
    analogWrite(motorA_1A, 0);
    analogWrite(motorA_1B, 0);

    // 모터 B 제어
    analogWrite(motorB_1A, 0);
    analogWrite(motorB_1B, MOTOR_POWER);
  }
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}