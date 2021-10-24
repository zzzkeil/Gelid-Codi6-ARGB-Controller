// My modification based on a amazon.de user review code from Orkan 
// Original from Orkan : https://www.amazon.de/gp/customer-reviews/R1FNEZSZ2LP1ZT
// find more mods and "try and error examples" here :
// https://github.com/zzzkeil/Gelid-Codi6-ARGB-Controller

#include <FastLED.h>

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


#define BRIGHTNESS 255 /* Control the brightness of your leds */
#define SATURATION 255 /* Control the saturation of your leds */

//total number of LED

#define NUM_LEDS NUM_LEDS_GPU + NUM_LEDS_CPU + NUM_LEDS_FRONT_FANS + NUM_LEDS_SIDE_FANS + NUM_LEDS_STRIPS

#define NUM_LEDSA NUM_LEDS_GPU
#define NUM_LEDSB NUM_LEDS_CPU
#define NUM_LEDSC NUM_LEDS_FRONT_FANS
#define NUM_LEDSD NUM_LEDS_SIDE_FANS
#define NUM_LEDSE NUM_LEDS_STRIPS



CRGB leds[NUM_LEDS];
CRGB ledsA[NUM_LEDSA];
CRGB ledsB[NUM_LEDSB];
CRGB ledsC[NUM_LEDSC];
CRGB ledsD[NUM_LEDSD];
CRGB ledsE[NUM_LEDSE];

void setup() {
FastLED.addLeds<NEOPIXEL, 5>(leds, 0, NUM_LEDSA);
FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDSA, NUM_LEDSB);
FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDSA+NUM_LEDSB, NUM_LEDSC);
FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDSA+NUM_LEDSB+NUM_LEDSC, NUM_LEDSD);
FastLED.addLeds<NEOPIXEL, 9>(leds, NUM_LEDSA+NUM_LEDSB+NUM_LEDSC+NUM_LEDSD, NUM_LEDSE);

}



void loop() {
for (int j = 0; j < 255; j++) {
for (int i = 0; i < NUM_LEDS; i++) {
ledsA[i] = CHSV(i - (j * 4), BRIGHTNESS, SATURATION); /* The higher the value 4 the less fade there is */
ledsB[i] = CHSV(i - (j * 4), BRIGHTNESS, SATURATION);
ledsC[i] = CHSV(i - (j * 4), BRIGHTNESS, SATURATION);
ledsD[i] = CHSV(i - (j * 4), BRIGHTNESS, SATURATION);
ledsE[i] = CHSV(i - (j * 4), BRIGHTNESS, SATURATION);
}
FastLED.show();
delay(15); /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
}
}
