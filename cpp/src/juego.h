// Juego.hpp
// Cabecera de la parte jugable
////////////////////////////////////////////////////////////////////////

#include <string>

#include "defs.h"
#include "parser.h"

class ParserJuego : public Parser {
public:
    ParserJuego(const std::string &jugador, unsigned int x= 60000)
        : Parser( jugador, x )
        {}

    void hazResp();
    void hazProc1();
};

class Juego {
public:
    Juego(const std::string &nombreJugador, unsigned int limiteDePeso);

    void cargaPantallas();
    void cargaVocablos();
    void cargaObjetos();
    void cargaVbles();
    void cargaMensajes();

    Parser * getParser()
        { return parser; }
    const Parser * getParser() const
        { return parser; }
protected:
    Parser *parser;
    unsigned int limiteDePeso;
};

