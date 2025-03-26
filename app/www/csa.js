// csa (c) Baltasar 2017/18 MIT License <baltasarq@gmail.com>
/*
 *      Cacahuetes, sal y aceite (v4)
 *          1998, 1999, 2000, 2012: Csa: Parser KAC/C++
 *          2009, 2010, 2016: Csa v2 a Csa v3: informATE!/Zcode
 *          2017, 2018: Aventura de texto onírica construida con fi.js.
 *      (c) 1998-2017 baltasarq@gmail.com MIT License
 *
 *      Este relato tiene una larga historia.
 *      Fue creado inicialmente para una *NanoComp* en 2000.
 *      El soporte era un parser propio, que posteriormente cambié por
 *      InformATE!, pero en realidad se trataba más de un relato interactivo
 *      que de una verdadera aventura conversacional (objetos, puzzles, etc.)
 *      Así que en 2017 me lié la manta a la cabeza y la porté a mi propio
 *      sistema HTML5: **fi.js**. El resultado es así más versátil.
 */

ctrl.ponTitulo( "Cacahuetes, sal y aceite" );
ctrl.ponIntro( "Despiertas atontado... \
                en un cubo de acero totalmente regular." );
ctrl.ponImg( "res/cube.jpg" );
ctrl.ponAutor( "Baltasarq" );
ctrl.ponVersion( "4.1 20181221" );

// *** Locs --
// ---------------------------------------------------------------------- Celda
var locCube = ctrl.places.creaLoc(
    "Celda", ["camarote", "sala", "prision", "cubo", "celda"],
    "Las ${paredes, ex paredes} de acero de esta \
     habitación perfectamente regular parecen \
     estar hechas de una sola pieza, pulidas hasta el punto de brillar con \
     una luz que... no sabes de donde viene. El silencio es sobrecogedor, \
     y la sensación de fría, y tensa espera abrumadora, como la extraña \
     ${niebla, ex niebla} que te rodea." );
locCube.pic = "res/cube.jpg";

locCube.time = 0;
locCube.advanceTime = function() {
    ctrl.clearAnswers();

    this.time++;
    if ( this.time >= 3 &&
        this.time < 4 ) {
        ctrl.print( "Te sientes realmente mal. Tus manos tiemblan y... \
                     multitud de arrugas las surcan. Te sientes mareado, \
                     cansado... casi no puedes sostenerte..." );
    } else
    if ( this.time >= 4 ) {
        this.time = 0;
        ctrl.print( "No puedes creerlo. Como en una pesadilla de Poe, tu \
            cuerpo se descompone ante tus propios ojos... \
            Tienes ganas de llorar, de gritar, pero no puedes, \
            porque no sientes dolor, y, entonces, de repente, \
            de  repente...<br>\
            caes... caes... hacia el abismo infinito...<br>\
            respiras agitadamente, tu corazón se desboca, \
            abres los ojos como si despertaras \
            de una pesadilla y entonces te das cuenta de \
            que todo sigue igual... qué está pasando... \
            qué está pasando..." );
    } else {
        ctrl.print( "Mueves las agujas hacia adelante. \
                     Notas un cierto temblor, y curiosamente, te \
                     sientes como más viejo..." );
    }
};

var objNiebla = ctrl.creaObj(
    "niebla", ["niebla", "bruma", "neblina"],
    "Esta neblina lo envuelve todo... es agobiante, abrumadora...",
    locCube,
    Ent.Scenery
);
objNiebla.setReachable( false );

var objWindow = ctrl.creaObj(
    "ventana", ["ventana", "vista", "enrejado", "ventanuco", "cristal"],
    "Un pequeño ventanuco, cortado sin remaches ni marcas \
    en la misma pared. Al otro lado, tan solo oscuridad. \
    Su cristal enrejado de 1cm. de espesor te separa de... lo que sea \
    lo de fuera... porque no ves nada... curiosamente, tu \
    respiración no deja vaho en el cristal... \
    <br/>Quieres intentar ${abrirlo, abre ventana}, \
    o incluso ${romperlo, rompe ventana}.",
    locCube,
    Ent.Scenery
);

objWindow.preAttack = function() {
    return "Lo intentas con todas tus fuerzas... pero es \
            imposible... estás atrapado...";
};

objWindow.preOpen = function() {
    return "¿Pero, cómo? No hay pestillos, ni cerrojos...";
};

