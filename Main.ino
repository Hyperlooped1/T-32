/* Created by: Hyperlooped1
* This is code for project T-32 
*It uses a proximity sensor. If the distance changes by more then 25cm then it will count it in the 7-segment-display.
* 
*
* 
* 
* 
* 
* 
*
* 
*/
uint8_t trigPin = 9;    // TRIG pin
uint8_t echoPin = 8;    // ECHO pin

float duration_us, distance_cm, old_distance;
float calculate_distance = 0;
uint8_t led = 7;
uint8_t num = 0;
// for the display

  // connect to the ST_CP of 74HC595 (pin 3,latch pin)
  uint8_t latchPin = 3;
  // connect to the SH_CP of 74HC595 (pin 4, clock pin)
  uint8_t clockPin = 4;
  // connect to the DS of 74HC595 (pin 2)
  uint8_t dataPin = 2;
  byte seven_seg_digits[10] = { B11111100,  // = 0
                                B01100000,  // = 1
                                B11011010,  // = 2
                                B11110010,  // = 3
                                B01100110,  // = 4
                                B10110110,  // = 5
                                B10111110,  // = 6
                                B11100000,  // = 7
                                B11111110,  // = 8
                                B11100110   // = 9
                               };
  
 
void setup() {
  //for the display
  // Set latchPin, clockPin, dataPin as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  // begin serial port
  Serial.begin (9600);

  pinMode(led, OUTPUT);
  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
}

// display a number on the digital segment display
void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}

void loop() {

  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;



   if (abs(distance_cm - old_distance) > 20) {
     num++;
        if (num > 9) {
            num = 0;
        }
        sevenSegWrite(num); 
        delay(500);

     old_distance =  distance_cm;
     Serial.print("DISTURBANCE");
     digitalWrite
  }
  // print the value to Serial Monitor
  {Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  delay(500);
  }
}
