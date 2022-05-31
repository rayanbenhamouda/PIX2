#include <Servo.h>

//initialisation
int init1 = 0;
//--------------------------------------------servo 
//------------------servo 1
int PS1 = 5;
Servo myservo1;
const int tape = 2;
const int grate = 3;
//------------------servo 2
int PS2 = 6;
Servo myservo2;
const int tape_conserve = 18;
const int tape_corde = 19;
//------------------servo 3
int PS3 = 7;
Servo myservo3;
const int secoue_bille = 20;
//------------------PIN Validation
const int validate = 21;

//------------------------------------------ taille du tableau 
const int taille = 10;
int arrayOne[taille] = {} ;

// Afichage 
volatile byte compteur = 0;

int digit1 = A1;
int digit2 = A2;
int digit3 = A3;
int digit4 = A4;
/*
int A = 31;
int B = 32;
int C = 35;
int D = 36;
int E = 37;
int F = 30;
int G = 33;

int dp = 34;
*/
int A = 31;
int B = 34;
int C = 33;
int D = 32;
int E = 37;
int F = 35;
int G = 36;

int dp = 30;

// Variable utilisateur
volatile byte state1 = 0;

void setup() {
  myservo1.attach(PS1);
  attachInterrupt(digitalPinToInterrupt(tape), boutonpress1, RISING);
  attachInterrupt(digitalPinToInterrupt(grate), boutonpress2, RISING);
  
  myservo2.attach(PS2);
  attachInterrupt(digitalPinToInterrupt(tape_conserve), boutonpress3, RISING);
  attachInterrupt(digitalPinToInterrupt(tape_corde), boutonpress4, RISING);

  myservo3.attach(PS3);
  attachInterrupt(digitalPinToInterrupt(secoue_bille), boutonpress5, RISING);
  attachInterrupt(digitalPinToInterrupt(validate), boutonpress6, RISING);

  //AFFICHEUR
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  //Désactivation de tous les digits
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);
  
  myservo3.write(90);
  myservo2.write(90);
  myservo3.write(0);
  Serial.begin(9600);
}
//---------------------------------------------------------------------------------------Main Function
void loop() {
  //----------------------------------------initialization function 
  if(init1==0){
    Serial.println("valeur contenu dans le tableau");
    Serial.print("[");
    for(int i=0; i<taille; i++){
      arrayOne[i]=0;
      Serial.print(arrayOne[i]);
      
    }
    Serial.println("]");
    Serial.println("fin de l'initialisation");
    init1=1;
    state1 = 0;
  }
  //----------------------------------------taper function
  if(state1==1 && compteur!=taille){
    Serial.println("taper");
    taper();
    arrayOne[compteur]=1;
    compteur = compteur+1;
    state1 = 0;
    
  }//----------------------------------------gratter function
  else if(state1==2 && compteur!=taille){
    Serial.println("gratter");
    gratter();
    arrayOne[compteur]=2;
    compteur = compteur+1;
    state1 = 0;
  }//----------------------------------------taper boite de conserve function
  else if(state1==3 && compteur!=taille){
    Serial.println("taper boite de conserve");
    boite_conserve_taper();
    arrayOne[compteur]=3;
    compteur = compteur+1;
    state1 = 0;
  }//----------------------------------------Taper Corde function
  else if(state1==4 && compteur!=taille){
    Serial.println("taper corde");
    corde_taper();
    arrayOne[compteur]=4;
    compteur = compteur+1;
    state1 = 0;
  }//----------------------------------------Secouer bille function
  else if(state1==5 && compteur!=taille){
    Serial.println("secoue");
    secouer();
    arrayOne[compteur]=5;
    compteur = compteur+1;
    state1 = 0;
  }
  //----------------------------------------repeat function 
  if(compteur==taille){
    Serial.println("repeat");
    repeat();
    init1=0;
    compteur=0;
    state1 = 0;
  }
  setAfficheur(taille-compteur);
  //  setAfficheur(8888);
  //afficheDemo();
}
//---------------------------------------------------------------------------------------Other Function
//----------------------------------------Interupt Function
void boutonpress1(){
  state1 = 1;
}
void boutonpress2(){
  state1 = 2;
}
void boutonpress3(){
  state1 = 3;
}
void boutonpress4(){
  state1 = 4;
}
void boutonpress5(){
  state1 = 5;
}
void boutonpress6(){
  compteur = taille;
}
//----------------------------------------music Function
//----------------------gratter boite de conserve
void gratter(){
  myservo1.write(50);
  delay(1000);
  myservo1.write(90);
}
//----------------------taper xylophone
void taper(){
  myservo1.write(180);
  delay(1000);
  myservo1.write(90);
}
//----------------------Taper boite de conserve 
void boite_conserve_taper(){
  myservo2.write(0);
  delay(1000);
  myservo2.write(90);
}
//----------------------Taper boite de conserve 
void corde_taper(){
  myservo2.write(180);
  delay(1000);
  myservo2.write(90);
}
//----------------------Secouer les billes
void secouer(){
  myservo3.write(0);
  delay(1000);
  myservo3.write(180);
  delay(1000);
  myservo3.write(0);
  delay(1000);
  myservo3.write(180);
  delay(1000);
  myservo3.write(0);
  delay(1000);
}
//----------------------repete 
void repeat(){
  int test = 0;
  for(int i=0;i<taille;i++){
    /*compteur-=1;
    setAfficheur(taille-compteur);*/
    if(arrayOne[0]==0){
       test = 1;
       afficheTest();
    }
    if(test==1){
      arrayOne[i]=random(1,6);
    }
    if(arrayOne[i]==0){
      Serial.println("end repeat");
      return;
     }
    delay(1000);
    int x = arrayOne[i];
    Serial.print(i);
    Serial.print("->");
    Serial.println(x);
    switch(x){
      case 1:
          taper();
          break;
      case 2:
          gratter();
          break;
      case 3:
          boite_conserve_taper();
          break;
      case 4:
          corde_taper();
          break;
      case 5:
          secouer();
          break;
      default:
          continue;
    }
  }
  Serial.println("end repeat");
}


