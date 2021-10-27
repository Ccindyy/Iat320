const int button1 = 9;
const int button2 = 6;
const int button3 = 12;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int piezoPin = 10;

const int ledPin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  
}

void loop() {
  
  bool buttonState1 = digitalRead(button1);
  bool buttonState2 = digitalRead(button2);
  bool buttonState3 = digitalRead(button3);

//Buzzer tutorial from: https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45
//Buzzer tones: https://youtu.be/K8AnlUT0ng0?t=87

  if(buttonState1 == 0) {
    tone(piezoPin, 392, 500);
    }
   if(buttonState2 == 0) {
    tone(piezoPin, 330, 500);
    }

    if(buttonState3 == 0) {
    tone(piezoPin, 261, 500);
    }

  delay(1000);
}
