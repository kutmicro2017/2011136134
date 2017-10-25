#define UPPER_RED 2
#define UPPER_YELLOW 3
#define UPPER_GREEN 4 //위쪽 불
#define LOWER_RED 22
#define LOWER_YELLOW 24
#define LOWER_GREEN 26  //아래쪽 불
#define RIGHT_RED 11
#define RIGHT_YELLOW 12
#define RIGHT_GREEN 10  //오른쪽 불
#define LEFT_RED 23
#define LEFT_YELLOW 25
#define LEFT_GREEN 27  //왼쪽 불
#define SW 30       //위아래 스위치


int timePinRow[8] = { 40, 41, 42, 43, 44, 45, 46, 47 };
int timePinCol[8] = { 32, 33, 34, 35, 36, 37, 38, 39 };
// 보행자 신호 출력용 매트릭스 핀 번호 배열
int signPinRow[8] = { A8, A9, A10, A11, A12, A13, A14, A15 };
int signPinCol[8] = { A0, A1, A2, A3, A4, A5, A6, A7 };

//기타 기호상수
#define DRIVABLE_DURATION           10000u                                                  //주행 가능 시간, 녹색등 유지시간(20sec)
#define LED_YELLOW_BLINK_DURATION   5000u                                                   //경고등 점멸 시간(5sec)
#define BLINK_TIME                  LED_YELLOW_BLINK_DURATION / 1000                        //점멸 횟수(1초당 1회)
#define TRAFFIC_LIGHT_IDLE_TIME     3000u                                                   //입력 받았을 시 대기 시간(3sec)
#define ARRAY_LENGTH                8                                                       //배열 길이
#define CYCLE                       (DRIVABLE_DURATION + LED_YELLOW_BLINK_DURATION) / 1000  //신호 바뀔 때까지의 걸리는 시간
#define WALK_DURATION               CYCLE * 1000                                            //

//폴링시 필요한 변수
bool gbChange = false;
//DotMatrix 타이머 출력을 위한 변수
int gNumbers[10][8][4] =
{
  // ZERO
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // ONE
  {
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 1, 1, 1, 1 }
  },
  // TWO
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 }
  },
  // THREE
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // FOUR
  {
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 }
  },
  // FIVE
  {
    { 1, 1, 1, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 1, 1, 1, 1 }
  },
  // SIX
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // SEVEN
  {
    { 1, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 }
  },
  // EIGHT
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // NINE
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  }
};
//DotMatrix 보행자 그림 출력을 위한 변수
int gWalkerSigns[2][8][8] =
{
  // RED : CANNOT CROSS
  {
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 }
  },
  // GREEN : CAN CROSS
  {
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 }
  }
};
/*
//좌우를 위한 함수
//기능 : 좌우의 노란등을 한번 점멸합니다.
void BlinkLEDForLR();
//기능 : duration 동안 보행 신호를 출력하면서 폴링을 받습니다.
//인자 : duration은 ms단위입니다.
void PrintWalkSignWithPolling(int duration);
//기능 : 신호를 바꿉니다.
void AdjustTrafficLightForLR();

//위아래를 위한 함수
//기능 : 위아래의 노란등을 한번 점멸합니다.
//인자 : former는 출력할 수의 십의 자리, later는 출력할 수의 일의 자리입니다.
void BlinkLEDForUD(int former, int later);
//기능 : 신호를 바꿉니다.
void AdjustTrafficLightForUD();
//기능 : duration 동안 타이머를 출력하면서 폴링을 받습니다.
//인자 : duration은 ms단위이고, former는 출력할 수의 십의 자리, later는 출력할 수의 일의 자리입니다.
void PrintStopSignWithPolling(int duration, int former, int later);

//공통 함수
//기능 : 상단의 DotMatrix 신호를 지웁니다.
void ClearUpper();
//기능 : 하단의 DotMatrix 신호를 지웁니다.
void ClearLower();
//기능 : former, later순으로 DotMatrix에 숫자를 출력합니다.
//인자 : former는 출력할 수의 십의 자리, later는 출력할 수의 일의 자리입니다.
void DisplayNumber(int former[][4], int later[][4]);
//기능 : 상단 DotMatrix에 정지 신호를 출력합니다.
void DisplayStopSign();
//기능 : 하단 DotMatrix에 보행 신호를 출력합니다.
void DisplayWalkSign();
//기능 : duration 동안 타이머를 출력하면서 대기합니다.
//인자 : duration은 ms 단위, former는 출력할 수의 십의 자리, later는 출력할 수의 일의 자리입니다.
void PrintStopSign(int duration, int former, int later);
//기능 : duration동안 보행 신호를 출력합니다.
//인자 : duration은 ms단위입니다.
void PrintWalkSign(unsigned duration);
*/
void setup()
{
  //상하 출력 핀 모드 설정
  pinMode(UPPER_RED, OUTPUT);
  pinMode(LOWER_RED, OUTPUT);
  pinMode(UPPER_YELLOW, OUTPUT);
  pinMode(LOWER_YELLOW, OUTPUT);
  pinMode(UPPER_GREEN, OUTPUT);
  pinMode(LOWER_GREEN, OUTPUT);
  //좌우 출력 핀 모드 설정
  pinMode(LEFT_RED, OUTPUT);
  pinMode(RIGHT_RED, OUTPUT);
  pinMode(LEFT_YELLOW, OUTPUT);
  pinMode(RIGHT_YELLOW, OUTPUT);
  pinMode(LEFT_GREEN, OUTPUT);
  pinMode(RIGHT_GREEN, OUTPUT);
  //DotMatrix 핀 모드 설정 및 초기화
  for(int i = 0; i < ARRAY_LENGTH; ++i)
  {
    pinMode(timePinRow[i], OUTPUT);
    pinMode(timePinCol[i], OUTPUT);
    pinMode(signPinRow[i], OUTPUT);
    pinMode(signPinCol[i], OUTPUT);

    digitalWrite(timePinRow[i], LOW);
    digitalWrite(timePinCol[i], HIGH);
    digitalWrite(signPinRow[i], LOW);
    digitalWrite(signPinCol[i], HIGH);
  }
  //입력 핀 모드 설정
  pinMode(SW, INPUT_PULLUP);
}

