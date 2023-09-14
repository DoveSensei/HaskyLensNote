#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// 모터 드라이버의 핀 정의
// 아래에 코드 작성

int xOrigin = 0;
int xTarget = 0;

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
  // 아래에 코드 작성
  
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
	// 아래에 코드 작성
  }

  // x좌표 오차 계산
  // 아래에 코드 작성


  // x좌표 오차에 따른 모터 제어
  // 아래에 코드 작성

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