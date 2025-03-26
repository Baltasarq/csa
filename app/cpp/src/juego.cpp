// Juego.cpp
// Contiene el juego en si: descripciones, objetos...
/////////////////////////////////////////////////////////////////////////

#include "juego.h"
#include "scr.h"

#include <cstring>

const std::string aventPRESYNOMBRE = "CACAHUETE, SAL y ACEITE\n\n"
		"Abres los ojos poco a poco...\n"
        "no sabes donde te encuentras, ni lo que ha pasado. Lo ves todo a tu\n"
        "alrededor como filtrado por una densa niebla...\n"
        "Lo que realmente sabes es que no es un lugar conocido:\n"
        "hay que salir como sea.\n\n"
        "Tres entidades luminosas aparecen ante ti, un \n"
        "cacahuete, una bolsa de sal, y una botella de aceite\n"
        "\"Descubre el reto... y pasa las tres pruebas...\"\n"
        "Las entidades desaparecen...";


const std::string juegoPRESPANT[] = {

// Primera hab
"El lugar es perfectamente cuadrado. "
"Perfectamente regular en sus tres dimensiones. Tanto el suelo "
"como las paredes son de acero pulido, aunque hay una ventana de "
"un cristal raro."
,

// Segunda hab
"Te encuentras al borde de un precipicio. La oscuridad inunda el "
" lugar, y percibes todo envuelto en neblina. Te apoyas con la"
" espalda en la pared del saliente de roca sobre el desfiladero, "
" mientras a tus pies"
" se abre una brecha de 30 metros de ancho. Al otro lado, hay otro saliente."
" Y entre ellos, la nada."
,
// Tercera hab
"Has despertado en una sala con una solitaria puerta. "
"En realidad, no puedes ver las paredes de la estancia, y la "
"puerta no tiene puerta, tan solo es un marco. Es tan raro...  "
,

// Cuarta hab
"Al pasar bajo el marco, un destello cegador te aturde, y te notas mareado... "
"Poco a poco pierdes el sentido, y notas un efecto como de desplome en el "
"vientre... Recuperas la consciencia tumbado frente a la TV de tu casa, "
"a las tantas de la madrugada.\n"
"El bote de mantequilla de cacahuetes sigue sobre la mesa, al lado de los DVD "
"de Indiana Jones, H.G. Wells, y otros, "
"que cogiste para pasar la noche... "
"y te arde la barriga...\n"
"No debes tomarla para cenar... no te va bien...\n"
"\"Afortunadamente, todo ha sido una quimera...\" piensas mientras te "
"sacudes arena de los pies...\n\n\tFin."
};

const std::string juegoVOCAB[] = {
    "NORTE","SUR","ESTE","OESTE",
    "N","S","E","O",
    "RETROCEDER", "RETROCEDE",
    "CRUZAR", "CRUZA",
    "VENTANA",
    "ROCAS",
    "PAREDES",
    "SUELO",
    "TECHO",
    "CIELO",
    "ARENA",
    "SALIENTE",
    "CARTEL",
    "ESCRITURA",
    "AVISO",
    "ENTRA",
    "TIEMPO",
    "RASCA", "RASCAR", "ROMPE", "ROMPER",
    "IR","VE",
    "TIRAR", "ECHAR", "LANZAR",
    "TIRA", "ECHA", "LANZA",
    "RELOJ",
    "GIRA","MUEVE", "GIRAR", "MOVER",
    "MANECILLAS",
    "INVERSA", "INVERSAMENTE",
    "BEBE","BEBER",
    "FUENTE",
    "ENTRAR",
    "SALIR", "SAL",
    "PARED",
    "PUERTA", "MARCO",
    "AGUJAS",
    "ATRAS"
};

