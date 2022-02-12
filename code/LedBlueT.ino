#include<SoftwareSerial.h>
#define RX 03
#define TX 02
SoftwareSerial BlueT(RX,TX);

#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
int X = 20; //nombre de LED
int led = 6; // I/O du bandeau


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(X, led, NEO_GRB + NEO_KHZ800); 

String rec;



unsigned long currentTime=0;

void setup() {
  // put your  setup code here, to run once:
  Serial.begin(9600);
  BlueT.begin(9600);
  strip.begin();
  strip.show();
  

}

void loop() {
  
  if (BlueT.available()){
    rec = char(BlueT.read());
  }
  
  // mode numéro 1 _________________________________________
   if (rec=="a"){
     firstL();
    }
  //mode numéro 2
   if (rec=="b"){
    secondL();
   }
    rec = "";
    //Serial.println("end");
    Serial.println("out");

}
void secondL(){
  for (int i=0;i<6;i++){
    int rouge = 0;
    int vert = 0;
    int bleu = 255;
    for (int n=0;n<X;n++){
              strip.setPixelColor(n,0,0,255);
              strip.show();
            }
    //augmentation du rouge
    while (rouge<255){
      for (int n=0;n<X;n++){
              strip.setPixelColor(n,min(rouge,255),0,255);
              strip.show();
            }
      currentTime=millis();
        
      while(millis()-currentTime<20){
        Serial.println("wait");
      }
      rouge = rouge + 5;
    }
    
    //descente du bleu
    while (bleu>0){
      for (int n=0;n<X;n++){
              strip.setPixelColor(n,255,0,max(0,bleu));
              strip.show();
            }
      currentTime=millis();
        
      while(millis()-currentTime<20){
        Serial.println("wait");
      }
      bleu = bleu - 5;
    }
    
    //augmentation du vert  
    while (vert<255){
      vert = vert + 5;
      for (int n=0;n<X;n++){
              strip.setPixelColor(n,255,min(255,vert),0);
              strip.show();
            }
      currentTime=millis();
        
      while(millis()-currentTime<20){
        Serial.println("wait");
      }
      vert = vert + 5;
    }
    
    //descente du rouge
    while (rouge>0){
      for (int n=0;n<X;n++){
              strip.setPixelColor(n,max(rouge,0),255,0);
              strip.show();
            }
      currentTime=millis();
        
      while(millis()-currentTime<20){
        Serial.println("wait");
      }
      rouge = rouge - 5;
    }
    
    //augmentation du bleu
    while (bleu<255){
      for (int n=0;n<X;n++){
              strip.setPixelColor(n,0,255,min(bleu,255));
              strip.show();
            }
      currentTime=millis();
        
      while(millis()-currentTime<20){
        Serial.println("wait");
      }
      bleu = bleu + 5;
    }
    
    //descente du vert
    while (vert>0){
      for (int n=0;n<X;n++){
              strip.setPixelColor(n,0,max(vert,0),255);
              strip.show();
            }
      currentTime=millis();
        
      while(millis()-currentTime<20){
        Serial.println("wait");
      }
      vert = vert - 5;
    }
    
  }
  int eteint = 255;
  while(eteint>0){
    eteint = eteint-5;
    for (int n=0;n<X;n++){
              strip.setPixelColor(n,0,0,eteint);
              strip.show();
    }
    while(millis()-currentTime<20){
        Serial.println("wait");
      }
  }
}

void firstL(){
  
    Serial.println("first mode");
    
    for (int i =1;i<=5;i++){  
      int vert = 0;   
      int retard = 200/i;
      Serial.println(i);
      
      currentTime=millis();
      
      while (vert<230){
        
        vert = vert+5;
          
          for (int n=0;n<X;n++){
            strip.setPixelColor(n,255,min(vert,230),0);
            strip.show();
          }
        currentTime=millis();
        
        while(millis()-currentTime<retard){
          Serial.println("wait");
          Serial.println(millis());
        }

      }
      vert = 230;
      while (vert>0){
        
        vert = vert-5;
          
          for (int n=0;n<X;n++){
            strip.setPixelColor(n,255,max(vert,0),0);
            strip.show();
          }
        currentTime=millis();
        
        while(millis()-currentTime<retard){
          Serial.println("wait");
          Serial.println(millis());
        }

      }
      
    }
    
    for (int k=255;k>=0;k=k-5){
      for (int n=0;n<X;n++){
          strip.setPixelColor(n,k,0,0);
          }
      strip.show();
      Serial.println("off");
    
    }
    while(millis()-currentTime<50){
          Serial.println("wait");
          Serial.println(millis());
        }
}
