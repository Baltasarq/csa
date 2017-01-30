#ifndef __DEFS
#define __DEFS

// defs.hpp
// Definiciones
////////////////////////////////////////////////////////////////////////

// Mensajes
#define parsNUMIDMENSAJES           5

// Variables
#define parsNUMIDVBLES              7

// MAPA
#define parsNUMIDMAPA             10
#define parsMAXCONEXIONESLOC          20


// VOCABLOS
#define parsNUMIDVOCABLOS         20
#define parsMAXMENSAJITOS         10
#define parsMAXVOCABLOSSENTENCIA      95
#define parsMAXLETRASVOCABLOS         50

// Tipos de palabras

  // Verbos
  #define parsDIRECCION           20
  #define parsACCION              21
  #define parsCTRL            22
  #define parsVERBO           23        // Limite de verbos
                                        // Por debajo, todo acciones

  // Otros
  #define parsNOMBRE              23
  #define parsATRIBUTO            24
  #define parsART             25
  #define parsADV             26
  #define parsPREP            27
  #define parsVALETODO           100


// Pantalla
#define parsNUMIDPANT             80
#define parsMAXLINS           22
#define parsMAXCOLS           80

// Objetos
#define parsNUMIDOBJ              30
#define parsOBJSI              1
#define parsOBJNO              0

// Otros
#define OSMAXLIN             256
#define MAXJUGADOR            50
#define parsUNSIGFAIL             65535
#define parsanalizaNORMAL          0
#define parsanalizaPUNTUACION          1

// Debugging
    //#define _RT_debug
    //#define _debug
    //#define _pars_debug
    //#define _voc_debug
    //#define _juego_debug
    //#define _mapa_debug

#endif