const std::string juegoDESCOBJS[]  = {
    // VENTANA
    "La ventana es de cristal. No es posible abrirla.\n"
    "Pruebas a romperlo con todas tus\n"
    "fuerzas, pero eres incapaz. Solamente hay oscuridad al otro lado.",
    // ROCA
    "Son grandes y escarpadas rocas. Es imposible escalarlas o\n"
    "descender por ellas.",
    // PAREDES
    "No ves nada especial en las paredes... un momento...\n"
    "en una de ellas hay una escritura.",
    // SUELO
    "Miras hacia abajo y nada te parece interesante.",
    // TECHO
    "Miras hacia arriba y nada se sale de lo habitual.",
    // ARENA
    "La arena es de un grano muy gordo.",
    // SALIENTE
    "El saliente de roca en el que te encuentras apenas es suficientemente\n"
    "grande como para mantenerte en pie. En el suelo del mismo\n"
    "ves montoncitos de arena.",
    // CARTEL
    "El cartel indica: \"Ten Fe: pero que no sea ciega.\"",
    // ESCRITURA
    "Dice: \"Piensa en cuatro dimensiones. No hay prisa...\"",
    // AVISO
    "El aviso, dice: \"Mantente puro.\"",
    // RELOJ
    "En el centro de la una de las paredes hay un reloj como de cocina,\n"
    "con manecillas negras. No tiene mecanismo. Marca las doce en punto,\n"
    "permanentemente.",
    // FUENTE
    "Una fuente muy barroca como algunas urbanas. Y funciona. Un "
    "transparente chorro de agua brota de su concha.",
    // PUERTA
    "Es verdad, es una puerta. Rara, muy rara, pero puerta al fin"
    " y al cabo."
};

///////////////////////////////// Clase Juego /////////////////////////////
Juego::Juego(const std::string &nombreJugador, unsigned int limiteDePeso)
{
    parser = new ParserJuego( nombreJugador, limiteDePeso );

    cargaVocablos();
    cargaPantallas();
    cargaObjetos();
    cargaMensajes();
    cargaVbles();
}

//----------------------------------------------------------------- Carga Mapa
void Juego::cargaPantallas()
{
    Localidad aux;

    // Localidad 1
    aux.desc            = juegoPRESPANT[ 0 ];
    aux.numConexiones   = 0;
    aux.numLoc          = 0;
    parser->mapa.mas( aux );

    // Localidad 2
    aux.desc            = juegoPRESPANT[ 1 ];
    aux.numConexiones   = 0;
    aux.numLoc          = 1;
    parser->mapa.mas( aux );

    // Localidad 3
    aux.desc            = juegoPRESPANT[ 2 ];
    aux.numConexiones   = 0;
    aux.numLoc          = 2;
    parser->mapa.mas( aux );

    // Localidad 4
    aux.desc            = juegoPRESPANT[ 3 ];
    aux.numConexiones   = 0;
    aux.numLoc          = 3;
    parser->mapa.mas( aux );

    return;
}