void loop()
{
  //상하 주행
  digitalWrite(LEFT_RED, HIGH);
  digitalWrite(RIGHT_RED, HIGH);
  digitalWrite(UPPER_GREEN, HIGH);
  digitalWrite(LOWER_GREEN, HIGH);
  for (int t = CYCLE; t > 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        PrintStopSignWithPolling(1000, former, later);
        if (gbChange)
       {
        gbChange = false;
        break;
       }
     }
     else if (digitalRead(UPPER_RED) == LOW && digitalRead(LOWER_RED) == LOW)
     {
       digitalWrite(UPPER_GREEN, LOW);
       digitalWrite(LOWER_GREEN, LOW);
       BlinkLEDForUD(former, later);
     }
  }
  digitalWrite(LEFT_RED, LOW);
  digitalWrite(RIGHT_RED, LOW);

  //좌우 주행
  digitalWrite(UPPER_RED, HIGH);
  digitalWrite(LOWER_RED, HIGH);
  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(RIGHT_GREEN, HIGH);
  for (int t = CYCLE; t > 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        PrintWalkSignWithPolling(1000);
        if(gbChange)
       {
        gbChange = false;
        break;
       }
     }
     else if (digitalRead(LEFT_RED) == LOW && digitalRead(RIGHT_RED) == LOW)
     {
       digitalWrite(LEFT_GREEN, LOW);
       digitalWrite(RIGHT_GREEN, LOW);
       BlinkLEDForLR();
     }
  }
  digitalWrite(UPPER_RED, LOW);
  digitalWrite(LOWER_RED, LOW);
}

void BlinkLEDForLR()
{
  static const int delayTime = LED_YELLOW_BLINK_DURATION / (BLINK_TIME + BLINK_TIME);
  
  digitalWrite(LEFT_YELLOW, HIGH);
  digitalWrite(RIGHT_YELLOW, HIGH);
  PrintWalkSign(delayTime);
  digitalWrite(LEFT_YELLOW, LOW);
  digitalWrite(RIGHT_YELLOW, LOW);
  PrintWalkSign(delayTime);
}

void PrintWalkSignWithPolling(int duration)
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    DisplayWalkSign();
    //Polling
    timeEnd = millis();
  }
}

void AdjustTrafficLightForLR()
{
  for (int t = (TRAFFIC_LIGHT_IDLE_TIME + LED_YELLOW_BLINK_DURATION) / 1000; t > 0; --t)
  {
    if (t > BLINK_TIME)
    {
      //1초간 보행 신호 출력
      PrintWalkSign(1000);
    }
    else
    {
      digitalWrite(LEFT_GREEN, LOW);
      digitalWrite(RIGHT_GREEN, LOW);
      BlinkLEDForLR();
    }
  }
  digitalWrite(LEFT_RED, HIGH);
  digitalWrite(RIGHT_RED, HIGH);
  PrintWalkSign(WALK_DURATION);
  gbChange = true;
}