var objWalls = ctrl.creaObj(
    "paredes", ["pared", "acero", "muro", "muros"],
    "Las paredes son de acero pulido, sin remaches, \
     ni molduras o marcas de ningún tipo.",
    locCube,
    Ent.Scenery
);

objWalls.preExamine = function() {
    var toret = objWalls.desc;

    if ( this.timesExamined == 3 ) {
        locCube.desc += "<p>Se te ocurre que quizás \
                        puedas ${romper las paredes, golpea paredes}. \
                        Precisamente debido a su uniformidad, \
                        varios elementos llaman tu atención \
                        en ${ellas, ex paredes}. En la pared sur \
                        puedes ver una \
                        ${ventana, ex ventana} y un ${reloj, ex reloj} \
                        mientras en la pared oeste hay algún tipo de \
                        ${inscripción, ex aviso}.</p>";
        actions.execute( "look" );
    }

    return toret;
};

objWalls.preAttack = function() {
    return "Golpeas con todas tus fuerzas, y... ¡te haces mucho \
            daño! ...es inútil.";
};

ctrl.creaObj(
    "inscripcion",
    ["aviso", "escritura"],
    "Reza: 'Piensa en cuatro dimensiones. Aún tienes tiempo...'",
    locCube,
    Ent.Scenery
);

var objClock = ctrl.creaObj(
    "reloj",
    ["manecillas", "agujas"],
    "Es un extraño reloj, pues sus agujas no se mueven por si solas. \
     No crees que tenga mecanismo. Te preguntas por el sentido que pueda \
     tener un reloj como de juguete ahí puesto.",
    locCube,
    Ent.Scenery
);
objClock.preExamine = function() {
    var toret = this.desc;

    if ( this.timesExamined == 1 ) {
        locCube.desc += "<p>Las manecillas del reloj \
                         pueden ser manipuladas libremente. Podrías \
                         ${girarlas en el sentido horario, tira de reloj}, \
                         o ${girarlas en el sentido contrario, empuja reloj}. \
                         </p>";
        actions.execute( "look" );
    }

    return toret;
};

objClock.prePull = function() {
    locCube.advanceTime();
};

objClock.prePush = function() {
    var toret = "Tras girar las agujas a la inversa, \
            todo pareció ennublecerse, desvanecerse en finas hebras \
            de humo. Y lo que comprobaste al recobrar el sentido fue \
            que era mejor no moverse...";
    ctrl.goto( locCliff );
    return toret;
};

// --------------------------------------------------------------------- Abismo
var locCliff = ctrl.places.creaLoc(
    "Abismo", ["caida", "sima", "agujero"],
    "A tus pies, se abre el ${abismo, ex pozo} insondable. \
    Un ${saliente de roca, ex saliente} evita que caigas. Te mantienes en \
    tensión, de espaldas a la pared sur \
    del mismo. Al otro lado, el lado norte, un saliente de roca \
    gemelo al que pisas ahora, da paso a la caverna que se abre \
    al exterior. En medio de los salientes, la nada. La ${niebla, ex niebla} \
    aparece cargando toda la estancia, a base de espesos jirones..." );
locCliff.pic = "res/cliff.jpg";

ctrl.creaObj(
    "puente", ["pasarela"],
    "Un puente que antes no veías por un efecto óptico ${cruza, norte} \
    entre ambos salientes.",
    locCliff,
    Ent.Scenery
);

var objRock = ctrl.creaObj(
    "saliente", ["roca"],
    "Casi no te atreves a mover los pies, en la superficie resbaladiza por \
     la arena.",
    locCliff,
    Ent.Scenery
);
objRock.preExamine = function() {
    if ( objRock.timesExamined == 1 ) {
        objSand.moveTo( locCliff );
        locCliff.desc += "<p>El suelo del saliente está lleno \
                        de montoncitos de ${arena, ex arena}. \
                        Hacia una lado, se puede \
                        ver un ${cartel, ex cartel}.</p>";
        actions.execute( "look" );
    }

    return objRock.desc;
};

ctrl.creaObj(
    "sima", ["pozo"],
    "El abismo es negro e insondable. Muy profundo. Da miedo.",
    locCliff,
    Ent.Scenery
);

var objSign = ctrl.creaObj(
    "cartel", ["aviso"],
    "Medio podrido por la humedad, indica: 'Ten Fe: pero que no sea ciega.'",
    locCliff,
    Ent.Scenery
);

