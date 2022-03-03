
#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
int X = 20; //nombre de LED
int led = 6; // I/O du bandeau
int ledAl;
int cool = 0;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(X, led, NEO_GRB + NEO_KHZ800);

char rec; //valeur récupérée par le module bluetooth

unsigned long currentTime = 0;

#include <SoftwareSerial.h>

#define RXm 12
#define TXm 13

SoftwareSerial mySerial(RXm,TXm);

#define RXb 11 
#define TXb 10
SoftwareSerial BlueT(RXb,TXb);

//////////////////////////////////////////////////////////////////////////////////// 

//all the commands needed in the datasheet(http://geekmatic.in.ua/pdf/Catalex_MP3_board.pdf) 

static int8_t Send_buf[8] = {0} ;//The MP3 player undestands orders in a 8 int string 

                                 //0X7E FF 06 command 00 00 00 EF;(if command =01 next song order)  

#define NEXT_SONG 0X01  
#define PREV_SONG 0X02  
#define CMD_PLAY_W_INDEX 0X03 //DATA IS REQUIRED (number of song) 
#define VOLUME_UP_ONE 0X04 
#define VOLUME_DOWN_ONE 0X05 
#define CMD_SET_VOLUME 0X06//DATA IS REQUIRED (number of volume from 0 up to 30(0x1E)) 
#define SET_DAC 0X17 
#define CMD_PLAY_WITHVOLUME 0X22 //data is needed  0x7E 06 22 00 xx yy EF;(xx volume)(yy number of song) 
#define CMD_SEL_DEV 0X09 //SELECT STORAGE DEVICE, DATA IS REQUIRED 
#define DEV_TF 0X02 //HELLO,IM THE DATA REQUIRED 
#define SLEEP_MODE_START 0X0A 
#define SLEEP_MODE_WAKEUP 0X0B 
#define CMD_RESET 0X0C//CHIP RESET 
#define CMD_PLAY 0X0D //RESUME PLAYBACK 
#define CMD_PAUSE 0X0E //PLAYBACK IS PAUSED 
#define CMD_PLAY_WITHFOLDER 0X0F//DATA IS NEEDED, 0x7E 06 0F 00 01 02 EF;(play the song with the directory \01\002xxxxxx.mp3 
#define STOP_PLAY 0X16 
#define PLAY_FOLDER 0X17// data is needed 0x7E 06 17 00 01 XX EF;(play the 01 folder)(value xx we dont care) 
#define SET_CYCLEPLAY 0X19//data is needed 00 start; 01 close 
#define SET_DAC 0X17//data is needed 00 start DAC OUTPUT;01 DAC no output 
#define SINGLE_PLAY 0X08//Single play(without folder)

void sendCommand(int8_t command, int16_t dat, unsigned long cmd_delay) { 
  Serial.print("send command ok");
  //delay(20); 
  Send_buf[0] = 0x7e; //starting byte 
  Send_buf[1] = 0xff; //version 
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte 
  Send_buf[3] = command; // 
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback 
  Send_buf[5] = (int8_t)(dat >> 8);//datah 
  Send_buf[6] = (int8_t)(dat); //datal 
  Send_buf[7] = 0xef; //ending byte 
  for(uint8_t i=0; i<8; i++){ 
    mySerial.write(Send_buf[i]) ; 
  }
  //delay(cmd_delay);
}

void couleur(int a, int b, int c){
  for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, a, b, c); //normalement ca fait du orange, si tu veux que ca soit plus rouge, tu diminue la deuxième valeur
        strip.show();
        //delay(5000);
        Serial.println("carrotte");
      }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin();
  strip.show();
  BlueT.begin(9600);
  
  mySerial.begin(9600);//Start our Serial coms for our serial monitor! 
  
  delay(500);//Wait chip initialization is complete 
  sendCommand(CMD_SEL_DEV, DEV_TF, 10);//select the TF card  
  delay(200);
  BlueT.begin(9600);
  delay(500);
  sendCommand(0x06, 21, 10);
}

//permet d'attendre x ms mais en même récupérer des info venant du bluetooth et faire les fonctions nécessaire
void attente(int temps) {
  currentTime = millis();
  while (millis() - currentTime < temps) {
    //Serial.println("wait");
    //Serial.println(millis());
    if (BlueT.available()){
    rec = char(BlueT.read());
    chemin(rec);
    break;}
  }
}

//fonction gay (arc en ciel)
int secondL() {
  for (int i = 0; i < 6; i++) {
    int rouge = 0;
    int vert = 0;
    int bleu = 255;
    for (int n = 0; n < X; n++) {
      strip.setPixelColor(n, 0, 0, 255);
      strip.show();
    }
    //augmentation du rouge
    while (rouge < 255) {
      for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, min(rouge, 255), 0, 255);
        strip.show();
      }
      attente(20);
      rouge = rouge + 5;
    }

    //descente du bleu
    while (bleu > 0) {
      for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, 255, 0, max(0, bleu));
        strip.show();
      }
      attente(20);
      bleu = bleu - 5;
    }

    //augmentation du vert
    while (vert < 255) {
      vert = vert + 5;
      for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, 255, min(255, vert), 0);
        strip.show();
      }
      attente(20);
      vert = vert + 5;
    }

    //descente du rouge
    while (rouge > 0) {
      for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, max(rouge, 0), 255, 0);
        strip.show();
      }
      attente(20);
      rouge = rouge - 5;
    }

    //augmentation du bleu
    while (bleu < 255) {
      for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, 0, 255, min(bleu, 255));
        strip.show();
      }
      attente(20);
      bleu = bleu + 5;
    }

    //descente du vert
    while (vert > 0) {
      for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, 0, max(vert, 0), 255);
        strip.show();
      }
      attente(20);
      vert = vert - 5;
    }

  }
  int eteint = 255;
  while (eteint > 0) {
    eteint = eteint - 5;
    for (int n = 0; n < X; n++) {
      strip.setPixelColor(n, 0, 0, eteint);
      strip.show();
    }
    attente(20);
  }
  return 0;
}

