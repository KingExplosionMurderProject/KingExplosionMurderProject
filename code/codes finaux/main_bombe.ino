//Paramètres de départ
const int relais_ventilo = 2 ;
const int relais_resistance = 7 ;

#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
int X = 37; //nombre de LED
int led = 6; // I/O du bandeau
int count =0;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(X, led, NEO_GRB + NEO_KHZ800); 

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
const int bouton = 4;
int val = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  Serial.println("Initialisation du système");
  pinMode(relais_ventilo, OUTPUT);
  pinMode(relais_resistance, OUTPUT);
  // put your setup code here, to run once:
  pinMode(bouton,INPUT);
}

void loop() {

  Serial.println("_____Test_____");

  
  
  val = digitalRead(bouton);
  if (val==LOW){
    count = count + 1;

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
           if (m==X-1 and a==200 and k==3){
            digitalWrite(relais_resistance,HIGH);
            digitalWrite(relais_ventilo,LOW);
          }

  
          if (m==X-1 and a==200 and k==6){
            digitalWrite(relais_resistance,LOW);
            digitalWrite(relais_ventilo,HIGH);
            delay(950);
            
            digitalWrite(relais_ventilo,LOW);
          }
        }
      }
    }
    for ( int h=0; h<8; h++){ //effet sur la fin
      for (int j=0;j<X;j++){
        strip.setPixelColor(j,255,100,0);
      }
      strip.show();
      delay(50);
      for(int t=0;t<X;t++){
      strip.setPixelColor(t,0,0,0);
      }
      strip.show();
      delay(50);
    }
    if(count>=10){
      count = 0;
      for(int t=0;t<X;t++){
        strip.setPixelColor(t,0,0,255);
      }  
      
    }
    
  }  


}