var objSand = ctrl.creaObj(
    "arena",
    ["montoncitos", "montoncito", "monton", "montones", "grano", "granos"],
    "Montoncitos de arena gorda",
    ctrl.places.limbo,
    Ent.Scenery
);

objSand.prePush = function() {
    var toret = "Al tirar la arena hacia el abismo, \
                 parte quedó suspendida sobre una \
                 superficie que no habías percibido antes debido a un \
                 elaborado efecto óptico que no aciertas a descubrir...";

    locCliff.desc += "<p>Un ${puente, ex puente} ha quedado parcialmente \
                      descubierto por la arena posada sobre su superficie. \
                      </p>";
    actions.execute( "look" );

    return toret;
};

objSand.preExamine = function() {
    var toret = objSand.desc;
    var player = ctrl.personas.getPlayer();

    if ( player.has( this ) ) {
        toret += ", tanto en el suelo del saliente como en tus manos. \
                  Observas un efecto muy extraño: al estar asomado al abismo, \
                  algunos granos de arena han caído hacia adelante... pero su \
                  caída se ha detenido abruptamente a tus pies... ¡La arena \
                  parece flotar sobre la oscuridad de la nada! Lo extraño del \
                  efecto te invita a ${tirar arena, empuja arena} hacia \
                  adelante.";
    } else {
        toret += ", que podrías ${coger, coge arena} con tus manos.";
    }

    return toret;
};

objSand.preTake = function() {
    this.moveTo( ctrl.personas.getPlayer() );
    return "Tomas un montoncito de arena en tus manos, mientras los \
            granos se escurren por entre tus dedos.";
};

ctrl.creaObj(
    "puente", ["pasarela"],
    "Un puente que antes no veías por un efecto óptico ${cruza, norte} \
    entre ambos salientes.",
    locCliff,
    Ent.Scenery
);

// --------------------------------------------------------------------- Salida
var locFountain = ctrl.places.creaLoc(
    "Salida", ["sala", "estancia"],
    "Extraño lugar... No hay \
        paredes, ni marcas que delimiten el recinto, pero sientes que \
        conoces perfectamente donde están los límites. Hay algunas \
        columnas distribuidas por la estancia, rodeadas idílicamente por \
        ${enredaderas, ex enredaderas}, por supuesto, entre una suerte de \
        ${neblina, ex niebla}. Al fondo de la estancia, puedes \
        ver una ${puerta, ex puerta}. Y en el medio, \
        una ${fuente, ex fuente}." );
locFountain.pic = "res/fountain.jpg";
locFountain.setExitBi( "sur", locCliff );

locFountain.preGo = function() {
    var toret = "";

    if ( !objFountain.drunk ) {
        toret = "Avanzas por el medio de la sala, decidido hacia la puerta. \
                 Al acercarte más al marco, éste va adquiriendo una tonalidad \
                 rojiza, hasta que parece ponerse al rojo vivo. \
                 No es una buena idea cruzar la puerta ahora.";
        objDoor.triedToCross = true;
    } else {
        toret = goAction.exe( parser.sentence );
    }

    return toret;
};

ctrl.creaObj(
    "enredadera", ["enredaderas", "hiedra", "hiedras", "columnas", "columna"],
    "Las enredaderas trepan por entre las columnas, \
    formando un tupido entramado.",
    locFountain,
    Ent.Scenery
);

var objDoor = ctrl.creaObj(
    "puerta", ["marco"],
    "Es una rara puerta. En realidad, sólo es un marco, con extrañas \
    inscripciones en forma de figuras geométricas. A través del marco \
    parece poder verse una ${extraña imagen, ex imagen}, que ondula... \
    Pero sientes que podrías ${atravesarla, norte}.",
    locFountain,
    Ent.Scenery
);
objDoor.triedToCross = false;

ctrl.creaObj(
    "imagen", ["ondulacion"],
    "A través de la puerta, ves... ves... ¡Eres tú! \
    Te ves en posición horizontal, en una extraña estancia \
    llena de elementos irreconocibles. Al fondo parece haber \
    un enjambre de moscas, perturbadoramente estático... todo es muy \
    extraño. De repente, la niebla lo envuelve todo, y la \
    imagen se desvanece...",
    locFountain,
    Ent.Scenery
);