//---------------------------------------------------------- Carga de Vocablos
void Juego::cargaVocablos(void)
{
    // Palabras -------------------------------------------- Direcciones
    for (unsigned int i = 0; i < 8; i++) {
        unsigned int syn;

        if ( i < 4 ) {
            syn = i +4;
        } else {
            syn = i -4;
        }

        parser->vocablos.mas( Voc( i, syn, parsDIRECCION, juegoVOCAB[ i ] ) );
    }

    // Palabras --------------------------------------------- RETROCEDE[R]
    parser->vocablos.mas( Voc( 8, 9, parsACCION, juegoVOCAB[ 8 ] ) );
    parser->vocablos.mas( Voc( 9, 29, parsACCION, juegoVOCAB[ 9 ] ) );

    // Palabras --------------------------------------------- CRUZA[R]
    parser->vocablos.mas( Voc( 10, 11, parsACCION, juegoVOCAB[ 10 ] ) );
    parser->vocablos.mas( Voc( 11, 10, parsACCION, juegoVOCAB[ 11 ] ) );

    // Palabras --------------------------------------------- VENTANA
    parser->vocablos.mas( Voc( 12, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 12 ] ) );

    // Palabras --------------------------------------------- ROCA
    parser->vocablos.mas( Voc( 13, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 13 ] ) );

    // Palabras --------------------------------------------- PAREDES
    parser->vocablos.mas( Voc( 14, 51, parsNOMBRE, juegoVOCAB[ 14 ] ) );

    // Palabras --------------------------------------------- SUELO
    parser->vocablos.mas( Voc( 15, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 15 ] ) );

    // Palabras --------------------------------------------- TECHO
    parser->vocablos.mas( Voc( 16, 17, parsNOMBRE, juegoVOCAB[ 16 ] ) );

    // Palabras --------------------------------------------- CIELO
    parser->vocablos.mas( Voc( 17, 16, parsNOMBRE, juegoVOCAB[ 17 ] ) );

    // Palabras --------------------------------------------- ARENA
    parser->vocablos.mas( Voc( 18, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 18 ] ) );

    // Palabras --------------------------------------------- SALIENTE
    parser->vocablos.mas( Voc( 19, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 19 ] ) );

    // Palabras --------------------------------------------- CARTEL
    parser->vocablos.mas( Voc( 20, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 20 ] ) );

    // Palabras --------------------------------------------- ESCRITURA
    parser->vocablos.mas( Voc( 21, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 21 ] ) );

    // Palabras --------------------------------------------- AVISO
    parser->vocablos.mas( Voc( 22, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 22 ] ) );

    // Palabras --------------------------------------------- ENTRAR
    parser->vocablos.mas( Voc( 23, 48, parsACCION, juegoVOCAB[ 23 ] ) );

    // Palabras --------------------------------------------- TIEMPO
    parser->vocablos.mas( Voc( 24, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 24 ] ) );

    // Palabras --------------------------------------------- RASCA[R]
    parser->vocablos.mas( Voc( 25, 26, parsACCION, juegoVOCAB[ 25 ] ) );
    parser->vocablos.mas( Voc( 26, 27, parsACCION, juegoVOCAB[ 26 ] ) );

    // Palabras --------------------------------------------- ROMPE[R]
    parser->vocablos.mas( Voc( 27, 28, parsACCION, juegoVOCAB[ 27 ] ) );
    parser->vocablos.mas( Voc( 28, 25, parsACCION, juegoVOCAB[ 28 ] ) );

    // Palabras --------------------------------------------- IR, VE
    parser->vocablos.mas( Voc( 29, 30, parsACCION, juegoVOCAB[ 29 ] ) );
    parser->vocablos.mas( Voc( 30, 8, parsACCION, juegoVOCAB[ 30 ] ) );

    // Palabras --------------------------------------------- Tirar
    parser->vocablos.mas( Voc( 31, 32, parsACCION, juegoVOCAB[ 31 ] ) );

    // Palabras --------------------------------------------- Echar
    parser->vocablos.mas( Voc( 32, 33, parsACCION, juegoVOCAB[ 32 ] ) );

    // Palabras --------------------------------------------- Lanzar
    parser->vocablos.mas( Voc( 33, 34, parsACCION, juegoVOCAB[ 33 ] ) );

    // Palabras --------------------------------------------- Tira
    parser->vocablos.mas( Voc( 34, 35, parsACCION, juegoVOCAB[ 34 ] ) );

    // Palabras --------------------------------------------- Echa
    parser->vocablos.mas( Voc( 35, 36, parsACCION, juegoVOCAB[ 35 ] ) );

    // Palabras --------------------------------------------- Lanza
    parser->vocablos.mas( Voc( 36, 31, parsACCION, juegoVOCAB[ 36 ] ) );

    // Palabras --------------------------------------------- Reloj
    parser->vocablos.mas( Voc( 37, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[37 ] ) );

    // Palabras --------------------------------------------- GIRAR
    parser->vocablos.mas( Voc( 38, 39, parsACCION, juegoVOCAB[ 38 ] ) );

    // Palabras --------------------------------------------- MUEVE
    parser->vocablos.mas( Voc( 39, 40, parsACCION, juegoVOCAB[ 39 ] ) );

    // Palabras --------------------------------------------- GIRA
    parser->vocablos.mas( Voc( 40, 41, parsACCION, juegoVOCAB[ 40 ] ) );

    // Palabras --------------------------------------------- MOVER
    parser->vocablos.mas( Voc( 41, 38, parsACCION, juegoVOCAB[ 41 ] ) );

    // Palabras --------------------------------------------- MANECILLAS
    parser->vocablos.mas( Voc( 42, 54, parsNOMBRE, juegoVOCAB[ 42 ] ) );

    // Palabras --------------------------------------------- INVERSA
    parser->vocablos.mas( Voc( 43, 44, parsADV, juegoVOCAB[ 43 ] ) );

    // Palabras --------------------------------------------- INVERSAMENTE
    parser->vocablos.mas( Voc( 44, 55, parsADV, juegoVOCAB[ 44 ] ) );

    // Palabras --------------------------------------------- BEBE[R]
    parser->vocablos.mas( Voc( 45, 46, parsACCION, juegoVOCAB[ 45 ] ) );
    parser->vocablos.mas( Voc( 46, 45, parsACCION, juegoVOCAB[ 46 ] ) );

    // Palabras --------------------------------------------- FUENTE
    parser->vocablos.mas( Voc( 47, parsUNSIGFAIL, parsNOMBRE, juegoVOCAB[ 47 ] ) );

    // Palabras --------------------------------------------- ENTRA
    parser->vocablos.mas( Voc( 48, 49, parsACCION, juegoVOCAB[ 48 ] ) );

    // Palabras --------------------------------------------- SALIR
    parser->vocablos.mas( Voc( 49, 50, parsACCION, juegoVOCAB[ 49 ] ) );

    // Palabras --------------------------------------------- SAL
    parser->vocablos.mas( Voc( 50, 23, parsACCION, juegoVOCAB[ 50 ] ) );

    // Palabras --------------------------------------------- PARED
    parser->vocablos.mas( Voc( 51, 14, parsNOMBRE, juegoVOCAB[ 51 ] ) );

    // Palabras --------------------------------------------- PUERTA
    parser->vocablos.mas( Voc( 52, 53, parsNOMBRE, juegoVOCAB[ 52 ] ) );

    // Palabras --------------------------------------------- MARCO
    parser->vocablos.mas( Voc( 53, 52, parsNOMBRE, juegoVOCAB[ 53 ] ) );

    // Palabras --------------------------------------------- AGUJAS
    parser->vocablos.mas( Voc( 54, 42, parsNOMBRE, juegoVOCAB[ 54 ] ) );

    // Palabras --------------------------------------------- ATRAS
    parser->vocablos.mas( Voc( 55, 43, parsADV, juegoVOCAB[ 55 ] ) );

    return;
}

