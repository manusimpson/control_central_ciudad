int rojoImp=4; int rojoPar=5;
int verdeImp=6; int verdePar=7;
int amarilloImp=8; int amarilloPar=9;

int CAMBIO_S=10000;

void setup() {

 pinMode(rojoImp, OUTPUT); pinMode(rojoPar, OUTPUT);
 
 pinMode(verdeImp, OUTPUT); pinMode(verdePar, OUTPUT);

 pinMode(amarilloImp, OUTPUT); pinMode(amarilloPar, OUTPUT);

 digitalWrite(rojoImp, LOW);digitalWrite(verdeImp, HIGH);digitalWrite(amarilloImp, LOW);
 digitalWrite(rojoPar, HIGH);digitalWrite(verdePar, LOW);digitalWrite(amarilloPar, LOW);

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
         digitalWrite(verdeImp,LOW);
         digitalWrite(amarilloImp,HIGH);
         etapa=1;
         banderaRI=true;
         tiempoA=millis();
  break;
  case 1:if (banderaRI)
            {
              if((millis()-tiempoA)<1000)
                break;
              digitalWrite(amarilloImp,LOW);
              digitalWrite(rojoImp,HIGH);
              digitalWrite(verdePar,HIGH);
              
              if((millis()-tiempo)>10000)
              {
                etapa=2;
                banderaRI=false;
                tiempo=millis();
              }
            }
  
    break;
  case 2:
          digitalWrite(verdePar,LOW);
          digitalWrite(amarilloPar,HIGH);
          etapa=3;
          banderaRP=true;
    break;
  case 3:
          if (banderaRP)
          {
            if((millis()-tiempoA)<1000)
                break;
            digitalWrite(amarilloPar,LOW);
            digitalWrite(rojoPar,HIGH);
            digitalWrite(verdeImp,HIGH);

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
