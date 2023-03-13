const int button1Pin = 2;
const int button2Pin = 3;
const int ledPin = 13;

int button1State = 0;
int lastButton1State = 1;
int startPressedB1 = 0;
int endPressedB1 = 0;
int holdTimeB1 = 0;
int idleTimeB1 = 0;
int charGap = 250;

int button2State = 0;
int lastButton2State = 1;
int startPressedB2 = 0;
int endPressedB2 = 0;
int holdTimeB2 = 0;

bool messagePrinted = 0;

String tempSequence = "";
String sequence = "";
String message = "";

void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  
  if (button1State != lastButton1State) {
    if (messagePrinted) {
      message = "";
      sequence = "";
      tempSequence = "";
      messagePrinted = 0;
    }
    updateButton1State();
  }
  
  lastButton1State = button1State;
  
  if (button2State != lastButton2State) {
    updateButton2State();
  }

  lastButton2State = button2State;
}

void updateButton1State() {
  if (button1State == LOW) {
    startPressedB1 = millis();
    idleTimeB1 = startPressedB1 - endPressedB1;

    if (idleTimeB1 > charGap) {
      if (tempSequence != "") {
        Serial.print(" ");
      }
      message = message + convert(tempSequence);
      sequence = sequence + tempSequence + " ";
      tempSequence = "";
    }
  }
  else {
    endPressedB1 = millis();
    holdTimeB1 = endPressedB1 - startPressedB1;
    
    if (holdTimeB1 > 10 && holdTimeB1 <= 200) {
      Serial.print(".");
      tempSequence = tempSequence + ".";
    }
    if (holdTimeB1 > 300) {
      Serial.print("-");
      tempSequence = tempSequence + "-";
    }
  }
}

void updateButton2State() {
  if (button2State == LOW) {
    startPressedB2 = millis();
  }
  else {
    endPressedB2 = millis();
    holdTimeB2 = endPressedB2 - startPressedB2;
    
    if (holdTimeB2 > 0 && holdTimeB2 < 250) {
      if (tempSequence != "") {
        message = message + convert(tempSequence);
        sequence = sequence + tempSequence + " ";
        tempSequence = "";
      }
      if (message != "") {
        if (!messagePrinted) {
          Serial.println();
          Serial.print(message);
          Serial.println();
          messagePrinted = 1;
        }
        displayLED();
      }
    }
  }
}

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(150);
  digitalWrite(ledPin, LOW);
  delay(150);
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(450);
  digitalWrite(ledPin, LOW);
  delay(150);
}

void displayLED() {
  for (int i = 0; i < sequence.length(); i++) {
    if (sequence[i] == '.') {
      dot();
    }
    if (sequence[i] == '-') {
      dash();
    }
    if (sequence[i] == ' ') {
      delay(500);
    }
  }
}

String convert(String str) {
  if (str == ".-") {
    return "A";
  }
  else if (str == "-...") {
    return "B";
  }
  else if (str == "-.-.") {
    return "C";
  }
  else if (str == "-..") {
    return "D";
  }
  else if (str == ".") {
    return "E";
  }
  else if (str == "..-.") {
    return "F";
  }
  else if (str == "--.") {
    return "G";
  }
  else if (str == "....") {
    return "H";
  }
  else if (str == "..") {
    return "I";
  }
  else if (str == ".---") {
    return "J";
  }
  else if (str == "-.-") {
    return "K";
  }
  else if (str == ".-..") {
    return "L";
  }
  else if (str == "--") {
    return "M";
  }
  else if (str == "-.") {
    return "N";
  }
  else if (str == "---") {
    return "O";
  }
  else if (str == ".--.") {
    return "P";
  }
  else if (str == "--.-") {
    return "Q";
  }
  else if (str == ".-.") {
    return "R";
  }
  else if (str == "...") {
    return "S";
  }
  else if (str == "-") {
    return "T";
  }
  else if (str == "..-") {
    return "U";
  }
  else if (str == "...-") {
    return "V";
  }
  else if (str == ".--") {
    return "W";
  }
  else if (str == "-..-") {
    return "X";
  }
  else if (str == "-.--") {
    return "Y";
  }
  else if (str == "--..") {
    return "Z";
  }
  else if (str == ".----") {
    return "1";
  }
  else if (str == "..---") {
    return "2";
  }
  else if (str == "...--") {
    return "3";
  }
  else if (str == "....-") {
    return "4";
  }
  else if (str == ".....") {
    return "5";
  }
  else if (str == "-....") {
    return "6";
  }
  else if (str == "--...") {
    return "7";
  }
  else if (str == "---..") {
    return "8";
  }
  else if (str == "----.") {
    return "9";
  }
  else if (str == "-----") {
    return "0";
  }
  else {
    return "";
  }
}
