// csa.js
/*
 *      Cacahuetes, sal y aceite (v4)
 *          1998, 1999, 2000, 2012: Csa: Parser KAC/C++
 *          2009, 2010, 2016: Csa v2 a Csa v3: informATE!/Zcode
 *      (c) 1998-2017 baltasarq@gmail.com MIT License
 *
 *      2017: Aventura de texto onírica construida con fi.js.
 *      Licencia MIT
 */

ctrl.ponTitulo( "Cacahuetes, sal y aceite" );
ctrl.ponIntro( "Despiertas atontado... \
                en un cubo de acero totalmente regular." );
ctrl.ponImg( "res/cube.jpg" );
ctrl.ponAutor( "Baltasarq" );
ctrl.ponVersion( "4 20170106" );

function amenities() {
    return "<p>Este relato fue creado para una <i>NanoComp</i> en 2000.<br> \
            El soporte era un parser propio, que posteriormente cambié por \
            InformATE!, pero en realidad se trataba \
            más de un relato interactivo que de una verdadera aventura \
            conversacional (objetos, puzzles, etc.)</p><p>Así que en 2017 \
            me lié la manta a la cabeza y la porté a mi propio sistema, \
            <b>fi.js</b>. El resultado es así más versátil.</p> \
            <p>Los ingredientes de la mantequilla de cacahuete son:<br><ul>\
            <li>Cacahuetes\
            <li>Aceite\
            <li>Sal\
            </ul></p>";
}

// *** Locs --
// ---------------------------------------------------------------------- Celda
var locCube = ctrl.places.creaLoc(
    "Celda",
    [ "camarote", "sala", "prision", "cubo", "celda" ],
    "<p class='firstP'>Las ${paredes, ex paredes} de acero de esta \
     habitación perfectamente regular parecen \
     estar hechas de una sola pieza, pulidas hasta el punto de brillar con \
     una luz que... no sabes de donde viene. El silencio es sobrecogedor, \
     y la sensación de fría, y tensa espera abrumadora, como la extraña \
     ${niebla, ex niebla} que te rodea.</p>" );
