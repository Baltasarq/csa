// Parser.cpp
// Analizador sintct.
// KAC (c) 1998,99,2000, 2012 Kit de Aventuras Conversacionales
///////////////////////////////////////////////////////////////////////////

#include <string>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>

#include "parser.h"
#include "scr.h"

const std::string parsPROMPT     = "> ";
const std::string parsMSGNOPANT  = "Pulse ENTER para continuar...";

const std::string parsPUNTUACION = "_Y__ENTONCES__,__;__.__entonces__y__despues__DESPUES_"
                                   "_seguidamente__SEGUIDAMENTE_";

const std::string   parsFINALJUEGO = "FIN";
const std::string   parsFINALJUEGO2 = "EXIT";
const std::string   parsFINALJUEGO3 = "QUIT";
const std::string   parsFINALJUEGO4 = "TERMINA";
const std::string   parsFINALJUEGO5 = "TERMINAR";

const std::string   parsPONINV     = "INVENTARIO";
const std::string   parsPONINV2    = "INV";
const std::string   parsPONINV3     = "I";

const std::string   parsPONEX      = "EXAMINA";
const std::string   parsPONEX2     = "EX";
const std::string   parsPONEX3     = "EXAMINAR";

const std::string   parsPONSALIDA  = "SALIDAS";
const std::string   parsPONSALIDA2 = "X";
const std::string   parsPONSALIDA3 = "SALIDA";

const std::string   parsCOGER      = "COGE";
const std::string   parsCOGER2     = "COGER";
const std::string   parsCOGER3     = "COJO";

const std::string   parsDEJAR      = "DEJA";
const std::string   parsDEJAR2     = "DEJAR";
const std::string   parsDEJAR3     = "DEJO";

const std::string   parsPONER      = "PONTE";
const std::string   parsPONER2     = "PONER";
const std::string   parsPONER3     = "PON";

const std::string   parsQUITAR     = "QUITATE";
const std::string   parsQUITAR2    = "QUITAR";
const std::string   parsQUITAR3    = "QUITO";

const std::string   parsMSGDIRNO   = "No es una salida que pueda tomar.";

const std::string   parsMSGNOPUEDES= "No puedo hacer eso.";

const std::string   parsMSGSALIDA  = "Puedo ir por las salidas siguientes";
const std::string   parsMSGNOHAYSALIDAS = "No veo ninguna salida.";

const std::string   parsPONAYUDA   = "AYUDA";
const std::string   parsPONAYUDA2  = "?";
const std::string   parsPONAYUDA3  = "AYUDAME";

const std::string   parsPUNT       = "PUNTUACION";


const std::string   parsMSGAYUDA   = "Puedes usar lo siguiente:\n?/AYUDA\t\tEsta ayuda.\n"
    "FIN/TERMINA\tSalir del Juego\n"
    "PUNTUACION\tMuestra los puntos del jugador.\n"
    "SALIDAS\t\tMuestra las salidas de cada sitio\n"
    "tecla: ENTER\tEn la entrada del jugador, repite el sitio\n"
    "INVENTARIO\tMuestra los objetos que llevas.\n"
    "EXAMINA/EX [x]\tBusca objetos en la localidad actual o describe un objeto en concreto.\n"
    "COGE x\t\tEl objeto x pasa a ser llevado por el jugador.\n"
    "DEJA x\t\tEl objeto x deja de ser llevado por el jugador.\n"
    "PONTE x\t\tEl objeto x deja de ser llevado y pasa a estar puesto\n"
    "QUITATE x\tEl objeto x deja de ser llevado puesto y pasa a ser llevado\n";

const std::string   parsMSGINV     = "Llevo:";

const std::string   parsMSGEX      = "Alrededor hay lo siguiente:";

const std::string   parsMSGNOHAY   = "Nada de nada.";

const std::string   parsMSGSYSNOSE = "Busca otra forma de hacer eso con ";

const std::string   parsMSGSYSPUESTO = " (puesto)";

const std::string   parsMSGSYSNOLOLLEVAS
             = "No puedo examinarlo porque no lo llevo conmigo.";