void BlinkLEDForUD(int former, int later)
{
  static const int delayTime = LED_YELLOW_BLINK_DURATION / (BLINK_TIME + BLINK_TIME);
  
  digitalWrite(UPPER_YELLOW, HIGH);
  digitalWrite(LOWER_YELLOW, HIGH);
  PrintStopSign(delayTime, former, later);
  digitalWrite(UPPER_YELLOW, LOW);
  digitalWrite(LOWER_YELLOW, LOW);
  PrintStopSign(delayTime, former, later);
}

void AdjustTrafficLightForUD()
{
  for (int t = (TRAFFIC_LIGHT_IDLE_TIME + LED_YELLOW_BLINK_DURATION) / 1000; t > 0; --t)
  {
    if (t > BLINK_TIME)
    {
      //1초간 타이머 출력
      PrintStopSign(1000, t / 10, t % 10);
    }
    else
    {
      digitalWrite(UPPER_GREEN, LOW);
      digitalWrite(LOWER_GREEN, LOW);
      BlinkLEDForUD(t / 10, t % 10);
    }
  }
  digitalWrite(UPPER_RED, HIGH);
  digitalWrite(LOWER_RED, HIGH);
  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(RIGHT_GREEN, HIGH);
  digitalWrite(RIGHT_RED, LOW);
  digitalWrite(LEFT_RED, LOW);
  PrintWalkSign(WALK_DURATION);
  gbChange = true;
}

void PrintStopSignWithPolling(int duration, int former, int later)
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    DisplayStopSign();
    DisplayNumber(gNumbers[former], gNumbers[later]);
    //Polling
    if (digitalRead(SW) == LOW && digitalRead(UPPER_GREEN) == HIGH && digitalRead(LOWER_GREEN) == HIGH)
    {
      AdjustTrafficLightForUD();
    }
    timeEnd = millis();
  }
}

void ClearUpper()
{
  for (int i = 0; i < ARRAY_LENGTH; ++i)
  {
    digitalWrite(timePinRow[i], LOW);
    digitalWrite(timePinCol[i], HIGH);
  }
}

void ClearLower()
{
  for (int i = 0; i < ARRAY_LENGTH; ++i)
  {
    digitalWrite(signPinRow[i], LOW);
    digitalWrite(signPinCol[i], HIGH);
  }
}

void DisplayNumber(int former[][4], int later[][4])
{
  for(int r = 0; r < 8; ++r)
  {
    ClearLower();
    digitalWrite(signPinRow[r], HIGH);
    //십의 자리 출력
    for(int c = 0; c < 4; ++c)
    {
      if (former[r][c])
      {
        digitalWrite(signPinCol[c], LOW);
      }
    }
    //일의 자리 출력
    for(int c = 0; c < 4; ++c)
    {
      if (later[r][c])
      {
        digitalWrite(signPinCol[c + 4], LOW);
      }
    }
    //HACK : 이 함수가 없을 시, 출력 신호가 뚜렷하게 보이지 않음
    delay(1);
  }
}

void DisplayStopSign()
{
  for(int r = 0; r < 8; ++r)
  {
    ClearUpper();
    digitalWrite(timePinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(gWalkerSigns[0][r][c])
      {
        digitalWrite(timePinCol[c], LOW);
      }
    }
    //HACK : 출력 신호를 유지하기 위해 사용
    delay(1);
  }
}

void DisplayWalkSign()
{
  for(int r = 0; r < 8; ++r)
  {
    ClearUpper();
    ClearLower();
    digitalWrite(signPinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(gWalkerSigns[1][r][c])
      {
        digitalWrite(signPinCol[c], LOW);
      }
    }
    //HACK : 출력 신호를 유지하기 위해 사용
    delay(1);
  }
}

void PrintStopSign(int duration, int former, int later)
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    DisplayStopSign();
    DisplayNumber(gNumbers[former], gNumbers[later]);
    timeEnd = millis();
  }
}

void PrintWalkSign(unsigned duration)
{
  ClearUpper();
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    DisplayWalkSign();
    timeEnd = millis();
  }
}