var objFountain = ctrl.creaObj(
    "fuente", ["barroco", "barroca", "concha"],
    "Hay una pequeña fuente en el centro exacto de la sala. \
     Un chorro brillante y sugerente de agua cristalina brota de ella. \
     Sientes el extraño impulso de ${cogerla, ex agua} en tu mano...",
    locFountain,
    Ent.Scenery
);
objFountain.drunk = false;

objFountain.preHave = function() {
    this.drunk = true;
    return "El agua no te refresca... pero te sientes como más puro.";
};

objFountain.preExamine = function() {
    var toret = objFountain.desc;

    if ( objDoor.triedToCross ) {
        toret += " Y después del calor desprendido por el marco, sientes la \
                  necesidad de ${beberla, bebe fuente}.";
    }

    return toret;
};

ctrl.creaObj(
    "agua", ["chorro"],
    "Intentas coger el chorro de agua... el agua se escurre por \
     entre tus dedos... pero... que extraño... no moja...",
    locFountain,
    Ent.Scenery
);

// --------------------------------------------------------------------- Final
var locLiving = ctrl.places.creaLoc(
    "Salón", ["sala", "estancia"],
    "Al cruzar esta última puerta, sientes que el suelo \
     se desvanece, se abre bajo tus pies...<br/>\
     Comienzas a caer, a caer, y notas una sensación de vértigo insoportable \
     en el estómago...<br/>\
     No puedes evitar gritar, gritar cada vez más fuerte, desesperado...<br/>\
     Y entonces abres los ojos. La neblina se desvanece al fin, y tu vista \
     se aclara y se define completamente.<br/> \
     Delante de tí, por fín enfocas la vista y ves... una mesa. \
     -<i>¿Una mesa?</i>-<br/><br/>\
     Te despiertas tirado en el sofá, en el salón de tu casa. \
     No puedes creer lo que ha pasado. <i>¿Todo ha sido un sueño?</i><br/>\
     <i>Tiene que haberlo sido</i>-piensas-.<br/>\
     Ahí están las tres películas que habías alquilado: \
     \"La máquina del tiempo\", \"Indiana Jones y la última cruzada\" y \
     el \"Niño de Oro\". El televisor crepita silenciosamente...<br/><br/>\
     Te arde la barriga. Ahí está, el maldito bote de Mantequilla de \
     Cacahuete, encima de la mesa; la causa de tus males de estómago.<br/>\
     Deberías dejar de tomarla para cenar. No te va bien.<br/>\
     Esto lo explica todo. ${Ahora está claro, norte}." );
locLiving.pic = "res/sofa.jpg";
locLiving.setExitBi( "sur", locFountain );

locLiving.preGo = function() {
    ctrl.endGame(
        "-<i>Todo ha sido un sueño.</i>-Piensas- \
        mientras te sacudes arena (?) de los pies.</p>\
        <p align='right'>\
        <a href='#' onClick='javascript: location.reload()'>Recomienza</a>\
        la historia.</p>\
        <p id='lnkAmenities' align='right'>\
        <a href='#'\
        onClick='javascript: document.getElementById( \"amenities\" )\
        .style.display=\"block\";document.getElementById( \"lnkAmenities\" ).\
        outerHTML=\"\"'>Ver las curiosidades</a>.</p>\
        <p id='amenities' align='right' style='display: none'>\
        Los ingredientes de la mantequilla de cacahuete son:<br/>\
            Cacahuetes, sal y aceite.",
        "res/sofa.jpg" );
};

// Fog all around
locCliff.objs.push( objNiebla );
locFountain.objs.push( objNiebla );

// *** PNJs --
var pnjPan = ctrl.personas.creaPersona( "Pan", ["pan"],
    "No eres capaz de mirarte. Por mucho que intentas hacerlo, \
    no consigues enfocar la vista hacia tu propio cuerpo, tan \
    solo hacia adelante...<br>De repente, te comienza \
    a pesar la neblina que parece rodearlo todo...<br>\
    Y finalmente, todo vuelve a la normalidad... normalidad...",
    locCube
);
pnjPan.postAction = function() {
    if ( ( this.turns % 7 ) == 0
      && this.turns > 0 )
    {
        ctrl.print( "La neblina parece hacerse más y más pesada, \
                     te embota los sentidos, te sientes mal... \
                     Notas una sensación pesada en el estómago, por un \
                     momento piensas que vas a vomitar, y entonces \
                     todo parece enfocarse de nuevo." );
    }
};

// Arranque ------------------------------------------------------------
ctrl.personas.changePlayer( pnjPan );
ctrl.lugares.setStart( locCube );
