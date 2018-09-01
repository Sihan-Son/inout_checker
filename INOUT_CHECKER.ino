#include <Wire.h>                            
#include <LiquidCrystal_I2C.h>          
#include <DHT11.h>


#define pin 3
#define LED 13
#define PIR 2

#define TRIG_1 10 // 초음파 센서 수신부
#define ECHO_1 9 // 초음파 센서 송출부

#define TRIG_2 12
#define ECHO_2 11

LiquidCrystal_I2C lcd(0x27, 16, 2); //lcd 주소설정 
DHT11 dht11(pin);

unsigned people = 0; // 실내 인원
unsigned IN;
unsigned OUT;
int pirValue; // 모션 감지 유무

void setup() 
{
	pinMode(TRIG_1, OUTPUT);
	pinMode(TRIG_2, OUTPUT);
	
	pinMode(ECHO_1, INPUT);
	pinMode(ECHO_2, INPUT);
	
	pinMode(LED, OUTPUT);
	pinMode(PIR, INPUT);

	lcd.init();
	lcd.backlight();
	
	Serial.begin(9600);
}


int getDistance(char TRIG, char ECHO)
{
	digitalWrite(TRIG, HIGH);
	delay(10);
	digitalWrite(TRIG, LOW);
	int  duration = pulseIn(ECHO, HIGH);
	int distance = duration / 58.2;
	return distance;
}

void loop() 
{

  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0) //온도, 습도 읽어와서 표시
  {
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  else                                //에러일 경우 처리
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
  delay(1000);                        //1초마다 측정
  

  lcd.print("Temp : ");
  lcd.print(temp);
  lcd.print("Hum : ");
  lcd.print(humi);
  lcd.print("MAN : ");
  lcd.print(people);

  IN = getDistance(TRIG_1, ECHO_1);
  OUT = getDistance(TRIG_2, ECHO_2);

  if (IN <= 25) {
	  if (pirValue == HIGH) {
		  if (OUT <= 25)
			  people++;
	  }
  }

  else if (OUT <= 25) {
	  if (pirValue == HIGH) {
		  if (IN <= 25){
			  if(people > 0)
				people--;
		  }
	  }
  }
}
