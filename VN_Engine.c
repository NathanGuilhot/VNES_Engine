//                        ___    
//                      //|||\\  
//                      /|^,^|\\ 
//                      ||\-/||| 
//                      \\| |||| 
//                     /|-----|\ 
//                    |\|  &  |/|
//                    | |     | |
//                    | |     | |
////---------------------------------------------------\\
//||						       ||
//|| ~VИES_ENGINE - A VISUAL NOVEL ENGINE FOR THE NES~ ||
//||						       ||
//\\---------------------------------------------------//



//#include <stdlib.h>
#include <string.h>
//#include <stdio.h> //I don't know if I really needs it

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

//Music ! // setup Famitone library
//#link "famitone2.s"
void __fastcall__ famitone_update(void);
//#link "beach_shertigan.s"
extern char beach_shertigan_data[];

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
  {0x0B,0x0B,0x0B,0xD0,0x03,0xD1,0x03,0xD2}
  
};


/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x11,			// screen color

  0x0D,0x15,0x30,0x00,	// background palette 0
  0x1C,0x20,0x2C,0x00,	// background palette 1
  0x00,0x10,0x20,0x00,	// background palette 2
  0x06,0x16,0x26,0x00,   // background palette 3

  0x16,0x35,0x24,0x00,	// sprite palette 0
  0x00,0x37,0x25,0x00,	// sprite palette 1
  0x0D,0x2D,0x3A,0x00,	// sprite palette 2
  0x0D,0x27,0x2A	// sprite palette 3
};

const char btn_next[] = {0x16};

//----Enums

//enum LABELS {START, l_DIAL, l_NON, l_OUI /*LABELS_COUNT*/};
//enum LABELS labl=START;

enum GAME_STATE {GAME, DIAL, CHOICE, END};
enum GAME_STATE game_st = DIAL;

enum DIAL_T {N/*NARRATOR*/, C/*CHOICE*/, F/*FIN*/, J/*JUMP*/
,SWPEL/*SWAP LEFT EYE*/,SWPER/*SWAP RIGHT EYE*/,SWPM/*SWAP MOUTH*/ ,A/*ANGE*/,H/*HIDE/SHOW*/};

//----Struct definition
typedef struct Passage Passage;
struct Passage
{
    enum DIAL_T t; //Type de passage
    char* c;//Content, en general le texte affiché
};

typedef struct Choice Choice;
struct Choice
{
    char* txt; //Texte du choix
    int jmp;	  //Indice du label de destination
};

//-----Variables utiles

unsigned int index = 131; //index dans le label en cours //328 max sans visage+choice
unsigned char cursor = 1;

unsigned char choice_sel=0;

char pad; //controller
bool a_pressed = false; //A
bool b_pressed = false; //B
bool u_pressed = false; //UP
bool d_pressed = false; //DOWN
bool l_pressed = false;	//LEFT (gauche)
bool r_pressed = false; //RIGHT (drouate)

const bool debug_mode = true;

int i;
char oam_id;

//face var
char sprEl=0; //gauche
char sprEr=0;//Drouate
char sprM=1;//Bouche

int scrnBrightness = 0;
bool dispAnge = true;

//0'v'   1 :)  	2 :|   	3 :(   	4 :D  	5 D:    6 A_A	7 /	8 \	9 é	10 è

#define FR 1 //bolean, 1 = FR 0 = EN
//Visual Novel Content
#if FR
  #include "script_fr.h"
#else
  #include "script_en.h"
#endif


const char expr[]={ //liste des expressions
  211	,212	,213	,214	,215	, 216	,217	, 218	, 219	,220	,221
//0'v'   1 :)  	2 :|   	3 :(   	4 :D  	5 D:    6 A_A	7 /	8 \	9 é	10 è
};

//Choix CHOIX[]={}

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}

int c_atoi(char* str){ //custom atoi function so I don't need the stdlib
  int res = 0;
  for (i = 0; str[i] != '\0'; i++) res = res * 10 + str[i] - '0';
  return res;
  //Credit : https://www.geeksforgeeks.org/write-your-own-atoi/
}

