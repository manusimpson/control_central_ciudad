#include <Servo.h>  
Servo servo;     

int trigPin = 5;    
int echoPin = 6;
int servoPin = 7;
unsigned long tiempoBarrera=0;
long duration, promedio;   

long aver[3];  


void setup() 
{       
  Serial.begin(9600);

  servo.attach(servoPin);  
    
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
    
  servo.write(0);         
  servo.detach(); 
}
 

long measure() 
{  
 //digitalWrite(10,HIGH);
 long dist=0;
digitalWrite(trigPin, LOW);

delayMicroseconds(5);

digitalWrite(trigPin, HIGH);

delayMicroseconds(15);

digitalWrite(trigPin, LOW);

pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);

dist = (duration/2) / 29.1;
Serial.println(dist);    
return dist;
}

void barreraArriba()
{
  for (int i=0;i<=2;i++) 
{   //average distance
    aver[i]=measure();            
    delay(10);             
}
 promedio=(aver[0]+aver[1]+aver[2])/3;    

  if ( promedio < 10 ) {
  //Change distance as per your need
    servo.attach(servoPin);
    delay(1);
    servo.write(90);
    tiempoBarrera=millis();        
    }
}

void barreraAbajo()
{
  servo.write(0);    
  servo.detach();
}

void loop() 
{ 
  barreraArriba();
  if((millis()-tiempoBarrera)>10000)
  barreraAbajo();
}