const std::string   parsMSGSYSOBJNOEXISTE = "Eso no lo veo alrededor... ";

const std::string   parsMSGSYSDENTRO = "Veo dentro de ";

const std::string   parsMENSAJITOPREPROMPT[parsMAXMENSAJITOS] = {
        "Espero.", "Venga, escribe algo...",
        "Ahora...", "En fin...",
        "Siguiente orden:", "Es tu turno.",
        "Pensamos un poquito y...", "Adelante.",
        "Espero instrucciones", "Venga."
};

const std::string parsMENSAJEPUNT1 = "Jugadas: ";
const std::string parsMENSAJEPUNT2 = "Puntos: ";
const std::string parsMENSAJECOGER = "Lo he cogido.";
const std::string parsMENSAJEDEJAR = "Lo he dejado.";
const std::string parsMENSAJEPONER = "Me lo he puesto.";
const std::string parsMENSAJEQUITAR= "Me lo he quitado.";
const std::string parsNOHAYDEESOS  = "No hay nada de eso en este sitio...";
const std::string parsNOLLEVASDEESOS = "Eso no lo llevo...";
const std::string parsNOLLEVASDEESOSP = "Eso no lo llevo puesto...";
const std::string parsNOSEPUEDECOGER = "Eso no se puede coger.";
const std::string parsMSGFIN        = "Abandonas la aventura...";
const std::string parsDEMASIADOPESO = "Eso pesa demasiado.";
const std::string parsNOESPONIBLE   = "No me lo puedo poner.";
const std::string parsNOSECOMO      = "No entiendo lo que quieres hacer.";
const std::string parsYALOLLEVAS    = "Ya lo tienes.";

//////////////////////////////// Clase Mapa   //////////////////////////////

void Mapa::escribeFormato(const std::string &str)
{
    int  ultesp;
    char *ptr;
    char ch;
    char *aux;


    Scr::println();

    aux = new char[ str.length() +1 ];
    strcpy( aux, str.c_str() );
    ptr = aux;

    while ( ptr < ( aux + str.length() ) ) {

        ultesp = parsMAXCOLS-1;

        if ( ( (unsigned int) ( ( ptr - aux ) + ultesp ) ) < str.length() ) {

         while(*(ptr+ultesp)!=' ') {
              ultesp--;
         }

         ch =*(ptr+ultesp+1);
         *(ptr+ultesp+1) = 0;

         Scr::print( ptr );

         if ( ultesp < parsMAXCOLS-1 ) {
            Scr::println();
         }

         ptr += ultesp + 1;
         *ptr = ch;

        } else {
            Scr::print( ptr );
            break;
        }
    }

    Scr::println();
    delete[] aux;
}



bool Mapa::describe(unsigned int x)
{
    bool toret;

    // Buscar la loc
    ve( inic() );
    while( !esFin()
        && getActual()->numLoc < x )
    {
        sig();
    }

    // Comprobar que la hemos encontrado
    if ( !esFin()
      && x == getActual()->numLoc )
    {
        toret = true;
        escribeFormato( getActual()->desc );
        numLoc = getActual()->numLoc;
    }
    else {
        toret = false;
    }

    return toret;
}