locCube.pic = "res/cube.jpg";
locCube.time = 0;
locCube.advanceTime = function() {
    ctrl.clearAnswers();

    this.time++;
    if ( this.time >= 3
      && this.time < 4)
    {
        ctrl.print( "Te sientes realmente mal. Tus manos tiemblan y... \
                     multitud de arrugas las surcan. Te sientes mareado, \
                     cansado... casi no puedes sostenerte..." );
    }
    else
    if ( this.time >= 4) {
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
}

var objNiebla = ctrl.creaObj(
    "niebla",
    [ "niebla", "bruma", "neblina" ],
    "Esta neblina lo envuelve todo... es agobiante, abrumadora...",
    locCube,
    Ent.Scenery
);
objNiebla.setReachable( false );

var objWindow = ctrl.creaObj(
    "ventana",
    [ "ventana", "vista", "enrejado", "ventanuco", "cristal" ],
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
}

objWindow.preOpen = function() {
    return "¿Pero, cómo? No hay pestillos, ni cerrojos...";
}

var objWalls = ctrl.creaObj(
    "paredes",
    [ "pared", "acero", "muro", "muros" ],
    "Las paredes son de acero pulido, sin remaches, \
     ni molduras o marcas de ningún tipo.",
    locCube,
    Ent.Scenery
);

objWalls.preExamine = function() {
    var toret = objWalls.desc;

    if ( this.examinations == 0 ) {
        locCube.desc += "<p>Precisamente debido a su uniformidad, \
                        varios elementos llaman tu atención \
                        en las ${paredes, ex paredes}. En la pared sur \
                        puedes ver una \
                        ${ventana, ex ventana} y un ${reloj, ex reloj} \
                        mientras en la pared oeste hay algún tipo de \
                        ${inscripción, ex aviso}. Piensas que quizás \
                        puedas ${romperlas, golpea paredes}.</p>";
        actions.execute( "look" );
    }

    return toret;
}

objWalls.preAttack = function() {
    return "Golpeas con todas tus fuerzas, y... ¡te haces mucho \
            daño! ...es inútil.";
}

var objInscripcion = ctrl.creaObj(
    "inscripcion",
    [ "aviso", "escritura" ],
    "Reza: 'Piensa en cuatro dimensiones. Aún tienes tiempo...'",
    locCube,
    Ent.Scenery
);

var objClock = ctrl.creaObj(
    "reloj",
    [ "manecillas", "agujas" ],
    "Es un extraño reloj, pues sus agujas no se mueven por si solas. \
     No crees que tenga mecanismo. Te preguntas por el sentido que pueda \
     tener un reloj como de juguete ahí puesto.",
    locCube,
    Ent.Scenery
);
objClock.preExamine = function() {
    var toret = this.desc;

    if ( this.examinations == 0 ) {
        locCube.desc += "<p>Las manecillas del reloj \
                         pueden ser manipuladas libremente. Podrías \
                         ${girarlas en el sentido horario, tira de reloj}, \
                         o ${girarlas en el sentido contrario, empuja reloj}. \
                         </p>";
        actions.execute( "look" );
    }

    return toret;
}

objClock.prePull = function() {
    locCube.advanceTime();
}

objClock.prePush = function() {
    var toret = "Al girar las agujas a la inversa, todo parece ennublecerse. \
            Te sientes mareado, y esa neblina que parece cargarlo todo se hace \
            más y más espesa...<br/>Te despiertas para comprobar que es mejor \
            no moverse...";
    objNiebla.moveTo( locCliff );
    ctrl.goto( locCliff );
    return toret;
}

// --------------------------------------------------------------------- Abismo
var locCliff = ctrl.places.creaLoc(
    "Abismo",
    [ "caida", "sima", "agujero"],
    "<p class='firstP'>A tus pies, se abre el ${abismo, ex pozo} insondable. \
    Un ${saliente de roca, ex saliente} evita que caigas. Te mantienes en \
    tensión, de espaldas a la pared sur \
	del mismo. Al otro lado, el lado norte, un saliente de roca \
	gemelo al que pisas ahora, da paso a la caverna que se abre \
	al exterior. En medio de los salientes, la nada. La ${niebla, ex niebla} \
	aparece cargando toda la estancia, a base de espesos jirones...</p>" );
locCliff.pic = "res/cliff.jpg";

var objBridge = ctrl.creaObj(
    "puente",
    [ "pasarela" ],
    "Un puente que antes no veías por un efecto óptico cruza \
    entre ambos salientes.",
    locCliff,
    Ent.Scenery
);

var objRock = ctrl.creaObj(
    "saliente",
    [ "roca" ],
    "El suelo del saliente está lleno de montoncitos de ${arena, ex arena}. \
     También puedes ver un ${cartel, ex cartel}.",
    locCliff,
    Ent.Scenery
);
objRock.preExamine = function() {
    if ( ctrl.places.limbo.has( objSand ) ) {
        objSand.moveTo( locCliff );
    }

    return objRock.desc;
}

var objWell = ctrl.creaObj(
    "sima",
    [ "pozo" ],
    "El abismo es negro e insondable. Muy profundo. Da miedo.",
    locCliff,
    Ent.Scenery
);

var objSign = ctrl.creaObj(
    "cartel",
    [ "aviso" ],
    "Medio podrido por la humedad, indica: 'Ten Fe: pero que no sea ciega.'",
    locCliff,
    Ent.Scenery
);

var objSand = ctrl.creaObj(
    "arena",
    [ "montoncitos", "montoncito", "monton", "montones" ],
    "Montoncitos de arena gorda",
    ctrl.places.limbo,
    Ent.Portable
);
objSand.preExamine = function() {
    var toret = objSand.desc;
    var player = ctrl.personas.getPlayer();

    if ( player.has( this ) ) {
        toret += ", como la que tienes entre las manos.";
    } else {
        toret += ", que podrías ${coger, coge arena} con tus manos."
    }

    return toret;
}

// *** PNJs --
var pnjPan = ctrl.personas.creaPersona( "Pan",
                    [ "pan" ],
                    "No eres capaz de mirarte. Por mucho que intentas hacerlo, \
                    no consigues enfocar la vista hacia tu propio cuerpo, tan \
                    solo hacia adelante...<br>De repente, te comienza \
                    a pesar la neblina que parece rodearlo todo...<br>\
                    Y finalmente, todo vuelve a la normalidad... normalidad...",
                    locCube
);

// Arranque ------------------------------------------------------------
ctrl.personas.changePlayer( pnjPan );
ctrl.lugares.setStart( locCube );
