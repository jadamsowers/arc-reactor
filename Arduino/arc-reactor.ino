#include <Adafruit_NeoPixel.h>
//#include <math.h>

#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif

#define PIN 1

// 24 for the ring, 7 for the disc
#define LEDs 31

// scale this down if you're using transparent plastic
#define maxBrightness 255

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDs, PIN);

/* this array generated by breathe.py
using LED 'breathing' function by Sean Voisen.
http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/ */
#define numSteps 100
int breath[numSteps] = {
0xCCDDFF, 0xCBDCFE, 0xCBDCFE, 0xCADBFD, 0xCADAFC, 0xC9D9FB, 0xC7D8F9, 0xC6D6F7, 0xC4D5F5, 0xC2D3F3,
0xC0D0F0, 0xBECEEE, 0xBCCBEB, 0xB9C8E7, 0xB6C5E4, 0xB3C2E0, 0xB0BFDC, 0xADBBD8, 0xA9B8D4, 0xA6B4D0,
0xA2B0CB, 0x9FACC7, 0x9BA8C2, 0x97A4BD, 0x93A0B8, 0x909CB4, 0x8C97AF, 0x8893AA, 0x848FA5, 0x808AA0,
0x7C869B, 0x788296, 0x747E91, 0x70798C, 0x6C7587, 0x687182, 0x646D7E, 0x616979, 0x5D6574, 0x596170,
0x565D6B, 0x525967, 0x4F5563, 0x4C525F, 0x484E5A, 0x454B56, 0x424753, 0x3F444F, 0x3C414B, 0x393E48,
0x363B44, 0x343841, 0x31353D, 0x2F323A, 0x2C3037, 0x2A2D34, 0x282B32, 0x25292F, 0x23262C, 0x21242A,
0x1F2227, 0x1D2025, 0x1C1E23, 0x1A1C21, 0x181A1E, 0x17191C, 0x15171B, 0x141519, 0x121417, 0x111315,
0x101114, 0x0F1012, 0x0D0F11, 0x0C0D10, 0x0B0C0E, 0x0A0B0D, 0x090A0C, 0x09090B, 0x08080A, 0x070809,
0x060708, 0x060607, 0x050506, 0x040505, 0x040405, 0x030304, 0x030303, 0x020203, 0x020202, 0x010202,
0x010102, 0x010101, 0x010101, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000};


void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
  pixels.setBrightness(maxBrightness);
}

void startup()
{
  uint8_t i;
  uint8_t delay_ms = 25;
  uint8_t color = breath[ (25 - delay_ms) * 4]

  while(delay_ms > 0)
  {

    pixels.show();

    for(i = 0; i < 24; i++)
    {
      // always keep the center LED on.
      pixels.setPixelColor(24, (color));

      //rotate clockwise on the ring.
      pixels.setPixelColor(i, color);

      //rotate counterclockwise in the center.
      pixels.setPixelColor(30 - (i % 6), color);

      pixels.show();
      delay(delay_ms);
    }
    delay_ms--;
  }

  // full on brightness for a few seconds
  for(i = 0; i < 31; i++)
  {
    pixels.setPixelColor(i, breath[0]);
  }
  pixels.show();
  delay(3000);
}

void breathe()
{
  // assuming all lights are on already
  int i,j;
  int direction = 1;

  while(true)
  {
    for(i = 0; i < numSteps; i++)
    {
      for(j = 0; j < 24; j++)
      {
        pixels.setPixelColor(j, direction == 1 ? breath[i] : breath[numSteps - 1 - i]);
      }
      pixels.show();
      delay(10);

    }
    direction *= -1;
  }
}

void loop()
{
  startup();
  breathe();
}