//////////////////////////////// Clase Parser //////////////////////////////
void Parser::prepara()
{
    final = false;
    movidas = punt = 0;
    std::srand( (unsigned int) time(NULL) );

    // Final de juego ----------------------- Exit
    vocablos.mas( Voc( 59996, 59997, parsCTRL, parsFINALJUEGO ) );
    vocablos.mas( Voc( 59997, 59998, parsCTRL, parsFINALJUEGO2 ) );
    vocablos.mas( Voc( 59998, 59999, parsCTRL, parsFINALJUEGO3 ) );
    vocablos.mas( Voc( 59999, 60000, parsCTRL, parsFINALJUEGO4 ) );
    vocablos.mas( Voc( 60000, 59996, parsCTRL, parsFINALJUEGO5 ) );

    // -------------------------------------- Pon Salidas
    vocablos.mas( Voc( 60001, 60002, parsCTRL, parsPONSALIDA ) );
    vocablos.mas( Voc( 60002, 60003, parsCTRL, parsPONSALIDA2 ) );
    vocablos.mas( Voc( 60003, 60001, parsCTRL, parsPONSALIDA3 ) );

    // -------------------------------------- Pon AYUDA
    vocablos.mas( Voc( 60004, 60005, parsCTRL, parsPONAYUDA ) );
    vocablos.mas( Voc( 60005, 60006, parsCTRL, parsPONAYUDA2 ) );
    vocablos.mas( Voc( 60006, 60004, parsCTRL, parsPONAYUDA3 ) );

    // -------------------------------------- Pon Inventario
    vocablos.mas( Voc( 60007, 60008, parsCTRL, parsPONINV ) );
    vocablos.mas( Voc( 60008, 60009, parsCTRL, parsPONINV2 ) );
    vocablos.mas( Voc( 60009, 60007, parsCTRL, parsPONINV3 ) );

    // -------------------------------------- Pon Examinar
    vocablos.mas( Voc( 60010, 60011, parsCTRL, parsPONEX ) );
    vocablos.mas( Voc( 60011, 60012, parsCTRL, parsPONEX2 ) );
    vocablos.mas( Voc( 60012, 60010, parsCTRL, parsPONEX3 ) );

    // -------------------------------------- COGER
    vocablos.mas( Voc( 60013, 60014, parsCTRL, parsCOGER ) );
    vocablos.mas( Voc( 60014, 60015, parsCTRL, parsCOGER2 ) );
    vocablos.mas( Voc( 60015, 60013, parsCTRL, parsCOGER3 ) );

    // -------------------------------------- DEJAR
    vocablos.mas( Voc( 60016, 60017, parsCTRL, parsDEJAR ) );
    vocablos.mas( Voc( 60017, 60018, parsCTRL, parsDEJAR2 ) );
    vocablos.mas( Voc( 60018, 60016, parsCTRL, parsDEJAR3 ) );

    // -------------------------------------- Poner
    vocablos.mas( Voc( 60019, 60020, parsCTRL, parsPONER ) );
    vocablos.mas( Voc( 60020, 60021, parsCTRL, parsPONER2 ) );
    vocablos.mas( Voc( 60021, 60019, parsCTRL, parsPONER3 ) );

    // -------------------------------------- quitar
    vocablos.mas( Voc( 60022, 60023, parsCTRL, parsQUITAR ) );
    vocablos.mas( Voc( 60023, 60024, parsCTRL, parsQUITAR2 ) );
    vocablos.mas( Voc( 60024, 60022, parsCTRL, parsQUITAR3 ) );

    // -------------------------------------- Pon puntos
    vocablos.mas( Voc( 60026, parsUNSIGFAIL, parsCTRL, parsPUNT ) );
}

bool Parser::hazDir()
{
    Conexion mov;
    unsigned int i = 0;
    Localidad &loc = *( mapa.getActual() );

    mov = loc.conexiones[ 0 ];
    unsigned int numVocVerbo = vocablos.busca( orden.verbo );

    if ( numVocVerbo != parsUNSIGFAIL )
    {
        const std::string &verbo = vocablos.getActual()->getPalabra();

        // Buscar la conexion
        while ( i < loc.numConexiones ) {
            if ( vocablos.compara( mov.palabra, verbo ) ) {
                break;
            }

            i++;
            mov = loc.conexiones[ i ];
        }

        // Al encontrarlo, actual
        if ( i < loc.numConexiones ) {
            mapa.setNumLoc( mov.numLocDest );
            hazDesc();
        }
    }

    return ( i < loc.numConexiones );
}

void Parser::muestraPuntuacion()
{
    std::ostringstream mensajeResumen;

    decrementaMovidas();
    mensajeResumen << parsMENSAJEPUNT1 << getMovidas() << std::endl;
    mensajeResumen << parsMENSAJEPUNT2 << getPuntuacion() << '%'<< std::endl;

    Scr::print( mensajeResumen.str() );
}