//-------------------------------------------------------------- Carga Objetos
void Juego::cargaObjetos()
// Cargar los objetos de la aventura
{
    // Objetos -------------------12--------------------- Ventana
    parser->vocablos.busca( "VENTANA" );
    parser->objetos.carga( Objeto( 9, parser->vocablos.getActual()->getNumId(),
             juegoDESCOBJS[ 0 ], false, true, false, 0, 1000, Objeto::Escenario )
    );

    // Objetos --------13-------------------------------- Rocas
    parser->vocablos.busca( "ROCAS" );
    parser->objetos.carga( Objeto( 0, parser->vocablos.getActual()->getNumId(),
             juegoDESCOBJS[ 1 ], false, true, false, 1, 1000, Objeto::Escenario )
    );

    // Objetos ------------------14---------------------- Paredes
    parser->vocablos.busca( "PAREDES" );
    parser->objetos.carga( Objeto( 1, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 2 ], false, true, false, 0, 1000, Objeto::Escenario )
    );

    // Objetos ----------------15------------------------ Suelo
    parser->vocablos.busca( "SUELO" );
    parser->objetos.carga( Objeto( 2, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 3 ], false, true, false, 0, 1000, Objeto::Escenario )
    );

    // Objetos ---------------16------------------------- Techo
    parser->vocablos.busca( "TECHO" );
    parser->objetos.carga( Objeto( 3, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 4 ], false, true, false, 0, 1000, Objeto::Escenario )
    );

    // Objetos --------------18-------------------------- Arena
    parser->vocablos.busca( "ARENA" );
    parser->objetos.carga( Objeto( 4, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 5 ], false, false, false, 1, 1, Objeto::Llevable )
    );

    // Objetos --------------19-------------------------- Saliente
    parser->vocablos.busca( "SALIENTE" );
    parser->objetos.carga( Objeto( 5, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 6 ], false, true, false, 1, 1000, Objeto::Escenario )
    );

    // Objetos --------------20-------------------------- Cartel
    parser->vocablos.busca( "CARTEL" );
    parser->objetos.carga( Objeto( 6, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 7 ], false, true, false, 1, 1000, Objeto::Escenario )
    );

    // Objetos --------------21-------------------------- Escritura
    parser->vocablos.busca( "ESCRITURA" );
    parser->objetos.carga( Objeto( 7, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 8 ], false, false, false, 0, 1000, Objeto::Escenario )
    );

    // Objetos --------------22-------------------------- Aviso
    parser->vocablos.busca( "AVISO" );
    parser->objetos.carga( Objeto( 8, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 9 ], false, true, false, 2, 1000, Objeto::Escenario )
    );

    // Objetos --------------37-------------------------- Reloj
    parser->vocablos.busca( "RELOJ" );
    parser->objetos.carga( Objeto( 9, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 10 ], false, true, false, 0, 1000, Objeto::Escenario )
    );

    // Objetos --------------47-------------------------- FUENTE
    parser->vocablos.busca( "FUENTE" );
    parser->objetos.carga( Objeto( 10, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 11 ], false, true, false, 2, 1000, Objeto::Escenario )
    );

    // Objetos --------------47-------------------------- PUERTA
    parser->vocablos.busca( "PUERTA" );
    parser->objetos.carga( Objeto( 10, parser->vocablos.getActual()->getNumId(),
            juegoDESCOBJS[ 12 ], false, true, false, 2, 1000, Objeto::Escenario )
    );

    return;
}

