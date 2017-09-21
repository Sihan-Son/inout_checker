#include <DHT11.h>

#define pin 2
#define TRIG_1 3
#define ECHO_1 4

#define TRIG_2 5
#define ECHO_2 6

#define LED 13

DHT11 dht11(pin);
int Dis_in;
int Dis_out;
int status;

unsigned people = 0; // �� �ο�
unsigned inMan = 0; //�� �ο�



void setup() 
{
	pinMode(TRIG_1, OUTPUT);
	pinMode(TRIG_2, OUTPUT);
	pinMode(ECHO_1, INPUT);
	pinMode(ECHO_2, INPUT);
  pinMode(LED, OUTPUT);
	
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
  
	Dis_in = getDistance(TRIG_1, ECHO_1);
	Dis_out = getDistance(TRIG_2, ECHO_2);

	if (Dis_in < 20)
	{
		status = 1; //in
		Serial.println("Status >> in\n");
	}
	else if (Dis_out < 20)
	{
		status = 2;//out
		Serial.println("Status >> out\n");

		if (inMan == 0);
			status = 3;
	}

	

	switch (status)
	{
	case 1:
	{
		Dis_out = getDistance(TRIG_2, ECHO_2);

		if (Dis_out < 20)
		{
			people++;
			inMan++;

			Serial.print("Dis_in >> ");
			Serial.println(Dis_in);

			Serial.print("Dis_out >> ");
			Serial.println(Dis_out);
			Serial.println();

			Serial.print("Now in Room >> ");
			Serial.println(inMan);

			Serial.print("All People >> ");
			Serial.println(people);
			Serial.println();

			Serial.println("Someone is in");
			Serial.println();
			Serial.println("///////////////////////////////////////////////////");

      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);
		}
		break;

	}

	case 2:
	{
	
		Dis_in = getDistance(TRIG_1, ECHO_1);

		if (Dis_in < 20)
		{
			inMan--;

			Serial.print("Dis_in >> ");
			Serial.println(Dis_in);

			Serial.print("Dis_out >> ");
			Serial.println(Dis_out);
			Serial.println();

			Serial.print("Now in Room >> ");
			Serial.println(inMan);

			Serial.print("All People >> ");
			Serial.println(people);
			Serial.println();

			Serial.println("Someone is out");
			Serial.println();
			Serial.println("///////////////////////////////////////////////////");
		}
		break;
	}
	
	case 3:
		break;
	}


}
