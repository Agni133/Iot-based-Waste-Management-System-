#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);//RS,EN,D4,D5,D6,D7
#include <Servo.h>
#define ir1 A1
#define sen1 A0 // moisture
#define buzzer 2
#define theft A2
#define trigPin1 5////right
#define echoPin1 4
#define trigPin2 7  //// front
#define echoPin2 6
int lvl1=0;
 int  lvl2=0;
int chori=0;
long duration, distance,sensor1,sensor2; // us variable
int onetime=0,onetime1=0 ;
int wet=0,moisture=0,object=0,cabin2=0,c1=0,c2=0;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most board
void setup() 
{
 Serial.begin(9600);
 lcd.begin(16, 2);//initializing LCD
 lcd.setCursor(0,0); 
 lcd.print("Automatic WASTE");
 lcd.setCursor(0,1); 
 lcd.print("Segregation sys");
 delay(3000);
 pinMode(ir1,INPUT);
 pinMode(theft,INPUT);
 pinMode(sen1,INPUT);
 pinMode(buzzer,OUTPUT);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 myservo.attach(3);  // attaches the servo on pin 9 to the servo object
 myservo.write(85);
 delay(3000);
}

void loop() 
{
 chori=digitalRead(theft);
 if(chori==HIGH){digitalWrite(buzzer,HIGH); lcd.setCursor(0,1); 
  lcd.print("theft Alert!");}
 else{digitalWrite(buzzer,LOW);}
 moisture=analogRead(sen1);
 Serial.print("moisture = ");
 Serial.println(moisture);
 delay(500);
 //////////////////////////////////////////////////////
 ultrasensor(trigPin1, echoPin1);
 sensor1 = distance;
 delay(10);
 
  ultrasensor(trigPin2, echoPin2);
  sensor2 = distance;    
  delay(10);
  
  Serial.println(sensor1);
  Serial.println(sensor2);
  
  int lvl1=(16-sensor1)*6.5;
  int lvl2=(16-sensor2)*6.5;
  Serial.println(lvl1);
  Serial.println(lvl2);
  if(lvl1<0){lvl1=0;}
  if(lvl2<0){lvl2=0;}
  if(lvl1>100){lvl1=100;}
  if(lvl2>100){lvl2=100;}
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("moisture: ");
  lcd.setCursor(12,0); 
  lcd.print(moisture);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,1); 
  lcd.print("DL= ");
  lcd.setCursor(4,1); 
  lcd.print(lvl1);
  lcd.setCursor(8,1); 
  lcd.print("WL= ");
  lcd.setCursor(13,1); 
  lcd.print(lvl2);
  delay(1000);
  if(lvl1 <= 100 && lvl1 >= 70)
  {      
   if(onetime==0)
   {
     lcd.setCursor(0,0); 
     lcd.print("-send msg-");
     digitalWrite(buzzer,HIGH); 
     // tracking1(); 
     digitalWrite(buzzer,LOW);
     onetime=1;
   }
  }
  else if (lvl2 <= 100 && lvl2 >= 70)
  {
    if(onetime1==0)
    {
      lcd.setCursor(0,0); 
  lcd.print("-send msg-");
     digitalWrite(buzzer,HIGH); 
     
     
     //tracking();
     digitalWrite(buzzer,LOW);
     onetime1=1; 
    }
  }
else
{
 onetime=0;
 onetime1=0;
}
/////////////////////////////////////////////////////
  object=digitalRead(ir1);
  moisture=analogRead(sen1);
  if(object==LOW)
  {
   moisture=analogRead(sen1);
   lcd.setCursor(0,0); 
   lcd.print("-GARBAGE SENSE-");
   digitalWrite(buzzer,HIGH);
   delay(150);
   digitalWrite(buzzer,LOW);
   delay(1000);
   moisture=analogRead(sen1);
   Serial.print("moisture = ");
   Serial.println(moisture);
   delay(500);
   moisture=analogRead(sen1);
   Serial.print("moisture = ");
   Serial.println(moisture);
   delay(500);
   //delay(2000);
   if(moisture>=40)                         
   {
    lcd.setCursor(0,0); 
    lcd.print(" WET  GARBAGE");
    myservo.write(35);
    delay(5000);
    myservo.write(85);
    delay(2000);
    Serial.println("wet");
   }
   else if(moisture<100)
   {  
    lcd.setCursor(0,0); 
    lcd.print(" dry  GARBAGE");
    myservo.write(145); 
    delay(5000);
    myservo.write(85);
    delay(2000);
    Serial.println("moisture");
    lcd.clear();
   } 
    
  } 
        
 }

 
 void init_sms()
 {
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"+9199780347\"");   // use your 10 digit cell no. here
  delay(400);
 }

 void init_sms1()
 {
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"+9199710347\"");   // use your 10 digit cell no. here
  delay(400);
 }
  
 void send_data(String message)
 {
  Serial.println(message);
  delay(200);
 }
 
 void send_sms()
 {
  Serial.write(26);
 }
 
 void tracking1()
 {
  init_sms();
  send_data("KEC  dustbin's dry side  is full:\n");
  send_sms();
  delay(5000);

   init_sms1();
  send_data("KEC  dustbin's dry side  is full:\n");
  send_sms();
  delay(5000);
 }
  void tracking()
 {
  init_sms();
  send_data("KEC  dustbin's wet side  is full:\n");
  send_sms();
  delay(5000);
  init_sms1();
  send_data("KEC dustbin's wet side  is full:\n");
  send_sms();
  delay(5000);
 }
 void ultrasensor(int trigPin,int echoPin)
 { 
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 }