void Parser::describeObjeto(Objeto &obj)
{
    std::string aux;

    vocablos.busca( obj.getCodVoc() );
    const Voc &voc = *( vocablos.getActual() );

    aux = StringTokenizer::normaliza( voc.getPalabra() );
    aux += ':';
    aux += ' ';
    Scr::print( aux );
    Scr::print( obj.getDesc() );

    obj.setExaminado();
}

void Parser::hazCtrl()
{
    if ( vocablos.compara( parsFINALJUEGO, vocablos.getActual()->getPalabra() ) )
    {
        // Final del juego
        Scr::println( parsMSGFIN );
        Scr::println();

        final = true;
    }
    else
    if ( vocablos.compara( parsPUNT, vocablos.getActual()->getPalabra() ) )
    {
        muestraPuntuacion();
        Scr::println();
    }
    else
    if ( vocablos.compara( parsPONSALIDA, vocablos.getActual()->getPalabra() ) )
    {
        // Ver salidas
        Scr::println( parsMSGSALIDA );
        Localidad &loc = *( mapa.getActual() );

        for(unsigned int i = 0; i < loc.numConexiones; i++) {
            Scr::println( loc.conexiones[ i ].palabra );
        }

        if ( loc.numConexiones == 0 ) {
            Scr::println( parsMSGNOHAYSALIDAS );
        }

        decrementaMovidas();
        Scr::println();
    }
    else
    if ( vocablos.compara( parsPONAYUDA, vocablos.getActual()->getPalabra() ) )
    {
        // Poner ayuda en pantalla
        decrementaMovidas();
        Scr::println( parsMSGAYUDA );
        Scr::println();
    }
    else
    if ( vocablos.compara( parsPONEX, vocablos.getActual()->getPalabra() )
      && orden.cd == parsUNSIGFAIL )
    {
        // Examinar la localidad
        decrementaMovidas();
        unsigned int num = 0;
        Scr::println( parsMSGEX );

        objetos.ve( objetos.inic() );

        while( objetos.buscaSigPerLoc( mapa.getNumLoc() ) != parsUNSIGFAIL )
        {
            const Objeto &obj = *( objetos.getActual() );
            if ( obj.esVisible() )
            {
                vocablos.busca( obj.getCodVoc() );
                Scr::print( "- " );
                Scr::println( StringTokenizer::normaliza(
                                        vocablos.getActual()->getPalabra() )
                );
                ++num;
            }

            objetos.sig();
        }

        if ( num == 0 ) {
            Scr::println( parsMSGNOHAY );
        }
    }
    else
    if ( vocablos.compara( parsPONEX, vocablos.getActual()->getPalabra() )
      && orden.cd != parsUNSIGFAIL )
    {
        // Examinar un objeto
        unsigned int palact = orden.cd,
        pali = palact;
        bool enc = false;

        do {
            if ( objetos.buscaPerVoc( palact ) != parsUNSIGFAIL )
            {
                Objeto & obj = *( objetos.getActual() );

                if ( ( obj.getNumLoc() == mapa.getNumLoc()
                    || obj.esLlevado() )
                  && obj.esVisible() )
                {
                    describeObjeto( obj );
                    Scr::println();
                    enc = true;
                } else {
                    Scr::println( parsMSGSYSOBJNOEXISTE );
                }
            }

            vocablos.busca( palact );
            palact = vocablos.getActual()->getSyn();

          } while ( pali != palact
                 && palact != parsUNSIGFAIL
                 && !enc );

          if ( !enc ) {
              Scr::println( parsMSGSYSOBJNOEXISTE );
          }
    }
    else
    if ( vocablos.compara( parsPONINV, vocablos.getActual()->getPalabra() ) )
    {

        // INVENTARIO
        objetos.inic();
        unsigned int num = 0;

        Scr::println( parsMSGINV );
        while( !objetos.esFin() ) {
            // de todos los objs, listar los llevados
            if ( objetos.getActual()->esLlevado() ) {

                const Objeto & obj = *( objetos.getActual() );
                std::string aux = "- ";

                vocablos.busca( obj.getCodVoc() );
                aux += StringTokenizer::normaliza(
                                        vocablos.getActual()->getPalabra()
                );

                if ( obj.estaPuesto() ) {
                    aux += parsMSGSYSPUESTO;
                }

                Scr::println( aux );
                num++;

            }

            objetos.sig();
        }

        if ( num == 0 ) {
            Scr::println( parsMSGNOHAY );
        }
    }
    else
    // COGER
    if ( vocablos.compara( parsCOGER, vocablos.getActual()->getPalabra() ) )
    {
        // El CD es el objeto
        if ( ( vocablos.busca(orden.cd) ) != parsUNSIGFAIL )
        {
            objetos.buscaPerVoc( vocablos.getActual()->getNumId() );
            if ( !objetos.getActual()->esLlevado()
              && !objetos.getActual()->estaPuesto() )
            {
                if ( objetos.getActual()->getNumLoc() == mapa.getNumLoc()
                  && objetos.getActual()->esVisible() )
                {
                    if ( objetos.getActual()->getTipo() == Objeto::Llevable
                      || objetos.getActual()->getTipo() == Objeto::Ponible )
                    {
                        if ( limpeso >=
                            ( objetos.getPesoLlevados() + objetos.getActual()->getPeso() ) )
                        {
                            // Ahora lo lleva
                            objetos.getActual()->setLlevado();
                            Scr::println( parsMENSAJECOGER );
                            objetos.sumaPeso( objetos.getActual()->getPeso() );
                        } else {
                            Scr::println( parsDEMASIADOPESO );
                        }
                    } else {
                        Scr::println( parsNOSEPUEDECOGER );
                    }
                } else {
                    Scr::println( parsNOHAYDEESOS );
                }
            } else {
                Scr::println( parsYALOLLEVAS );
            }
        } else {
            Scr::println( parsNOHAYDEESOS );
        }
    }
    else
    // DEJAR
    if ( vocablos.compara( parsDEJAR, vocablos.getActual()->getPalabra() ) )
    {
        // El CD es el objeto
        if ( ( vocablos.busca( orden.cd ) ) != parsUNSIGFAIL )
        {
          if ((objetos.buscaPerVoc( orden.cd ) ) != parsUNSIGFAIL )
          {
            // Lo llevas
            if ( objetos.getActual()->esLlevado()
             && !objetos.getActual()->estaPuesto() )
            {
              // Ahora lo deja
              objetos.getActual()->setLlevado( false );
              objetos.getActual()->setNumLoc( mapa.getNumLoc() );
              Scr::println( parsMENSAJEDEJAR );
              objetos.sumaPeso( objetos.getActual()->getPeso() * -1 );
            } else {
                Scr::println( parsNOLLEVASDEESOS );
            }
          } else {
              Scr::println( parsNOLLEVASDEESOS );
          }
        }
        else Scr::println( parsNOLLEVASDEESOS );
    }
    else
    // PONER
    if ( vocablos.compara( parsPONER, vocablos.getActual()->getPalabra() ) )
    {
        // El CD es el objeto
        if ( ( vocablos.busca( orden.cd ) ) != parsUNSIGFAIL )
        {
          if ( ( objetos.buscaPerVoc( orden.cd ) )!=parsUNSIGFAIL )
          {
            // Lo lleva en las manos?
            if ( objetos.getActual()->getTipo()==Objeto::Ponible )
            {
                if ( objetos.getActual()->esLlevado()
                 && !objetos.getActual()->estaPuesto() )
                {
                  // Ahora lo lleva puesto
                  objetos.getActual()->setPuesto();
                  Scr::println( parsMENSAJEPONER );
                } else {
                    Scr::println( parsNOLLEVASDEESOS );
                }
            } else {
               Scr::println( parsNOESPONIBLE );
            }
          } else {
              Scr::println( parsNOLLEVASDEESOS );
          }
        } else {
            Scr::println( parsNOLLEVASDEESOS );
        }
    }
    else
    // QUITAR
    if ( vocablos.compara( parsQUITAR, vocablos.getActual()->getPalabra() ) )
    {
        // El CD es el objeto
        if ( ( vocablos.busca( orden.cd ) ) != parsUNSIGFAIL)
        {
          if ( ( objetos.buscaPerVoc( orden.cd ) ) != parsUNSIGFAIL )
          {
            // Lo llevas puesto
            if ( objetos.getActual()->esLlevado()
             && objetos.getActual()->estaPuesto() )
            {
              // Ahora lo deja
              objetos.getActual()->setPuesto( false );
              objetos.getActual()->setNumLoc( mapa.getNumLoc() );
              Scr::println( parsMENSAJEQUITAR );
            }
            else {
                Scr::println( parsNOLLEVASDEESOSP );
            }
          } else {
              Scr::println( parsNOLLEVASDEESOSP );
          }
        }
        else Scr::println( parsNOLLEVASDEESOSP );
    }
    else {
        // No se entiende nada
        std::string aux = parsMSGSYSNOSE;
        Scr::println( aux + vocablos.getActual()->getPalabra() );
    }
}

