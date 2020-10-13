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

//----Enums

//enum LABELS {START, l_DIAL, l_NON, l_OUI /*LABELS_COUNT*/};
//enum LABELS labl=START;

enum GAME_STATE {GAME, DIAL, CHOICE, END};
enum GAME_STATE game_st=GAME;

enum DIAL_T {N/*NARRATOR*/, C/*CHOICE*/, F/*FIN*/, J/*JUMP*/
,SWPEL/*SWAP LEFT EYE*/,SWPER/*SWAP RIGHT EYE*/,SWPM/*SWAP MOUTH*/ ,A/*ANGE*/};

//----Struct definition
typedef struct Passage Passage;
struct Passage
{
    enum DIAL_T t; //Type de passage
    char c[60];//Content, en génrale le texte affiché
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

unsigned int index = 0; //index dans le label en cours
unsigned char cursor = 1;

unsigned char choice_sel=0;

char pad; //controller
bool a_pressed = false; //A
bool b_pressed = false; //B
bool u_pressed = false; //UP
bool d_pressed = false; //DOWN
bool l_pressed = false;	//LEFT (gauche)
bool r_pressed = false; //RIGHT (drouate)

bool debug_mode = false;

int i;
char oam_id;

//face var
char sprEl=0; //gauche
char sprEr=0;//Drouate
char sprM=1;//Bouche

int scrnBrightness = 0;

//0'v'   1 :)  	2 :|   	3 :(   	4 :D  	5 D:    6 A_A   7 /   8 \

//-----Visual Novel content !! °˖✧◝(⁰▿⁰)◜✧˖°

const Passage SCRPT[] = {
  {SWPM,"4"},
  {N, "En cette fin d'apres-midi,      tu marches sur la plage."},
  {N, "Il y a peu de monde ici.        C'est calme."},
  {N, "Rythme par le son de la mer,    tu avance sur le sable."},
  {N, "Tu trouve enfin la personne     que tu cherchais."},
  //Show ANGE
  {A, "Ah tu es la!"},
  {A, "Ca me fait plaisir de te voir,  tu vas bien?"},

  //> "Oui ca va! Et toi ?"},
  {A, "Moi aussi je vais bien,         tres bien meme!"},
  {A, "J'avais un peu peur qu'on       arrive pas a se retrouver,"},
  {A, "mais finalement il n'y avait    pas a s'inquieter!"},

  //> "Desole du retard"
  {A, "Ne t'excuse pas, tu es la       c'est l'essentiel!"},
  {A, "Et j'ai pu profiter du          paysage en attendant!"},

  //> "C'etait dur de te trouver"
  {A, "Haha, mes indications           etaient si vagues que ca?"}, ///////////
  {A, "Desole, je ne connais pas       beaucoup la region."},
  {A, "Et puis au moins sur cette      plage on est tranquille!"},

  {N, "Son attention se porte          alors sur la mer."},
  {N, "Elle est calme, reguliere,      et s'etant a perte de vu."},
  {A, "C'est beau,                     tu ne trouves pas?"},

  //> "Oui, c'est tres joli!"},
  {A, "Ah! Je vois que tu apprecies    la vue autant que moi!"},
  {A, "Si je le pouvais je resterai    ici toute ma vie."},
  {A, "Bon ce ne serait pas tres       confortable a la longue,"},

  //> "Bof, c'est la mer quoi."},
  {A, "Hehe, tu n'as toujours          pas une ame d'artiste."},
  {A, "Et c'est pas grave, tu as le    droit de trouver ca banal."},

  {A, "Mais pour un rendez-vous ca     reste un tres bon endroit."},
  {A, "Maintenant ma connexion         n'est plus un probleme."}, 
  {A, "Et c'est bien plus chouette     qu'en visio!"},

  //
  {A, "Hum, au fait, je voulais        te poser une question..."},
  {A, "Tu te souviens de ton projet?   Celui dont tu m'as parle?"},
  {A, "Il avait l'air interessant,     comment il avance?"},

  //> J'en vois le bout!
  {A, "Genial! Il y a de quoi etre     fier de toi!"},
  {A, "Tu sais, j'admire beaucoup      ta determination."},
  {A, "Tu dit souvent que j'exagere,   mais c'est sincere!"},
  {A, "Rien que de te parler me        motive beaucoup!"},


  //> J'ai du mal a avancer...
  {A, "Oh mince, excuse-moi...         Ca vas aller j'espere!"},
  {A, "Surtout ne te rend pas          malade par rapport a ca,"},
  {A, "C'est normal d'avoir des        periodes de doute."},
  {A, "Peut etre que tu as juste       besoin de te reposer!"},
  {A, "Est-ce que tu as pense a        demander de l'aide?"},
  //>Oui
  {A, "Super, je penses que tu         es sur la bonne voie!"},
  {A, "Penses a parler de tes          doutes avec ces personnes,"},
  {A, "Parfois, juste parler aide      a trouver une solution."},
  {A, "En tout cas c'est ce qui        m'arrive quand on discute!"},

  //>Je sais pas si ça m'aiderait
  {A, "Tu sais, il y a pas de          honte a demander de l'aide."},
  {A, "Mais je comprends, c'est        pas toujours facile."},
  {A, "Je... je veux bien              t'aider si tu veux!"},
  {A, "Mais tu as surement des amis    plus competents que moi!"},
  {A, "Dans tous les cas ne reste      pas solitaire, promis?"},


  //> Je suis passe a autre chose
  {A, "Oh d'accord, excuse moi!"},
  {A, "C'est pas grave, tu as le       droit de changer."},
  {A, "Si on concretisait toutes nos   idees on en sortirait pas."},
  //a"(meme si je devrais pas          faire totalement l'inverse)"},


  {A, "D'ailleurs... Je sais pas       si tu t'en souviens..."},
  {A, "Mais recemment tu m'as          encourage a envoyer mon CV."},
  {A, "Je ne pensais pas avoir de      reponses pour etre honnete."},
  {A, "Mais quelqu'un a repondu!"},
  //>Trop bien!
  {A, "Haha, merci beaucoup!           Mais tout n'est pas gagne."},
  {A, "Ils m'ont invite a un           entretiens mais..."},

  //>Qu'est-ce qu'ils t'ont dit?
  {A, "Et bien..."},
  {A, "Je crois que j'ai un            entretiens d'embauche..."},

  {A, "Mais ça me fait un peu          peur."},
  {A, "Tu vois, ca fait longtemps      que je n'ai pas travaille."},
  {A, "J'ai meme oublie comment se     passe ces entretiens."},
  {A, "Tu sais en quoi ça consiste     toi?"},

  //>C'est juste des questions
  {A, "Ah d'accord, ils veulent        juste me connaitre?"},
  {A, "C'est un peu comme un           rendez-vous amoureux, hehe"},
  {A, "Mais il faut bien s'habiller    pour un rendez-vous, non?"},
  {A, "Arg, j'ai aucune idee de        ce que je vais mettre!"},
  {A, "Une chemise peut etre?          Ou un costume c'est mieux?"},

  //>Ils vont pas te manger haha
  {A, "Haha, tu as raison; je me       prends trop la tete."},
  {A, "Mais ça reste un moment         important,"},
  {A, "Je voudrais pas faire           n'importe quoi..."},
  {A, "Par exemple, j'ai des           articles sur le sujet."},
  {A, "Et ils conseillent de bien      s'habiller, mais j'hesite."},
  {A, "Je dois vraiment mettre une     chemise? Tu en penses quoi?"},

  //>J'ai oublie moi aussi
  {A, "Haha, je suis pas la seule      personne dans ce cas."},
  {A, "Ca me rassure un peu je         t'avoue."},
  {A, "Au final ça ne doit pas         etre si complique que ça."},
  {A, "Mais j'ai peur de faire         un truc de travers."},
  {A, "Genre, est-ce que je dois       mettre une... chemise?"},


  //>Oui, ca fait serieux
  {A, "D'accord d'accord, il faut      que j'ai l'air pro!"},
  {A, "Si je fais bonne impression     il me feront confiance."},
  {A, "Oui, c'est logique!"},
  {A, "...maintenant je vais devoir    trouver une chemise."},
  {A, "J'en ai peut etre une dans      mon placard..."},
  {A, "Elle date, je la ressort que    pour les mariage."},
  {A, "Mais ça devrait faire           l'affaire!"},

  //>Non, soit decontract'
  {A, "Ouf, j'avais peur de devoir     m'habiller en pingouin!"},
  {A, "Donc, une tenue plus            decontractee..."},
  {A, "Hum, je pourrais ressortir      mes tee shirt d'ado."},
  {A, "Mais tu ne voulais surement     pas dire ça haha"},
  {A, "Qu'est-ce qu'ils vont penser    de moi si j'arrive avec ça?"},
  {A, "Je penses devoir faire des      essais avant de me decider."},

  //>Porte ce qui te plait
  {A, "Oh, c'est gentil."},
  {A, "Tu as peut etre raison, faut    que je me fasse confiance."},
  {A, "Tu sais, je fais pas tres       attention a ce que je porte."},
  {A, "Meme ici je porte mon pull      gris, comme tous les jours."},
  {A, "Je n'ai jamais vraiment         reflechi a ce qui me plait."},
  {A, "Il faudra que j'experimente     avec ce que j'ai!"},

  {A, "Dit, je pourrai t'envoyer       des photos de mes essais?"},

  //>Bien sur!
  {A, "Merci! Je savais que je         pouvais compter sur toi!"},
  {A, "Juste un avis exterieur         m'aidera beaucoup a choisir."},

  //>Je ne saurais pas t'aider
  {A, "Mais non, tu exagere!"},
  {A, "Je demande juste ton            avis honnete, c'est tout!"},
  {A, "Tu es quelqu'un en qui j'ai     confiance pour ça."},
  {A, "Et si je veux m'embarrasser,    c'est pas devant un styliste"},
  //>Bon, si tu insiste
  {A, "Merci beaucoup! Je te           revaudrai ça!"},

  {A, "Bon, j'arrete de t'embeter      avec mes tracas."},
  {A, "Tu veux faire quelque           chose en particulier?"},
  //>Et si on achetait une glace?
  {A, "Oh oui! Tres bonne idee!"},
  {A, "On dit qu'ils vendent tous      les parfums imaginables ici."},
  {A, "C'est quoi ton parfum           prefere?"},

  //>Vanille
  {A, "Oh, je vois que tu es           du genre classique!"},
  {A, "C'est exactement comme moi,     j'adore la Vanille."},
  {A, "C'est un gout si doux, qui      chatouille les papilles."},
  {A, "Je choisissais toujours ce      parfum etant enfant!"},
  {A, "Et meme adulte d'ailleurs!"},

  //>Chocolat
  {A, "Hehe, chocolat, ça correspond   bien a ton style."},
  {A, "J'aime beaucoup le choco' mais  en glace c'est...bizarre."},
  {A, "Comme s'ils utilisait une       arome totalement different."},
  {A, "Tu trouves pas? Ou c'est moi    qui me fait des films?"},
  //>Je suis d'accord
  {A, "Ah! Ca fait plaisir de savoir   que je ne delire pas."},
  {A, "Mais dans tous les cas tu as    le droit d'aimer!"},
  //>Je penses que c'est des films
  {A, "C'est fort possible!"},
  {A, "Peut etre que je n'ai juste     pas goute les bonnes marques"},
  {A, "Tu m'en recommandera un de      ces jours!"},

  //>Fruit
  {A, "Sympa, et ça correspond bien    a l'ambiance estivale!"},
  {A, "J'adore les fruits, c'est ça    qui me maintient la sante."},
  {A, "Mais alors en glace, ça me      rappel ma grand-mere."},
  {A, "Elle m'en offrait a chacune     de mes visites."},
  {A, "Bon c'etait previsible          au bout d'un moment."},
  {A, "Mais ça reste de chouettes      souvenirs!"},
  {A, "Oups! voila que je parle        encore trop de moi."},
  {A, "Excuse moi,                     je le fais pas expres."},

  //>Peu importe
  {A, "Oh d'accord, tu n'es pas        tres glace?"},
  //>J'aime tous les parfums
  {A, "Ah! Te connaissant ça ne        m'etonne pas en effet!"},
  {A, "On verras bien ce qu'il y a     et ce qui te fait envie."},

  //>Non pas trop
  {A, "Oh d'accord..."},
  {A, "Je comprends, tu proposais      ça pour me faire plaisir?"},
  {A, "C'est gentil, mais tu as pas    a te forcer tu sais."},
  //>Pardon, oublions les glaces
  {A, "Ne t'excuse pas! C'est tres     sympa au contraire."},
  {A, "Et puis, on est tres bien       sur la plage, pas vrai?"},
  {A, "Je prefere rester ici,          c'est plus calme."},
  {A, "Tu as vu qu'ils font            une fete en ville?"},
  {N, "En effet, en arrivant tu as     entendu de la musique."},
  {A, "De ce que j'ai compris, c'est   un grand festival annuel."},
  {A, "Si je peux eviter de me meler   a la foule, c'est mieux."},
  {N, "D'ici, vous entendez des        chants et des bruits festifs"},
  {N, "Il doit y avoir beaucoup de     monde la bas."},
  {N, "Et c'est peut etre pour ça      que la plage est deserte."},
  {A, "Tu as du mal avec la foule      toi?"},
  //>Oui, je ne supporte pas
  {A, "Tu es un peu comme moi alors."},
  {A, "Il m'arrive de stresser rien    qu'en y pensant."},
  {A, "Sortir de chez moi est deja     un challenge,"},
  {A, "Alors faire la fete, impossible d'y aller en vrai."},
  {A, "Mais c'est pas vraiment         la meme chose ici."},
  {A, "Et puis tu es la,               on peut se soutenir!"},

  //>Ca me derange pas vraiment
  {A, "Ca te pose pas de problemes     particulier? C'est chouette!"},
  {A, "Je veux dire, j'aimerais bien   etre comme toi."},
  {A, "Pas forcement aimer ça, mais    etre plus neutre."},
  {A, "Ne pas stresser juste a l'idee  de voir des gens..."},
  {A, "..."},
  {A, "Excuse moi."},
  {A, "Beaucoup de choses me font      stresser de toutes façons,"},
  {A, "je crois que tu commence a      me connaître!"},
  {A, "Je suis comme ça, j'ignore      si je changerais un jour."},
  //{A, "Mais cette raison que je suis   bien en ta compagnie."}, //Line à supprimer ? Doublon
  //{A, "Tu m'acceptes, meme quand       j'ai du mal a le faire."},
  //{A, "Et ça me fait du bien."},

  //>J'adore la foule!
  {A, "Vraiment? C'est dingue ça!"},
  {A, "C'est vrai que tu vas souvent   faire la fetes."},
  {A, "Enfin plus que moi ça           c'est sur!"},
  {A, "Tu as l'esprit festif, c'est    surement une bonne chose."},
  {A, "Je suis un peu a l'oppose."},
  {A, "Mais tu sais, c'est que         j'aime avec notre amitie."},
  {A, "On est des personnes si         differentes,"},
  {A, "mais on se comprend."},
  {A, "C'est tres enrichissant,        tu ne trouves pas?"},
  {A, "Puis j'aurais du mal a trouver  des personnes comme moi."},
  {A, "Enfin, je crois..."},

  //(jump branch)

  //---

  //>Non, ça peut etre drole
  {A, "D'accord, c'est comme           tu veux!"},
  {A, "Mais il y a une autre raison    de ne pas se forcer..."}, //(??)

  {A, "Euh, par contre                 je dois t'avouer..."},
  {A, "Je n'ai pas vraiment d'argent   sur moi."},
  {A, "Vraiment, excuse moi!"},
  {A, "Tu vois, j'ai du acheter de     l'equipement pour ma maison."},
  {A, "Et du coup... c'est un peu      ric rac en ce moment."},
  {A, "Ca te derange de m'avancer?"},
  //>Je comptais te l'offrir
  {A, "V... vraiment?"},
  {A, "Merci beaucoup! C'est           vraiment gentil de ta part."},
  {A, "Promis, des que je peux         je te rendrai la pareil!"},

  //>Penses a me rembourser
  {A, "Oui! Tu as ma parole!"},
  {A, "Les bon comptes font            les bons amis apres tout."},
  {A, "Et c'est deja tres gentil       a toi de m'avancer!"},
  {A, "Promis, dans quelques jours     je pourrai te rembourser."},

  //>Franchement, t'abuses
  {A, "Haha, desole, je sais que       c'est pas la premiere fois."},
  {A, "Mais apres tout c'est toi qui   a propose la glace!"},
  {A, "Aller c'est promis,             c'est la derniere."},
  //>La derniere?
  {A, "La derniere! Parole d'Ange!"},
  {A, "Il faut juste que je fasse      moins de shopping haha."},


  {A, "Allons-y!"},
  {N, "Vous avancez tranquillement     vers la ville cotiere."},
  {N, "Une musique festive vient       a vos oreilles."},
  {N, "Vous entendez le sifflement     de fusees et de confettis."},//

  {N, "C'est bien l'epoque du          festival annuel,"},
  {N, "et la foule s'en donne          a coeur joie."},
  {N, "Tu t'assures qu'Ange est        toujours derriere toi."},
  {A, "Ne t'en fais pas...             je te suis!"},
  {N, "Tu progresse dans la ville, en  direction du stand de glace."},
  {N, "Autours de vous volent          confettis et feu d'artifice."},
  {N, "Le gros de la foule danse sur   la place principale."},
  {N, "Tu comprends mieux pourquoi     la plage etait si vide."},
  {N, "Tu arrives enfin a la boutique  de glace."},
  {N, "Apres inspection du menu,       tu te tourne vers Ange."},
  //>Tout me fait envie!
  //>Prends ce que tu veux
  //>C'est vraiment cher!
  //>Tu veux pas une crepe plutot?

  {N, "Mais en te retournant,          tu ne vois personne."},
  {N, "Ange n'est plus derriere toi."},
  {N, "Tu sors rapidement de la        boutique."},
  {N, "Personne."},
  {N, "Misere, Ange t'as surement      perdu en chemin."},
  {N, "Plein d'inquietude,             tu entame tes recherches."},

  //>Demander a un passant
  {N, "Tu interpele un passant,        esperant avoir des info."},
  {N, "\"Quelqu'un avec un pull gris?   Ici c'pas commun haha\""},
  {N, "\"Maintenant tout le monde porte la collection estival!\"" },
  {N, "\"La classe pas vrai? Attendez   de voir ma nouvelles dance!\"" },
  {N, "\"Il survivra votre pull gris,   venez faire la fete!\""},
  {N, "Ce type etait sympathique,      mais ne t'a pas avance."},
  {N, "Les gens ici sont trop occupes  a faire la fete pour t'aider"},

  //>Chercher dans la foule
  {N, "Si Ange t'a perdu, c'est surement a cause de la foule."},
  {N, "Bravement, tu te glisse entre   les danseurs a sa recherche."},
  {N, "Tu sens bien que tu gene, mais  c'est au nom de l'amitie."},
  {N, "Sur la place, tu grimpe sur la  fontaine centrale."},
  {N, "Te surelever t'aidera plus      dans tes recherches."},
  {N, "Tu surplombe la foule du        regard, mais sans succes."},
  {N, "Pourtant ses vetements gris     est facilement reperables,"},
  {N, "Surtout dans la maree de        costumes colores."},
  {N, "Tu scrutes une derniere fois    la foule, au cas où."},
  {N, "Tu te resous finalement a       changer de strategie."},

  //>Retourner sur la plage
  {N, "Tu rebrousse chemin jusqu'a     la plage."},
  {N, "Peut etre qu'Ange est quelque   part sur la route."},

  {N, "Tu fais attention a regarder    partout autours de toi."},
  {N, "Inspectant ruelles et detours   au cas où Ange y serait."},
  {N, "Tu sors de la ville,            et toujours aucune trace."},
  {N, "Mais revenu sur la plage, tu    retrouve un visage familier."},
  {A, "Ah, tu es la!"},
  //>Non c'est toi qui est la!
  {A, "Oh non, tu me cherchais         c'est ça?"},
  {A, "Excuse-moi...                   je voulais pas t'inquieter."},
  {A, "Je me suis trouve mal           au milieu de la foule."},

  //>Qu'est-ce qui s'est passe?
  {A, "Et bien...au milieu de la      foule, j'etais pas tres bien."},

  //>Tu vas bien?
  {A, "Oui, ça vas, ne t'inquiete     pas pour moi!"},
  {A, "En tout cas je vais mieux      maintenant!"},
  {A, "C'est juste que... la foule    c'est pas trop mon truc."},

  {A, "Je savais pour le festival,    mais je le pensais plus..."},
  {A, "petit. Je pensais pas voir     autant de monde ici."},
  {A, "Le bruit m'a distrait, et      quelqu'un m'a bouscule."},
  {A, "ca a suffit pour que je te     perde de vue."},
  {A, "Mais heureusement              j'ai l'habitude!"},
  //>L'habitude?
  {A, "Oui, avant j'avais la manie    de me perdre au supermarche."},
  {A, "Ca arrivais a chaque fois que  quelque chose me distrayait"},
  {A, "Des que je regardais ailleurs, ma mere avait disparu."},
  //>C'est pour ça que tu es revenu?
  {A, "C'est ça, c'est ma mere qui    me l'as appris!"},
  {A, "J'ai compris quoi faire        en cas de probleme:"},
  {A, "Revenir a la caisse centrale   et attendre maman!"},
  {A, "Enfin, c'est un image hein!    hehe"},

  //>Tu as prit de bonnes habitudes
  {A, "Haha, si on peut appeler ça    comme ça!"},
  {A, "C'est vrai que grace a ça      on a pu se retrouver."},
  {A, "Encore pardon, la prochaine    fois je ferai attention!"},

  //>Au final, on a pu se retrouver
  {A, "Oui, c'est l'essentiel!"},
  {A, "Encore pardon de t'avoir fais  soucis!"},

  //>Tu parles peu de ta mere
  {A, "Oh... euh..."},
  {A, "T-tu trouves? Je vois pas      pourquoi en parler plus..."},
  {A, "Je crois que je parles         beaucoup de ma vie deja."},
  {A, "Ca te derange pas vrai? Je     ferais plus attention!"},
  {A, "Desole, c'etait stupide de     raconter ce genre de cho-"},
  //>Ce n'est rien
  {A, "Ah... d'accord..."},
  {A, "Je crois que mes emotions      ont encore prit le dessus..."},
  {A, "Parlons d'autre chose,         si veux bien."},


  {A, "Bah d'ailleurs, au final       on a toujours pas nos glaces!"},
  {A, "C'est bete, on aura fait       cette expedition pour rien"},
  {A, "Mais c'est pas tres grave,     c'est pour une autre fois!"},

  {N, "Son regard se porta alors      vers la mer."},
  {N, "Le jour est a present bien     avance,"},
  {N, "et le soleil descend           progressivement dans le ciel."},
  {N, "Ses rayons se refletent        etrangement sur l'eau bleue."},
  {N, "C'est vraiment un beau         spectacle."},
  {N, "Soudain, Ange remarque         quelque chose a l'horizon."},
  {A, "Oh regarde! Il y a un          bâteau la bas!"},
  {A, "Je me demande a qui            il appartient."},
  {A, "Ce doit etre chouette          d'avoir sa maison sur l'eau."},
  {A, "Je pourrais voyager sans       sortir de chez moi haha"},
  {A, "Un jour peut etre..."},
  {A, "Tu aimes voyager toi?"},
  //>Oui, partout dans le monde!
  {A, "Woah, tu as vraiment le        gout de l'aventure!"},
  {A, "Il doit y avoir tant a         decouvrir dans le monde."},
  {A, "J'en vois une partie dans des  documentaires,"},
  {A, "Mais je suis sur qu'il y a     beaucoup plus a decouvrir."},
  {A, "je te l'ai surement deja dit,  mais je t'envie beaucoup."},
  {A, "C'est comme si tu vivais plus que moi."},

  //>Oui mais proche de chez moi
  {A, "C'est pas bete, il y a de     beaux endroits vers chez toi."},
  {A, "Je me demande ce qu'il y a    dans ma region."},
  {A, "Je n'en n'ai aucune idee,     mais il doit y en avoir."},
  {A, "Je penses que je ferai ça     si je me decide a voyager."},
  {A, "Au moins je peux rentrer      chez moi n'importe quand."},

  //>Non pas du tout
  {A, "Oh, donc tu es un peu         comme moi."},
  {A, "C'est vrai qu'on est bien     chez soi, dans son cocon."},
  {A, "Si je le pouvais, je ne       sortirais jamais."},
  {A, "Mais je devrais pas faire     ça toute ma vie, pas vrai?"},
  {A, "Il faudra bien que je me      reprenne en main."},


  //main and last branch
  {A, "J'espere un jour avoir un     peu plus de courage."},
  {A, "Tu le sais, meme une          rencontre ici me fait stresser"},
  {A, "Des fois, je me demande       ce que je vais devenir."},
  {A, "Des fois, je.'é"},
  {A, "..."},
  {A, "Excuse moi, c'est encore      mes emotions."},
  {A, "Tu sais, je ne sais pas       pourquoi tu reste avec moi."},
  {A, "Je ne suis pas une personne   tres interessante."},
  {A, "Juste une petite chose qui    essaye de traverser la vie."},
  {A, "Mais tu es toujours la pour   ecouter, me conseiller."},
  {A, "On a certes des differences,  mais toi au moins..."},
  {A, "..."},
  {A, "C'est pour ça que j'aime      autant ta compagnie."},
  {A, "Tu m'acceptes, meme quand     j'ai du mal a le faire."},
  {A, "Et ça me fais d- b1en... "},
  {A, "Hey, ça t- dirait d'alle-    ramasser des coqvi'&lag-s?"},
  {A, "P' urquoi tu f-- ct - tete?"},
  {A, "....dd;...."},
  {N, " "},
  {N, "Connexion perdue..."},
  {N, "Ange s'est deconnecte"},

  {N, "F I N"},
  {N, "(merci d'avoir joue!)"},

};

const Choice ListeChoix[]= {
  {"Oui ca va! Et toi ?",1},
  {"Desole du retard",1},
  {"C'etait dur de te trouver",1},
  
  {"Oui, c'est tres joli!",1},
  {"Bof, c'est la mer quoi.",1},
  
  {"J'en vois le bout!",1},
  {"J'ai du mal a avancer...",1},
  	{"Oui",1},
  	{"Je sais pas si ça m'aiderait",1},
  {"Je suis passe a autre chose",1},
  
  {"Trop bien!",1},
  {"Qu'est-ce qu'ils t'ont dit?",1},
  
  {"C'est juste des questions",1},
  {"Ils vont pas te manger haha",1},
  {"J'ai oublie moi aussi",1},
  
  {"Oui, ca fait serieux",1},
  {"Non, soit decontract'",1},
  {"Porte ce qui te plait",1},
  
  {"Bien sur!",1},
  {"Je ne saurais pas t'aider",1},
	  {"Bon, si tu insiste",1},
  
  {"Vanille",1},
  {"Chocolat",1},
  {"Fruit",1},
  {"Peu importe",1},
  	{"J'aime tous les parfums",1},
  	{"Non pas trop",1},
  
          {"Oui, je ne supporte pas",1},
          {"Ca me derange pas vraiment",1},
          {"J'adore la foule!",1},
  //--Branche glace
  {"Je comptais te l'offrir",1},
  {"Penses a me rembourser",1},
  {"Franchement, t'abuses",1},
  
  {"Tout me fait envie!",1},
  {"Prends ce que tu veux",1},
  {"C'est vraiment cher!",1},
  {"Tu veux pas une crepe plutot?",1},
  
  {"Demander a un passant",1},
  {"Chercher dans la foule",1},
  {"Retourner à la plage",1},
  
  {"Non c'est toi qui est la!",1},
  {"Qu'est-ce qui s'est passe?",1},
  {"Tu vas bien?",1},
  
  {"L'habitude?",1},
  {"Et donc tu m'a attendu ici",1},
  
  {"Tu as prit de bonnes habitudes",1},
  {"Au final, on a pu se retrouver",1},
  {"Tu parles peu de ta mere",1},
  	{"Ce n'est rien",1},
  
  
  //--Main and last branch (?)
  {"Oui, partout dans le monde!",1},
  {"Oui mais proche de chez moi",1},
  {"Non pas du tout",1}
  
};

const char ChoiceCollection[][4] = {
  {0,1}
};

const char expr[]={ //liste des expressions
  211	,212	,213	,214	,215	, 216	,217	, 218	, 219
//0'v'   1 :)  	2 :|   	3 :(   	4 :D  	5 D:    6 A_A	7 /	8 \
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
  oam_id = oam_spr(111, 67, expr[sprEl], 2, oam_id);
  oam_id = oam_spr(129, 67, expr[sprEr], 2, oam_id);
  
  oam_id = oam_spr(121, 73, expr[sprM], 2, oam_id);
  
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
  draw_ange_face();
  
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
  else if (SCRPT[index].t==SWPEL){
    sprEl=atoi(SCRPT[index].c);
    index++;
  }
  else if (SCRPT[index].t==SWPER){
    sprEr=atoi(SCRPT[index].c);
    index++;
  }
  else if (SCRPT[index].t==SWPM){
    sprM=atoi(SCRPT[index].c);
    index++;
  }
  
  if (pad&PAD_A){
    if (!a_pressed){
      a_pressed=true;
      //if (cursor<63){cursor=63;}//Affiche tout le texte; pas top parce que taille varibale pour le texte
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
  else{
   a_pressed=false; 
  }
  
  if (cursor<59) cursor++;
  
  //delay(2);//Si tu veux ralentir la vitesse du texte
  
}

void draw_game(){
  //oam_spr(x,y,sprite,color,id)
  //oam_id = oam_spr(40, 40, 8, 1, oam_id);
  vrambuf_put(NTADR_A(13,10),"~ANGE~",6);
  vrambuf_put(NTADR_A(3,11),"_________________________",25);
  vrambuf_put(NTADR_A(5,13),"a date on the seaside",21);
  
  vrambuf_put(NTADR_A(1,26),"PRESS A",7);
  
  vrambuf_put(NTADR_A(19,26),"2020 NIGHTEN",12);
  
}

void updt_game(){
  if (pad&PAD_A){
    if (!a_pressed){
      game_st=DIAL;
      clrscr();
      draw_ange();
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
      draw_ange();
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
  draw_dial();
  vrambuf_put(NTADR_A(12,10),"GAMEOVER",8);
  vrambuf_put(NTADR_A(6,20),"merci d'avoir joue !",20);

  
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
      if (debug_mode){vrambuf_put(NTADR_A(2,2),"Game",4);}
      draw_game();
      updt_game();
      
    }
    else if (game_st==DIAL){
      if (debug_mode){vrambuf_put(NTADR_A(2,2),"Dialogue",8);}
      draw_dial();
      updt_dial();
      
    }
    else if (game_st==CHOICE){
      if (debug_mode){vrambuf_put(NTADR_A(2,2),"Choice",6);}
      draw_choice();
      updt_choice();
      
    }
    else if (game_st==END){
      if (debug_mode){vrambuf_put(NTADR_A(2,2),"END",3);}
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