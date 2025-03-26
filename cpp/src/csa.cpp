// csa.cpp
// Bucle principal de la aventura conversacional
// Interfaz con el usuario
// baltasarq@gmail.com

#include "parser.h"
#include "juego.h"
#include "scrutil.h"

#include <cstdio>
#include <string>
#include <sstream>
#include <utility>

const bool NoPrompt = false;
const bool Prompt   = true;
const bool Cr       = true;
const bool noCr     = false;
const unsigned int MaxInputToRead = 1024;

void putLine(const std::string &str, bool cr = true)
{
    static const char * FmtNoCr = "%s";
    static const char * FmtCr = "%s\n";
    const char * fmt = cr ? FmtCr : FmtNoCr;

    std::printf( fmt, str.c_str() );
}

void getLine(std::string &x, bool prompt)
{
    static char buffer[ MaxInputToRead ];

    if ( prompt ) {
        ScrUtil::setColors( ScrUtil::Yellow, ScrUtil::Blue );
        putLine( parsPROMPT, false );
    }

    std::fgets( buffer, MaxInputToRead, stdin );
    x = buffer;

    ScrUtil::setColors( ScrUtil::White, ScrUtil::Blue );
    std::fflush( stdin );
    putLine( "", true );
}

//---------------------------------------------------------------------- Main
int main()
{
    std::string entrada;
    Juego juego( "jugador", 2 );

    ScrUtil::setColors( ScrUtil::White, ScrUtil::Blue );
    ScrUtil::clear();

    putLine( aventPRESYNOMBRE );
    getLine( entrada, NoPrompt );

    do {
        juego.getParser()->hazAccion( entrada );

        if ( !juego.getParser()->esFinalJuego() ) {
            juego.getParser()->setEntrada( entrada );
		}
    } while ( !juego.getParser()->esFinalJuego() );

    // Mostrar puntaje y salir
    putLine( "" );
    juego.getParser()->muestraPuntuacion();
    putLine( "" );
    getLine( entrada, NoPrompt );
    ScrUtil::setColors( ScrUtil::White, ScrUtil::Black );
    ScrUtil::clear();

    return 0;
}
