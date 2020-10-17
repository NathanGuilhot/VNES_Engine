//-----Visual Novel content !! °˖✧◝(⁰▿⁰)◜✧˖°
//Here will come the english translation !

const Passage SCRPT[] = {
  {SWPM,"4"},
  {N, "En cette fin d'apres-midi,      tu marches sur la plage."},
  {N, "Il y a peu de monde ici.        C'est calme."},
  {N, "Rythme par le son de la mer,    tu avance sur le sable."},
  {N, "Tu trouve enfin la personne     que tu cherchais."},
  //Show ANGE
  {H, "show"},
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
  {A, "Haha, mes indications etaient   si vagues que ca?"},
  {A, "Desole, je ne connais pas       beaucoup la region."},
  {A, "Et puis au moins sur cette      plage on est tranquilles!"},

  {N, "Son attention se porte alors    sur la mer."},
  {N, "Elle est calme, reguliere,      et s'etant a perte de vu."},
  {A, "C'est beau,                     tu ne trouves pas?"},
  //{C, "1"},
  
  //> "Oui, c'est tres joli!"},
  {A, "Je vois que tu apprecies la     vue autant que moi!"},
  {A, "Si je le pouvais je resterais   ici toute ma vie."},
  {A, "Bon ca serait pas tres          confortable a la longue,"},

  //> "Bof, c'est la mer quoi."},
  {A, "Hehe, tu n'as toujours pas une  ame d'artiste."},
  {A, "Et c'est pas grave, tu as le    droit de trouver ca banal."},
  {A, "Apres tout, c'est un peu        absurde de s'y attarder ici."},

  {A, "Mais pour un rendez-vous ca     reste un tres bon endroit."}, ///
  {A, "Maintenant ma connexion n'est   plus un probleme."}, 
  {A, "Et c'est bien plus chouette     qu'en visio!"},

  //
  {A, "Hum, au fait, je voulais        te poser une question..."},
  {A, "Tu te souviens de ton projet?   Celui dont tu m'as parle?"},
  {A, "Il avait l'air interessant,     comment il avance?"},
  //{C, "2"},
  
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
  {C, "3"},
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
  {C, "4"},
  //>Trop bien!
  {A, "Haha, merci beaucoup!           Mais tout n'est pas gagne."},
  {A, "Ils m'ont invite a un           entretiens mais..."},

  //>Qu'est-ce qu'ils t'ont dit?
  {A, "Et bien..."},
  {A, "Je crois que j'ai un            entretiens d'embauche..."},

  {A, "Mais ça me fait un peu          peur."},
  {A, "Tu vois, ca fait longtemps      que je n'ai pas travaille."},
  {A, "J'ai meme oublie comment se     passent ces entretiens."},
  {A, "Tu sais en quoi ça consiste     toi?"},
  {C, "5"},
  
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

  {C, "6"},
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
  {C, "7"},
  //>Bien sur!
  {A, "Merci! Je savais que je         pouvais compter sur toi!"},
  {A, "Juste un avis exterieur         m'aidera beaucoup a choisir."},

  //>Je ne saurais pas t'aider
  {A, "Mais non, tu exagere!"},
  {A, "Je demande juste ton            avis honnete, c'est tout!"},
  {A, "Tu es quelqu'un en qui j'ai     confiance pour ça."},
  {A, "Et si je veux m'embarrasser,    c'est pas devant un styliste"},
  	  {C, "8"},
          //>Bon, si tu insiste
          {A, "Merci beaucoup! Je te           revaudrai ça!"},

  {A, "Bon, j'arrete de t'embeter      avec mes tracas."},
  {A, "Tu veux faire quelque           chose en particulier?"},
  {C, "20"},
  //>Et si on achetait une glace?
  {A, "Oh oui! Tres bonne idee!"},
  {A, "On dit qu'ils vendent tous      les parfums imaginables ici."},
  {A, "C'est quoi ton parfum           prefere?"},
  {C, "9"},

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
    {C, "21"},
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
  	{C, "10"},
        //>J'aime tous les parfums
        {A, "Ah! Te connaissant ça ne        m'etonne pas en effet!"},
        {A, "On verras bien ce qu'il y a     et ce qui te fait envie."},
  	//jump ici

        //>Non pas trop
        {A, "Oh d'accord..."},
        {A, "Je comprends, tu proposais      ça pour me faire plaisir?"},
        {A, "C'est gentil, mais tu as pas    a te forcer tu sais."},
        {A, "Oublions les glaces, mais       merci d'avoir propose!"},
        {A, "Et puis, on est tres bien       sur la plage, pas vrai?"},
        {A, "Je prefere rester ici,          c'est plus calme."},
        {A, "D'ailleurs, tu as vu qu'ils     font une fete en ville?"},
        {N, "En effet, en arrivant tu as     entendu de la musique."},
        {A, "De ce que j'ai compris, c'est   un grand festival annuel."},
        {A, "Si je peux eviter de me meler   a la foule, c'est mieux."},
        {N, "D'ici, vous entendez des        chants et des bruits festifs"},
        {N, "Il doit y avoir beaucoup de     monde la bas."},
        {N, "Et c'est peut etre pour ça      que la plage est deserte."},
        {A, "Tu as du mal avec la foule      toi?"},
 	{C, "11"},
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
  	//{J,"1"}, //(jump branch)

  //---

  {A, "Euh, par contre                 je dois t'avouer..."},
  {A, "Je n'ai pas vraiment d'argent   sur moi."},
  {A, "Vraiment, excuse moi!"},
  {A, "Tu vois, j'ai du acheter de     l'equipement pour ma maison."},
  {A, "Et du coup... c'est un peu      ric rac en ce moment."},
  {A, "Ca te derange de m'avancer?"},
  
  {C, "12"},
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
  {A, "(si j'arrete de craquer sur     des bibelots...)"},
  //>La derniere?
  {A, "La derniere! Parole d'Ange!"},
  {A, "Il faut juste que je fasse      moins de shopping haha."},


  {A, "Très bien, allons-y!"},
  {H, "hide"},
  {N, "Vous avancez tranquillement     vers la ville cotiere."},
  {N, "Une musique festive vient       a vos oreilles."},
  {N, "Vous entendez le sifflement     de fusees et de confettis."},//

  {N, "C'est bien l'epoque du          festival annuel,"},
  {N, "et la foule s'en donne          a coeur joie."},
  {N, "Tu t'assures qu'Ange est        toujours derriere toi."},
  {H, "show"},
  {A, "Ne t'en fais pas...             je te suis!"},
  {H, "show"},
  {N, "Tu progresses dans la ville en  direction du stand de glace."},
  {N, "Autours de vous volent          confettis et feu d'artifice."},
  {N, "Le gros de la foule danse sur   la place principale."},
  {N, "Tu comprends mieux pourquoi     la plage etait si vide."},
  {N, "Tu arrives enfin a la boutique  de glace."},
  {N, "Apres inspection du menu,       tu te tourne vers Ange."},
  
  {C, "13"},
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

  {C, "14"},
  //>Demander a un passant
  {N, "Tu interpele un passant,        esperant avoir des info."},
  {N, "\"Quelqu'un avec un pull gris?   Ici c'pas commun haha\""},
  {N, "\"Maintenant tout le monde porte la collection estival!\"" },
  {N, "\"La classe pas vrai? Attendez   de voir ma nouvelles dance!\"" },
  {N, "\"Il survivra votre pull gris,   venez faire la fete!\""},
  {N, "Ce type etait sympathique,      mais ne t'a pas avance."},
  {N, "Les gens ici sont trop occupes  a faire la fete pour t'aider"},
  {C, "14"},

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
  {C, "14"},

  //>Retourner sur la plage
  {N, "Tu rebrousse chemin jusqu'a     la plage."},
  {N, "Peut etre qu'Ange est quelque   part sur la route."},

  {N, "Tu fais attention a regarder    partout autours de toi."},
  {N, "Inspectant ruelles et detours   au cas où Ange y serait."},
  {N, "Tu sors de la ville,            et toujours aucune trace."},
  {N, "Mais revenu sur la plage, tu    retrouve un visage familier."},
  {A, "Ah, tu es la!"},
  
  {C, "15"},
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
  {C, "16"},
  //>L'habitude?
  {A, "Oui, avant j'avais la manie    de me perdre au supermarche."},
  {A, "Ca arrivais a chaque fois que  quelque chose me distrayait"},
  {A, "Des que je regardais ailleurs, ma mere avait disparu."},
  //>C'est pour ça que tu es revenu?
  {A, "C'est ça, c'est ma mere qui    me l'as appris!"},
  {A, "J'ai compris quoi faire        en cas de probleme:"},
  {A, "Revenir a la caisse centrale   et attendre maman!"},
  {A, "Enfin, c'est un image hein!    hehe"},
  {C, "17"},
  
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
  {C, "18"},
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
  {C, "19"},
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
  {"C'etait dur de te trouver",14},
  
  {"Oui, c'est tres joli!",1},
  {"Bof, c'est la mer quoi.",1},
  
  {"J'en vois le bout!",1},
  {"J'ai du mal a avancer...",1},
  	{"Oui",1},
  	{"Je sais pas si ca m'aiderait",1},
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
  {"Retourner a la plage",1},
  
  {"Non c'est toi qui est la!",1},
  {"Qu'est-ce qui s'est passe?",1},
  {"Tu vas bien?",1},
  
  {"L'habitude?",1},
  {"Et donc tu m'a attendu ici",1},
  
  {"C'est un bon reflexe",1},
  {"Au final on a pu se retrouver",1},
  {"Tu parles peu de ta mere",1},
  	{"Ce n'est rien",1},
  
  
  //--Main and last branch (?)
  {"Oui, partout dans le monde!",1},
  {"Oui mais proche de chez moi",1},
  {"Non pas du tout",1},
  
  {"Et si on achetait une glace?",1},
  
  {"Je suis d'accord",1},
  {"Je penses que c'est des films",1},

  
};

const char ChoiceCollection[][5] = {
  //{nb_choix,nchoix,...};
  {3,0,1,2},
  {2,3,4},
  {3,5,6,9},
    {2,7,8},
  {2,10,11},
  
  {3,12,13,14},
  {3,15,16,17},
  
  {2,18,19},
  	{1,20},
  
  {4,21,22,23,24}, //vanille, chocolat...
  	{2,25,26},
 		{3,27,28,29}, //branche glace-less
  {3,30,31,32},
  
  {4,33,34,35,36},
  
  {3,37,38,39},
  
  {3,40,41,42},
  
  {2,44,43},
  
  {3,46,45,47},
    {1,48},
  {3,49,50,51},//où tu veux voyager
  
  {1,52}, //et si on achetait une glace?
  {2,53,54}, //je suis d'accord/je penses que c'est des films
};
