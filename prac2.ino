#define Up_Red 2
#define Up_Yellow 3
#define Up_Green 4 //위쪽 불
#define Down_Red 22
#define Down_Yellow 24
#define Down_Green 26  //아래쪽 불
#define Right_Red 11
#define Right_Yellow 12
#define Right_Green 10  //오른쪽 불
#define Left_Red 23
#define Left_Yellow 25
#define Left_Green 27  //왼쪽 불
#define SW 30       //위아래 스위치

unsigned long TimeUD;
unsigned long TimeLR;

int timePinRow[8] = { 40, 41, 42, 43, 44, 45, 46, 47 };//정지신호를 출력하기위한 핀번호 배열
int timePinCol[8] = { 32, 33, 34, 35, 36, 37, 38, 39 };

int signPinRow[8] = { A8, A9, A10, A11, A12, A13, A14, A15 };//보행신호와 시간(숫자)를 출력하는 핀번호 배열
int signPinCol[8] = { A0, A1, A2, A3, A4, A5, A6, A7 };

//기타 기호상수
#define DRIVABLE_DURATION           10000u   //주행 가능 시간
#define LED_Yellow_BLINK_DURATION   5000u    //경고등 점멸 시간(5sec)
#define BLINK_TIME                  LED_Yellow_BLINK_DURATION / 1000 //점멸 횟수 (1초당1회),for문에서 조건으로 사용하기위해 1000으로 나눠줌
#define LED_DELAY_TIME              3000u    //입력 받았을 시 3초의 대기시간을 갖기위해
#define ARRAY_LENGTH                8        //열 길이
#define CYCLE                       (DRIVABLE_DURATION + LED_Yellow_BLINK_DURATION) / 1000  //현재 15000/1000 = 15 로 다음 신호로 바뀌는데까지 걸리는시간(초록불시간+점멸시간)
#define WALK_DURATION               CYCLE * 1000    //보행자신호를 출력하기위한(DisplayWalkSign) 시간을 설정한 변수 현재 15000