void Parser::hazDesc(unsigned int loc)
{
    if ( loc == parsUNSIGFAIL ) {
        loc = getNumLoc();
    }

    mapa.describe(loc);
    hazProc1();
}

void Parser::hazAccion(std::string &x)
{
    unsigned int enc;
    int devPars;

    StringTokenizer::trim( x );

    if ( x.length() != 0 )
    {
        ++movidas;

        devPars = analiza( x );
        enc = vocablos.busca( orden.verbo );

        // Ejecutar la posible accion segun el contenido de la orden
        if ( enc != parsUNSIGFAIL
          && ( devPars != parsUNSIGFAIL
            || devPars != parsanalizaPUNTUACION ) )
        {
            switch ( vocablos.getActual()->getTipo() ) {
                case parsDIRECCION:
                    if ( !hazDir() ) {
                        Scr::println( parsMSGDIRNO );
                    }
                    break;

                case parsCTRL:
                    hazCtrl();
                    break;

                case parsACCION:
                    hazResp();
                    break;

                default:
                    Scr::println( parsMSGNOPUEDES );
            }

            hazProc1();
        } else {
            if ( devPars != parsanalizaPUNTUACION ) {
               Scr::println( parsMSGNOPUEDES );
            }
        }

        if ( !esFinalJuego() ) {
            Scr::println();
            Scr::println( parsMENSAJITOPREPROMPT[ std::rand() % parsMAXMENSAJITOS ] );
        }
    } else {
        hazDesc();
    }
}

