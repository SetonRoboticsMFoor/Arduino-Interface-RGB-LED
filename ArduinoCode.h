// RGB LED Pins (PWM)
const int redPin   = 2;
const int greenPin = 3;
const int bluePin  = 4;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Start with LED off
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the line sent from JavaScript (Format: "R,G,B\n")
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() > 0) {
      // Parse comma-separated values
      int comma1 = input.indexOf(',');
      int comma2 = input.indexOf(',', comma1 + 1);

      if (comma1 > 0 && comma2 > comma1) {
        int rVal = input.substring(0, comma1).toInt();
        int gVal = input.substring(comma1 + 1, comma2).toInt();
        int bVal = input.substring(comma2 + 1).toInt();

        // Constrain inputs to 0-255
        rVal = constrain(rVal, 0, 255);
        gVal = constrain(gVal, 0, 255);
        bVal = constrain(bVal, 0, 255);

        // Apply gamma/exponential curve to each channel for accurate perception
        int rPwm = (long)rVal * rVal / 255;
        int gPwm = (long)gVal * gVal / 255;
        int bPwm = (long)bVal * bVal / 255;

        // Drive PWM output pins
        analogWrite(redPin, rPwm);
        analogWrite(greenPin, gPwm);
        analogWrite(bluePin, bPwm);
      }
    }
  }
}