//------------------------------------------------------------ Mensajes

const std::string juegoCRASCA = "RASCA";
const std::string juegoRASCA = "No me hace falta.";
const std::string juegoCRASCAPARAQUE = "RASCAPARAQUE";
const std::string juegoRASCAPARAQUE = "Rascar eso no va a ser de mucha utilidad.";
const std::string juegoCGIRAYGIRAMANECILLAS = "GIRAYGIRAMANECILLAS";
const std::string juegoGIRAYGIRAMANECILLAS = "Cada vez que mueves las manecillas\n"
    "hacia adelante sientes un ligero mareo, y como el efecto de que\n"
    "todo se mueve. Pero entonces, todo sigue como hasta ahora.\n"
    "Es curioso, te sientes como un poco mayor...";
const std::string juegoCRETROCEDETIEMPOCOMO = "RETROCEDETIEMPOCOMO";
const std::string juegoRETROCEDETIEMPOCOMO = "Correcto. Pero necesito detalles.";
const std::string juegoCRETROCEDETIEMPO = "RETROCEDETIEMPO";
const std::string juegoRETROCEDETIEMPO = "Retrocedes en el tiempo... ves\n"
"desvanecerse las paredes... gente a tu alrededor por entre\n"
"una intensa neblina... y, finalmente, pierdes el sentido...\n"
"recuperas de nuevo la consciencia, y descubres aterrado que es \n"
"mejor no moverse...";
const std::string juegoCMUYDURO = "MUYDURO";
const std::string juegoMUYDURO = "Todos los materiales son demasiado duros,\n"
                          "como para poder hacer eso.";
