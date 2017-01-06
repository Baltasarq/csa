// csa.js
/*
 *      Cacahuetes, sal y aceite (v4)
 *          1998, 1999, 2000, 2012: Csa: Parser KAC/C++
 *          2009, 2010: Csa v2 a Csa v3: informATE!/Zcode
 *      (c) 2017 baltasarq@gmail.com MIT License
 *
 *      Aventura de texto onírica construida con fi.js.
 *
 */

ctrl.ponTitulo( "Cacahuetes, sal y aceite" );
ctrl.ponIntro( "Despiertas atontado... en un cubo de acero totalmente regular." );
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
            <b>fi.js</b>. El resultado es así más versátil.</p>"
}

// *** Locs --
var locCube = ctrl.places.creaLoc(
    "Celda",
    [ "camarote", "sala" ],
    "Una celda perfectamente cúbica." );
locCube.pic = "res/cube.jpg";

var objWindow = ctrl.creaObj(
        "ventana",
        [ "ventana", "vista", "enrejado" ],
        "Una ventana enrejada.",
        locCube,
        Ent.Scenery
);

// *** PNJs --
var pnjPan = ctrl.personas.creaPersona( "Pan",
                    [ "pan" ],
                    "Eres el comandante Ungarr, del navío de combate estelar \
                     ALK-C34 en misión en el cuadrante SS-345 \
                     (contrarreferencia: sistema solar, planeta 'Tierra', \
                     habitado por los autodenominados 'humanos').",
                    locCube
);

// Arranque ------------------------------------------------------------
ctrl.personas.changePlayer( pnjPan );
ctrl.lugares.setStart( locCube );