void Parser::setEntrada(std::string &x)
{
    if ( x.empty() ) {
        Scr::println();
        Scr::input( x ); // Pedir texto por consola
        Scr::println();

        StringTokenizer::trim( x );
        StringTokenizer::mays( x );
    } else {
        Scr::println();
    }
}

// Analizar la entrada del jugador para descubrir los vocablos
// registrados en el vocabulario como movimiento o como respuesta
int Parser::analiza(std::string &x)
{
    // Usa el objeto vocablos para analizar la estructura de la frase,
    // y la vuelca en sentencia_jug, de tipo Tsentencia.
    int dev = parsanalizaNORMAL;

    Sentencia actual;
    StringTokenizer str( x );
    std::string tok;
    unsigned int index = 0;
    bool final = false;

    // Inic Actual
    actual.cd    = parsUNSIGFAIL;
    actual.verbo = actual.adv = parsUNSIGFAIL;
    actual.leidoHasta = 0;

    // Coger las palabras hasta el final de la frase
    while ( !str.eol()
         && !final )
    {
        tok = str.getNextToken();
        StringTokenizer::trim( tok );

        if ( !( final = StringTokenizer::esPuntuacion( tok[ 0 ] ) ) )
        {
          actual.codVocablos[ index++ ] = vocablos.busca( tok );

          if ( actual.codVocablos[ index -1 ] != parsUNSIGFAIL ) {

                if ( actual.verbo == parsUNSIGFAIL
                  && vocablos.getActual()->getTipo() <= parsVERBO )
                {
                    actual.verbo      = actual.codVocablos[ index -1 ];
                    actual.leidoHasta = index;
                }
                else
                if ( actual.cd == parsUNSIGFAIL
                  && vocablos.getActual()->getTipo() == parsNOMBRE )
                {
                    actual.cd = actual.codVocablos[ index -1 ];
                    actual.leidoHasta = index;
                }
                else
                if ( vocablos.getActual()->getTipo() == parsADV )
                {
                    actual.adv   = actual.codVocablos[ index -1 ];
                    actual.leidoHasta = index;
                }
          }
        } else {
            dev = parsanalizaPUNTUACION;
            // Borra lo que ya se ha tratado.
            x.erase( x.begin(), x.begin() + str.getPos() );
        }

    }

    orden = actual;
    dev = ( orden.leidoHasta == 0 ? parsUNSIGFAIL : dev );
    if ( dev != parsanalizaPUNTUACION ) {
        x.clear();
    }

    return dev;
}

