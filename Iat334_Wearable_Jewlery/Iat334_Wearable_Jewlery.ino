int led = 9;
void setup() {
  // put your setup code here, to run once:
pinMode(led, OUTPUT);
}

void loop() {
  //first thump
  
  digitalWrite(led, HIGH);  
  delay(250);                       
  digitalWrite(led, LOW);
  delay(100);  
  //second thump
  digitalWrite(led, HIGH);  
  delay(500);                       
  digitalWrite(led, LOW);
  delay(1000);      

}