bool state = false; //  false(위아래 빨간불 양옆 파란불), true(위아래 파란불 양옆 빨간불)
//DotMatrix 타이머 출력을 위한 변수
int Numbers[10][8][4] =
{
  // 숫자 0
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
  // 숫자 1
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
  // 숫자 2
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
  // 숫자 3
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
  // 숫자 4
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
  // 숫자 5
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
  // 숫자 6
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
  // 숫자 7
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
  // 숫자 8
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
  // 숫자 9
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
int WalkerSigns[2][8][8] =
{
  // 보행자 빨간불
  {
   { 0, 0, 0, 1, 1, 0, 0, 0 },
   { 0, 0, 0, 1, 1, 0, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 0, 0 },
   { 0, 0, 1, 1, 1, 1, 0, 0 },
   { 0, 0, 0, 1, 1, 0, 0, 0 },
   { 0, 0, 0, 1, 1, 0, 0, 0 }
  },

  // 보행자 초록불
{
{0,0,0,1,1,0,0,0},
{0,0,0,1,1,0,0,0},
{0,0,1,1,1,1,0,0},
{0,0,1,1,1,1,0,0},
{0,0,1,1,1,1,0,0},
{1,1,0,1,1,0,1,0},
{0,0,0,1,1,0,0,1},
{0,0,1,0,1,0,0,0},
}
};

void setup()
{
  //상하 출력 핀 모드 설정
  pinMode(Up_Red, OUTPUT);
  pinMode(Down_Red, OUTPUT);
  pinMode(Up_Yellow, OUTPUT);
  pinMode(Down_Yellow, OUTPUT);
  pinMode(Up_Green, OUTPUT);
  pinMode(Down_Green, OUTPUT);
  //좌우 출력 핀 모드 설정
  pinMode(Left_Red, OUTPUT);
  pinMode(Right_Red, OUTPUT);
  pinMode(Left_Yellow, OUTPUT);
  pinMode(Right_Yellow, OUTPUT);
  pinMode(Left_Green, OUTPUT);
  pinMode(Right_Green, OUTPUT);
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
    checkLED();
    checkDotmatrix();
}

void loop()
{
  //상하 주행state = true
  digitalWrite(Left_Red, HIGH);
  digitalWrite(Right_Red, HIGH);
  digitalWrite(Up_Green, HIGH);
  digitalWrite(Down_Green, HIGH);
  for (int t = CYCLE; t > 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        DisplayStopSignWithSwitch(1000, former, later);
        if (state == true)
       {
        state = false;
        break;
       }
     }
     else if (digitalRead(Up_Red) == LOW && digitalRead(Down_Red) == LOW)
     {
       digitalWrite(Up_Green, LOW);
       digitalWrite(Down_Green, LOW);
       UD_BlinkYellow(former, later);
     }
  }
  digitalWrite(Left_Red, LOW);
  digitalWrite(Right_Red, LOW);

  //좌우 주행
  digitalWrite(Up_Red, HIGH);
  digitalWrite(Down_Red, HIGH);
  digitalWrite(Left_Green, HIGH);
  digitalWrite(Right_Green, HIGH);
  for (int t = CYCLE; t > 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        DisplayWalkSign(1000);
        if(state == true)
       {
        state = false;
        break;
       }
     }
     else if (digitalRead(Left_Red) == LOW && digitalRead(Right_Red) == LOW)
     {
       digitalWrite(Left_Green, LOW);
       digitalWrite(Right_Green, LOW);
       LR_BlinkYellow();
     }
  }
  digitalWrite(Up_Red, LOW);
  digitalWrite(Down_Red, LOW);
}


 void checkLED() {
  digitalWrite(Right_Green, HIGH);delay(100);digitalWrite(Right_Green, LOW);
  digitalWrite(Right_Yellow, HIGH);delay(100);digitalWrite(Right_Yellow, LOW);
  digitalWrite(Right_Red, HIGH);delay(100);digitalWrite(Right_Red, LOW);
  digitalWrite(Up_Green, HIGH);delay(100);digitalWrite(Up_Green, LOW);
  digitalWrite(Up_Yellow, HIGH);delay(100);digitalWrite(Up_Yellow, LOW);
  digitalWrite(Up_Red, HIGH);delay(100);digitalWrite(Up_Red, LOW);
  digitalWrite(Left_Red, HIGH);delay(100);digitalWrite(Left_Red, LOW);
  digitalWrite(Left_Yellow, HIGH);delay(100);digitalWrite(Left_Yellow, LOW);
  digitalWrite(Left_Green, HIGH);delay(100);digitalWrite(Left_Green, LOW);
  digitalWrite(Down_Red, HIGH);delay(100);digitalWrite(Down_Red, LOW); 
  digitalWrite(Down_Yellow, HIGH);delay(100);digitalWrite(Down_Yellow, LOW);
  digitalWrite(Down_Green, HIGH);delay(100);digitalWrite(Down_Green, LOW);
 }

void checkDotmatrix(){
for(int thisRow=7; thisRow>=0; thisRow--)
  {
    for(int thisCol=7; thisCol>=0; thisCol--)
    {
      digitalWrite(timePinRow[thisRow],HIGH);
      digitalWrite(signPinRow[thisRow],HIGH);
      digitalWrite(timePinCol[thisCol],LOW);
      digitalWrite(signPinCol[thisCol],LOW);
      delay(10);
      digitalWrite(timePinRow[thisRow],LOW);
      digitalWrite(signPinRow[thisRow],LOW);
      digitalWrite(timePinCol[thisCol],HIGH);
      digitalWrite(signPinCol[thisCol],HIGH);
      delay(10);    
      }
  }
  }



void LR_BlinkYellow() //양옆 노란불 점멸과 동시에 보행가능신호
{
  static const int delayTime = LED_Yellow_BLINK_DURATION / (BLINK_TIME + BLINK_TIME); // delayTime 은 500u
  //점멸시간동안 보행자신호 출력 + 점멸
  digitalWrite(Left_Yellow, HIGH);  
  digitalWrite(Right_Yellow, HIGH);
  DisplayWalkSign(delayTime);
  digitalWrite(Left_Yellow, LOW);
  digitalWrite(Right_Yellow, LOW);
  DisplayWalkSign(delayTime);
}



void UD_BlinkYellow(int former, int later) //위아래 노란불 점멸과 동시에 정지신호+시간출력
{
  static const int delayTime = LED_Yellow_BLINK_DURATION / (BLINK_TIME + BLINK_TIME); //delayTime = 500u
                                     //위아래 점멸과 동시에 정지신호와 시간 출력
  digitalWrite(Up_Yellow, HIGH);
  digitalWrite(Down_Yellow, HIGH);
  DisplayStopSign(delayTime, former, later);
  digitalWrite(Up_Yellow, LOW);
  digitalWrite(Down_Yellow, LOW);
  DisplayStopSign(delayTime, former, later);
}

