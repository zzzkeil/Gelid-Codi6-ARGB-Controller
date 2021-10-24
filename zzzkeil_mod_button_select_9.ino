// This is my first modification from gelidsolutions.com code exsample button_select_9
// https://gelidsolutions.com/thermal-solutions/codi6-argb-controller/
// find more mods and "try and error examples" here :
// https://github.com/zzzkeil/Gelid-Codi6-ARGB-Controller


#include <FastLED.h>
#include "colorutils.h"
#include "colorpalettes.h"

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

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

#define NUM_LEDS NUM_LEDS_GPU + NUM_LEDS_CPU + NUM_LEDS_FRONT_FANS + NUM_LEDS_SIDE_FANS + NUM_LEDS_STRIPS //total number of LED



#define BRIGHTNESS  200    // 255 is full brightness, 128 is half
#define SATURATION  255     // 0-255, 0 is pure white, 255 is fully saturated color
#define BUTTON_PIN  2      // Connect the button to GND and one of the pins.
#define UPDATES_PER_SECOND 100



#define NUM_MODES 10 //Update this number to the highest number of "cases"

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

uint16_t STEPS = 30;// STEPS set dynamically once we've started up
uint16_t SPEED = 30;// SPEED set dynamically once we've started up

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int ledMode = 0;

uint8_t       colorLoop = 1;

const TProgmemPalette16 MyColors_p PROGMEM =
{
  CRGB:: DarkBlue,
  CRGB:: HotPink,
  CRGB:: Teal,
  CRGB:: BlueViolet,
 
  CRGB:: DodgerBlue,    
  CRGB:: DeepPink,
  CRGB:: Turquoise,
  CRGB:: Indigo,
 
  CRGB:: DarkBlue,
  CRGB:: HotPink,
  CRGB:: Teal,
  CRGB:: BlueViolet,
 
  CRGB:: DodgerBlue,    
  CRGB:: DeepPink,
  CRGB:: Turquoise,
  CRGB:: Indigo,
};

byte prevKeyState = HIGH;         // button is active low

//int db[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,
//            102,103,101,104,105,108,106,107,113,114,112,115,111,116,110,117,109,125,124,126,123,118,122,119,121,120,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,
//            201,202,203,204,205,206,206,208,209,210,211};

            
void setup() {
  delay( 1000 ); // power-up safety delay
  
  // Assign pin  LED singal pin
  FastLED.addLeds<NEOPIXEL, 5>(leds, 0, NUM_LEDS_GPU);
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS_GPU, NUM_LEDS_CPU);
  FastLED.addLeds<NEOPIXEL, 9>(leds, NUM_LEDS_GPU+NUM_LEDS_CPU, NUM_LEDS_STRIPS);
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS_GPU+NUM_LEDS_CPU+NUM_LEDS_STRIPS, NUM_LEDS_FRONT_FANS);
  FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDS_GPU+NUM_LEDS_CPU+NUM_LEDS_STRIPS+NUM_LEDS_FRONT_FANS, NUM_LEDS_SIDE_FANS);

   
  FastLED.setBrightness( BRIGHTNESS );
 
  currentBlending = LINEARBLEND; //all of these will be blended unless I tell them not to be

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

//------------------MAIN LOOP------------------
void loop() {

  byte currKeyState = digitalRead(BUTTON_PIN);

  if ((prevKeyState == LOW) && (currKeyState == HIGH)) {
    shortKeyPress();
  }
  prevKeyState = currKeyState;

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  switch (ledMode) {

//FastLED has a bunch of built-in "palettes" to choose from:
//RainbowColors_p     is all the colors of the rainbow
//PartyColors_p     is all the colors of the rainbow minus greens
//RainbowStripeColors_p is all the colors of the rainbow divided into stripes
//HeatColors_p      is reds and yellows, white, and black
//LavaColors_p      is more reds and orangey colors
//ForestColors_p    is greens and yellows
//OceanColors_p     is lots of blues and aqua colors
//CloudColors_p     is blues and white
//MyColors_p        is whatever you define above

//The group of colors in a palette are sent through a strip of LEDS in speed and step increments youve chosen
//You can change the SPEED and STEPS to make things look exactly how you want
//SPEED refers to how fast the colors move.  Higher numbers = faster motion
//STEPS refers to how wide the bands of color are. Based on the palette & number of LEDs, some look better at different steps

  case 0:
  {currentPalette = RainbowColors_p;  SPEED = 50;  STEPS = 6; currentBlending = LINEARBLEND;}
  break;
  
  case 1: 
  {currentPalette = RainbowStripeColors_p;    SPEED = 50;   STEPS = 8; currentBlending = NOBLEND;} 
  break;

  case 2:
  {currentPalette = PartyColors_p;   SPEED = 150;   STEPS = 48; currentBlending = LINEARBLEND;}
  break;

  case 3:
  {currentPalette = MyColors_p;     SPEED = 75;   STEPS = 48;} 
  break;

  case 4:
  {currentPalette = HeatColors_p;     SPEED = 100;   STEPS = 11;} 
  break;

  case 5:
  {SetupWatermelonPalette(); SPEED = 125; STEPS = 8;}
  break;

  case 6:
  {currentPalette = ForestColors_p;     SPEED = 200;   STEPS = 48;} //all steps look good. Speed should be high.
  break;

  case 7:
  {currentPalette = OceanColors_p;    SPEED = 100;   STEPS = 8;} //
  break; 
 
  case 8:
  {SetupNewPalette(); SPEED = 250; STEPS = 16; currentBlending = NOBLEND;} 
  break;

  case 9:
  {currentPalette = LavaColors_p; SPEED = 100;   STEPS = 8;} 
  break;

  case 10:
  {currentPalette = CloudColors_p; SPEED = 100;   STEPS = 8;} 
  break;
  } 



     FillLEDsFromPaletteColors( startIndex);
     FastLED.show();
     FastLED.delay(1000 / SPEED);  
}


void shortKeyPress() {
  ledMode++;
  if (ledMode > NUM_MODES) {
    ledMode=0; 
  }  
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  for( int i = 0; i < NUM_LEDS; i++) {
    //leds[db[i]] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += STEPS;              
  }
}

void SetupNewPalette()
{
    fill_solid( currentPalette, 16, CRGB::Black);
    //  set half of the LEDs to the color selected here
    //  Play with the color, steps, and speed to get different results. 
    currentPalette[0] = CRGB::DodgerBlue;
    currentPalette[1] = CRGB::DodgerBlue;
    currentPalette[2] = CRGB::DodgerBlue;
    currentPalette[3] = CRGB::DodgerBlue;

    currentPalette[8] = CRGB::DodgerBlue;
    currentPalette[9] = CRGB::DodgerBlue;
    currentPalette[10] = CRGB::DodgerBlue;
    currentPalette[11] = CRGB::DodgerBlue;
 
}
//  This function sets up a palette of purple and green stripes.
//  Play with the color, steps, and speed to get different results. 
void SetupWatermelonPalette()
{
    CRGB Pink = CHSV(HUE_PINK, 255, 255);
    CRGB Green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   Green,  Green,  Green,  Green,
                                   Pink, Pink,  Pink, Pink,
                                   Green,  Green,  Green,  Green,
                                   Pink, Pink,  Pink, Pink );
}
