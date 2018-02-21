//Basic sine wave animation for NeoPixel Ring Bangle Bracelet
//by Dano Wall and Becky Stern for Adafruit Industries
#include <avr/power.h>
#include <Adafruit_NeoPixel.h>
 
#define PIN 2 //marked D1 on GEMMA
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);
 

int sine[] = {11, 10, 9, 8, 7, 6, 5, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 4, 3, 2, 1, 0, 15, 14, 13, 12};

void setup() {
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  strip.begin();
  strip.setBrightness(20); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
}
bool firsttime = true;
 
void loop() {
  if (firsttime) {
  rainbowCycle(20);
  theaterChaseRainbow(50);
  rainbow(20);
  infinityRainbow();
  firsttime=false;
  }
  else {
  theaterChaseRainbow(50);
  infinityRainbow();
  }

}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<30; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void infinityRainbow(){
  for (int j=0; j< 256; j += 8 ){
  for (int i =0; i < 32; i++) {
    strip.setPixelColor(sine[i], Wheel( (i+j) & 255));
    if (i < 31){
    strip.setPixelColor(sine[i+1], Wheel( (i+j) & 255));
    strip.setPixelColor(sine[i+2], Wheel( (i+j) & 255));
    }
      else {
      if (i = 31) {
        strip.setPixelColor(sine[i+1], Wheel( (i+j) & 255));
        strip.setPixelColor(sine[0], Wheel( (i+j) & 255));
        }
      if (i = 32) {
        strip.setPixelColor(sine[0], Wheel( (i+j) & 255));
        strip.setPixelColor(sine[1], Wheel( (i+j) & 255));
        }

      }
    strip.show();
    delay(35);
    strip.setPixelColor(sine[i], strip.Color(0, 0, 0));
    if (i < 31) {
    strip.setPixelColor(sine[i+1], strip.Color(0, 0, 0));
    strip.setPixelColor(sine[i+2], strip.Color(0, 0, 0));
    }
   else {
      if (i = 31) {
        strip.setPixelColor(sine[i+1], strip.Color(0,0,0));
        strip.setPixelColor(sine[0], strip.Color(0,0,0));
        }
      if (i = 32) {
        strip.setPixelColor(sine[0], strip.Color(0,0,0));
        strip.setPixelColor(sine[1], strip.Color(0,0,0));
        }

      }
    
    }
    for (int m = 0; m < 32; m++) {
      strip.setPixelColor(m, 0,0,0);
     }
  }
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
