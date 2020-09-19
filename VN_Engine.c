//                        ___    
//                      //|||\\  
//                      /|^,^|\\ 
//                      ||\-/||| 
//                      \\| |||| 
//                     /|-----|\ 
//                    |\|  &  |/|
//                    | |     | |
//                    | |     | |
//-----------------------------------------------------\\
//||						       ||
//|| ~VNES_ENGINE - A VISUAL NOVEL ENGINE FOR THE NES~ ||
//||						       ||
//-----------------------------------------------------//


#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

// include NESLIB header
#include "neslib.h"

// include CC65 NES Header (PPU)
#include <nes.h>

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// BCD arithmetic support
#include "bcd.h"
//#link "bcd.c"

// VRAM update buffer
#include "vrambuf.h"
//#link "vrambuf.c"

/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x03,			// screen color

  0x0D,0x25,0x30,0x00,	// background palette 0
  0x1C,0x20,0x2C,0x00,	// background palette 1
  0x00,0x10,0x20,0x00,	// background palette 2
  0x06,0x16,0x26,0x00,   // background palette 3

  0x16,0x35,0x24,0x00,	// sprite palette 0
  0x00,0x37,0x25,0x00,	// sprite palette 1
  0x0D,0x2D,0x3A,0x00,	// sprite palette 2
  0x0D,0x27,0x2A	// sprite palette 3
};

//----Enums
enum LABELS {START, l_DIAL, l_NON, l_OUI /*LABELS_COUNT*/};
enum LABELS labl=START;

enum GAME_STATE {GAME, DIAL, CHOICE, END};
enum GAME_STATE game_st=GAME;

enum DIAL_T {N='n', C='c', F='f', J='j', A='a'};

//----Struct definition
typedef struct Passage Passage;
struct Passage
{
    enum DIAL_T t; //Type de passage
    char c[63];//Content, en génrale le texte affiché
};

typedef struct Choix Choix;
struct Choix
{
    char txt[20]; //Texte du choix
    int jmp;	  //Indice du label de destination
};

//-----Variables utiles

unsigned int index = 0; //index dans le label en cours
unsigned char cursor = 1;

unsigned char choice_sel=0;

char pad; //controller
bool a_pressed = false;

//-----Visual Novel content !! °˖✧◝(⁰▿⁰)◜✧˖°

Passage SCRPT[] = {
  {N,"Bienvenue dans VNES ! *"},
  {A,"On est pas bien la ?"},
  {A,"Ce beau ciel bleu, cette mer    calme..."},
  {A,"Je pourrais rester assise       ici toute ma vie ! Oui oui !"},
  {A,"Qu'est-ce que tu en penses ?"},
  {C,"0"}, //Jump au début du dialogue
  {A,"Super ! Je suis contente :)"},
  {J,"9"},
  {A,"Oh dommage, on rentre ? :("},
  {N, "fin"}
};

//Choix CHOIX[]={}

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}
void clrscr() {
  vrambuf_clear();
  ppu_off();
  vram_adr(0x2000);
  vram_fill(0, 32*28);
  vram_adr(0x0);
  ppu_on_bg();
}

void clrtxt(){ //???
  vrambuf_clear();
  ppu_off();
  vram_adr(NTADR_A(2,24));
  vram_fill(0, 64);
  //vram_adr(0x0);
  ppu_on_bg();
}
//function
void draw_dial(){  
  if (SCRPT[index].t==N){
    vrambuf_put(NTADR_A(2,24),SCRPT[index].c, cursor);
  }
  else if (SCRPT[index].t==A){ //Prototype, trouver un moyen d'etre propre
    //Swap palette
    vrambuf_put(NTADR_A(2,24),SCRPT[index].c, cursor);
    vrambuf_put(NTADR_A(13,22),"_ANGE_", 6);
  }
}

void updt_dial(){
  //Managing les passages spéciaux
  if (SCRPT[index].t==C){
    clrscr();
    game_st=CHOICE;
  }
  else if (SCRPT[index].t==J){
    index = atoi(SCRPT[index].c);
  }
  
  if (pad&PAD_A){
    if (!a_pressed){
    if (index<5){
  	index+=1;
      	cursor=1;
      	//Remplace txt par blanc, trouver une autre soluce
      	// clrscr ?
      	vrambuf_put(NTADR_A(2,24),"                                                                ", 64);
      	//clrtxt();
      	//clrscr();
      
      	a_pressed=true;
    }
    else{
     game_st=END;
     clrscr();
    }
  }
  }
  else{
   a_pressed=false; 
  }
  
  if (cursor<63) cursor++;
  
  
}

char oam_id;
void draw_game(){
  //oam_spr(x,y,sprite,color,id)
  oam_id = oam_spr(40, 40, 21, 1, oam_id);
  
}

void updt_game(){
  if (pad&PAD_A){
    if (!a_pressed){
      game_st=DIAL;
      clrscr();
      a_pressed=true;
    }
  }
  else{
   a_pressed=false; 
  }
  
}

//-----------------------
//---- MAIN LOOP !

void main(void)
{
  setup_graphics();

  
  // enable rendering
  ppu_on_all();
  // infinite loop
  while(1) {
    oam_id = 0;
    ppu_wait_frame();
    vrambuf_clear();
    set_vram_update(updbuf);
    
    pad = pad_poll(0); //pad j1
    
    if (game_st==GAME){
      vrambuf_put(NTADR_A(2,2),"Game",4);
      draw_game();
      updt_game();
      
    }
    else if (game_st==DIAL){
      vrambuf_put(NTADR_A(2,2),"Dialogue",8);
      draw_dial();
      updt_dial();
      
    }
    else if (game_st==CHOICE){
      vrambuf_put(NTADR_A(2,2),"Choice",6);
      
    }
    else if (game_st==END){
      vrambuf_put(NTADR_A(2,2),"END",3);
      
    }
    
    
    
    
  }
}


//                                        ___
//                                   _.--'...`-._
//                                .-'..::::::::..\
//                               /.:::::::::::::::\
//                              |.::::::::::::::::.|
//                             .-..::::::::::::::::|
//           ugh?              | |\.\\|-\|//- \::::|
//                             | | `-\ 'D| 'D|||)::|
//                             | |  ||   <    ||::.|
//                             | |  |'        |/:__'
//                             | |   \\_ `  _  /=__=-
//                             | |      `--'   |::.`-.
//                             | |      _|    _/\::::\
//                             |_|     /#|  _/##'  \:|
//                             |-|    |/|__/\#'     \'
//                             | |  _/       //      \
//                             | |_/________//        |
//                             | |YO _ PIYO   \|/     |
//                             | |  <^|        `      |
//                             | |  (__)       |      |
//                            _|_|\_`'-'      ,'      |
//                           ( __ 7 \--       |      .'
//--------------------------------------------------------
// ASCII: http://www.ascii-art.de/ascii/ab/anime.txt