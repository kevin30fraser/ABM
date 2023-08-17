#include <SoftwareSerial.h>



#define trigPin 9


#define echoPin 10


#define piezoPin 8


SoftwareSerial mySerial(2, 3); //here software serial pin defined


int normalDistance;


boolean triggered = false;


long duration, distance;


void setup()


{


mySerial.begin(9600); //serial monitor


Serial.begin (9600);


delay(100);


pinMode(trigPin, OUTPUT);


pinMode(echoPin, INPUT);


pinMode(piezoPin, OUTPUT);


digitalWrite(piezoPin, HIGH);


long duration, distance;


while (millis() < 5000)


{


digitalWrite(piezoPin, HIGH);


digitalWrite(trigPin, LOW);


delayMicroseconds(20);


digitalWrite(trigPin, HIGH);


delayMicroseconds(100);


digitalWrite(trigPin, LOW);


duration = pulseIn(echoPin, HIGH);


distance= duration*0.034/2;


normalDistance = distance;


Serial.print("Distance: ");


Serial.println(distance);


digitalWrite(piezoPin, LOW);


} }


void loop()


{


digitalWrite(trigPin, LOW);


delayMicroseconds(2);


digitalWrite(trigPin, HIGH);


delayMicroseconds(10);


digitalWrite(trigPin, LOW);


duration = pulseIn(echoPin, HIGH);


distance= duration*0.034/2;


Serial.print("Distance: ");


Serial.println(distance);


if (distance < normalDistance+5)


{


triggered = true;


}


else


{


triggered = false;


}


if (triggered)


{


tone(piezoPin, 635);


delay(500);


tone(piezoPin, 912);


delay(250);


mySerial.println("AT+CMGF=1");


//Sets the GSM Module in Text Mode


delay(1000);

//delay of 1000 milli seconds or 1 second

mySerial.println("AT+CMGS=\"+917010871499\"\r"); // Replace your number get the alert sms




delay(1000);


mySerial.println("DUST BIN IS FULL"); //this text was written on the sms which come on your mobile number.


// The SMS text you want to send

delay(100);


mySerial.println((char)26);


// ASCII code of CTRL+Z


delay(1000);


} }
