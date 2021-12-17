#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
int X = 20;
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(X, 6, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


int rouge = 255;
int vert = 200;

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  int retard = 20;
  for (int k=0;k<=6;k++){
  vert = 230;
  rouge = 255;
  for (int j = 0;j<=200;j=j+20){
    vert = vert - 20 ;
    if (vert >0){
      for (int n=0;n<X;n++){
        strip.setPixelColor(n,rouge,vert,0);
        strip.show();
        delay(max(0,retard-k*5));
        }
      }
     Serial.println(vert);
    }
  for (int a = 0; a <= 255 ; a=a+20){
    rouge = rouge - 20;
    for (int m = 0;m<X;m++){
      strip.setPixelColor(m,max(rouge,0),0,0);
        strip.show();
        delay(max(0,retard-k*5-10));
      }
    }
  }      
}
