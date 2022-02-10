#include<SoftwareSerial.h>
#define RX 11 
#define TX 10
SoftwareSerial BlueT(RX,TX);
char recvChar;
char consigne;

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

////////////////////////////////////////////////////////////////////////////////////  


/* Constantes pour la communication avec le module KT403A */
const byte COMMAND_BYTE_START = 0x7E;
const byte COMMAND_BYTE_VERSION = 0xFF;
const byte COMMAND_BYTE_STOP = 0xEF;

/** Fonction de bas niveau pour envoyer une commande au module KT403A */
void send_kt_command(byte command, int16_t dat, unsigned long cmd_delay) {
  Serial.write(COMMAND_BYTE_START);
  Serial.write(COMMAND_BYTE_VERSION);
  Serial.write((byte) 0x06);
  Serial.write(command);
  Serial.write((byte) 0x00);
  Serial.write((int8_t)(dat >> 8));
  Serial.write((int8_t)(dat));
  Serial.write(COMMAND_BYTE_STOP);
  // 16-bits checksum is optionnal
  delay(cmd_delay);
} 


void setup(){
  Serial.begin(9600);
  delay(500);
  Serial.println("Bonjour - Pret pour les commandes AT");
  BlueT.begin(9600);
  delay(500);
  send_kt_command(CMD_SEL_DEV, DEV_TF,10); //select the TF card
  delay(200);
}

void loop(){
  // https://www.carnetdumaker.net/articles/utiliser-un-lecteur-serie-de-fichiers-mp3-avec-une-carte-arduino-genuino/#:~:text=Le%20principe%20de%20fonctionnement%20est%20assez%20simple%20sur,fichiers%20MP3%20contr%C3%B4lable%20via%20un%20simple%20port%20s%C3%A9rie.
  //ne fonctionne pas pour l'instant je pense que c'est la discussion avec le module music
  
  send_kt_command(SINGLE_PLAY, 0X0302,10);
  while (BlueT.available()) {
    consigne=char(BlueT.read());
    Serial.println(consigne);
    switch (consigne){
      case '0':
         //send_kt_command(0x06, 0, 0, 10);
        //setVolume(0);
        break;
      case '1':
        //send_kt_command(0x06, 0, 3, 10);
        //setVolume(1);
        break;
      case '2':
        //send_kt_command(0x06, 0, 6, 10);
        //setVolume(2);
        break;
      case '3':
        //send_kt_command(0x06, 0, 9, 10);
        //setVolume(3);
        break;
      case '4':
        //send_kt_command(0x06, 0, 12, 10);
        //setVolume(4);
        break;
      case '5':
        //send_kt_command(0x06, 0, 15, 10);
        //setVolume(5);
        break;
      case '6':
        //send_kt_command(0x06, 0, 18, 10);
        //setVolume(6);
        break;
      case '7':
        //send_kt_command(0x06, 0, 21, 10);
        //setVolume(7);
        break;
      case '8':
        //send_kt_command(0x06, 0, 24, 10);
        //setVolume(8);
        break;
      case '9':
        //send_kt_command(0x06, 0, 27, 10);
        //setVolume(9);
        break;

      case 'A':
        Serial.println("Musique d'après");
       break;
      case 'B':
        Serial.println("Musique d'après");
       break;
      case 'L':
        Serial.println("lecture mistro");
        send_kt_command(0x0D, 0, 20);
        break;
      case 'S':
        Serial.println("Stop music");
        send_kt_command(0x16, 0, 20);
        break;
    }    
    
    }  
}
