// Arduino 12-LED Light Chaser with Multiple Patterns
// Create mesmerizing lighting effects with 12 LEDs

// Pin definitions for 12 LEDs (using Arduino Uno pins 2-13)
const int numLeds = 12;
const int ledPins[numLeds] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

// Pattern speed control (lower = faster)
int delayTime = 100;  // Default delay time in milliseconds

// Brightness levels for fade effects (only matters for PWM pins)
const int brightnessLevels = 5;
int brightness[brightnessLevels] = {0, 64, 128, 192, 255};

void setup() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);  // Ensure all LEDs start off
  }
}

void loop() {
  // Run through various patterns
  basicChase();            // Simple chase pattern
  bouncePattern();         // Bounce back and forth
  multiLedChase(3);        // 3 LEDs on at once
  randomFlicker(30);       // Random LED flickering
  fadeInOutPattern();      // Fading effect (works best on PWM pins)
  convergeDiverge();       // Converging and diverging pattern
  allOnAllOff(3);          // All LEDs on then off
}

// PATTERN 1: Basic chase - one LED at a time in sequence
void basicChase() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[i], LOW);
  }
}

// PATTERN 2: Bounce - back and forth pattern
void bouncePattern() {
  // Forward
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[i], LOW);
  }
  
  // Backward
  for (int i = numLeds - 2; i > 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[i], LOW);
  }
}

// PATTERN 3: Multiple LEDs chase - several LEDs on at once
void multiLedChase(int numActive) {
  // Make sure numActive is valid
  if (numActive > numLeds) numActive = numLeds;
  
  // Turn off all LEDs to start
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  
  // Run the chase pattern
  for (int i = 0; i < numLeds; i++) {
    // Turn on current LED
    digitalWrite(ledPins[i], HIGH);
    
    // Turn off LED that's now out of range
    if (i >= numActive) {
      digitalWrite(ledPins[i - numActive], LOW);
    }
    
    delay(delayTime);
  }
  
  // Turn off remaining LEDs at the end
  for (int i = numLeds - numActive; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
    delay(delayTime);
  }
}

// PATTERN 4: Random flickering
void randomFlicker(int iterations) {
  for (int i = 0; i < iterations; i++) {
    int randomLed = random(numLeds);  // Pick a random LED
    digitalWrite(ledPins[randomLed], HIGH);
    delay(delayTime / 2);
    digitalWrite(ledPins[randomLed], LOW);
    delay(delayTime / 2);
  }
}

// PATTERN 5: Fade in/out (works best with PWM pins: 3, 5, 6, 9, 10, 11)
void fadeInOutPattern() {
  // Use only PWM pins for best effect
  int pwmPins[] = {3, 5, 6, 9, 10, 11};
  int numPwmPins = 6;
  
  // For each PWM pin
  for (int i = 0; i < numPwmPins; i++) {
    // Fade in
    for (int brightness = 0; brightness <= 255; brightness += 5) {
      analogWrite(pwmPins[i], brightness);
      delay(delayTime / 10);
    }
    
    // Fade out
    for (int brightness = 255; brightness >= 0; brightness -= 5) {
      analogWrite(pwmPins[i], brightness);
      delay(delayTime / 10);
    }
  }
}

// PATTERN 6: Converge/Diverge pattern
void convergeDiverge() {
  // Turn all LEDs off to start
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  
  // Converge from ends to middle
  for (int i = 0; i < numLeds / 2; i++) {
    digitalWrite(ledPins[i], HIGH);                 // Light from start
    digitalWrite(ledPins[numLeds - 1 - i], HIGH);   // Light from end
    delay(delayTime);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[numLeds - 1 - i], LOW);
  }
  
  // Diverge from middle to ends
  for (int i = numLeds / 2 - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[numLeds - 1 - i], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[numLeds - 1 - i], LOW);
  }
}

// PATTERN 7: All on, all off
void allOnAllOff(int iterations) {
  for (int i = 0; i < iterations; i++) {
    // All on
    for (int j = 0; j < numLeds; j++) {
      digitalWrite(ledPins[j], HIGH);
    }
    delay(delayTime * 2);
    
    // All off
    for (int j = 0; j < numLeds; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    delay(delayTime * 2);
  }
}
