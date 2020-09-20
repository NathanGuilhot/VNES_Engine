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
#include <stdio.h>

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

const char ANGESPR[][8] = { 
  {0x00,0x00,0x81,0x82,0x83,0x84,0x85,0x00},
  {0x00,0x86,0x87,0x87,0x87,0x87,0x89,0x00},
  {0x00,0x8A,0x87,0x8B,0x8C,0x8D,0x8E,0x00},
  
  {0x00,0x8F,0x88,0x03,0x90,0x91,0x92,0x93},
  {0x94,0x95,0x96,0x03,0x03,0x03,0x97,0x80},
  {0x98,0x99,0x9A,0x9B,0x03,0x9C,0x9D,0x85},
  {0x9E,0x9F,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5},
  {0x00,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0x00},
  
  {0x00,0x00,0xAC,0xAD,0xAE,0xAF,0xB0,0x00},
  {0x00,0x00,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6},
  
  {0x00,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD},
  {0x00,0xBE,0xBF,0xC0,0xC1,0xC2,0xC3,0x00},
  {0x00,0x00,0xC4,0xC5,0xC6,0xC7,0xC8,0x00},
  {0x00,0x00,0xC9,0xCA,0xCB,0x03,0xCC,0x00},
  
  {0x00,0x00,0x00,0xCD,0x03,0xCE,0xCF,0x00},
  {0x01,0x01,0x00,0xD0,0x03,0xD1,0x03,0xD2}
  
};


/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x03,			// screen color

  0x0D,0x31,0x30,0x00,	// background palette 0
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
enum GAME_STATE game_st=DIAL;

enum DIAL_T {N='n', C='c', F='f', J='j', A='a'};

//----Struct definition
typedef struct Passage Passage;
struct Passage
{
    enum DIAL_T t; //Type de passage
    char c[63];//Content, en génrale le texte affiché
};

typedef struct Choice Choice;
struct Choice
{
    char txt[30]; //Texte du choix
    int jmp;	  //Indice du label de destination
};

//typedef struct ChoiceCollection ChoiceCollection;
//struct ChoiceCollection{
//    int cc[2]; //liste des indice du tableau des Choice
  		//Pour le moment limité à 2 choix
//};

//-----Variables utiles

unsigned int index = 5; //index dans le label en cours
unsigned char cursor = 1;

unsigned char choice_sel=0;

char pad; //controller
bool a_pressed = false; //1
bool b_pressed = false; //B
bool u_pressed = false; //UP
bool d_pressed = false; //DOWN
bool l_pressed = false;	//LEFT (gauche)
bool r_pressed = false; //RIGHT (drouate)


int i;
char oam_id;

//-----Visual Novel content !! °˖✧◝(⁰▿⁰)◜✧˖°

Passage SCRPT[] = {
  {N,"Bienvenue dans VNES ! *"},
  {A,"On est pas bien la ?"},
  {A,"Ce beau ciel bleu, cette mer    calme..."},
  {A,"Je pourrais rester assise       ici toute ma vie !"},
  {A,"Qu'est-ce que tu en penses ?"},
  {C,"0"}, //Jump au début du dialogue
  {A,"Super ! Je suis contente :)"},
  {J,"9"},
  {A,"Oh dommage, on rentre ? :("},
  {N, "fin"}
};

Choice ListeChoix[]= {
  {"J'aime beaucoup !",6},
  {"Les mouettes m'ennuient",8}
};

int ChoiceCollection[][2] = {
  {0,1}
  
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
  
  //Dessin du visage
  oam_id = oam_spr(112, 67, 211, 2, oam_id);
  oam_id = oam_spr(130, 67, 211, 2, oam_id);
  oam_id = oam_spr(122, 73, 212, 2, oam_id);
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
    if (index<8){
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

void draw_game(){
  //oam_spr(x,y,sprite,color,id)
  oam_id = oam_spr(40, 40, 8, 1, oam_id);
  
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

void draw_choice(){
  vrambuf_put(NTADR_A(2,15+choice_sel+choice_sel),">",2);
  oam_id = oam_spr(112, 67, 211, 2, oam_id);
  
  for (i=0;i<2;i++){
  	vrambuf_put(NTADR_A(3,15+i+i),ListeChoix[ChoiceCollection[atoi(SCRPT[index].c)][i]].txt, 30);
  }
  
}

void updt_choice(){
  //Selection
  if (pad&PAD_A){
    if (!a_pressed){
      index = ListeChoix[ChoiceCollection[atoi(SCRPT[index].c)][choice_sel]].jmp;
      game_st=DIAL;
      clrscr();
      a_pressed=true;
      choice_sel=0;
    }
  } else{a_pressed=false;}
  
  //Up & Down
  if (pad&PAD_DOWN){
    if (!d_pressed){
      if (choice_sel<1){vrambuf_put(NTADR_A(2,15+choice_sel+choice_sel)," ",2);choice_sel++;}
      d_pressed=true;
    }
  } else{d_pressed=false;}
  if (pad&PAD_UP){
    if (!u_pressed){
      if (choice_sel>0){vrambuf_put(NTADR_A(2,15+choice_sel+choice_sel)," ",2);choice_sel--;}
      u_pressed=true;
    }
  } else{u_pressed=false;}
  
}

void draw_end(){
  
}

void updt_end(){
 if (pad&PAD_A){
    if (!a_pressed){
      game_st=GAME;
      clrscr();
      a_pressed=true;
      index=0;
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
  
  vram_adr(NTADR_A(0,20));
  vram_fill(1, 32*1);
  
  for (i=0;i<sizeof(ANGESPR)/8; i++){ //Draw_Ange
    vram_adr(NTADR_A(11,5+i));
    vram_write(ANGESPR[i],8);
  }
  
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
      draw_choice();
      updt_choice();
      
    }
    else if (game_st==END){
      vrambuf_put(NTADR_A(2,2),"END",3);
      draw_end();
      updt_end();
      
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