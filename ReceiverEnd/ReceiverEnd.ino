const int sensor = A0;  //sensor connected to analog pin A0
const int vcc = 8;      //connecting sensor to VCC of the arduino resulted in false outputs
const int led = 9;

int counter = 0;
int zeroCounter = 0;
int flag = 0;

int sensorValue = 0;   
int value = 0;

String answer = "WrongAnswer";
String finalAnswer = "";

byte textBuf[ 12 ];
byte *text;

const int threshold = 900;  //this needs to be changed according to your threshold value of the sensor which indicates a 1 
const int delayValue = 100; //delay value in milisecond per bit

//waits for 8-bit Ones to receive
void checkInput(){

  counter = 0;
  Serial.println("Waiting for Input");
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  
  while(counter !=8){
   if(analogRead(sensor) < threshold){
    counter++;
   }
   else {counter = 0;}
   delay(delayValue);
  }
  
}

//after 8-bit 1's are received
//if current sensor value is greater than threshold value, append 1 at the answer
//if current sensor value is lesser than threshold value , append 0 at the answer
void receiveData(){

    answer = "";
    zeroCounter = 0;
    Serial.println("Reading Start");
    while(zeroCounter != 8){
    
      sensorValue = analogRead(sensor);
  
      if(sensorValue < threshold){
        answer += "1" ;
        zeroCounter = 0;
        digitalWrite(led,HIGH);
      }
      else {
        answer += "0";
        zeroCounter++;
        digitalWrite(led,LOW);
      }
     delay(delayValue);
    }
}

//converts binary to string
void printAnswer(String binaryText){

  int space = 0;
  
  text = textBuf;
  *text = 0;

  for(int i=0;i<binaryText.length();i++)
  {
    
    if ( space != 8 )
    {
      (*text) *= 2; // without those parens the compiler makes it *(text *= 2);
      if ( binaryText[i] == '1' )  (*text)++; // without the parens it becomes *(text++);
    }
    else
    {
      space = 0;
      text++;
      *text = 0;
    }

    space++;
  }
  
  Serial.print((char *) textBuf );
  Serial.println(  );
}

void setup() {
  
  Serial.begin(9600);
  pinMode(vcc,OUTPUT);
  digitalWrite(vcc,HIGH);
  delay(3000);
  counter = 0;
  finalAnswer = "";
  
}

void loop() {
  
  checkInput();
  receiveData();

  Serial.println(answer);
  printAnswer(answer);
  
}