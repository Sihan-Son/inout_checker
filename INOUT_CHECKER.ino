
#define TRIG_1 3
#define ECHO_1 4

#define TRIG_2 5
#define ECHO_2 6

int Dis_in;
int Dis_out;
int status;

unsigned people = 0; // 총 인원
unsigned inMan = 0; //현 인원



void setup() 
{
	pinMode(TRIG_1, OUTPUT);
	pinMode(TRIG_2, OUTPUT);
	pinMode(ECHO_1, INPUT);
	pinMode(ECHO_2, INPUT);
	
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