//----------------------Afficheur
void setNumber(int nombre){
  switch(nombre){
    case 1:
      digitalWrite(A, 0);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      digitalWrite(E, 0);
      digitalWrite(F, 0);
      digitalWrite(G, 0);
      break;
    case 2:
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 0);
      digitalWrite(D, 1);
      digitalWrite(E, 1);
      digitalWrite(F, 0);
      digitalWrite(G, 1);
      break;
    case 3:
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      digitalWrite(E, 0);
      digitalWrite(F, 0);
      digitalWrite(G, 1);
      break;
    case 4:
      digitalWrite(A, 0);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      digitalWrite(E, 0);
      digitalWrite(F, 1);
      digitalWrite(G, 1);
      break;
    case 5:
      digitalWrite(A, 1);
      digitalWrite(B, 0);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      digitalWrite(E, 0);
      digitalWrite(F, 1);
      digitalWrite(G, 1);
      break;
    case 6:
      digitalWrite(A, 1);
      digitalWrite(B, 0);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      digitalWrite(E, 1);
      digitalWrite(F, 1);
      digitalWrite(G, 1);
      break;
    case 7:
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      digitalWrite(E, 0);
      digitalWrite(F, 0);
      digitalWrite(G, 0);
      break;
    case 8:
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      digitalWrite(E, 1);
      digitalWrite(F, 1);
      digitalWrite(G, 1);
      break;
    case 9:
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      digitalWrite(E, 0);
      digitalWrite(F, 1);
      digitalWrite(G, 1);
      break;
    case 0:
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 1);
      digitalWrite(E, 1);
      digitalWrite(F, 1);
      digitalWrite(G, 0);
      break;
    default:
      digitalWrite(A, 0);
      digitalWrite(B, 0);
      digitalWrite(C, 0);
      digitalWrite(D, 0);
      digitalWrite(E, 0);
      digitalWrite(F, 0);
      digitalWrite(G, 1);
      break;
    break;
  }
}

void setDigit(int digit, int nombre) {
  switch(digit) {
    case 1 :
      digitalWrite(digit1, LOW) ;
      digitalWrite(digit2, HIGH) ;
      digitalWrite(digit3, HIGH) ;
      digitalWrite(digit4, HIGH) ;
      setNumber(nombre) ;
      break;
    case 2 :
      digitalWrite(digit1, HIGH) ;
      digitalWrite(digit2, LOW) ;
      digitalWrite(digit3, HIGH) ;
      digitalWrite(digit4, HIGH) ;
      setNumber(nombre) ;
      break;
    case 3 :
      digitalWrite(digit1, HIGH) ;
      digitalWrite(digit2, HIGH) ;
      digitalWrite(digit3, LOW) ;
      digitalWrite(digit4, HIGH) ;
      setNumber(nombre) ;
    break;
    case 4 :
      digitalWrite(digit1, HIGH) ;
      digitalWrite(digit2, HIGH) ;
      digitalWrite(digit3, HIGH) ;
      digitalWrite(digit4, LOW) ;
      setNumber(nombre) ;
    break;
  }
}

void setAfficheur(int nombre) {
  int M = nombre/1000, C = (nombre-M*1000)/100, D = (nombre-M*1000-C*100)/10, U=(nombre-M*1000-C*100-D*10) ;
  setDigit(4, U) ;
  delay(2);
  setDigit(3, D) ;
  delay(2);
  setDigit(2, C) ;
  delay(2);
  setDigit(1, M) ;
  delay(2);
}

void afficheTest(){
   digitalWrite(digit1, HIGH) ;
  digitalWrite(digit2, HIGH) ;
  digitalWrite(digit3, HIGH) ;
  digitalWrite(digit4, LOW) ;
  digitalWrite(A, 0);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  digitalWrite(E, 1);
  digitalWrite(F, 1);
  digitalWrite(G, 1);
  delay(20);
   digitalWrite(digit1, HIGH) ;
  digitalWrite(digit2, HIGH) ;
  digitalWrite(digit3, LOW) ;
  digitalWrite(digit4, HIGH) ;
  digitalWrite(A, 1);
  digitalWrite(B, 0);
  digitalWrite(C, 1);
  digitalWrite(D, 1);
  digitalWrite(E, 0);
  digitalWrite(F, 1);
  digitalWrite(G, 1);
   delay(20);
  digitalWrite(digit1, HIGH) ;
  digitalWrite(digit2, LOW) ;
  digitalWrite(digit3, HIGH) ;
  digitalWrite(digit4, HIGH) ;
  digitalWrite(A, 1);
  digitalWrite(B, 1);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  digitalWrite(E, 1);
  digitalWrite(F, 1);
  digitalWrite(G, 1);
   delay(20);
 
   digitalWrite(digit1, LOW) ;
  digitalWrite(digit2, HIGH) ;
  digitalWrite(digit3, HIGH) ;
  digitalWrite(digit4, HIGH) ;
  digitalWrite(A, 0);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 1);
  digitalWrite(E, 1);
  digitalWrite(F, 1);
  digitalWrite(G, 1);
  delay(20);
  digitalWrite(digit1, LOW) ;
  digitalWrite(digit2, LOW) ;
  digitalWrite(digit3, LOW) ;
  digitalWrite(digit4, LOW) ;
 
  
}
