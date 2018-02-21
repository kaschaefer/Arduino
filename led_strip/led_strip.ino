#include <FastLED.h>
#include <math.h>
#include <avr/power.h>
#define FASTLED_FORCE_SOFTWARE_SPI
#define NUM_LEDS 42
#define BUTTON_PIN 0
#define DATA_PIN 1
#define CLOCK_PIN 2

typedef enum {
  MODE_ONE = 0,
  MODE_TWO,
  MODE_THREE,
  MODE_FOUR,
  MODE_FIVE,
  MODE_SIX,
  MODE_SEVEN,
  MODE_COUNT
  }LightMode;

bool buttonState = false;
LightMode lightMode = MODE_ONE;
CRGB leds[NUM_LEDS];
int rainbowCycleCurrent = 0;

void modeOne () { //All Off
    for (int i =0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    return;
  }
void modeTwo () { //All On
    for (int i =0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
    }
    return;
  }
void modeThree () { //Left Half On
    for (int i=0; i < NUM_LEDS; i++) {
        if (i < (NUM_LEDS/2)) {
          leds[i] = CRGB::White;
        }
        else {
          leds[i] = CRGB::Black;
          }
    }
    return;
  }
void modeFour () {  //Right Half On
    for (int i=0; i < NUM_LEDS; i++) {
        if (i >= (NUM_LEDS/2)){
          leds[i] = CRGB::White;
        }
        else {
          leds[i] = CRGB::Black;
          }
      }
      return;
  }
void modeFive () {  //Every Other LED Lit
    for (int i =0; i < NUM_LEDS; i++){
    if ( (i%2) == 0 ) {
        leds[i] = CRGB::White;
      }
      else {
        leds[i] = CRGB::Black;
        }
    }
    return;
  }

void modeSix() {  //Every 4th LED is Lit
  for (int i=0; i <NUM_LEDS; i++) {
    if ((i%4) == 0) {
      leds[i] = CRGB::White;
      }
     else {
      leds[i] = CRGB::Black;
      }
    }
  }

void modeSeven () { //Rainbow Gradient
  double frequency =.3;
  for (int i = 0; i < NUM_LEDS; i++) {
     int r = sin(frequency*i + 0) * 127 +128;
     int g = sin(frequency*i + 2) * 127 +128;
     int b = sin(frequency*i + 4) * 127 +128;
     leds[i].r = r;
     leds[i].g = g;
     leds[i].b = b;
  }
  return;
}





void setup() { 
      FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR, DATA_RATE_MHZ(12)>(leds, NUM_LEDS);
      pinMode(BUTTON_PIN, INPUT_PULLUP);
      if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
}
    void loop() { 
      bool curButtonState = digitalRead(BUTTON_PIN);
      if (!buttonState && curButtonState) {
          buttonState = true;
          lightMode = (LightMode) ((lightMode+1)%MODE_COUNT);
        }
        else if (!curButtonState) {
          buttonState = false;  
        }
        switch(lightMode) {
          case MODE_ONE:
            modeOne();
            break;
          case MODE_TWO:
            modeTwo();
            break;
          case MODE_THREE:
            modeThree();
            break;
          case MODE_FOUR:
            modeFour();
            break;
          case MODE_FIVE:
            modeFive();
            break;
          case MODE_SIX:
            modeSix();
            break;
         case MODE_SEVEN:
            modeSeven();
            break;
        }
        FastLED.show(); 
        delay(60);
    }