//led avec un effet de chargement de puissance
int firstL() {

  Serial.println("first mode");

  for (int i = 1; i <= 5; i++) {
    int vert = 0;
    int retard = 200 / i;
    Serial.println(i);

    currentTime = millis();

    while (vert < 230) {

      vert = vert + 5;

      for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, 255, min(vert, 230), 0);
        strip.show();
      }
      currentTime = millis();

      attente(retard);

    }
    vert = 230;
    while (vert > 0) {

      vert = vert - 5;

      for (int n = 0; n < X; n++) {
        strip.setPixelColor(n, 255, max(vert, 0), 0);
        strip.show();
      }
      attente(retard);

    }

  }

  for (int k = 255; k >= 0; k = k - 5) {
    for (int n = 0; n < X; n++) {
      strip.setPixelColor(n, k, 0, 0);
    }
    strip.show();
    Serial.println("off");

  }
  attente(50);
  return 0;
}


void loop() {
  // put your main code here, to run repeatedly:
  while (BlueT.available()){
    rec = char(BlueT.read());
    chemin(rec);}
}

//cette fonction redirige vers les bonnes fonctions
void chemin(char chem) {
  switch (chem) {

    case '0':
      sendCommand(0x06, 0, 10);
      Serial.println("son a 0");
      //setVolume(0);
      break;
    case '1':
      sendCommand(0x06, 3, 10);
      Serial.println("son a 1");
      //setVolume(1);
      break;
    case '2':
      sendCommand(0x06, 6, 10);
      Serial.println("son a 2");
      //setVolume(2);
      break;
    case '3':
      sendCommand(0x06, 9, 10);
      Serial.println("son a 3");
      //setVolume(3);
      break;
    case '4':
      sendCommand(0x06, 12, 10);
      Serial.println("son a 4");
      //setVolume(4);
      break;
    case '5':
      sendCommand(0x06, 15, 10);
      Serial.println("son a 5");
      //setVolume(5);
      break;
    case '6':
      sendCommand(0x06, 18, 10);
      Serial.println("son a 6");
      //setVolume(6);
      break;
    case '7':
      sendCommand(0x06, 21, 10);
      Serial.println("son a 7");
      //setVolume(7);
      break;
    case '8':
      sendCommand(0x06, 24, 10);
      Serial.println("son a 8");
      //setVolume(8);
      break;
    case '9':
      sendCommand(0x06, 27, 10);
      Serial.println("son a 9");
      //setVolume(9);
      break;

    case 'A':
      Serial.println("Musique d'après");
      sendCommand(0x01, 0, 10);
      //delay(100);
     break;
    case 'B':
      Serial.println("Musique d'avant");
      sendCommand(0x02, 0, 10);
     break;
    case 'L':
      Serial.println("lecture mistro");
      sendCommand(0x0D, 0, 20);
      break;
    case 'S':
      Serial.println("Stop music");
      sendCommand(0X0E, 0, 20);
      break;

    case 'O':
      Serial.println("BOOM");
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0303, 10000);//Troisieme chanson répertoire no 3
      if (ledAl == 0){
        ledAl = 1;
        ledAl = firstL();}
      break;

    case 'a':
      Serial.print("01 : Boku no Hero Academia OST - Bombing King _Bakugo Theme_");
      sendCommand(SINGLE_PLAY, 0X0001, 10000);//Troisieme chanson répertoire no 3
      break;
    case 'b':
      Serial.print("02 : My Hero Academia OST - You Say Run");
      sendCommand(SINGLE_PLAY, 0X0002, 10000);//Troisieme chanson répertoire no 3
      break;
    case 'c':
      Serial.print("03 : My Hero Academia – Opening Theme – The Day");
      sendCommand(SINGLE_PLAY, 0X0003, 10000);//Troisieme chanson répertoire no 3
      break;

     case 'G':
      if (ledAl ==0){
        ledAl = 1;
        ledAl = secondL();}
        break;
      case 'C':
      if (ledAl == 0){
        ledAl = 1;
        ledAl = firstL();}
        break;

      case 'z': //orange
      if (ledAl==0)
          couleur(255, 100, 0);
      break;
          
      case 'y': //jaune
      if (ledAl==0)
          couleur(243, 214, 23);
          break;
          
      case 'x': //rouge
      if (ledAl==0)
          couleur(255, 0, 00);
          break;
          
      case'w': //turquoise
      if (ledAl==0)
          couleur(38, 196, 236);
          break;
          
      case 'v': //vert
      if (ledAl==0)
          couleur(9, 156, 9);
          break;
          
      case 'u': //Héliotrope rose
      if (ledAl==0)
          couleur(255, 60, 150);
          break;

      case 't': //Bleu persan
      if (ledAl==0)
          couleur(102, 0, 255);
          break;
          
      case 's': //Rouge brique
      if (ledAl==0)
          couleur(225, 59, 10);
          break;
          
      case 'r': //Or
      if (ledAl==0)
          couleur(255, 215, 0);
          break;

      case 'q': // Ecarlate
      if (ledAl==0)
          couleur(200, 5, 7);
          break;
          
      case 'p': //éteint
      if (ledAl==0)
        couleur(0, 0, 0);
        break;
  }
}

//cette fonction permet de récuperer les informations envoyées depuis le téléphone
char recup() {
  return char(BlueT.read());
}
