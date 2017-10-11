#include <FrequencyTimer2.h>

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
#define UD_SW 30       //위아래 스위치
#define LR_SW 31      //양옆 스위치
#define STOP{\
{0,0,0,1,1,0,0,0},\
{0,0,0,1,1,0,0,0},\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0},\
{0,0,0,1,1,0,0,0},\
{0,0,0,1,1,0,0,0},\
}
byte col = 0;
byte leds[8][8];

int pins[17]= {-1,32, 33, 34, 35, 36, 37, 38, 39,40, 41, 42, 43, 44, 45, 46, 47};


const int cols[8] = {pins[1], pins[2], pins[3], pins[4], pins[5], pins[6], pins[7], pins[8]};
const int rows[] = {pins[9], pins[10], pins[11], pins[12], pins[13], pins[14], pins[15], pins[16]};
const int numPatterns = 1;
byte patterns[numPatterns][8][8] = {STOP};
int pattern = 0;

int interval = 10000;
unsigned long TimeUD;
unsigned long TimeLR;

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
  
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }
 
  // 행 0~7번까지를 high로 
  for (int i = 0; i < 8; i++) {
    digitalWrite(cols[i], HIGH );
  }
  // 열 0~7번 까지를 low로
  for (int i = 0; i < 8; i++) {
    digitalWrite(rows[i], HIGH);
  }
  clearLeds();
  FrequencyTimer2::setOnOverflow(display);  // leds를 보여주기 위해서 setOnOverFlow를 사용
  checkLED();
}

void loop() //반복
{
   
  if(digitalRead(LR_SW) == LOW && digitalRead(UPPER_GREEN) == HIGH){
    delay(3000);
    Blink_UD_LED();
    LeftRight();
  }
  else if(digitalRead(UD_SW) == LOW && digitalRead(LEFT_GREEN) == HIGH){
    delay(3000);
    Blink_LR_LED();
    UPPERLOWER();
  }
  else{
    unsigned long currentTime = millis();
    
    if(currentTime > TimeUD + interval && currentTime > TimeLR + interval*2){
      Blink_UD_LED();
      LeftRight(); 
    }
    else if(currentTime > TimeLR + interval && currentTime > TimeUD + interval*2){
      Blink_LR_LED();
      UPPERLOWER();
    }
 }
}
void clearLeds() {
  // Clear display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}
void setPattern(int pattern) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = patterns[pattern][i][j];
    }
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
}

void Blink_UD_LED(){
  digitalWrite(UPPER_GREEN, LOW);  digitalWrite(LOWER_GREEN, LOW);
   for(int i = 0; i<10; i++){
  digitalWrite(UPPER_YELLOW, HIGH);   digitalWrite(LOWER_YELLOW, HIGH);
  delay(500);
  digitalWrite(UPPER_YELLOW, LOW);   digitalWrite(LOWER_YELLOW, LOW);
  delay(500);
 }
}

void UPPERLOWER(){
  digitalWrite(UPPER_GREEN, HIGH); digitalWrite(LOWER_GREEN, HIGH);
  digitalWrite(LEFT_RED, HIGH); digitalWrite(RIGHT_RED, HIGH);
  
  digitalWrite(UPPER_YELLOW, LOW);   digitalWrite(LOWER_YELLOW, LOW);
  digitalWrite(LEFT_YELLOW, LOW);   digitalWrite(RIGHT_YELLOW, LOW);
  digitalWrite(UPPER_RED, LOW);  digitalWrite(LOWER_RED, LOW);
  digitalWrite(RIGHT_GREEN, LOW);  digitalWrite(LEFT_GREEN, LOW);
  TimeUD = millis();
  clearLeds();
  }
  
 void LeftRight(){
  digitalWrite(RIGHT_GREEN, HIGH);  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(UPPER_RED, HIGH);  digitalWrite(LOWER_RED, HIGH);

  digitalWrite(UPPER_YELLOW, LOW);   digitalWrite(LOWER_YELLOW, LOW);
  digitalWrite(LEFT_YELLOW, LOW);   digitalWrite(RIGHT_YELLOW, LOW);
  digitalWrite(LEFT_RED, LOW);  digitalWrite(RIGHT_RED, LOW);
  digitalWrite(UPPER_GREEN, LOW);  digitalWrite(LOWER_GREEN, LOW);
  TimeLR = millis();
  setPattern(pattern);
 }
 void checkLED() {
  digitalWrite(RIGHT_GREEN, HIGH);delay(200);digitalWrite(RIGHT_GREEN, LOW);
  digitalWrite(RIGHT_YELLOW, HIGH);delay(200);digitalWrite(RIGHT_YELLOW, LOW);
  digitalWrite(RIGHT_RED, HIGH);delay(200);digitalWrite(RIGHT_RED, LOW);
  digitalWrite(UPPER_GREEN, HIGH);delay(200);digitalWrite(UPPER_GREEN, LOW);
  digitalWrite(UPPER_YELLOW, HIGH);delay(200);digitalWrite(UPPER_YELLOW, LOW);
  digitalWrite(UPPER_RED, HIGH);delay(200);digitalWrite(UPPER_RED, LOW);
  digitalWrite(LEFT_RED, HIGH);delay(200);digitalWrite(LEFT_RED, LOW);
  digitalWrite(LEFT_YELLOW, HIGH);delay(200);digitalWrite(LEFT_YELLOW, LOW);
  digitalWrite(LEFT_GREEN, HIGH);delay(200);digitalWrite(LEFT_GREEN, LOW);
  digitalWrite(LOWER_RED, HIGH);delay(200);digitalWrite(LOWER_RED, LOW); 
  digitalWrite(LOWER_YELLOW, HIGH);delay(200);digitalWrite(LOWER_YELLOW, LOW);
  digitalWrite(LOWER_GREEN, HIGH);delay(200);digitalWrite(LOWER_GREEN, LOW);

  digitalWrite(RIGHT_GREEN, HIGH);  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(UPPER_RED, HIGH);  digitalWrite(LOWER_RED, HIGH);

  digitalWrite(UPPER_YELLOW, LOW);   digitalWrite(LOWER_YELLOW, LOW);
  digitalWrite(LEFT_YELLOW, LOW);   digitalWrite(RIGHT_YELLOW, LOW);
  digitalWrite(LEFT_RED, LOW);  digitalWrite(RIGHT_RED, LOW);
  digitalWrite(UPPER_GREEN, LOW);  digitalWrite(LOWER_GREEN, LOW);
  
  TimeUD = - interval;
  TimeLR = millis();
  setPattern(pattern);
 }
 void display() {
  digitalWrite(cols[col], HIGH);
  col++;
  if (col == 8) {
    col = 0;
  } 
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
      digitalWrite(rows[row], HIGH);
    }
    else {
      digitalWrite(rows[row], LOW);
    }
  } 
  digitalWrite(cols[col], LOW);
}