////////////////////////////// Clase Vocablos /////////////////////////
bool Vocablos::compara(const std::string &consta, const std::string &voc)
{
    bool dev = ( consta == voc );

    // Busca syn de voc que puedan coincidir con consta
    // Voc es tb el vocablo actual en el objeto vocablos
    if ( !dev
      && getActual()->getNumId() != parsUNSIGFAIL
      && getActual()->getSyn() != parsUNSIGFAIL )
    {

        // Buscar por el enlace de syn
        unsigned int actual = getActual()->getNumId();

        // hasta que volvamos a la que partimos
        do {
            if ( consta == getActual()->getPalabra() ) {
                dev = true;
                break;
            }

            busca( getActual()->getSyn() );

        } while ( actual != getActual()->getNumId() );
    }

    return dev;
}

unsigned int Vocablos::busca(const std::string &x)
{
    unsigned int toret = parsUNSIGFAIL;

    ve( inic() );
    while ( !esFin() )
    {
        if ( getActual()->getPalabra() == x )
        {
            toret = getActual()->getNumId();
            break;
        }

        sig();
    }

    return toret;
}

unsigned int Vocablos::busca(unsigned int x)
{
    unsigned int toret = parsUNSIGFAIL;

    ve( inic() );
    while ( !esFin() )

    {
        if ( getActual()->getNumId() == x )
        {
            toret = getActual()->getNumId();
            break;
        }

        sig();

    }

    return toret;
}

////////////////////////////////////// Clase Objetos    ///////////////////

Objeto::Objeto(unsigned int id, unsigned int codv,
               const std::string &d,
               bool esLlevado, bool esVisible, bool estaPuesto,
               unsigned int loc,
               unsigned int w, TipoObjeto to) :

    llevado(esLlevado), puesto(estaPuesto), numId(id),
    tipoObjeto(to), peso(w), codVoc(codv),
    numLoc(loc), desc(d), visible(esVisible), examinado(false)
{
}

bool Objeto::setNumLoc(unsigned int loc)
{
    bool toret = ( !esLlevado() && !estaPuesto() );

    if ( toret ) {
        numLoc = loc;
    }

    return toret;
}

bool Objeto::setLlevado(bool x)
{
    bool toret = false;

    if ( !x
      && esLlevado() )
    {
        toret = true;
        llevado = false;
        numLoc = parsUNSIGFAIL;
    }
    else
    if ( x
      && !esLlevado() )
    {
        toret = true;
        llevado = true;
        numLoc = parsUNSIGFAIL;
    }

    return toret;
}



bool Objeto::setPuesto(bool x)
{
    bool toret = false;

    if ( !x ) {
        if ( estaPuesto()
         &&  esLlevado() )
        {
            toret = true;
            puesto = false;
            numLoc = parsUNSIGFAIL;
        }
    }
    else
    if ( !estaPuesto() ) {
        toret = true;
        puesto = true;
        numLoc = parsUNSIGFAIL;
    }

    return toret;
}

///////////////////////////////// Clase Objetos ////////////////////////////

void Objetos::carga(const Objeto &o)
{
    ve( fin() );
    mas( o );

    if ( o.esLlevado() ) {
        pesoLlevados += o.getPeso();
    }

    return;
}

