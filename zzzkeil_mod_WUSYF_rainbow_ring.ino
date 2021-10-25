// My modification based on github user WUSYF  > rainbow_ring.java code  
// Original from WUSYF : https://github.com/WUSYF/RGB_GELID_CODI6/blob/main/simple_smooth_rainbow.java
// find more mods and "try and error esamples" here :
// https://github.com/zzzkeil/Gelid-Codi6-ARGB-Controller


#include "FastLED.h"
struct CRGB leds[211];
byte maxbright = 255;
byte max_hue = 120; //how many colors will be displayed simultaneously
byte hue_changer = 0;

//This is where we adjust things to match our unique project:

// Powercolor Red Devil 6900XT 
#define NUM_LEDS_GPU 3

// be quiet silent loop 2
#define NUM_LEDS_CPU 10

// 3 * ARCTIC P12 PWM PST A-RGB
#define NUM_LEDS_FRONT_FANS 36

// 4 * ARCTIC P12 PWM PST A-RGB
#define NUM_LEDS_SIDE_FANS 48

// 3 * Amusingtao / Phanteks 550mm Led-Strips
#define NUM_LEDS_STRIPS 114
//total number of LED

#define NUM_LEDS NUM_LEDS_GPU + NUM_LEDS_CPU + NUM_LEDS_FRONT_FANS + NUM_LEDS_SIDE_FANS + NUM_LEDS_STRIPS



int gpu[] = {0,1,2};
int cpu[] = {3,4,5,6,7,8,9,10,11,12};
int strips[] = {13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126};
int front[] = {127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162};
int side [] = {163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,206,208,209,210,211};


void setup() {
  delay(500); // power-up safety delay
  FastLED.addLeds<NEOPIXEL, 5>(leds, 0, 3);
  FastLED.addLeds<NEOPIXEL, 3>(leds, 3, 13);
  FastLED.addLeds<NEOPIXEL, 9>(leds, 13, 127);
  FastLED.addLeds<NEOPIXEL, 6>(leds, 127, 163);
  FastLED.addLeds<NEOPIXEL, 11>(leds, 163, 211);
  FastLED.setBrightness(255);
  for(int i = 0; i < 120; i++){
      leds[i] = CRGB(0,0,0);  
  }
  FastLED.show();
}

void loop(){
  rainbow();
}

void rainbow(){
  for(int i = 0; i < 3; i++) {
    leds[gpu[i]] = CHSV(i * max_hue/5 + hue_changer, 255, 255);
  }
   for(int i = 0; i < 10; i++) {
    leds[cpu[i]] = CHSV(i * max_hue/10 + hue_changer, 255, 255);
   }
    for(int i = 0; i < 114; i++) {
    leds[strips[i]] = CHSV(i * max_hue/16 + hue_changer, 255, 255);
    }
     for(int i = 0; i < 36; i++) {
    leds[front[i]] = CHSV(i * max_hue/16 + hue_changer, 255, 255);
     }
      for(int i = 0; i < 48; i++) {
    leds[side[i]] = CHSV(i * max_hue/16 + hue_changer, 255, 255);
  }

  hue_changer++;
  FastLED.show();
  delay(0); //increase to slow down animation
}