const std::string juegoCARENAPUENTE = "ARENAPUENTE";
const std::string juegoARENAPUENTE = "Al echar la arena sobre el abismo, te\n"
"das cuenta de que algunos granos quedan \"flotando\" sobre la brecha.\n"
"Deduces que hay un puente invisible que\n"
"serpentea entre los dos salientes. Ahora es posible cruzarlo sin peligro.";
const std::string juegoCNOCRUZADO = "NOCRUZADO";
const std::string juegoNOCRUZADO = "Si \"cruzas\" el abismo, te matas. "
            "Eso no es bueno...";
const std::string juegoCCRUZADO = "CRUZADO";
const std::string juegoCRUZADO = "Al cruzar el puente, una roca cae desde\n"
"arriba y te golpea la cabeza. Caes inconsciente, la niebla se hace\n"
"intolerable por momentos... Recuperas la consciencia para darte cuenta de que\n"
"has despertado en un raro lugar...";
const std::string juegoCBEBIDO = "BEBIDO";
const std::string juegoBEBIDO = "Tras beber te sientes mucho mejor.\n"
                          "Te sientes... purificado...";
const std::string juegoCNOBEBIDO = "NOBEBIDO";
const std::string juegoNOBEBIDO = "A medida que te acercas a la \"puerta\"\n"
            "te das cuenta de que esta cambia de color y despide un calor\n"
            "insoportable. No es una buena idea cruzar ahora.";

const std::string centeCACAHUETE = "ENTECACAHUETE";
const std::string enteCACAHUETE = "\nLa entidad luminosa cachuete"
" aparece y te dice: \n\"...el sabor de los cachuetes...\" y "
"desaparece. \nTe duele la barriga.";

const std::string centeSAL = "ENTESAL";
const std::string enteSAL = "\nLa entidad luminosa sal aparece y "
"te dice: \"...te arde la barriga...\".\nDesaparece. Es cierto, te arde el barriga.";

const std::string centeACEITE = "ENTEACEITE";
const std::string enteACEITE = "\nLa entidad luminosa aceite aparece y"
" dice: \"...te sientes...nauseabundo...\".\nDesaparece y te sientes muy mal.";

//------------------------------------------------------------ Carga Mensajes
void Juego::cargaMensajes()
{
    //---------------------------------------------- RASCA
    parser->mensajes.mas( Mensaje( juegoCRASCA, juegoRASCA ) );

    //---------------------------------------------- RASCARPARAQUE
    parser->mensajes.mas( Mensaje( juegoCRASCAPARAQUE, juegoRASCAPARAQUE ) );

    //---------------------------------------------- GIRAYGIRAMANECILLAS
    parser->mensajes.mas( Mensaje( juegoCGIRAYGIRAMANECILLAS, juegoGIRAYGIRAMANECILLAS ) );

    //---------------------------------------------- RETROCEDETIEMPOCOMO
    parser->mensajes.mas( Mensaje( juegoCRETROCEDETIEMPOCOMO, juegoRETROCEDETIEMPOCOMO ) );

    //---------------------------------------------- RETROCEDETIEMPO
    parser->mensajes.mas( Mensaje( juegoCRETROCEDETIEMPO, juegoRETROCEDETIEMPO ) );

    //---------------------------------------------- MUYDURO
    parser->mensajes.mas( Mensaje( juegoCMUYDURO, juegoMUYDURO ) );

    //---------------------------------------------- ARENAPUENTE
    parser->mensajes.mas( Mensaje( juegoCARENAPUENTE, juegoARENAPUENTE ) );

    //---------------------------------------------- NOCRUZADO
    parser->mensajes.mas( Mensaje( juegoCNOCRUZADO, juegoNOCRUZADO ) );

    //---------------------------------------------- CRUZADO
    parser->mensajes.mas( Mensaje( juegoCCRUZADO, juegoCRUZADO ) );

    //---------------------------------------------- BEBIDO
    parser->mensajes.mas( Mensaje( juegoCBEBIDO, juegoBEBIDO ) );

    //---------------------------------------------- NOBEBIDO
    parser->mensajes.mas( Mensaje( juegoCNOBEBIDO, juegoNOBEBIDO ) );

    //---------------------------------------------- ENTES
    parser->mensajes.mas( Mensaje( centeACEITE, enteACEITE ) );
    parser->mensajes.mas( Mensaje( centeSAL, enteSAL ) );
    parser->mensajes.mas( Mensaje( centeCACAHUETE, enteCACAHUETE ) );

    return;
}

