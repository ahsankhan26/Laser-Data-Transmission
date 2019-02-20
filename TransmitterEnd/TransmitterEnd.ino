const int laser = 8;  //pin number the laser is connected to
const int delayValue = 100; //dekay in miliseconds per bit

String myText = "Your Text Here"; //the string that needs to be sent
String sequence = "WrongAnswer";

//getInput takes the "myText" variable and converts the string into binary and returns in "sequence" variable
String getInput(String input){

  String loopSequence = "";
  
   for(int i=0; i<input.length(); i++){

   char myChar = input.charAt(i);
  
    for(int i=7; i>=0; i--){
      byte bytes = bitRead(myChar,i);
      loopSequence += bytes;
    }
  }
  return loopSequence;
}

//transmits the 'sequence' variable onto laser.
// '1' in string = laser on
// '0' in string = laser off
void transmitData(String sequence){
  
  for(int i=0; i<sequence.length();i++){
    
    if(sequence[i] == '1'){
      digitalWrite(laser,HIGH);
      Serial.print(sequence[i]);
    }
    else{
      digitalWrite(laser,LOW);
      Serial.print(sequence[i]);
     }
  
    delay(delayValue);
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(laser,OUTPUT);
  digitalWrite(laser,LOW);
  
  delay(3000);  //starts after 3 seconds

  //sends an 8-bit high sequence then the input sequence
  //receiver starts reading afte the 8-bit input
  for(int i=0;i<8;i++){
    digitalWrite(laser,HIGH);
    delay(delayValue);
  }
}

void loop() {
    sequence = "";
  Serial.println(myText);
  
  sequence = getInput(myText);  //converting string to binary
  Serial.println(sequence);
  
  transmitData(sequence); //sending the binary sequence

  //8-bit 0s are sent to stop reading
  for(int i=0;i<8;i++){
    digitalWrite(laser,LOW);
    delay(delayValue);
  }
 
}