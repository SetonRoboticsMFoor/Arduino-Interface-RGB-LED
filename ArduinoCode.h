// RGB LED Pins (PWM)
const int redPin   = 2;
const int greenPin = 3;
const int bluePin  = 4;

// COLOR BALANCING MULTIPLIERS (0.0 to 1.0)
// Tweak these values if colors still look off on your specific LED hardware!
const float RED_BALANCE   = 1.0;   // Red needs full power
const float GREEN_BALANCE = 0.55;  // Reduce green so it doesn't overpower red
const float BLUE_BALANCE  = 0.8;   // Slight blue adjustment for clean whites

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
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() > 0) {
      int comma1 = input.indexOf(',');
      int comma2 = input.indexOf(',', comma1 + 1);

      if (comma1 > 0 && comma2 > comma1) {
        int rVal = input.substring(0, comma1).toInt();
        int gVal = input.substring(comma1 + 1, comma2).toInt();
        int bVal = input.substring(comma2 + 1).toInt();

        rVal = constrain(rVal, 0, 255);
        gVal = constrain(gVal, 0, 255);
        bVal = constrain(bVal, 0, 255);

        // 1. Apply Gamma Correction Curve (v^2 / 255)
        float rGamma = ((float)rVal * rVal) / 255.0;
        float gGamma = ((float)gVal * gVal) / 255.0;
        float bGamma = ((float)bVal * bVal) / 255.0;

        // 2. Apply Hardware Color Balancing Factor
        int rPwm = (int)(rGamma * RED_BALANCE);
        int gPwm = (int)(gGamma * GREEN_BALANCE);
        int bPwm = (int)(bGamma * BLUE_BALANCE);

        // Drive Pins
        analogWrite(redPin, rPwm);
        analogWrite(greenPin, gPwm);
        analogWrite(bluePin, bPwm);
      }
    }
  }
}