void clrscr() {
  vrambuf_clear();
  ppu_off();
  vram_adr(0x2000);
  vram_fill(0, 32*29);
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
void draw_ange(){
  vrambuf_clear();
  ppu_off();
  
  vram_adr(NTADR_A(0,20));
  vram_fill(11, 32*1);
  
  for (i=0;i<sizeof(ANGESPR)/8; i++){ //Draw_Ange
    vram_adr(NTADR_A(11,5+i));
    vram_write(ANGESPR[i],8);
  }
  
  ppu_on_all();
}

void draw_ange_face(){
  oam_id = oam_spr(111, 67, expr[sprEl], 2, oam_id); //  o       
  oam_id = oam_spr(129, 67, expr[sprEr], 2, oam_id); //          O
   
  oam_id = oam_spr(121, 73, expr[sprM], 2, oam_id);  //    ___
  
}

//function
void draw_dial(){  
  if (SCRPT[index].t==N){
    vrambuf_put(NTADR_A(1,24),SCRPT[index].c, cursor);
    vrambuf_put(NTADR_A(13,22),"      ", 6);
  }
  else if (SCRPT[index].t==A){ //Prototype, trouver un moyen d'etre propre
    //Swap palette
    vrambuf_put(NTADR_A(1,24),SCRPT[index].c, cursor);
    vrambuf_put(NTADR_A(13,22),"_ANGE_", 6);
  }
  
  //Dessin du visage
  if (dispAnge){draw_ange_face();};
  
  //Draw text + Typewriter effect
  if (debug_mode){cursor=strlen(SCRPT[index].c);};
  if (cursor<strlen(SCRPT[index].c)) {cursor++;vrambuf_put(NTADR_A(28,26)," ",1);}
  else {vrambuf_put(NTADR_A(28,26),btn_next,1);}
  
}

void updt_dial(){
  //Managing les passages spéciaux
  switch (SCRPT[index].t){
  case C:{
    clrscr();
    game_st=CHOICE;
    break;
  }
  case J:{
    index = c_atoi(SCRPT[index].c);
    break;
  }
  case SWPEL:{
    sprEl=c_atoi(SCRPT[index].c);
    index++;
    break;
  }
  case SWPER:{
    sprEr=c_atoi(SCRPT[index].c);
    index++;
    break;
  }
  case SWPM:{
    sprM=c_atoi(SCRPT[index].c);
    index++;
    break;
  }
  case H:{
    if (dispAnge){clrscr();} else {draw_ange();}
    dispAnge=!dispAnge;
    index++;
    break;
  }
  }
  
  
  if (pad&PAD_A){
    if (!a_pressed){
      a_pressed=true;
      if (cursor<strlen(SCRPT[index].c)){cursor=strlen(SCRPT[index].c);}//Affiche tout le texte; pas top parce que taille varibale pour le texte
      else {
        if (index<sizeof(SCRPT)/sizeof(SCRPT[0])-1){
        index+=1;
        cursor=1;
        //Remplace txt par blanc, trouver une autre soluce
        // clrscr ?
        vrambuf_put(NTADR_A(2,24),"                                                                ", 64);

      	}
     	 else{
     	   game_st=END;
     	   cursor=0;
     	   clrscr();
      }
    }
    }
  }
  else{
   a_pressed=false; 
  }
  
  
}

void draw_game(){
  //oam_spr(x,y,sprite,color,id)
  //oam_id = oam_spr(40, 40, 8, 1, oam_id);
  vrambuf_put(NTADR_A(13,10),"~ANGE~",6);
  vrambuf_put(NTADR_A(3,11),"_________________________",25);
  vrambuf_put(NTADR_A(5,13),"a date on the seaside",21);
  
  
  #if FR
  vrambuf_put(NTADR_A(1,1),"fr",2);
  #else
  vrambuf_put(NTADR_A(5,16),"en",2);
  #endif
  
  vrambuf_put(NTADR_A(1,26),"PRESS A",7);
  
  vrambuf_put(NTADR_A(19,26),"2020 NIGHTEN",12);
  
}

void updt_game(){
  if (pad&PAD_A){
    if (!a_pressed){
      game_st=DIAL;
      clrscr();
      if (dispAnge){draw_ange();}
      a_pressed=true;
    }
  }
  else{
   a_pressed=false; 
  }
}

char nb_choice = 2;

void draw_choice(){
  vrambuf_put(NTADR_A(2,17+choice_sel+choice_sel),">",2);
  oam_id = oam_spr(112, 67, 211, 2, oam_id);
  nb_choice = ChoiceCollection[c_atoi(SCRPT[index].c)][0];
  
  for (i=1;i<=nb_choice;i++){
  	vrambuf_put(NTADR_A(3,15+i+i),
                    ListeChoix[ChoiceCollection[c_atoi(SCRPT[index].c)][i]].txt,
                    strlen(ListeChoix[ChoiceCollection[c_atoi(SCRPT[index].c)][i]].txt)); //ugly repetition
  }
  
}

void updt_choice(){
  //Selection
  if (pad&PAD_A){
    if (!a_pressed){
      index = ListeChoix[ChoiceCollection[c_atoi(SCRPT[index].c)][choice_sel+1]].jmp;
      game_st=DIAL;
      clrscr();
      if (dispAnge){draw_ange();} //(?)
      a_pressed=true;
      choice_sel=0;
    }
  } else{a_pressed=false;}
  
  //Up & Down
  if (pad&PAD_DOWN){
    if (!d_pressed){
      if (choice_sel<nb_choice-1){vrambuf_put(NTADR_A(2,17+choice_sel+choice_sel)," ",2);choice_sel++;}
      d_pressed=true;
    }
  } else{d_pressed=false;}
  if (pad&PAD_UP){
    if (!u_pressed){
      if (choice_sel>0){vrambuf_put(NTADR_A(2,17+choice_sel+choice_sel)," ",2);choice_sel--;}
      u_pressed=true;
    }
  } else{u_pressed=false;}
  
}

void draw_end(){
  //draw_dial();
  vrambuf_put(NTADR_A(14,10),"FIN",3);
  vrambuf_put(NTADR_A(5,20),"Merci d'avoir joue! *",21);

  
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
  
  //beach sound
  famitone_init(beach_shertigan_data);
  // set music callback function for NMI
  nmi_set_callback(famitone_update);
  // play music
  //music_play(0);

  
  // enable rendering
  ppu_on_all();
  // infinite loop
  if (debug_mode){draw_ange();};
  
  while(1) {
    
    oam_id = 0;
    ppu_wait_frame();
    vrambuf_clear();
    set_vram_update(updbuf);
    
    pad = pad_poll(0); //pad j1
    
    switch (game_st){
    case GAME:{
      if (debug_mode){vrambuf_put(NTADR_A(2,2),"Game",4);}
      draw_game();
      updt_game();
      break;

    }
    case DIAL:{
      if (debug_mode){vrambuf_put(NTADR_A(2,2),"Dialogue",8);}
      draw_dial();
      updt_dial();
      break;
      
    }
    case CHOICE:{
      if (debug_mode){vrambuf_put(NTADR_A(2,2),"Choice",6);}
      draw_choice();
      updt_choice();
      break; 
    }
    case END:{
      if (debug_mode){vrambuf_put(NTADR_A(2,2),"END",3);}
      draw_end();
      updt_end();
      break;
    }
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