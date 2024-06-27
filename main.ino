const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Pins connected to the segments (a-g)

// Segment configurations for letters A-Z and turning off the display
const byte letterPatterns[27] = {
  B01110111, // A
  B01111111, // B
  B00111001, // C
  B00111111, // D
  B01111001, // E
  B01110001, // F
  B01101111, // G
  B01110110, // H
  B00000110, // I
  B00011110, // J
  B01110101, // K
  B00111000, // L
  B00010101, // M
  B00110111, // N
  B00111111, // O
  B01110011, // P
  B01100111, // Q
  B00110001, // R
  B01101101, // S
  B01111000, // T
  B00111110, // U
  B00111110, // V
  B00011101, // W
  B01110110, // X
  B01101110, // Y
  B01011011, // Z
  B00000000  // Blank (off)
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Removes any whitespace from the start and end of the string

    if (command.length() == 1 && isAlpha(command[0])) {
      char letter = toupper(command[0]);
      displayLetter(letter);
      Serial.print("Displaying: ");
      Serial.println(letter);
    } else if (command == "off") {
      displayLetter(' '); // Turn off the display
      Serial.println("Display off");
    } else {
      Serial.println("Invalid command. Please enter a single letter (A-Z) or 'off' to turn off display.");
    }
  }
}

void displayLetter(char letter) {
  byte pattern;
  if (letter == ' ') {
    pattern = letterPatterns[26]; // Blank pattern
  } else if (letter >= 'A' && letter <= 'Z') {
    pattern = letterPatterns[letter - 'A'];
  } else {
    return;
  }
  
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], bitRead(pattern, i));
  }
}
