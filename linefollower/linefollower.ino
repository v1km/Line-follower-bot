#include <Servo.h> 

Servo left;
Servo right; 

int mid = 0;
int mn = 0;
int mx = 0;

void setup()
{

left.attach(9, 800, 2200); //left servo motor
right.attach(10, 800, 2200); //right servo motor

Serial.begin(115200);

digitalWrite(13, LOW);

right.write(90);//stop signal
left.write(90);//stop signal

for(int i=0; i<5000; i++)
{
digitalWrite(13, HIGH);

int val = 0;
for(int j=0; j<=5; j++)//Calibrating the sensor, finding max and 
{                      //min reflectance values.
val = analogRead(j);
if(val >= mx)
mx = val;
if(val <= mn)
mn = val;
}
delay(1);
}

mid = ((mx + mn)/2);
digitalWrite(13, LOW);

right.write(90);
left.write(90);
}

void loop()
{

int s0 = 0;
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;

s0 = analogRead(0);//Signal pin 1 on the board
s1 = analogRead(1);//Signal pin 2 on the board
s2 = analogRead(2);//Signal pin 3 on the board
s3 = analogRead(3);//Signal pin 4 on the board
s4 = analogRead(4);//Signal pin 5 on the board
s5 = analogRead(5);//Signal pin 6 on the board

Serial.print("Mid: ");
Serial.print(mid); 
Serial.print(" ");
Serial.print(s0); 
Serial.print(" ");
Serial.print(s1); 
Serial.print(" ");
Serial.print(s2); 
Serial.print(" ");
Serial.print(s3); 
Serial.print(" ");
Serial.print(s4); 
Serial.print(" ");
Serial.print(s5); 
Serial.print(" ");
Serial.println();

right.write(180);//Move forward
left.write(0);//Move forward

delay(1);

if((((s0+s1+s2)/3)>(((s3+s4+s5)/3)+240)))//Move right
{
right.write(130);//180
left.write(90);//90
Serial.print(" RIGHT");
delay(abs((((s5+s4+s3)/3)-((s0+s1+s2)/3))/2));
}

if((((s0+s1+s2)/3)<(((s3+s4+s5)/3)-240)))//Move left
{
right.write(40);//90
left.write(0);//0
Serial.print(" LEFT");
delay(abs((((s5+s4+s3)/3)-((s0+s1+s2)/3))/2));
}

if((s0 > mid)&&(s5 > mid))//Stop if all the sensors give low 
{                         //reflectance values
right.write(90);
left.write(90);
Serial.print(" STOP");

for(int k=0; k<50; k++)
{
digitalWrite(13, HIGH);
delay(100);
digitalWrite(13, LOW);
delay(100);
}
delay(5000);
}


}
