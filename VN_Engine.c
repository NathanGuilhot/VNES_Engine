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

  0x11,0x30,0x27,0x0,	// background palette 0
  0x1c,0x20,0x2c,0x0,	// background palette 1
  0x00,0x10,0x20,0x0,	// background palette 2
  0x06,0x16,0x26,0x0,   // background palette 3

  0x16,0x35,0x24,0x0,	// sprite palette 0
  0x00,0x37,0x25,0x0,	// sprite palette 1
  0x0d,0x2d,0x3a,0x0,	// sprite palette 2
  0x0d,0x27,0x2a	// sprite palette 3
};

//----Enums
enum LABELS {START, l_OUI, l_NON, LABELS_COUNT};

enum GAME_STATE {GAME, DIAL, CHOICE};

enum DIAL_T {N='n', C='c', F='f', A='a'};

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

//-----Visual Novel content !! °˖✧◝(⁰▿⁰)◜✧˖°

Passage SCRPT[] = {
  {N,"Bienvenue dans VNES !"},
  {A,"On est pas bien là ?"}
};

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}

void main(void)
{
  setup_graphics();
  // draw message  
  vram_adr(NTADR_A(2,20));
  vram_write(SCRPT[0].c, 63);
  // enable rendering
  ppu_on_all();
  // infinite loop
  while(1) {
    
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