void UD_LED() //3초의 대기시간동안 정지신호+숫자, 5초의 시간동안 UD_BlinkYellow() 그후에 상태를 (위아래정지 양옆파란불)
{
  for (int t = (LED_DELAY_TIME + LED_Yellow_BLINK_DURATION) / 1000; t > 0; --t)// t는 현재 8인데 if문3번돌고 else문 5번돈뒤 상태를(위아래 정지, 양옆 주행) 
  {
    if (t > BLINK_TIME)
      //1초간 타이머 출력
      DisplayStopSign(1000, t / 10, t % 10);//1번씩 십의자리숫자와 일의자리숫자에맞게 숫자와 정지표시를 출력
    else
    {
      digitalWrite(Up_Green, LOW);
      digitalWrite(Down_Green, LOW);
      UD_BlinkYellow(t / 10, t % 10);
    }
  }
  digitalWrite(Up_Red, HIGH);//상태를 위아래 정지 양옆 파란불 = false가됨
  digitalWrite(Down_Red, HIGH);
  digitalWrite(Left_Green, HIGH);
  digitalWrite(Right_Green, HIGH);
  digitalWrite(Right_Red, LOW);
  digitalWrite(Left_Red, LOW);
  DisplayWalkSign(WALK_DURATION);
  state = true;
}

void DisplayStopSignWithSwitch(int duration, int former, int later)//스위치 작동과 현재 위아래 주행가능하면(true일때) UD_LED실행, 정지신호와 숫자표시하는 함수
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    StopSign();
    DisplayNumber(Numbers[former], Numbers[later]);
    //Switch ON
    if (digitalRead(SW) == LOW && digitalRead(Up_Green) == HIGH && digitalRead(Down_Green) == HIGH)
      UD_LED();//8초간 3초대기시간 +5초의 위아래점멸 후 
    timeEnd = millis();
  }
}

void ClearUpperDisplay()//위 DOT_MATRIX CLEAR
{
  for (int i = 0; i < ARRAY_LENGTH; ++i)
  {
    digitalWrite(timePinRow[i], LOW);
    digitalWrite(timePinCol[i], HIGH);
  }
}

void ClearLowerDisplay()//아래 DOT_MATRIX CLEAR
{
  for (int i = 0; i < ARRAY_LENGTH; ++i)
  {
    digitalWrite(signPinRow[i], LOW);
    digitalWrite(signPinCol[i], HIGH);
  }
}

void DisplayNumber(int former[][4], int later[][4])//숫자를 표시하는 함수
{
  for(int r = 0; r < 8; ++r)
  {
    ClearLowerDisplay();
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
        digitalWrite(signPinCol[c + 4], LOW);// [C+4]는 앞의 행4개를 뛰어넘고 일의자리위치에 표기하기위해
      }
    }
    
    delay(1);// 이 함수가 없을 시, 출력 신호가 뚜렷하게 보이지 않음 FOR문을통해 전환시 사이사이에 흐릿해질수 있음
  }
}

void StopSign()// 정지표시를 핀입력으로 주는 함수
{
  for(int r = 0; r < 8; ++r)
  {
    ClearUpperDisplay();
    digitalWrite(timePinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(WalkerSigns[0][r][c])
      {
        digitalWrite(timePinCol[c], LOW);
      }
    }
   
    delay(1);// 이 함수가 없을 시, 출력 신호가 뚜렷하게 보이지 않음 FOR문을통해 전환시 사이사이에 흐릿해질수 있음
  }
}

void WalkSign() //보행가능표시를 핀입력주는 함수
{
  for(int r = 0; r < 8; ++r)
  {
    ClearUpperDisplay();
    ClearLowerDisplay();
    digitalWrite(signPinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(WalkerSigns[1][r][c])
      {
        digitalWrite(signPinCol[c], LOW);
      }
    }
    //HACK : 출력 신호를 유지하기 위해 사용
    delay(1);
  }
}

void DisplayStopSign(int duration, int former, int later)//(정지신호+숫자표기)+시간조건
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    StopSign();
    DisplayNumber(Numbers[former], Numbers[later]);
    timeEnd = millis();
  }
}

void DisplayWalkSign(unsigned duration)//(보행신호)+시간조건
{
  ClearUpperDisplay();
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    WalkSign();
    timeEnd = millis();
  }
}
