#define UPPER_RED 2
#define UPPER_YELLOW 3
#define UPPER_GREEN 4 //위쪽 불
#define LOWER_RED 22
#define LOWER_YELLOW 24
#define LOWER_GREEN 26  //아래쪽 불
#define RIGHT_RED 11
#define RIGHT_YELLOW 12
#define RIGHT_GREEN 13  //오른쪽 불
#define LEFT_RED 23
#define LEFT_YELLOW 25
#define LEFT_GREEN 27  //왼쪽 불
#define UD_SW 30       //위아래 스위치
#define LR_SW 32       //양옆 스위치

  int UDSW = digitalRead(UD_SW);
  int LRSW = digitalRead(LR_SW);

void setup()  // 초기 한번 실행
{
  pinMode(UPPER_RED, OUTPUT);
  pinMode(UPPER_YELLOW, OUTPUT);
  pinMode(UPPER_GREEN, OUTPUT);
  pinMode(LOWER_RED, OUTPUT);
  pinMode(LOWER_YELLOW, OUTPUT);
  pinMode(LOWER_GREEN, OUTPUT);
  pinMode(RIGHT_RED, OUTPUT);
  pinMode(RIGHT_YELLOW, OUTPUT);
  pinMode(RIGHT_GREEN, OUTPUT);
  pinMode(LEFT_RED, OUTPUT);
  pinMode(LEFT_YELLOW, OUTPUT);
  pinMode(LEFT_GREEN, OUTPUT);
  pinMode(UD_SW, INPUT_PULLUP);
  pinMode(LR_SW, INPUT_PULLUP);
}

void loop() //반복
{
  if(UDSW == LOW && digitalRead(LEFT_GREEN)==HIGH){
    delay(3000);
    Blink_LR_LED();
    initUpDown();
  }
  else if(LRSW == LOW && digitalRead(UPPER_GREEN)==HIGH){
    delay(3000);
    Blink_UD_LED();
    initLeftRight();
  }
  else{
  initLeftRight();//양옆 차 신호등 파란불
  Blink_LR_LED();//양옆 노란불 점멸
  initUpDown();//위아래 차 신호등 파란불
  Blink_UD_LED();//양옆 노란불 점멸
 }
}
 
void Blink_LR_LED(){
  digitalWrite(RIGHT_GREEN, LOW);  digitalWrite(LEFT_GREEN, LOW);
   for(int i = 0; i<10; i++){
  digitalWrite(LEFT_YELLOW, HIGH);   digitalWrite(RIGHT_YELLOW, HIGH);
  delay(500);
  digitalWrite(LEFT_YELLOW, LOW);   digitalWrite(RIGHT_YELLOW, LOW);
  delay(500);
 }
 digitalWrite(RIGHT_RED, HIGH);  digitalWrite(LEFT_RED, HIGH);
}
void Blink_UD_LED(){
  digitalWrite(UPPER_GREEN, LOW);  digitalWrite(LOWER_GREEN, LOW);
   for(int i = 0; i<10; i++){
  digitalWrite(UPPER_YELLOW, HIGH);   digitalWrite(LOWER_YELLOW, HIGH);
  delay(500);
  digitalWrite(UPPER_YELLOW, LOW);   digitalWrite(LOWER_YELLOW, LOW);
  delay(500);
 }
 digitalWrite(UPPER_RED, HIGH);  digitalWrite(LOWER_RED, HIGH);
}
void initUpDown(){
  digitalWrite(UPPER_GREEN, HIGH); digitalWrite(LOWER_GREEN, HIGH);
  digitalWrite(LEFT_RED, HIGH); digitalWrite(RIGHT_RED, HIGH);
  
  digitalWrite(UPPER_YELLOW, LOW);   digitalWrite(LOWER_YELLOW, LOW);
  digitalWrite(LEFT_YELLOW, LOW);   digitalWrite(RIGHT_YELLOW, LOW);
  digitalWrite(UPPER_RED, LOW);  digitalWrite(LOWER_RED, LOW);
  digitalWrite(RIGHT_GREEN, LOW);  digitalWrite(LEFT_GREEN, LOW);
  delay(30000);
  }
 void initLeftRight(){
  digitalWrite(RIGHT_GREEN, HIGH);  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(UPPER_RED, HIGH);  digitalWrite(LOWER_RED, HIGH);

  digitalWrite(UPPER_YELLOW, LOW);   digitalWrite(LOWER_YELLOW, LOW);
  digitalWrite(LEFT_YELLOW, LOW);   digitalWrite(RIGHT_YELLOW, LOW);
  digitalWrite(LEFT_RED, LOW);  digitalWrite(RIGHT_RED, LOW);
  digitalWrite(UPPER_GREEN, LOW);  digitalWrite(LOWER_GREEN, LOW);
  delay(30000);
 }

