#define PIR 2 //모션 센서

#define TRIG_1 10 // 초음파 센서 수신부
#define ECHO_1 9 // 초음파 센서 송출부

#define TRIG_2 12
#define ECHO_2 11

void setup() {
  pinMode(TRIG_1, OUTPUT);
  pinMode(TRIG_2, OUTPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(ECHO_2, INPUT);
  pinMode(PIR, INPUT);
}

int getDistance(char TRIG, char ECHO) //초음파를 이용하여 거리 측정
{
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  int  duration = pulseIn(ECHO, HIGH);
  int distance = duration / 58.2;
  return distance;
}

unsigned people = 0; // 실내 인원
unsigned IN;
unsigned OUT;
int pirValue; // 모션 감지 유무

void loop() {

  IN = getDistance(TRIG_1, ECHO_1);
  OUT = getDistance(TRIG_2, ECHO_2);

  if(IN <=25){
    if(pirValue == HIGH){
      if(OUT <= 25)
        people++;
    }
  }

  else if(OUT <= 25){
    if(pirValue == HIGH){
      if(IN <= 25)
        people--;
    }
  }
}