//------------------------------------------------------------- Carga Vbles
void Juego::cargaVbles()
{
    parser->vbles.mas( Var( "ARENAPUENTE" ) );
    parser->vbles.mas( Var( "ARENACOGIDA" ) );
    parser->vbles.mas( Var( "BEBIDO" ) );

    return;
}

//--------------------------------------------------------------  Proc1
void ParserJuego::hazProc1()
{
    if ( !esFinalJuego() ) {
        Var &arenaCogida = vbles.busca( "ARENACOGIDA" );

        // Si examinadas las paredes, el escrito es visible
        objetos.buscaPerVoc( vocablos.busca( "PAREDES" ) );
        if ( objetos.getActual()->fueExaminado() )
        {
            objetos.buscaPerVoc( vocablos.busca( "ESCRITURA" ) );
            objetos.getActual()->setVisible();
        }

        // Si examinado el saliente, la arena es visible
        objetos.buscaPerVoc( vocablos.busca( "SALIENTE" ) );
        Objeto &objSaliente = *( objetos.getActual() );
        objetos.buscaPerVoc( vocablos.busca( "ARENA" ) );
        Objeto &objArena = *( objetos.getActual() );
        if( objSaliente.fueExaminado() )
        {
            objArena.setVisible();
        }

        if ( arenaCogida == 0
          && objArena.esLlevado() )
        {
            arenaCogida = 1;
            objSaliente.setDesc(
                    "El saliente de roca en el que te encuentras apenas es "
                    "suficientemente\ngrande como para mantenerte en pie."
            );
        }

        // Si un multpl de 8 jugadas ...
        if ( getMovidas() > 0 ) {
         if ( ( getMovidas() %8 ) == 0 ) {
            Scr::println( mensajes.busca( "ENTECACAHUETE" )->getMensaje() );
         }
         else
        // Si un multpl de 7 jugadas ...
         if ( getMovidas() %7 == 0 ) {
            Scr::println( mensajes.busca("ENTEACEITE")->getMensaje() );
         }
         else
        // Si un multpl de 12 jugadas ...
         if ( ( getMovidas() %12 ) ==0 )
            Scr::println( mensajes.busca("ENTESAL")->getMensaje() );
        }
    }
}

