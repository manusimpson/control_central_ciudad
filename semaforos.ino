int rojo1=1; int rojo5=5;
int rojo2=2; int rojo6=6;
int rojo3=3; int rojo7=7;
int rojo4=4; int rojo8=8;

int verde1=11; int verde5=15;
int verde2=12; int verde6=16;
int verde3=13; int verde7=17;
int verde4=14; int verde8=18;

int amarillo1=21; int amarillo5=25;
int amarillo2=22; int amarillo6=26;
int amarillo3=23; int amarillo7=27;
int amarillo4=24; int amarillo8=28;

int CAMBIO_S=10000;

void setup() {

 pinMode(rojo1, OUTPUT); pinMode(rojo5, OUTPUT);
 pinMode(rojo2, OUTPUT); pinMode(rojo6, OUTPUT);
 pinMode(rojo3, OUTPUT); pinMode(rojo7, OUTPUT);
 pinMode(rojo4, OUTPUT); pinMode(rojo8, OUTPUT);
 
 pinMode(verde1, OUTPUT); pinMode(verde5, OUTPUT);
 pinMode(verde2, OUTPUT); pinMode(verde6, OUTPUT);
 pinMode(verde3, OUTPUT); pinMode(verde7, OUTPUT);
 pinMode(verde4, OUTPUT); pinMode(verde8, OUTPUT);

 pinMode(amarillo1, OUTPUT); pinMode(amarillo5, OUTPUT);
 pinMode(amarillo2, OUTPUT); pinMode(amarillo6, OUTPUT);
 pinMode(amarillo3, OUTPUT); pinMode(amarillo7, OUTPUT);
 pinMode(amarillo4, OUTPUT); pinMode(amarillo8, OUTPUT);

 digitalWrite(rojo1, LOW);digitalWrite(verde1, HIGH);digitalWrite(amarillo1, LOW);
 digitalWrite(rojo2, HIGH);digitalWrite(verde2, LOW);digitalWrite(amarillo2, LOW);
 digitalWrite(rojo3, LOW);digitalWrite(verde3, HIGH);digitalWrite(amarillo3, LOW);
 digitalWrite(rojo4, HIGH);digitalWrite(verde4, LOW);digitalWrite(amarillo4, LOW);
 digitalWrite(rojo5, LOW);digitalWrite(verde5, HIGH);digitalWrite(amarillo5, LOW);
 digitalWrite(rojo6, HIGH);digitalWrite(verde6, LOW);digitalWrite(amarillo6, LOW);
 digitalWrite(rojo7, LOW);digitalWrite(verde7, HIGH);digitalWrite(amarillo7, LOW);
 digitalWrite(rojo8, HIGH);digitalWrite(verde8, LOW);digitalWrite(amarillo8, LOW);

}

void loop() {
VRSem();
}

void VRSem()
{
  static unsigned long tiempo=0, tiempoA=0;
  static unsigned char etapa=0;
  bool banderaRI,banderaRP=true;

  switch (etapa)
  {

  case 0:
         amarillosI();
         etapa=1;
         banderaRI=true;
         tiempoA=millis();
  break;
  case 1:if (banderaRI)
            {
              if((millis()-tiempoA)>1000)
                rojosI();
              if((millis()-tiempo)>10000)
              {
              etapa=2;
              banderaRI=false;
              tiempo=millis();
              }
            }
  
    break;
  case 2:
          amarillosP();
          if((millis()-tiempoA)>1000)
          etapa=3;
          banderaRP=true;
    break;
  case 3:
          if (banderaRP)
          {
            rojosP();
            if((millis()-tiempo)>10000)
            {
            etapa=0;
            banderaRP=false;
            tiempo=millis();
            }
          }
    break;

  default:
    break;
  }
}
void rojosI()
{
  digitalWrite(amarillo1, LOW);
  digitalWrite(amarillo3, LOW);
  digitalWrite(amarillo5, LOW);
  digitalWrite(amarillo7, LOW);

  digitalWrite(rojo1, HIGH);
  digitalWrite(rojo3, HIGH);
  digitalWrite(rojo5, HIGH);
  digitalWrite(rojo7, HIGH);

  digitalWrite(verde2, HIGH);
  digitalWrite(verde4, HIGH);
  digitalWrite(verde6, HIGH);
  digitalWrite(verde8, HIGH);
  }
void rojosP()
{
  digitalWrite(amarillo2, LOW);
  digitalWrite(amarillo4, LOW);
  digitalWrite(amarillo6, LOW);
  digitalWrite(amarillo8, LOW);

  digitalWrite(rojo2, HIGH);
  digitalWrite(rojo4, HIGH);
  digitalWrite(rojo6, HIGH);
  digitalWrite(rojo8, HIGH);

  digitalWrite(verde1, HIGH);
  digitalWrite(verde3, HIGH);
  digitalWrite(verde5, HIGH);
  digitalWrite(verde7, HIGH);
}

void amarillosI()
{
  digitalWrite(verde1, LOW);
  digitalWrite(verde3, LOW);
  digitalWrite(verde5, LOW);
  digitalWrite(verde7, LOW);

  digitalWrite(amarillo1, HIGH);
  digitalWrite(amarillo3, HIGH);
  digitalWrite(amarillo5, HIGH);
  digitalWrite(amarillo7, HIGH);
}
void amarillosP()
{
  digitalWrite(verde2, LOW);
  digitalWrite(verde4, LOW);
  digitalWrite(verde6, LOW);
  digitalWrite(verde8, LOW);

  digitalWrite(amarillo2, HIGH);
  digitalWrite(amarillo4, HIGH);
  digitalWrite(amarillo6, HIGH);
  digitalWrite(amarillo8, HIGH);
}