bool Objetos::busca(unsigned int numObj)
{
    ve( inic() );

    while( getActual()->getNumId() != numObj
        && !esFin() )
    {
        sig();
    }

    if( !esFin() )
            return ( getActual()->getNumId() == numObj );
    else    return false;
}

unsigned int Objetos::buscaPerVoc(unsigned int voc)
{
    ve( inic() );
    while ( !esFin() )
    {
        if ( getActual() != NULL
         &&  getActual()->getCodVoc() == voc )
        {
            break;
        }

        sig();
    }

    return ( ( !esFin() )? getActual()->getCodVoc() : parsUNSIGFAIL);
}



unsigned int Objetos::buscaSigPerLoc(unsigned int loc)
{
    unsigned int toret = parsUNSIGFAIL;

    while ( !esFin()
        &&  getActual()->getNumLoc() != loc )
    {
        sig();
    }


    if ( !esFin() ) {
          toret = getActual()->getNumId();
    }

    return toret;
}

//------------------------------------------------------------- Mensajes
Mensaje Mensajes::FAIL( "ERROR","Mensaje no encontrado.");

Mensaje * Mensajes::busca(const std::string &x)
{
	Mensaje * toret = &FAIL;

	ve( inic() );

	while( !esFin() ) {
	if ( getActual()->getNombre() == x )
		toret = getActual();

		sig();
	}

	return toret;
}

//------------------------------------------------------------ Variables
Var Variables::FAIL( "FAIL", -1 );

Var &Variables::busca(const std::string &x)
{
	Var * toret = &FAIL;
    ve( inic() );

    while( !esFin() ) {
		if ( getActual()->getNombre() == x ) {
			toret = getActual();
			break;
		}

        sig();
    }

    return *toret;
}

// ------------------------------------------------------ StringTokenizer
const std::string StringTokenizer::Delimitadores = "{}[]\"' \t\n(),.;:|&/*+-=<>";

std::string StringTokenizer::normaliza(const std::string &s)
{
    std::string lema = s.substr( 1 );
    std::string inicialLema = s.substr( 0, 1 );

    mins( lema );
    mays( inicialLema );
    return inicialLema + lema;
}

std::string &StringTokenizer::mays(std::string &s)
{
    std::string::iterator it = s.begin();

    while( it != s.end() ) {
        *it = std::toupper( *it );
        ++it;
    }

    return s;
}

std::string &StringTokenizer::mins(std::string &s)
{
    std::string::iterator it = s.begin();

    while( it != s.end() ) {
        *it = std::tolower( *it );
        ++it;
    }

    return s;
}

std::string &StringTokenizer::trim(std::string &x)
{
    static const std::string Sobrantes = " \n\t";

    // elimina los espacios sobrantes
    // la cadena puede quedar vacia

    if ( !x.empty() )
    {
        // Quitar los espacios del principio
        std::string::iterator ini = x.begin();

        while( Sobrantes.find( *ini ) != std::string::npos
            && ini != x.end() )
        {
            ++ini;
        }

        if ( ini >= x.begin() ) {
            x.erase( x.begin(), ini );
        }

        // Quitar los espacios del final
        std::string::iterator fin = x.end();
        --fin;

        while ( Sobrantes.find( *fin ) != std::string::npos
             && fin > x.begin() )
        {
            --fin;
        }

        ++fin;

        if ( fin < x.end() ) {
            x.erase( fin, x.end() );
        }
    }

    return x;
}

bool StringTokenizer::esPuntuacion(char c)
{
    std::string aux;
    aux = '_';
    aux += c;
    aux += '_';

    return ( parsPUNTUACION.find( aux ) != std::string::npos );
}

std::string StringTokenizer::getNextToken()
{
    token = "";

    // Llegar a la sig palabra
    while( !eol()
        && Delimitadores.find( buffer[ index ] ) != std::string::npos )
    {
        ++index;
    }

    // Tomar la palabra
    while( !eol()
        && Delimitadores.find( buffer[ index ] ) == std::string::npos )
    {
        token.push_back( buffer[ index ] );
        ++index;
    }

    return token;
}