//--------------------------------------------------------------  Respuestas
void ParserJuego::hazResp()
{
    Var &haBebido = vbles.busca( "BEBIDO" );
    Var &hayArenaPuente = vbles.busca( "ARENAPUENTE" );

    // Explicaciones necesarias para retroceder en el tiempo
    vocablos.busca( orden.verbo );

    if ( getNumLoc() == 0
        && vocablos.compara( "RETROCEDE", vocablos.getActual()->getPalabra() )
        && orden.cd != parsUNSIGFAIL )
    {
        vocablos.busca( orden.cd );
        if ( vocablos.compara( "TIEMPO", vocablos.getActual()->getPalabra() ) ) {
            Scr::println( mensajes.busca( "RETROCEDETIEMPOCOMO" )->getMensaje() );
        }
    }
    else
    // Retroceder en el tiempo
    if ( getNumLoc() == 0
        && vocablos.compara( "GIRA", vocablos.getActual()->getPalabra() )
        && orden.cd != parsUNSIGFAIL )
    {
        vocablos.busca( orden.cd );
        if ( vocablos.compara( "MANECILLAS", vocablos.getActual()->getPalabra() ) ) {
            if ( orden.adv != parsUNSIGFAIL ) {
                 vocablos.busca( orden.adv );
                 if ( vocablos.compara( "INVERSAMENTE", vocablos.getActual()->getPalabra() ) )
                 {
                    Scr::println( mensajes.busca( "RETROCEDETIEMPO" )->getMensaje() );
                    mapa.setNumLoc( 1 );
                    hazDesc();
                    sumaPuntuacion( 33 );
                 } else {
                     Scr::println( mensajes.busca( "GIRAYGIRAMANECILLAS" )->getMensaje() );
                 }
            } else {
                Scr::println( mensajes.busca( "GIRAYGIRAMANECILLAS" )->getMensaje() );
            }
        }
    }
    else
    if ( getNumLoc() == 0
     && vocablos.compara( "RASCA", vocablos.getActual()->getPalabra() )
     && orden.cd != parsUNSIGFAIL )
    {
        Scr::println( mensajes.busca( "MUYDURO" )->getMensaje() );
    }
    else
    if ( vocablos.compara( "RASCA", vocablos.getActual()->getPalabra() )
      && orden.cd == parsUNSIGFAIL )
    {
        Scr::println( mensajes.busca( "RASCA" )->getMensaje() );
    }
    else
    if ( vocablos.compara( "RASCA", vocablos.getActual()->getPalabra() )
     && orden.cd != parsUNSIGFAIL )
    {
        Scr::println( mensajes.busca( "RASCARPARAQUE" )->getMensaje() );
    }
    else
    if ( getNumLoc() == 1
      && vocablos.compara( "TIRAR", vocablos.getActual()->getPalabra() )
      && orden.cd != parsUNSIGFAIL )
    {
        vocablos.busca( orden.cd );
        if ( vocablos.compara( "ARENA", vocablos.getActual()->getPalabra() ) ) {
            if ( esLlevado( "ARENA" ) ) {
                objetos.getActual()->setLlevado( false );
                objetos.getActual()->setNumLoc( parsUNSIGFAIL );
                Scr::println( mensajes.busca( "ARENAPUENTE" )->getMensaje() );
                hayArenaPuente = 1;
            } else Scr::println( parsNOLLEVASDEESOS );
        }
        else {
            Scr::println( parsNOLLEVASDEESOS );
        }
    }
    else
    if ( getNumLoc() == 1
      && vocablos.compara( "CRUZAR", vocablos.getActual()->getPalabra() ) )
    {
        if ( hayArenaPuente == 1 ) {
            Scr::println( mensajes.busca( "CRUZADO" )->getMensaje() );
            mapa.setNumLoc( 2 );
            hazDesc();
            sumaPuntuacion( 34 );
        } else {
            Scr::println( mensajes.busca( "NOCRUZADO" )->getMensaje() );
        }
    }
    else
    if ( getNumLoc() == 2
      && vocablos.compara( "BEBER", vocablos.getActual()->getPalabra() ) )
    {
            Scr::println( mensajes.busca( "BEBIDO" )->getMensaje() );
            haBebido = 1;
    }
    else
    if ( getNumLoc() == 2
     && ( vocablos.compara( "ENTRAR", vocablos.getActual()->getPalabra() )
      ||  vocablos.compara( "CRUZA", vocablos.getActual()->getPalabra() ) ) )
    {
        if ( haBebido == 1 ) {
            final = true;
            mapa.setNumLoc( 3 );
            hazDesc();
            sumaPuntuacion( 33 );
        } else {
            Scr::println( mensajes.busca( "NOBEBIDO" )->getMensaje() );
        }
    } else {
        Scr::println( parsNOSECOMO );
    }
}
