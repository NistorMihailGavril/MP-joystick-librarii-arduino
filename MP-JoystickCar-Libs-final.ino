#define ENA 9
#define ENB 10
#define IN1 7
#define IN2 6
#define IN3 3
#define IN4 4
#define LED1 11
#define LED2 12
float x,y;
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
const int acc_pin = 2; 

int stateIN1=LOW;
int stateIN2=LOW;
int stateIN3=LOW;
int stateIN4=LOW;
int powerA=0;
int powerB=0;

void setup() {
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  MotorSetup();
  Accelerometru();
}

void MotorSetup() {
  x = analogRead(X_pin)/2 - 256;
  y = analogRead(Y_pin)/2 - 256;
  
  if(y < -30) {
    stateIN1=LOW;
    stateIN2=HIGH;
    stateIN3=HIGH;
    stateIN4=LOW;               // setarea directiei inapoi
    if(x < -30) { 
      powerA = abs(y)/(-x/127+1)-1;
      powerB = abs(y)-1;// inapoi-stanga
      
    }
    else if(x > 30) {
     
      powerA = abs(y)-1;             // inapoi-dreapta
      powerB = abs(y)/(x/127+1)-1;
    }
    else {
      
      powerA = abs(y)-1;             // inapoi
      powerB = abs(y)-1; 
    }
  }
  else if(y > 30) {
    stateIN1=HIGH;
    stateIN2=LOW;
    stateIN3=LOW;
    stateIN4=HIGH;        // setarea directiei inainte
    if(x < -30) {
      powerA = (y/(-x/127+1))/2;  // inainte-stanga
      powerB = y/2;
    }
    else if(x > 30) {
      powerA = y/2;               // inainte-dreapta
      powerB = (y/(x/127+1))/2;
    }
    else {
      powerA = y/2;               // inainte
      powerB = y/2;
    }
  }
  else if(x < -30) {
    stateIN1=LOW;
    stateIN2=HIGH;
    stateIN3=LOW;
    stateIN4=HIGH;         // setarea directiei in stanga
    powerA = abs(x);
    powerB = abs(x);
  }
  else if(x > 30) {
    stateIN1=HIGH;
    stateIN2=LOW;
    stateIN3=HIGH;
    stateIN4=LOW;         // setarea directiei in dreapta
    powerA = x;
    powerB = x;
  }
  else {
    stateIN1=LOW;
    stateIN2=LOW;
    stateIN3=LOW;
    stateIN4=LOW;         // Starea de repaos
  }
  digitalWrite(IN1,stateIN1);
  digitalWrite(IN2,stateIN2);
  digitalWrite(IN3,stateIN3);
  digitalWrite(IN4,stateIN4);
  analogWrite(ENA,powerA);
  analogWrite(ENB,powerB);
}

void Accelerometru() {
  int x = analogRead(acc_pin); 

  if((((float)x - 331.5)/65*9.8)>2.2&&(y<=0)) { // conditia pentru aprinderea ledurilor
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
  }
  else {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
  }
} 
